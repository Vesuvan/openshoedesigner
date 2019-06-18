///////////////////////////////////////////////////////////////////////////////
// Name               : KernelDensityEstimator.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 05.06.2019
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

#include "KernelDensityEstimator.h"

#include <cmath>
#include <stdexcept>

KernelDensityEstimator::KernelDensityEstimator()
{
	count = 0;
	weightsum = 0.0;
}

void KernelDensityEstimator::YInit(double value)
{
	DependentVector::YInit(value);
	weightsum = 0.0;
	count = 0;
}

void KernelDensityEstimator::Insert(double pos, double weight, double sigma,
		kerneltype kernel)
{
	const size_t N = Size();
	const double x0 = X(0);
	const double x1 = X(N - 1);

	count++;
	weightsum += weight;

	double px = 0.0;
	double p = pos;
	if(IsCyclic()){
		if(x1 > x0){
			while(p > x1)
				p -= CycleLength();
			while(p < x0)
				p += CycleLength();
		}else{
			while(p > x0)
				p -= CycleLength();
			while(p < x1)
				p += CycleLength();
		}
		if(p > (x0 + CycleLength() / 2.0)) p = p - CycleLength();
		px = p + CycleLength() / 2.0;
	}
	for(size_t n = 0; n < N; ++n){
		double v;
		if(IsCyclic()){
			v = X(n) - (p + ((X(n) >= px)? CycleLength() : 0));
		}else{
			v = X(n) - p;
		}

		switch(kernel){
		case EpanechnikovKernel:
			Y(n) += EpanechnikovFunction(v / sigma) / sigma * weight;
			break;
		case CosineKernel:
			Y(n) += CosineFunction(v / sigma) / sigma * weight;
			break;
		case TricubeKernel:
			Y(n) += TricubeFunction(v / sigma) / sigma * weight;
			break;
		case QuarticKernel:
			Y(n) += QuarticFunction(v / sigma) / sigma * weight;
			break;
		case TriweightKernel:
			Y(n) += TriweightFunction(v / sigma) / sigma * weight;
			break;
		case TriangularKernel:
			Y(n) += TriangularFunction(v / sigma) / sigma * weight;
			break;
		case GaussianKernel:
			Y(n) += GaussianFunction(v / sigma) / sigma * weight;
			break;
		case UniformKernel:
			Y(n) += UniformFunction(v / sigma) / sigma * weight;
			break;
		case LogisticKernel:
			Y(n) += LogisticFunction(v / sigma) / sigma * weight;
			break;
		case SigmoidKernel:
			Y(n) += SigmoidFunction(v / sigma) / sigma * weight;
			break;
		case SilvermanKernel:
			Y(n) += SilvermanFunction(v / sigma) / sigma * weight;
			break;
		case PicardKernel:
			Y(n) += PicardFunction(v / sigma) / sigma * weight;
			break;
		case CauchyKernel:
			Y(n) += CauchyFunction(v / sigma) / sigma * weight;
			break;
		}
	}
}

