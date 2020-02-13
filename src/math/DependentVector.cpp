///////////////////////////////////////////////////////////////////////////////
// Name               : DependentVector.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 17.06.2019
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

#include "DependentVector.h"

#include <GL/gl.h>
#include <stddef.h>
#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "MatlabFile.h"
#include "MatlabMatrix.h"

DependentVector::DependentVector()
{
	cyclic = false;
	cyclelength = 0.0;
	searchspeedup = 0;
}

void DependentVector::Clear(void)
{
	x.clear();
	y.clear();
}

void DependentVector::Resize(size_t N)
{
	x.resize(N);
	y.resize(N);
}

void DependentVector::PushBack(double x, double y)
{
	this->x.push_back(x);
	this->y.push_back(y);
}

size_t DependentVector::Size(void) const
{
	return x.size();
}

void DependentVector::XLinspace(double x0, double x1, size_t N)
{
	if(N == 0){
		N = x.size();
	}else{
		x.assign(N, 0);
	}
	y.resize(N, 0.0);
	for(size_t n = 0; n < N; ++n)
		x[n] = x0 + (double) n / (double) (N - 1) * (x1 - x0);
}

void DependentVector::XSetCyclic(double cyclelength)
{
	cyclic = true;
	this->cyclelength = cyclelength;
}

void DependentVector::XSetLinear(void)
{
	cyclic = false;
	cyclelength = 0.0;
}

bool DependentVector::IsCyclic(void) const
{
	return cyclic;
}

double DependentVector::CycleLength(void) const
{
	return cyclelength;
}

void DependentVector::YInit(double value)
{
	y.assign(x.size(), value);
}

void DependentVector::YLinspace(double y0, double y1)
{
	const size_t N = x.size();
	for(size_t n = 0; n < N; ++n)
		x[n] = y0 + (double) n / (double) (N - 1) * (y1 - y0);
}

double& DependentVector::X(size_t index)
{
	return x[index];
}

const double& DependentVector::X(size_t index) const
{
	return x[index];
}

double& DependentVector::Y(size_t index)
{
	return y[index];
}

const double& DependentVector::Y(size_t index) const
{
	return y[index];
}

double& DependentVector::operator [](size_t index)
{
	return y[index];
}

double DependentVector::operator [](size_t index) const
{
	return y[index];
}

double DependentVector::YatX(const double xval) const
{
	if(x.size() == 0) return 0.0;
	if(x.size() == 1) return y[0];
	if(searchspeedup > x.size()) searchspeedup = 0;
	if(x[searchspeedup] > xval) searchspeedup = 0;
	while((searchspeedup + 1) < x.size() && x[searchspeedup + 1] < xval)
		searchspeedup++;

	if(cyclic) throw(std::logic_error(
	__FILE__" - YatX : Cyclic lookup not yet implemented!"));

	const double s = (xval - x[searchspeedup])
			/ (x[searchspeedup + 1] - x[searchspeedup]);
	return (y[searchspeedup + 1] - y[searchspeedup]) * s + y[searchspeedup];
}

DependentVector& DependentVector::operator +=(const double val)
{
	for(size_t n = 0; n < y.size(); ++n)
		y[n] += val;
	return (*this);
}

DependentVector& DependentVector::operator -=(const double val)
{
	for(size_t n = 0; n < y.size(); ++n)
		y[n] -= val;
	return (*this);
}

DependentVector& DependentVector::operator *=(const double val)
{
	for(size_t n = 0; n < y.size(); ++n)
		y[n] *= val;
	return (*this);
}

DependentVector& DependentVector::operator /=(const double val)
{
	for(size_t n = 0; n < y.size(); ++n)
		y[n] /= val;
	return (*this);
}

void DependentVector::YLimit(double ymin, double ymax)
{
	const size_t N = x.size();
	for(size_t n = 0; n < N; ++n)
		y[n] = fmin(fmax(y[n], ymin), ymax);
}

double DependentVector::Area(void) const
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

void DependentVector::Sort(void)
{
	const size_t N = x.size();
	if(N <= 1) return;
	// Shortcut, maybe the x vector is simply ordered in reverse.
	if(x[0] > x[N - 1]) Reverse();
	bool flag = true;
	while(flag){
		flag = false;
		for(size_t n = 1; n < N; ++n){
			if(x[n - 1] > x[n]){
				flag = true;
				std::swap(x[n - 1], x[n]);
				std::swap(y[n - 1], y[n]);
			}
		}
		if(!flag) break;
		flag = false;
		for(size_t n = (N - 1); n > 0; --n){
			if(x[n - 1] > x[n]){
				flag = true;
				std::swap(x[n - 1], x[n]);
				std::swap(y[n - 1], y[n]);
			}
		}
	}
}

void DependentVector::Reverse(void)
{
	if(x.size() <= 1) return;
	std::reverse(x.begin(), x.end());
	std::reverse(y.begin(), y.end());
}

