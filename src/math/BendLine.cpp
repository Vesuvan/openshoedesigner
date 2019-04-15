///////////////////////////////////////////////////////////////////////////////
// Name               : BendLine.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 02.03.2019
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

#include "BendLine.h"

#include <cmath>

BendLine::BendLine()
{
	N = 0;
}

BendLine::~BendLine()
{
}

void BendLine::SetCount(size_t N)
{
	this->N = N;
	angle.resize(N);
	x.resize(N);
	y.resize(N);
}

void BendLine::InitAngle(double a)
{
	for(size_t n = 0; n < N; ++n)
		angle[n] = a;
}

void BendLine::SetBend(double angle, double x0, double sigma, Kernel kernel)
{
	std::vector <double> temp;
	temp.resize(N);
	double r = -x0 / sigma;
	const double dr = 1.0 / sigma / (double) (N - 1);
	switch(kernel){
	case Gauss:
		{
			const double f = 1.0 / sqrt(2 * M_PI);
			for(size_t n = 0; n < N; ++n){
				temp[n] = exp(-r * r / 2) * f;
				r += dr;
			}
		}
		break;
	case Picard:
		{
			for(size_t n = 0; n < N; ++n){
				temp[n] = 0.5 * exp(-fabs(r) / 2);
				r += dr;
			}
		}
		break;
	case Epanechnikov:
		{
			for(size_t n = 0; n < N; ++n){
				temp[n] = 0.75 * fmax(1 - r * r, 0);
				r += dr;
			}
		}
		break;
	case Cauchy:
		{
			for(size_t n = 0; n < N; ++n){
				temp[n] = 1.0 / (M_PI * (1 + r * r));
				r += dr;
			}
		}
		break;
	}
	for(size_t n = 1; n < N; ++n)
		temp[n] += temp[n - 1];
	const double a = 1.0 / (temp[N - 1] - temp[0]);
	const double b = temp[0];
	for(size_t n = 0; n < N; ++n)
		this->angle[n] += angle * (temp[n] - b) * a;
}

void BendLine::Finish(double L)
{
	x[0] = 0.0;
	y[0] = 0.0;
	const double dr = L / (N - 1);
	for(size_t n = 1; n < N; ++n){
		x[n] = x[n - 1] + dr * cos(angle[n]);
		y[n] = y[n - 1] + dr * sin(angle[n]);
	}
}
