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

#include "../3D/OpenGLMaterial.h"
Symmetry::Symmetry()
{
	sigma = 0.2;
	minsymmetry = 0.3;
	InitSupport(360);
}

Symmetry::~Symmetry()
{
}

void Symmetry::InitSupport(size_t N)
{
	support.assign(N, 0.0);
}

void Symmetry::AddTransform(const FourierTransform& transform)
{
	const size_t N = support.size();
	double sum = 0.0;
	std::vector <double> temp(N, 0);
	const double ds = M_PI / (double) N;
	for(size_t n = 0; n < transform.f.size(); ++n){
		const int f = (int) round(transform.f[n]);
		if(f == 0) continue;
		const double d = (transform.OutRe[n] * transform.OutRe[n]
				+ transform.OutIm[n] * transform.OutIm[n]);
		sum += d;
		double a = -atan2(transform.OutIm[n], transform.OutRe[n]) / (double) f;
		while(a < 0.0)
			a += M_PI;
		const double da = M_PI / (double) f;
		for(size_t m = 0; m < abs(f); ++m){
			while(a > M_PI)
				a -= M_PI;
			double s = 0.0;
			for(size_t q = 0; q < N; ++q){
				temp[q] += (Epanechnikov((s - a - M_PI) / sigma)
						+ Epanechnikov((s - a) / sigma)
						+ Epanechnikov((s - a + M_PI) / sigma)) * d;
				s += ds;
			}
			a += da;
		}
	}
	sum *= Epanechnikov(0);
	for(size_t n = 0; n < N; ++n)
		support[n] += temp[n] / sum;
}

double Symmetry::Epanechnikov(double x)
{
	return fmax(1.0 - x * x, 0.0) * 0.75;
}

void Symmetry::FindPeaks(void)
{
	angle.clear();
	strength.clear();
	const size_t N = support.size();
	const double ds = M_PI / (double) support.size();
	double s = -ds;
	for(size_t n = 0; n < N; ++n){
		double v0 = support[n];
		double v1 = (n < N - 1)? support[n + 1] : support[n + 1 - N];
		double v2 = (n < N - 2)? support[n + 2] : support[n + 2 - N];
		s += ds;
		if(v0 >= v1 || v2 >= v1) continue;
		if(v1 < minsymmetry) continue;

		// Interpolate peaks with 2nd order polynoms to find the position and value of the maximum.
		const double den = v2 - 2 * v1 + v0;
		const double pos = (s * (v0 - 2 * v1 + v2)
				+ ds * (1.5 * v0 - 2 * v1 + 0.5 * v2)) / den;

		const double amax = (v0 * (-v0 / 8 + v1 + v2 / 4) + v1 * (v2 - 2 * v1)
				- v2 * v2 / 8) / den;

		std::vector <double>::iterator ma = angle.begin();
		std::vector <double>::iterator ms = strength.begin();

		while(ma != angle.end() && *ms > amax){
			++ma;
			++ms;
		}
		if(ma == angle.end()){
			angle.push_back(pos);
			strength.push_back(amax);

		}else{
			angle.insert(ma, pos);
			strength.insert(ms, amax);
		}
	}
}

void Symmetry::Paint(void) const
{
	OpenGLMaterial mat;
	mat.SetSimpleColor(0.8, 0.8, 0.8);
	mat.UseColor(1); // Emitter material -> normals not needed

	glBegin(GL_LINE_LOOP);
	for(size_t n = 0; n < support.size(); ++n){
		const float co = cos(M_PI / support.size() * n);
		const float si = sin(M_PI / support.size() * n);
		Vector3 temp = center + localx * co * support[n]
				+ localy * si * support[n];
		glVertex3f(temp.x, temp.y, temp.z);
	}
	for(size_t n = 0; n < support.size(); ++n){
		const float co = cos(M_PI / support.size() * n);
		const float si = sin(M_PI / support.size() * n);
		Vector3 temp = center - localx * co * support[n]
				- localy * si * support[n];
		glVertex3f(temp.x, temp.y, temp.z);
	}
	glEnd();

	mat.SetSimpleColor(0.3, 0.3, 0.3);
	mat.UseColor(1);

	glBegin(GL_LINE_LOOP);
	for(size_t n = 0; n < 100; ++n){
		const float co = cos(2 * M_PI / 100 * n);
		const float si = sin(2 * M_PI / 100 * n);
		Vector3 temp = center - (localx * co + localy * si);
		glVertex3f(temp.x, temp.y, temp.z);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(size_t n = 0; n < 100; ++n){
		const float co = cos(2 * M_PI / 100 * n);
		const float si = sin(2 * M_PI / 100 * n);
		Vector3 temp = center - (localx * co + localy * si) * 0.75;
		glVertex3f(temp.x, temp.y, temp.z);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(size_t n = 0; n < 100; ++n){
		const float co = cos(2 * M_PI / 100 * n);
		const float si = sin(2 * M_PI / 100 * n);
		Vector3 temp = center - (localx * co + localy * si) * 0.5;
		glVertex3f(temp.x, temp.y, temp.z);
	}
	glEnd();

	OpenGLMaterial::EnableColors();
}
