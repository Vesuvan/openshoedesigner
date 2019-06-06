///////////////////////////////////////////////////////////////////////////////
// Name               : CoreDensityEstimator.cpp
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

#include "CoreDensityEstimator.h"

#include <GL/gl.h>
#include <cmath>

CoreDensityEstimator::CoreDensityEstimator()
{
	cyclic = false;
}

CoreDensityEstimator::~CoreDensityEstimator()
{
}

void CoreDensityEstimator::SetRange(double t0, double t1, size_t N, bool cyclic)
{
	x.assign(N, 0);
	this->cyclic = cyclic;
	for(size_t n = 0; n < N; n++)
		x[n] = t0 + (double) n / (double) (N - 1) * (t1 - t0);
	Zero();
}

void CoreDensityEstimator::Zero(void)
{
	y.assign(x.size(), 0);
}

void CoreDensityEstimator::Add(coretype core, double sigma, double pos,
		double weight)
{
	const size_t N = x.size();
	const double x0 = x[0];
	const double x1 = x[x.size() - 1];
	const double d = fabs(x1 - x0);

	double px = 0.0;
	double p = pos;
	if(cyclic){
		if(x1 > x0){
			while(p > x1)
				p -= d;
			while(p < x0)
				p += d;
		}else{
			while(p > x0)
				p -= d;
			while(p < x1)
				p += d;
		}
		if(p > ((x0 + x1) / 2.0)) p = p - d;
		px = p + d / 2.0;
	}

	for(size_t n = 0; n < N; ++n){
		double v;
		if(cyclic){
			v = x[n] - (p + ((x[n] >= px)? d : 0));
		}else{
			v = x[n] - p;
		}
		v = v / sigma;
		switch(core){
		case Epanechnikov:
			y[n] += (0.75 * fmax(1 - v * v, 0.0)) / sigma * weight;
			break;
		}
	}
}

void CoreDensityEstimator::Paint(void) const
{
	glBegin(GL_LINE_STRIP);
	for(size_t n = 0; n < x.size(); ++n){
		double si = sin(x[n]);
		double co = cos(x[n]);
		double d = y[n];

		glVertex3d(0, co * d, si * d);
	}
	glEnd();
}
