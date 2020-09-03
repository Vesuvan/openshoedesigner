///////////////////////////////////////////////////////////////////////////////
// Name               : Symmetry.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 27.05.2019
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

#include "Symmetry.h"

#include <GL/gl.h>
#include <cmath>
#include <cstdlib>
#include "Kernel.h"
#include "FourierTransform.h"

Symmetry::Symmetry()
{
	Init(180);
}

void Symmetry::Init(size_t N)
{
	XLinspace(0, M_PI, N);
	XSetCyclic(M_PI);
	YInit();
}

void Symmetry::AddTransform(const FourierTransform& transform)
{
	for(size_t n = 0; n < transform.f.size(); ++n){
		const int f = (int) round(transform.f[n]);
		const size_t F = (size_t)(abs(f));
		if(f == 0) continue;

		const double d = (transform.OutRe[n] * transform.OutRe[n]
				+ transform.OutIm[n] * transform.OutIm[n]);
		double a = -atan2(transform.OutIm[n], transform.OutRe[n]) / (double) f;

		const double da = M_PI / (double) f;
		for(size_t m = 0; m < F; ++m){
			Insert(a, Kernel::Epanechnikov, d, sigma);
			a += da;
		}
	}
}

void Symmetry::Normalize(void)
{
	KernelDensityEstimator::NormalizeByWeightSum();
	this->operator/=(Kernel::Epanechnikov(0) / sigma);
}

void Symmetry::Paint(void) const
{
	glPushMatrix();
	KernelDensityEstimator::Paint();
	glRotatef(180.0, 0.0, 0.0, 1.0);
	KernelDensityEstimator::Paint();
	glPopMatrix();
}
