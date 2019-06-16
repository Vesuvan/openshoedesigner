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

#include <GL/gl.h>
#include <cmath>
#include <stdexcept>

KernelDensityEstimator::KernelDensityEstimator()
{
	cyclic = false;
	cyclelength = 0.0;
	count = 0;
	weightsum = 0.0;
}

void KernelDensityEstimator::XLinspace(double t0, double t1, size_t N)
{
	x.assign(N, 0);
	for(size_t n = 0; n < N; ++n)
		x[n] = t0 + (double) n / (double) (N - 1) * (t1 - t0);
	YInit();
}

void KernelDensityEstimator::XSetCyclic(double cyclelength)
{
	cyclic = true;
	this->cyclelength = cyclelength;
}

void KernelDensityEstimator::XSetLinear(void)
{
	cyclic = false;
	cyclelength = 0.0;
}

void KernelDensityEstimator::YInit(double value)
{
	y.assign(x.size(), value);
	weightsum = 0.0;
	count = 0;
}

void KernelDensityEstimator::Insert(double pos, kerneltype kernel, double sigma,
		double weight)
{
	const size_t N = x.size();
	const double x0 = x[0];
	const double x1 = x[x.size() - 1];

	count++;
	weightsum += weight;

	double px = 0.0;
	double p = pos;
	if(cyclic){
		if(x1 > x0){
			while(p > x1)
				p -= cyclelength;
			while(p < x0)
				p += cyclelength;
		}else{
			while(p > x0)
				p -= cyclelength;
			while(p < x1)
				p += cyclelength;
		}
		if(p > (x0 + cyclelength / 2.0)) p = p - cyclelength;
		px = p + cyclelength / 2.0;
	}
	for(size_t n = 0; n < N; ++n){
		double v;
		if(cyclic){
			v = x[n] - (p + ((x[n] >= px)? cyclelength : 0));
		}else{
			v = x[n] - p;
		}

		switch(kernel){
		case EpanechnikovKernel:
			y[n] += EpanechnikovFunction(v / sigma) / sigma * weight;
			break;
		case CosineKernel:
			y[n] += CosineFunction(v / sigma) / sigma * weight;
			break;
		case TricubeKernel:
			y[n] += TricubeFunction(v / sigma) / sigma * weight;
			break;
		case QuarticKernel:
			y[n] += QuarticFunction(v / sigma) / sigma * weight;
			break;
		case TriweightKernel:
			y[n] += TriweightFunction(v / sigma) / sigma * weight;
			break;
		case TriangularKernel:
			y[n] += TriangularFunction(v / sigma) / sigma * weight;
			break;
		case GaussianKernel:
			y[n] += GaussianFunction(v / sigma) / sigma * weight;
			break;
		case UniformKernel:
			y[n] += UniformFunction(v / sigma) / sigma * weight;
			break;
		case LogisticKernel:
			y[n] += LogisticFunction(v / sigma) / sigma * weight;
			break;
		case SigmoidKernel:
			y[n] += SigmoidFunction(v / sigma) / sigma * weight;
			break;
		case SilvermanKernel:
			y[n] += SilvermanFunction(v / sigma) / sigma * weight;
			break;
		case PicardKernel:
			y[n] += PicardFunction(v / sigma) / sigma * weight;
			break;
		case CauchyKernel:
			y[n] += CauchyFunction(v / sigma) / sigma * weight;
			break;
		}
	}
}