void KernelDensityEstimator::Attenuate(double pos, double weight, double sigma,
		kerneltype kernel)
{
	const size_t N = Size();
	const double x0 = X(0);
	const double x1 = X(N - 1);
	double px = 0.0;
	double p = pos;
	if(IsCyclic()){
		if(x1 > x0){
			while(p > x1)
				p -= CycleLength();
			while(p < x0)
				p += CycleLength();
		}else{
			while(p > x0)
				p -= CycleLength();
			while(p < x1)
				p += CycleLength();
		}
		if(p > (x0 + CycleLength() / 2.0)) p = p - CycleLength();
		px = p + CycleLength() / 2.0;
	}
	for(size_t n = 0; n < N; ++n){
		double v;
		if(IsCyclic()){
			v = X(n) - (p + ((X(n) >= px)? CycleLength() : 0));
		}else{
			v = X(n) - p;
		}

		switch(kernel){
		case EpanechnikovKernel:
			Y(n) *= 1.0
					- (EpanechnikovFunction(v / sigma) / EpanechnikovFunction(0)
							* weight);
			break;
		case CosineKernel:
			Y(n) *= 1.0
					- (CosineFunction(v / sigma) / CosineFunction(0) * weight);
			break;
		case TricubeKernel:
			Y(n) *=
					1.0
							- (TricubeFunction(v / sigma) / TricubeFunction(0)
									* weight);
			break;
		case QuarticKernel:
			Y(n) *=
					1.0
							- (QuarticFunction(v / sigma) / QuarticFunction(0)
									* weight);
			break;
		case TriweightKernel:
			Y(n) *= 1.0
					- (TriweightFunction(v / sigma) / TriweightFunction(0)
							* weight);
			break;
		case TriangularKernel:
			Y(n) *= 1.0
					- (TriangularFunction(v / sigma) / TriangularFunction(0)
							* weight);
			break;
		case GaussianKernel:
			Y(n) *= 1.0
					- (GaussianFunction(v / sigma) / GaussianFunction(0)
							* weight);
			break;
		case UniformKernel:
			Y(n) *=
					1.0
							- (UniformFunction(v / sigma) / UniformFunction(0)
									* weight);
			break;
		case LogisticKernel:
			Y(n) *= 1.0
					- (LogisticFunction(v / sigma) / LogisticFunction(0)
							* weight);
			break;
		case SigmoidKernel:
			Y(n) *=
					1.0
							- (SigmoidFunction(v / sigma) / SigmoidFunction(0)
									* weight);
			break;
		case SilvermanKernel:
			Y(n) *= 1.0
					- (SilvermanFunction(v / sigma) / SilvermanFunction(0)
							* weight);
			break;
		case PicardKernel:
			Y(n) *= 1.0
					- (PicardFunction(v / sigma) / PicardFunction(0) * weight);
			break;
		case CauchyKernel:
			Y(n) *= 1.0
					- (CauchyFunction(v / sigma) / CauchyFunction(0) * weight);
			break;
		}
	}
}

void KernelDensityEstimator::Normalize(void)
{
	operator/=(Area());
	count = 0;
	weightsum = 1.0;
}

void KernelDensityEstimator::NormalizeByWeightSum(void)
{
	if(count == 0) throw(std::logic_error(
	__FILE__":Normalize - Function called, before kernel were inserted."));
	operator/=(weightsum);
	count = 0;
	weightsum = 1.0;
}

double KernelDensityEstimator::EpanechnikovFunction(double x)
{
	if(x < -1.0 || x > 1.0) return 0.0;
	return (1.0 - x * x) * 0.75;
}

double KernelDensityEstimator::CosineFunction(double x)
{
	if(x < -1.0 || x > 1.0) return 0.0;
	return ((M_PI_4) * cos(M_PI_2 * x));
}

double KernelDensityEstimator::TricubeFunction(double x)
{
	if(x < -1.0 || x > 1.0) return 0.0;
	const double b = fabs(x);
	const double a = (1.0 - b * b * b);
	return (70.0 / 81.0 * a * a * a);
}

double KernelDensityEstimator::QuarticFunction(double x)
{
	if(x < -1.0 || x > 1.0) return 0.0;
	const double a = (1.0 - x * x);
	return (15.0 / 16.0 * a * a);
}

double KernelDensityEstimator::TriweightFunction(double x)
{
	if(x < -1.0 || x > 1.0) return 0.0;
	const double a = (1.0 - x * x);
	return (35.0 / 32.0 * a * a * a);
}

double KernelDensityEstimator::TriangularFunction(double x)
{
	if(x < -1.0 || x > 1.0) return 0.0;
	return (1 - fabs(x));
}

double KernelDensityEstimator::GaussianFunction(double x)
{
	return (1 / sqrt(2 * M_PI) * exp(-x * x / 2.0));
}

double KernelDensityEstimator::UniformFunction(double x)
{
	return (x >= -1 && x <= 1)? 0.5 : 0;
}

double KernelDensityEstimator::LogisticFunction(double x)
{
	const double b = exp(x);
	const double a = 1 + b;
	return (b / (a * a));
}

double KernelDensityEstimator::SigmoidFunction(double x)
{
	const double b = exp(x);
	return (M_2_PI * 1 / (b + 1 / b));
}

double KernelDensityEstimator::SilvermanFunction(double x)
{
	const double a = fabs(x) / M_SQRT2;
	return exp(-a) / 2.0 * sin(a + M_PI_4);
}

double KernelDensityEstimator::PicardFunction(double x)
{
	return exp(-fabs(x)) / 2.0;
}

double KernelDensityEstimator::CauchyFunction(double x)
{
	return 1.0 / (M_PI * (1.0 + x * x));
}
