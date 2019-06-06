///////////////////////////////////////////////////////////////////////////////
// Name               : PolyFilter.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.06.2019
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

#include "PolyFilter.h"

#include <cmath>
#include <stdexcept>

PolyFilter::PolyFilter()
{
	order = 0;
}

PolyFilter::~PolyFilter()
{
}

void PolyFilter::Init(size_t order, size_t size)
{
	filter_a.assign(size, 0.0);
	filter_b.assign(size, 0.0);
	filter_c.assign(size, 0.0);
	filter_d.assign(size, 0.0);
	const double N = (double) size;

	switch(order){
	case 0:
		filter_d.assign(size, 1.0 / N);
		break;
	case 1:
		{
			const double a = 12.0 / (N * N * N - N);
			const double b = -6.0 / (N * N + N);
			for(size_t i = 0; i < size; ++i)
				filter_c[i] = a * i + b;
		}
		{
			const double a = -6.0 / (N * N + N);
			const double b = (4.0 * N - 2.0) / (N * N + N);
			for(size_t i = 0; i < size; ++i)
				filter_d[i] = a * i + b;
		}
		break;
	case 2:
		{
			const double a = 180.0
					/ ((N - 2.0) * (N - 1.0) * N * (N + 1.0) * (N + 2.0));
			const double b = -180.0 / ((N - 2.0) * N * (N + 1.0) * (N + 2.0));
			const double c = 30.0 / (N * (N + 1.0) * (N + 2.0));
			for(size_t i = 0; i < size; ++i)
				filter_b[i] = (a * i + b) * i + c;
		}
		{
			const double a = -180.0 / ((N - 2.0) * N * (N + 1.0) * (N + 2.0));
			const double b = (12.0 * (2.0 * N - 1.0) * (8.0 * N - 11.0))
					/ ((N - 2.0) * (N - 1) * N * (N + 1.0) * (N + 2.0));
			const double c = -(36.0 * N - 18.0) / (N * (N + 1.0) * (N + 2.0));
			for(size_t i = 0; i < size; ++i)
				filter_c[i] = (a * i + b) * i + c;
		}
		{
			const double a = 30.0 / (N * (N + 1.0) * (N + 2.0));
			const double b = -(36.0 * N - 18.0) / (N * (N + 1.0) * (N + 2.0));
			const double c = (9.0 * N * N - 9.0 * N + 6.0)
					/ (N * (N + 1.0) * (N + 2.0));
			for(size_t i = 0; i < size; ++i)
				filter_d[i] = (a * i + b) * i + c;
		}
		break;
	case 3:
		{
			const double den1 = ((N - 3.0) * (N - 2.0) * (N - 1.0) * N
					* (N + 1.0) * (N + 2.0) * (N + 3.0));
			const double den2 = (N * (N + 1.0) * (N + 2.0) * (N + 3.0));
			{
				const double a = 2800.0 / den1;
				const double b = (4200.0 - 4200.0 * N) / den1;
				const double c = (3080.0 - 4200.0 * N + 1680.0 * N * N) / den1;
				const double d = -140.0 / den2;
				for(size_t i = 0; i < size; ++i)
					filter_a[i] = ((a * i + b) * i + c) * i + d;
			}
			{
				const double a = (4200.0 - 4200.0 * N) / den1;
				const double b = (4680.0 - 12600.0 * N + 6480.0 * N * N) / den1;
				const double c = (3000.0 - 9300.0 * N + 9000.0 * N * N
						- 2700.0 * N * N * N) / den1;
				const double d = (-120.0 + 240.0 * N) / den2;
				for(size_t i = 0; i < size; ++i)
					filter_b[i] = ((a * i + b) * i + c) * i + d;
			}
			{
				const double a = (3080.0 - 4200.0 * N + 1680.0 * N * N) / den1;
				const double b = (3000.0 - 9300.0 * N + 9000.0 * N * N
						- 2700.0 * N * N * N) / den1;
				const double c = (2200.0 - 6000.0 * N + 8400.0 * N * N
						- 5400.0 * N * N * N + 1200.0 * N * N * N * N) / den1;
				const double d = (-100.0 + 120.0 * N - 120.0 * N * N) / den2;
				for(size_t i = 0; i < size; ++i)
					filter_c[i] = ((a * i + b) * i + c) * i + d;
			}
			{
				const double a = -140.0 / den2;
				const double b = (-120.0 + 240.0 * N) / den2;
				const double c = (-100.0 + 120.0 * N - 120.0 * N * N) / den2;
				const double d = (-24.0 + 56.0 * N - 24.0 * N * N
						+ 16.0 * N * N * N) / den2;
				for(size_t i = 0; i < size; ++i)
					filter_d[i] = ((a * i + b) * i + c) * i + d;
			}
		}
		break;
	default:
		throw(std::range_error(
		__FILE__"Init: Only filters of order 0 .. 3 are supported."));
	}
	this->order = order;
}