void KernelDensityEstimator::Attenuate(double pos, kerneltype kernel,
		double sigma, double weight)
{
	const size_t N = x.size();
	const double x0 = x[0];
	const double x1 = x[x.size() - 1];
	double px = 0.0;
	double p = pos;
	if(cyclic){
		if(x1 > x0){
			while(p > x1)
				p -= cyclelength;
			while(p < x0)
				p += cyclelength;
		}else{
			while(p > x0)
				p -= cyclelength;
			while(p < x1)
				p += cyclelength;
		}
		if(p > (x0 + cyclelength / 2.0)) p = p - cyclelength;
		px = p + cyclelength / 2.0;
	}
	for(size_t n = 0; n < N; ++n){
		double v;
		if(cyclic){
			v = x[n] - (p + ((x[n] >= px)? cyclelength : 0));
		}else{
			v = x[n] - p;
		}

		switch(kernel){
		case EpanechnikovKernel:
			y[n] *= 1.0
					- (EpanechnikovFunction(v / sigma) / EpanechnikovFunction(0)
							* weight);
			break;
		case CosineKernel:
			y[n] *= 1.0
					- (CosineFunction(v / sigma) / CosineFunction(0) * weight);
			break;
		case TricubeKernel:
			y[n] *=
					1.0
							- (TricubeFunction(v / sigma) / TricubeFunction(0)
									* weight);
			break;
		case QuarticKernel:
			y[n] *=
					1.0
							- (QuarticFunction(v / sigma) / QuarticFunction(0)
									* weight);
			break;
		case TriweightKernel:
			y[n] *= 1.0
					- (TriweightFunction(v / sigma) / TriweightFunction(0)
							* weight);
			break;
		case TriangularKernel:
			y[n] *= 1.0
					- (TriangularFunction(v / sigma) / TriangularFunction(0)
							* weight);
			break;
		case GaussianKernel:
			y[n] *= 1.0
					- (GaussianFunction(v / sigma) / GaussianFunction(0)
							* weight);
			break;
		case UniformKernel:
			y[n] *=
					1.0
							- (UniformFunction(v / sigma) / UniformFunction(0)
									* weight);
			break;
		case LogisticKernel:
			y[n] *= 1.0
					- (LogisticFunction(v / sigma) / LogisticFunction(0)
							* weight);
			break;
		case SigmoidKernel:
			y[n] *=
					1.0
							- (SigmoidFunction(v / sigma) / SigmoidFunction(0)
									* weight);
			break;
		case SilvermanKernel:
			y[n] *= 1.0
					- (SilvermanFunction(v / sigma) / SilvermanFunction(0)
							* weight);
			break;
		case PicardKernel:
			y[n] *= 1.0
					- (PicardFunction(v / sigma) / PicardFunction(0) * weight);
			break;
		case CauchyKernel:
			y[n] *= 1.0
					- (CauchyFunction(v / sigma) / CauchyFunction(0) * weight);
			break;
		}
	}
}

void KernelDensityEstimator::Normalize(void)
{
	const double A = Area();
	for(size_t n = 0; n < y.size(); ++n)
		y[n] /= A;
	count = 0;
	weightsum = 0;
}

void KernelDensityEstimator::NormalizeByWeightSum(void)
{
	if(count == 0) throw(std::logic_error(
	__FILE__":Normalize - Function called, before kernel were inserted."));
	for(size_t n = 0; n < y.size(); ++n)
		y[n] /= weightsum;
	count = 0;
	weightsum = 0;
}

size_t KernelDensityEstimator::Size(void) const
{
	return y.size();
}

double& KernelDensityEstimator::operator [](size_t index)
{
	return y[index];
}

const double& KernelDensityEstimator::operator [](size_t index) const
{
	return y[index];
}

KernelDensityEstimator& KernelDensityEstimator::operator *=(const double v)
{
	for(size_t n = 0; n < y.size(); ++n)
		y[n] *= v;
	return (*this);
}

KernelDensityEstimator& KernelDensityEstimator::operator /=(const double v)
{
	for(size_t n = 0; n < y.size(); ++n)
		y[n] /= v;
	return (*this);
}

double KernelDensityEstimator::Area(void) const
{
	const size_t N = x.size();
	double area = 0.0;
	for(size_t n = 1; n < N; ++n){
		area += (y[n] + y[n - 1]) * (x[n] - x[n - 1]) / 2.0;
	}
	if(cyclic){
		area += (y[0] + y[N - 1]) * (x[0] + cyclelength - x[N - 1]) / 2.0;
	}
	return area;
}

size_t KernelDensityEstimator::FindPeaks(const double minvalue)
{
	resultpos.clear();
	resultvalue.clear();
	size_t N = Size();
	// Prevent errors in cases, where the first and last x match up.
	if(cyclic && fabs(x[N - 1] - x[0] - cyclelength) < 1e-6) N--;
	for(size_t n = 0; n < N; ++n){
		const double x0 = x[n];
		const double x1 = (
				(n + 1 >= N)? (x[(n + 1) % N] + cyclelength) : x[n + 1]);
		const double x2 = (
				(n + 2 >= N)? (x[(n + 2) % N] + cyclelength) : x[n + 2]);
		const double y0 = y[n];
		const double y1 = y[(n + 1) % N];
		const double y2 = y[(n + 2) % N];
		if(y1 <= minvalue) continue;
		if(y0 > y1 || y2 > y1) continue;

		// Interpolate peaks with 2nd order polynoms to find the position and value of the maximum.
		const double dx1 = x1 - x0;
		const double dx2 = x2 - x0;
		const double den1 = 2 * (dx1 * y2 - dx2 * y1 + (dx2 - dx1) * y0);
		const double den2 = -2 * den1 * dx1 * dx2 * (dx2 - dx1);
		if(den1 == 0.0 || den2 == 0.0) continue;
		const double pos = (dx1 * (2 * x0 + dx1) * y2
				- dx2 * (dx2 + 2 * x0) * y1
				+ (dx2 - dx1) * (2 * x0 + dx2 + dx1) * y0) / den1;
		const double value = (((dx2 - dx1) * (dx2 - dx1) * (dx2 - dx1)
				* (dx2 - dx1) * y0 * y0)
				- (2 * dx2 * dx2 * (dx2 - dx1) * (dx2 - dx1) * y0 * y1)
				+ (dx2 * dx2 * dx2 * dx2 * y1 * y1)
				+ (dx1 * dx1 * dx1 * dx1 * y2 * y2)
				- (2 * dx1 * dx1
						* (dx1 * dx1 * y0 - 2 * dx1 * dx2 * y0 + dx2 * dx2 * y0
								+ dx2 * dx2 * y1) * y2)) / den2;

		std::vector <double>::iterator ptpos = resultpos.begin();
		std::vector <double>::iterator ptval = resultvalue.begin();
		while(ptpos != resultpos.end() && *ptval > value){
			++ptpos;
			++ptval;
		}
		if(ptpos == resultpos.end()){
			resultpos.push_back(pos);
			resultvalue.push_back(value);

		}else{
			resultpos.insert(ptpos, pos);
			resultvalue.insert(ptval, value);
		}
	}
	return resultpos.size();
}

