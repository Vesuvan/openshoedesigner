///////////////////////////////////////////////////////////////////////////////
// Name               : CMAESOptimizer.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 05.10.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////

#include "CMAESOptimizer.h"

//#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdexcept>

CMAESOptimizer::CMAESOptimizer()
{
	lambda = 6;
	sigmaInit = 0.3;

	errorLimit = 1e-3;
	evalLimit = 1000;

	reevalBest = false;
	keepCovarianceMatrix = true;

	evaluationCount = 0;
	initialized = false;
	state = 0;
	index = 0;

	sigma = 0.0;
	mu = 0;
	mueff = 0.0;

	cc = 0.0;
	cs = 0.0;
	c1 = 0.0;
	cmu = 0.0;
	damps = 0.0;

	chiN = 0;
	eigeneval = 0;
}

CMAESOptimizer::~CMAESOptimizer()
{
}

void CMAESOptimizer::Start(void)
{
	sigma = sigmaInit;
	mu = floor((double) lambda / 2.0);
	weights.resize(mu);
	double weightsum = 0.0;
	for(size_t n = 0; n < weights.size(); ++n){
		weights[n] = log((double) lambda / 2.0 + 0.5) - log(n + 1.0);
		weightsum += weights[n];
	}
	for(size_t n = 0; n < weights.size(); ++n)
		weights[n] /= weightsum;
	weightsum = 0.0;
	double weightsum2 = 0.0;
	for(size_t n = 0; n < weights.size(); ++n){
		weightsum += weights[n];
		weightsum2 += weights[n] * weights[n];
	}
	mueff = weightsum * weightsum / weightsum2;

	const size_t N = param.size();

	cc = (4.0 + mueff / (double) N)
			/ ((double) N + 4.0 + 2.0 * mueff / (double) N);
	cs = (mueff + 2.0) / ((double) N + mueff + 5.0);
	c1 = 2 / ((N + 1.3) * (N + 1.3) + mueff);
	cmu = fmin(1 - c1,
			2 * (mueff - 2 + 1 / mueff) / ((N + 2) * (N + 2) + mueff));
	damps = 1 + 2 * fmax(0, sqrt((mueff - 1) / (N + 1)) - 1) + cs;

	pc.assign(N, 0.0);
	ps.assign(N, 0.0);
	B.assign(N * N, 0.0);
	C.assign(N * N, 0.0);
	invsqrtC.assign(N * N, 0.0);
	for(size_t n = 0; n < N * N; n += (N + 1)){
		B[n] = 1.0;
		C[n] = 1.0;
		invsqrtC[n] = 1.0;
	}
	D.assign(N, 1.0);
	arx.resize(N * lambda);
	arfitness.resize(lambda);
	arindex.resize(lambda);
	artmp.resize(N * mu);
	xold.resize(N);
	temp.resize(N);
	eigeneval = 0;
	chiN = sqrt((double) N)
			* (1.0 - 1.0 / (4.0 * (double) N)
					+ 1.0 / (21.0 * (double) N * (double) N));

	evaluationCount = 0;
	state = 1;
	index = 0;
	initialized = true;
}

