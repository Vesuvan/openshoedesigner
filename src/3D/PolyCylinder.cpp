///////////////////////////////////////////////////////////////////////////////
// Name               : PolyCylinder.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.02.2019
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

#include "PolyCylinder.h"

#include <GL/gl.h>
#include <cmath>
#include <cstring>
#include <cstdio>

PolyCylinder::CircleSection::Segment::Segment()
{
}

void PolyCylinder::CircleSection::Segment::Scale(double sy, double sz)
{
	y = y0 * sy;
	z = z0 * sz;
	dy = y.Derive();
	dz = z.Derive();
}

double PolyCylinder::CircleSection::Segment::GetLength(void) const
{
	double d = 0;

	const double dr = 0.1;
	for(double r = 0.0; r < (1.000001 - dr); r += dr){
		const double hdy = dy.Evaluate(r + dr / 2) * dr;
		const double hdz = dz.Evaluate(r + dr / 2) * dr;
		d += sqrt(hdy * hdy + hdz * hdz);
	}
	return d;
}

void PolyCylinder::CircleSection::Segment::Paint(void) const
{
	glBegin(GL_LINE_STRIP);

	const double dr = 0.2;

	glNormal3d(0, dz.Evaluate(0), -dy.Evaluate(0));
	glVertex3d(0, y.Evaluate(0), z.Evaluate(0));

	for(double r = 0.0; r <= 1.00001; r += dr){
		glNormal3d(0, dz.Evaluate(r), -dy.Evaluate(r));
		glVertex3d(0, y.Evaluate(r), z.Evaluate(r));
	}

	glEnd();
}

PolyCylinder::CircleSection::CircleSection()
{
}

void PolyCylinder::CircleSection::Scale(double sy, double sz)
{
	for(size_t n = 0; n < segments.size(); ++n)
		segments[n].Scale(sy, sz);
}

double PolyCylinder::CircleSection::GetLength(void) const
{
	double d = 0.0;
	for(size_t n = 0; n < segments.size(); ++n)
		d += segments[n].GetLength();
	return d;
}

Vector3 PolyCylinder::CircleSection::Evaluate(double r)
{
	if(r < 0.0) r = 1.0 - fmod(-r, 1.0);
	const size_t M = segments.size();
	double h = r * (double) M;
	double p;
	double q = modf(h, &p);
	size_t m = (size_t) p;
	if(m >= M) m -= M;
	return Vector3(0, segments[m].y.Evaluate(q), segments[m].z.Evaluate(q));
}

void PolyCylinder::CircleSection::Paint(void) const
{
	for(size_t n = 0; n < segments.size(); ++n)
		segments[n].Paint();
}

PolyCylinder::PolyCylinder()
{
	dx = 1.0;
}

void PolyCylinder::Scale(double sx, double sy, double sz)
{
	dx = sx;
	for(size_t n = 0; n < sections.size(); ++n)
		sections[n].Scale(sy, sz);
}