void DependentVector::Resample(size_t Nnew)
{
	//TODO Test all edge-cases: linear, cyclic, cyclic with overlapping ends
	if(Nnew < 2) return;
	size_t N = x.size();
	bool overlappingends = false;
	if(cyclic){
		if(x[N - 1] > x[0]){
			if(fabs(x[N - 1] - (x[0] + cyclelength)) < 1e-6){
				overlappingends = true;
			}else{
				// Let the ends overlap, while interpolating
				x.push_back(x[0] + cyclelength);
				y.push_back(y[0]);
				N++;
				Nnew++;
			}
		}else{
			if(fabs(x[N - 1] - (x[0] - cyclelength)) < 1e-6){
				overlappingends = true;
			}else{
				// Let the ends overlap, while interpolating
				x.push_back(x[0] - cyclelength);
				y.push_back(y[0]);
				N++;
				Nnew++;
			}
		}
	}
	std::vector <double> xnew(Nnew);
	std::vector <double> ynew(Nnew);
	// First and last point are fixed
	xnew[0] = x[0];
	ynew[0] = y[0];
	xnew[Nnew - 1] = x[N - 1];
	ynew[Nnew - 1] = y[N - 1];
	{
		// Linear x
		double xinterp = x[0];
		const double dxi = (x[N - 1] - x[0]) / (Nnew - 1);
		for(size_t n = 1; n < (Nnew - 1); ++n){
			xinterp += dxi;
			xnew[n] = xinterp;
		}
	}
	if(x[N - 1] > x[0]){
		// Interpolate y normally
		size_t p = 0;
		for(size_t n = 1; n < (Nnew - 1); ++n){
			while(x[p] < xnew[n])
				++p;
			ynew[n] = y[p - 1]
					+ (y[p] - y[p - 1]) / (x[p] - x[p - 1])
							* (xnew[n] - x[p - 1]);
		}
	}else{
		// Interpolate y if x is reversed
		size_t p = 0;
		for(size_t n = 1; n < (Nnew - 1); ++n){
			while(x[p] > xnew[n])
				++p;
			ynew[n] = y[p - 1]
					+ (y[p] - y[p - 1]) / (x[p] - x[p - 1])
							* (xnew[n] - x[p - 1]);
		}
	}
	if(cyclic && !overlappingends){
		// Remove extra points
		xnew.pop_back();
		ynew.pop_back();
	}
	x.swap(xnew);
	y.swap(ynew);
}

void DependentVector::CumSum(void)
{
	const size_t N = y.size();
	for(size_t n = 1; n < N; ++n)
		y[n] += y[n - 1];
}

void DependentVector::Integrate(void)
{
	const size_t N = y.size();
	std::vector <double> temp(N);
	temp[0] = 0.0;
	for(size_t n = 1; n < N; ++n)
		temp[n] = temp[n - 1] + (y[n] + y[n - 1]) * (x[n] - x[n - 1]) / 2.0;
	y.swap(temp);
}

void DependentVector::CumProd(void)
{
	const size_t N = y.size();
	for(size_t n = 1; n < N; ++n)
		y[n] *= y[n - 1];
}

size_t DependentVector::FindPeaks(const double minvalue)
{
	resultx.clear();
	resulty.clear();
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

		std::vector <double>::iterator ptpos = resultx.begin();
		std::vector <double>::iterator ptval = resulty.begin();
		while(ptpos != resultx.end() && *ptval > value){
			++ptpos;
			++ptval;
		}
		if(ptpos == resultx.end()){
			resultx.push_back(pos);
			resulty.push_back(value);

		}else{
			resultx.insert(ptpos, pos);
			resulty.insert(ptval, value);
		}
	}
	return resultx.size();
}

size_t DependentVector::FindValleys(const double minvalue)
{
	resultx.clear();
	resulty.clear();
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

		std::vector <double>::iterator ptpos = resultx.begin();
		std::vector <double>::iterator ptval = resulty.begin();

		while(ptpos != resultx.end() && *ptval < value){
			++ptpos;
			++ptval;
		}
		if(ptpos == resultx.end()){
			resultx.push_back(pos);
			resulty.push_back(value);

		}else{
			resultx.insert(ptpos, pos);
			resulty.insert(ptval, value);
		}
	}
	return resultx.size();
}

size_t DependentVector::ResultSize(void) const
{
	return resultx.size();
}

double DependentVector::ResultX(size_t index) const
{
	return resultx[index];
}

double DependentVector::ResultY(size_t index) const
{
	return resulty[index];
}

void DependentVector::Paint(void) const
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

void DependentVector::PaintCircle(double radius)
{
	glBegin(GL_LINE_LOOP);
	for(size_t n = 0; n < 100; ++n){
		const float co = cos(2 * M_PI / 100 * n);
		const float si = sin(2 * M_PI / 100 * n);
		glNormal3f(co, si, 0);
		glVertex2f(co * radius, si * radius);
	}
	glEnd();
}

void DependentVector::Export(std::string filename) const
{
	MatlabMatrix Mx("x", x.size());
	for(size_t n = 0; n < x.size(); ++n)
		Mx[n] = x[n];
	MatlabMatrix My("y", y.size());
	for(size_t n = 0; n < y.size(); ++n)
		My[n] = y[n];
	MatlabFile mf(filename);
	mf.WriteMatrix(Mx);
	mf.WriteMatrix(My);
	mf.Close();
}