size_t KernelDensityEstimator::FindValleys(const double minvalue)
{
	resultpos.clear();
	resultvalue.clear();
	size_t N = Size();
	// Prevent errors in cases, where the first and last x match up.
	if(cyclic && fabs(x[N - 1] - x[0] - cyclelength) < 1e-6) N--;
	for(size_t n = 0; n < N; ++n){
		const double x0 = x[n];
		const double x1 = (
				(n + 1 >= N)? (x[(n + 1) % N] + cyclelength) : x[n + 1]);
		const double x2 = (
				(n + 2 >= N)? (x[(n + 2) % N] + cyclelength) : x[n + 2]);
		const double y0 = y[n];
		const double y1 = y[(n + 1) % N];
		const double y2 = y[(n + 2) % N];
		if(y1 <= minvalue) continue;
		if(y0 < y1 || y2 < y1) continue;

		// Interpolate peaks with 2nd order polynoms to find the position and value of the maximum.
		const double dx1 = x1 - x0;
		const double dx2 = x2 - x0;
		const double den1 = 2 * (dx1 * y2 - dx2 * y1 + (dx2 - dx1) * y0);
		const double den2 = -2 * den1 * dx1 * dx2 * (dx2 - dx1);
		if(den1 == 0.0 || den2 == 0.0) continue;
		const double pos = (dx1 * (2 * x0 + dx1) * y2
				- dx2 * (dx2 + 2 * x0) * y1
				+ (dx2 - dx1) * (2 * x0 + dx2 + dx1) * y0) / den1;
		const double value = (((dx2 - dx1) * (dx2 - dx1) * (dx2 - dx1)
				* (dx2 - dx1) * y0 * y0)
				- (2 * dx2 * dx2 * (dx2 - dx1) * (dx2 - dx1) * y0 * y1)
				+ (dx2 * dx2 * dx2 * dx2 * y1 * y1)
				+ (dx1 * dx1 * dx1 * dx1 * y2 * y2)
				- (2 * dx1 * dx1
						* (dx1 * dx1 * y0 - 2 * dx1 * dx2 * y0 + dx2 * dx2 * y0
								+ dx2 * dx2 * y1) * y2)) / den2;

		std::vector <double>::iterator ptpos = resultpos.begin();
		std::vector <double>::iterator ptval = resultvalue.begin();

		while(ptpos != resultpos.end() && *ptval < value){
			++ptpos;
			++ptval;
		}
		if(ptpos == resultpos.end()){
			resultpos.push_back(pos);
			resultvalue.push_back(value);

		}else{
			resultpos.insert(ptpos, pos);
			resultvalue.insert(ptval, value);
		}
	}
	return resultpos.size();
}

size_t KernelDensityEstimator::Count(void) const
{
	return resultpos.size();
}

double KernelDensityEstimator::Pos(size_t index) const
{
	return resultpos[index];
}

double KernelDensityEstimator::Value(size_t index) const
{
	return resultvalue[index];
}

void KernelDensityEstimator::Paint(void) const
{
	glBegin(GL_LINE_STRIP);
	if(cyclic){
		for(size_t n = 0; n < x.size(); ++n){
			double co = cos(x[n]);
			double si = sin(x[n]);
			double d = y[n];
			glVertex2d(co * d, si * d);
		}
	}else{
		for(size_t n = 0; n < x.size(); ++n)
			glVertex2d(x[n], y[n]);
	}
	glEnd();
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