bool PolyCylinder::Load(std::string filename)
{
	using namespace std;

	FILE* fhd = fopen(filename.c_str(), "rb");
	if(fhd == NULL) return false;

// Test header
	{
		char header[10];
		int res = fread(header, sizeof(char), 10, fhd);
		if(res < 10){
			fclose(fhd);
			return false;
		}
		if(std::strncmp(header, "SPLINEDATA", 10) != 0){
			fclose(fhd);
			return false;
		}
	}
// Test endianess
	{
		uint16_t magic;
		int res = fread(&magic, sizeof(uint16_t), 1, fhd);
		if(res < 1){
			fclose(fhd);
			return false;
		}
		if(magic != 4660){
			fclose(fhd);
			return false;
		}
	}

// Load dimensions from file.
	uint32_t dim[4];
	size_t res = fread(dim, sizeof(uint32_t), 4, fhd);
	if(res < 4){
		fclose(fhd);
		return false;
	}
	if(dim[2] != 2 || dim[3] != 4){
		fclose(fhd);
		return false;
	}

	size_t N = dim[0] * dim[1] * dim[2] * dim[3];

// Load all double data en block.
	double *temp = new double[N];
	res = fread(temp, sizeof(double), N, fhd);
	if(res < N){
		fclose(fhd);
		delete[] temp;
		return false;
	}
	fclose(fhd);

// Spread the data into the model.
	sections.resize(dim[0]);
	size_t p = 0;
	for(size_t n = 0; n < dim[0]; ++n){
		sections[n].segments.resize(dim[1]);
		for(size_t m = 0; m < dim[1]; ++m){
			sections[n].segments[m].z0.c3 = temp[p++];
			sections[n].segments[m].z0.c2 = temp[p++];
			sections[n].segments[m].z0.c1 = temp[p++];
			sections[n].segments[m].z0.c0 = temp[p++];
			sections[n].segments[m].y0.c3 = temp[p++];
			sections[n].segments[m].y0.c2 = temp[p++];
			sections[n].segments[m].y0.c1 = temp[p++];
			sections[n].segments[m].y0.c0 = temp[p++];
			sections[n].segments[m].Scale(0.002, 0.002);
		}
	}

	delete[] temp;

	dx = 1.0 / dim[0];
	return true;
}

void PolyCylinder::Paint(void) const
{
	glPushMatrix();
	for(size_t n = 0; n < sections.size(); ++n){
		sections[n].Paint();
		glTranslatef(dx, 0, 0);
	}
	glPopMatrix();
}

void PolyCylinder::GenerateGeometry(Geometry &geometry, bool mirrored)
{
	geometry.Clear();
	size_t N = 64;
	const double dr = 1.0 / (double) N;
	Vector3 a, b, c, d;

	{
		a.Zero();
		double r = 0.0;
		for(size_t m = 0; m < N; ++m){
			a += sections[0].Evaluate(r);
			r += dr;
		}
		a /= N;
		a.x = -0.5 * dx;
		r = 0.0;
		b = sections[0].Evaluate(0);
		for(size_t m = 0; m < N; ++m){
			r += dr;
			c = sections[0].Evaluate(r);
			if(mirrored){
				geometry.AddTriangle(a, b, c);
			}else{
				geometry.AddTriangle(a, c, b);
			}
			b = c;
		}
	}

	for(size_t n = 1; n <  sections.size(); ++n){
		double r = 0.0;
		a =  sections[n - 1].Evaluate(r);
		b =  sections[n].Evaluate(r);
		a.x = (n - 1) *  dx;
		b.x = (n) *  dx;
		for(size_t m = 0; m < N; ++m){
			r += dr;
			c =  sections[n - 1].Evaluate(r);
			d =  sections[n].Evaluate(r);
			c.x = (n - 1) *  dx;
			d.x = (n) *  dx;
			if(mirrored){
				geometry.AddQuad(a, b, d, c);
			}else{
				geometry.AddQuad(b, a, c, d);
			}
			a = c;
			b = d;
		}
	}
	{
		a.Zero();
		double r = 0.0;
		for(size_t m = 0; m < N; ++m){
			a +=  sections[ sections.size() - 1].Evaluate(r);
			r += dr;
		}
		a /= N;
		a.x = ((double) ( sections.size() - 1) + 0.5) *  dx;
		r = 0.0;
		b =  sections[ sections.size() - 1].Evaluate(0);
		b.x = ( sections.size() - 1) *  dx;
		for(size_t m = 0; m < N; ++m){
			r += dr;
			c =  sections[ sections.size() - 1].Evaluate(r);
			c.x = ( sections.size() - 1) *  dx;
			if(mirrored){
				geometry.AddTriangle(a, c, b);
			}else{
				geometry.AddTriangle(a, b, c);
			}
			b = c;
		}
	}
}


void PolyCylinder::Test(void)
{
//	double L = sections[0].GetLength();
//	std::fprintf(stdout, "%g mm\n", L * 1e3);
}