bool CMAESOptimizer::IsRunning(void)
{

	switch(state){
	case 0:
		throw(std::logic_error(
				"CMAESOptimizer::IsRunning - StartRun was not called."));

	case 1:
		{
			const size_t N = param.size();
			if(index == 0){
				// Calculate new sample points in arx:
				for(size_t n = 0; n < N; ++n)
					xold[n] = param[n];

				size_t c = 0;
				for(size_t m = 0; m < lambda; ++m){
					for(size_t n = 0; n < N; ++n)
						arx[c + n] = xold[n];

					for(size_t n = 0; n < N; ++n)
						temp[n] = D[n] * RandN();
					size_t d = 0;
					for(size_t q = 0; q < N; ++q){
						for(size_t n = 0; n < N; ++n){
							arx[c + n] += sigma * B[d] * temp[q];
							++d;
						}
					}
					c += N;
				}
			}
			if(index >= lambda) throw(std::logic_error(
					"CMAESOptimizer::IsRunning - State progression not working."));

			for(size_t n = 0; n < N; n++)
				param[n] = arx[index * N + n];

			state = 2;
			return true;
		}
	case 2:
		throw(std::logic_error(
				"CMAESOptimizer::IsRunning - SetError was not called."));

	case 3:
		break;

	default:
		throw(std::logic_error(
				"CMAESOptimizer::IsRunning - State machine reached invalid state."));
	}

	if(state == 3){
		const size_t N = param.size();

		// Sort result
		for(size_t n = 0; n < lambda; ++n)
			arindex[n] = n * N;
		bool flag = true;
		while(flag){
			flag = false;
			for(size_t m = 0; m < (lambda - 1); m++){
				if(arfitness[m] > arfitness[m + 1]){
					std::swap(arindex[m], arindex[m + 1]);
					std::swap(arfitness[m], arfitness[m + 1]);
					flag = true;
				}
			}
		}

		if(arfitness[0] <= errorLimit){
			for(size_t n = 0; n < N; ++n)
				param[n] = arx[arindex[0] + n];
			state = 10;

		}else{

			// Recombinate new best parameter
			for(size_t n = 0; n < N; ++n){
				param[n] = 0.0;
				for(size_t m = 0; m < mu; ++m){
					param[n] += arx[arindex[m] + n] * weights[m];
				}
			}

			// Update evolution paths
			temp.assign(N, 0.0);
			size_t c = 0;
			for(size_t m = 0; m < N; ++m){
				for(size_t n = 0; n < N; ++n){
					temp[n] += invsqrtC[c] * (param[m] - xold[m]);
					++c;
				}
			}
			for(size_t n = 0; n < N; ++n){
				ps[n] = (1 - cs) * ps[n]
						+ sqrt(cs * (2.0 - cs) * mueff) * temp[n] / sigma;
			}
			double hsig = 0.0;
			for(size_t n = 0; n < N; ++n)
				hsig += ps[n] * ps[n];
			hsig = sqrt(hsig);
			hsig /= sqrt(1 - pow((1.0 - cs), (2.0 * evaluationCount / lambda)));
			hsig /= chiN;
			if(hsig < (1.4 + 2.0 / ((double) N + 1.0))){
				hsig = 1.0;
			}else{
				hsig = 0.0;
			}
			for(size_t n = 0; n < N; ++n){
				pc[n] = (1 - cc) * pc[n]
						+ hsig * sqrt(cc * (2.0 - cc) * mueff)
								* (param[n] - xold[n]) / sigma;
			}

			// Adapt covariance matrix C
			c = 0;
			for(size_t m = 0; m < mu; ++m){
				for(size_t n = 0; n < N; ++n){
					artmp[c] = (arx[arindex[m] + n] - xold[n]) / sigma;
					++c;
				}
			}
			double corr = (1.0 - hsig) * cc * (2 - 0 - cc);
			c = 0;
			for(size_t m = 0; m < N; ++m){
				for(size_t n = 0; n < N; ++n){
//					C[c] = (1.0-c1-cmu)*C[c] + c1*(pc[n]*pc[m]+)
				}
			}

//		      C = (1-c1-cmu) * C ...                  % regard old matrix
//		           + c1 * (pc*pc' ...                 % plus rank one update
//		                   + (1-hsig) * cc*(2-cc) * C) ... % minor correction if hsig==0
//		           + cmu * artmp * diag(weights) * artmp'; % plus rank mu update

// Adapt step size sigma
//		     sigma = sigma * exp((cs/damps)*(norm(ps)/chiN - 1));

// Decomposition of C into B*diag(D.^2)*B' (diagonalization)
//		      if counteval - eigeneval > lambda/(c1+cmu)/N/10  % to achieve O(N^2)
//		          eigeneval = counteval;
//		          C = triu(C) + triu(C,1)'; % enforce symmetry
//		          [B,D] = eig(C);           % eigen decomposition, B==normalized eigenvectors
//		          D = sqrt(diag(D));        % D is a vector of standard deviations now
//		          invsqrtC = B * diag(D.^-1) * B';
//		      end

			double maxD = D[0];
			double minD = D[0];
			for(size_t n = 2; n < N; ++n){
				maxD = fmax(maxD, D[n]);
				minD = fmin(minD, D[n]);
			}
			if(maxD > 1e7 * minD) state = 10;
		}
	}
	if(state == 10){
		if(reevalBest){
			state = 11;
			return true;
		}
		state = 12;
		return false;
	}
	return false;
}

void CMAESOptimizer::SetError(double error)
{
	evaluationCount++;

	switch(state){
	case 2:
		arfitness[index] = error;
		index++;
		state = (index < lambda)? 1 : 3;
		break;

	case 10:
		break;

	case 11:
		state = 12;
		break;

	default:
		throw(std::logic_error(
				"CMAESOptimizer::SetError was called outside the main loop."));
	}

	if(evaluationCount >= evalLimit){
		if(state < 10) state = 10;
	}
}

void CMAESOptimizer::Stop(void)
{
	if(state < 10) state = 10;
}

size_t CMAESOptimizer::EvaluationsDone(void) const
{
	return evaluationCount;
}

double CMAESOptimizer::ResidualError(void) const
{
	return arfitness[0];
}

double CMAESOptimizer::RandN(void)
{
	double r = 0.0;
	for(size_t n = 0; n < 12; ++n)
		r += (double) rand();
	return (r / (double) RAND_MAX) - 6.0;
}