size_t PolyFilter::GetSize(void) const
{
	return filter_a.size();
}

size_t PolyFilter::GetOrder(void) const
{
	return order;
}

double PolyFilter::FilterA(const std::vector <double> &vec, size_t pos) const
{
	const size_t N = vec.size();
	const size_t F = filter_a.size();
	double temp = 0.0;
	for(size_t f = 0; f < F; ++f)
		temp += vec[(pos + f) % N] * filter_a[f];
	return temp;
}

double PolyFilter::FilterB(const std::vector <double> &vec, size_t pos) const
{
	const size_t N = vec.size();
	const size_t F = filter_b.size();
	double temp = 0.0;
	for(size_t f = 0; f < F; ++f)
		temp += vec[(pos + f) % N] * filter_b[f];
	return temp;
}

double PolyFilter::FilterC(const std::vector <double> &vec, size_t pos) const
{
	const size_t N = vec.size();
	const size_t F = filter_c.size();
	double temp = 0.0;
	for(size_t f = 0; f < F; ++f)
		temp += vec[(pos + f) % N] * filter_c[f];
	return temp;
}

double PolyFilter::FilterD(const std::vector <double> &vec, size_t pos) const
{
	const size_t N = vec.size();
	const size_t F = filter_d.size();
	double temp = 0.0;
	for(size_t f = 0; f < F; ++f)
		temp += vec[(pos + f) % N] * filter_d[f];
	return temp;
}

bool PolyFilter::GetExtremum(double& pos, const double a, const double b,
		const double c, const double d) const
{
	switch(order){
	case 2:
		{
			if(fabs(b) < 1e-9) return false;
			pos = -c / (2 * b);
			return true;
		}
	case 3:
		{
			if(fabs(a) < 1e-9) return false;
			const double h = b * b - 3 * a * c;
			if(h < 0) return false;
			pos = (-b - sqrt(h)) / (3 * a);
			return true;
		}
	}
	return false;
}

bool PolyFilter::GetExtremum2(double& pos, const double a, const double b,
		const double c, const double d) const
{
	if(order != 3) return false;
	if(fabs(a) < 1e-9) return false;
	const double h = b * b - 3 * a * c;
	if(h < 0) return false;
	pos = (-b + sqrt(h)) / (3 * a);
	return true;
}

bool PolyFilter::GetInflectionPoint(double& pos, const double a, const double b,
		const double c, const double d) const
{
	if(order != 3) return false;
	if(fabs(a) < 1e-9) return false;
	pos = -b / (3 * a);
	return true;
}
//double Filter(double data[], double filter[], int shift)
//{
//	int N = ArraySize(filter);
//	double result = 0.0;
//	for(int i = 0; i < N; i++){
//		result = result + data[i + shift] * filter[i];
//	}
//	return (result);
//}
//
//double FilterSTD0(double data[], double a, int N, int shift)
//{
//	double result = 0.0;
//	for(int i = 0; i < N; i++)
//		result = result + (data[i + shift] - a) * (data[i + shift] - a);
//	return (MathSqrt(result / N));
//}
//
//double FilterSTD1(double data[], double a, double b, int N, int shift)
//{
//	double result = 0.0;
//	double ref;
//	for(int i = 0; i < N; i++){
//		ref = a * i + b;
//		result = result + (data[i + shift] - ref) * (data[i + shift] - ref);
//	}
//	return (MathSqrt(result / N));
//}
//
//double FilterSTD2(double data[], double a, double b, double c, int N, int shift)
//{
//	double result = 0.0;
//	double ref;
//	for(int i = 0; i < N; i++){
//		ref = (a * i + b) * i + c;
//		result = result + (data[i + shift] - ref) * (data[i + shift] - ref);
//	}
//	return (MathSqrt(result / N));
//}
//
//double FilterSTD3(double data[], double a, double b, double c, double d, int N,
//		int shift)
//{
//	double result = 0.0;
//	double ref;
//	for(int i = 0; i < N; i++){
//		ref = ((a * i + b) * i + c) * i + d;
//		result = result + (data[i + shift] - ref) * (data[i + shift] - ref);
//	}
//	return (MathSqrt(result / N));
//}
//
//}
