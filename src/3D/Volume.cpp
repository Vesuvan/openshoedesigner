///////////////////////////////////////////////////////////////////////////////
// Name               : Volume.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 19.08.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Volume.h"

#include "../StdInclude.h"
//#include <wx/textfile.h>
//#include <wx/string.h>
#include <GL/gl.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdint.h>

Volume::Volume()
{
	dx = 1.0;
	dy = 1.0;
	dz = 1.0;
	surface = 0.5;
	color.Set(0.5, 0.5, 0.5);
	display2D = Image;
	display3D = MarchingCubes;
}

Volume::~Volume()
{
}

void Volume::SetCount(unsigned int nx, unsigned int ny, unsigned int nz,
		float resolution)
{
	MatlabMatrix::SetSize(nx, ny, nz);
	dx = resolution;
	dy = resolution;
	dz = resolution;
}

void Volume::SetSize(float x, float y, float z, float resolution)
{
	size_t nx = (unsigned int) ceil(x / resolution);
	size_t ny = (unsigned int) ceil(y / resolution);
	size_t nz = (unsigned int) ceil(z / resolution);
	MatlabMatrix::SetSize(nx, ny, nz);
	dx = resolution;
	dy = resolution;
	dz = resolution;
}

void Volume::SetOrigin(Vector3 origin)
{
	this->origin = origin;
}

void Volume::AddHalfplane(const Vector3& p1, float d0, float k0)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);
	Vector3 p(0, 0, 0);
	const float kh = -log(2 * M_E - 1) / k0;
	unsigned int c = 0;
	for(size_t nz = 0; nz < Nz; nz++){
		for(size_t ny = 0; ny < Ny; ny++){
			for(size_t nx = 0; nx < Nx; nx++){
				const float d = (p + origin).Dot(p1);
				buffer[c] += 1 - 1 / (1 + exp(kh * (d - d0)));
				c++;
				p.x += dx;
			}
			p.x = 0.0;
			p.y += dy;
		}
		p.y = 0.0;
		p.z += dz;
	}
}

void Volume::AddSphere(const Vector3 &p1, float r1, float k1)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);
	const Vector3 h1 = p1 - origin;
	Vector3 p(0, 0, 0);
	unsigned int c = 0;
	const float kh = -log(2 * M_E - 1) / k1;
	for(size_t nz = 0; nz < Nz; nz++){
		for(size_t ny = 0; ny < Ny; ny++){
			for(size_t nx = 0; nx < Nx; nx++){
				const float d = 1 - 1 / (1 + exp(kh * ((p - h1).Abs() - r1)));
				buffer[c] += d;
				c++;
				p.x += dx;
			}
			p.x = 0.0;
			p.y += dy;
		}
		p.y = 0.0;
		p.z += dz;
	}
}

void Volume::AddCylinder(const Vector3& p1, const Vector3& p2, const float r1,
		const float k1)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);
	const Vector3 h1 = p1 - origin;
	const Vector3 h2 = p2 - origin;
	Vector3 n = h2 - h1;
	const float nd = n.Abs();
	const float kh = -log(2 * M_E - 1) / k1;
	n.Normalize();
	Vector3 p(0, 0, 0);
	unsigned int c = 0;
	for(size_t nz = 0; nz < Nz; nz++){
		for(size_t ny = 0; ny < Ny; ny++){
			for(size_t nx = 0; nx < Nx; nx++){
				float r = n.Dot(p - h1);
				if(r < 0) r = 0;
				if(r > nd) r = nd;
				const Vector3 h = h1 + n * r;
				const float d = (p - h).Abs() - r1;

				buffer[c] += 1 - 1 / (1 + exp(kh * d));
				c++;
				p.x += dx;
			}
			p.x = 0.0;
			p.y += dy;
		}
		p.y = 0.0;
		p.z += dz;
	}
}

void Volume::AddCylinder(const Vector3& p1, const Vector3& p2, const float r1,
		const float r2, const float k1)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	const Vector3 h1 = p1 - origin;
	const Vector3 h2 = p2 - origin;
	Vector3 n = h2 - h1;
	const double nd = n.Abs();
	if(nd == 0){
		AddSphere(p1, fmax(r1, r2), k1);
		return;
	}
	if(nd + r2 <= r1){
		AddSphere(p1, r1, k1);
		return;
	}
	if(nd + r1 <= r2){
		AddSphere(p2, r2, k1);
		return;
	}

	n.Normalize();

//	float a = 1 / (1 + (2 * r1 * r2 - r1 * r1 - r2 * r2) / (nd * nd));
//	float b = (r1 * r2 - r1 * r1) / nd;

// x2 = x1*a
// y2 = x1*b

	const double s0 = (r1 * r1 - r1 * r2) / nd;
	const double h0 = r1 * sqrt(2 * r1 * r2 + nd * nd - r1 * r1 - r2 * r2) / nd;
	// Coordinatesystemtransformation:
	const double a11 = 1 / nd;
	const double a12 = -s0 / (h0 * nd);
//	const float a21 = (r1 - r2) / nd;
//	const float a22 = (r2 * s0 - r1 * s0 + nd * r1) / (h0 * nd);
	const double a21 = 0;
	const double a22 = r1 / h0;

	const double kh = -log(2 * M_E - 1) / k1;
	Vector3 p(0, 0, 0);
	Vector3 h;
	unsigned int c = 0;
	for(size_t nz = 0; nz < Nz; nz++){
		for(size_t ny = 0; ny < Ny; ny++){
			for(size_t nx = 0; nx < Nx; nx++){
				const double x = n.Dot(p - h1);
				h = n * x + h1;
				const double y = (p - h).Abs();
				const double x2 = fma(x, a11, y * a12);
				const double y2 = fma(x, a21, y * a22);
				double d = y2;

				if(x2 < 0) d = (p - h1).Abs();
				if(x2 > 1) d = (p - h2).Abs();
//				if(x2 >= 0) d = sqrt(
//						(x2 - nd * a) * (x2 - nd * a) + y2 * y2);
				double r;
				if(x2 < 0){
					r = r1;
				}else{
					if(x2 < 1){
						r = fma(x2, r2 - r1, r1); // = r1 + (r2 - r1) * x2;
					}else{
						r = r2;
					}
				}
				d -= r;
				d *= kh;

				if(d > -2){
					if(d > 2){
						d = 1.0;
					}else{
						d = d * 0.25 + 0.5;
					}
					buffer[c] += d;
				}
				//d = 1 - 1 / (1 + exp(-k1 * d));
//				if(d > -5){
//					if(d > 5){
//						d = 1.0;
//					}else{
//						d = 1 - 1 / (1 + exp(d));
//					}
//					buffer[c] += d;
//				}
				c++;
				p.x += dx;
			}
			p.x = 0.0;
			p.y += dy;
		}
		p.y = 0.0;
		p.z += dz;
	}
}

void Volume::AddCylinder(const Vector3& p1, const Vector3& p2, const float r1,
		const float r2, const float k1, const float k2)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);
	const Vector3 h1 = p1 - origin;
	const Vector3 h2 = p2 - origin;
	Vector3 n = h2 - h1;
	const float nd = n.Abs();
	if(nd == 0){
		AddSphere(p1, fmax(r1, r2), k1);
		return;
	}
	if(nd + r2 <= r1){
		AddSphere(p1, r1, k1);
		return;
	}
	if(nd + r1 <= r2){
		AddSphere(p2, r2, k1);
		return;
	}

	n.Normalize();

//	float a = 1 / (1 + (2 * r1 * r2 - r1 * r1 - r2 * r2) / (nd * nd));
//	float b = (r1 * r2 - r1 * r1) / nd;

// x2 = x1*a
// y2 = x1*b

	const float dlimit = fmax(fmax(dx, dy), dz);

	const float s0 = (r1 * r1 - r1 * r2) / nd;
	const float h0 = r1 * sqrt(2 * r1 * r2 + nd * nd - r1 * r1 - r2 * r2) / nd;
// Coordinatesystemtransformation:
	const float a11 = 1 / nd;
	const float a12 = -s0 / (h0 * nd);
//	const float a21 = (r1 - r2) / nd;
//	const float a22 = (r2 * s0 - r1 * s0 + nd * r1) / (h0 * nd);
	const float a21 = 0;
	const float a22 = r1 / h0;

	const float kh = -log(2 * M_E - 1);
	Vector3 p(0, 0, 0);
	size_t c = 0;
	for(size_t nz = 0; nz < Nz; nz++){
		for(size_t ny = 0; ny < Ny; ny++){
			for(size_t nx = 0; nx < Nx; nx++){
				float x = n.Dot(p - h1);
				const Vector3 h = h1 + n * x;
				const float y = (p - h).Abs();
				const float x2 = x * a11 + y * a12;
				const float y2 = x * a21 + y * a22;
				float d = y2;

				if(x2 < 0) d = (p - h1).Abs();
				if(x2 > 1) d = (p - h2).Abs();
				//				if(x2 >= 0) d = sqrt(
				//						(x2 - nd * a) * (x2 - nd * a) + y2 * y2);
				float r;
				if(x2 < 0){
					r = r1;
				}else{
					if(x2 < 1){
						r = r1 + (r2 - r1) * x2;
					}else{
						r = r2;
					}
				}
				float k;
//				if(x2 < 0){
//					k = k1;
//				}else{
//					if(x2 < 1){
				k = k1 + (k2 - k1) * x2;
//					}else{
//						k = k2;
//					}
//				}
				if(k < dlimit) k = dlimit;

				d -= r;
				//d = 1 - 1 / (1 + exp(-k1 * d));
				d = 1 - 1 / (1 + exp(kh * d / k));
				buffer[c] += d;
				c++;
				p.x += dx;
			}
			p.x = 0.0;
			p.y += dy;
		}
		p.y = 0.0;
		p.z += dz;
	}
}

const static int8_t tri[3072] =
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, 3, 0, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8,
			3, 1, 8, 1, 9, -1, -1, -1, -1, -1, -1, 11, 2, 3, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, 11, 2, 0, 11, 0, 8, -1, -1, -1, -1, -1, -1, 11, 2,
			3, 0, 1, 9, -1, -1, -1, -1, -1, -1, 2, 1, 11, 1, 9, 11, 11, 9, 8,
			-1, -1, -1, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, 3, 0,
			1, 2, 10, -1, -1, -1, -1, -1, -1, 9, 0, 2, 9, 2, 10, -1, -1, -1, -1,
			-1, -1, 3, 2, 8, 2, 10, 8, 8, 10, 9, -1, -1, -1, 10, 1, 3, 10, 3,
			11, -1, -1, -1, -1, -1, -1, 1, 0, 10, 0, 8, 10, 10, 8, 11, -1, -1,
			-1, 0, 3, 9, 3, 11, 9, 9, 11, 10, -1, -1, -1, 8, 10, 9, 8, 11, 10,
			-1, -1, -1, -1, -1, -1, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			3, 0, 4, 3, 4, 7, -1, -1, -1, -1, -1, -1, 1, 9, 0, 8, 4, 7, -1, -1,
			-1, -1, -1, -1, 9, 4, 1, 4, 7, 1, 1, 7, 3, -1, -1, -1, 2, 3, 11, 7,
			8, 4, -1, -1, -1, -1, -1, -1, 7, 11, 4, 11, 2, 4, 4, 2, 0, -1, -1,
			-1, 3, 11, 2, 4, 7, 8, 9, 0, 1, -1, -1, -1, 2, 7, 11, 2, 1, 7, 1, 4,
			7, 1, 9, 4, 10, 1, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, 2, 10, 1, 0,
			4, 7, 0, 7, 3, -1, -1, -1, 4, 7, 8, 0, 2, 10, 0, 10, 9, -1, -1, -1,
			2, 7, 3, 2, 9, 7, 7, 9, 4, 2, 10, 9, 8, 4, 7, 11, 10, 1, 11, 1, 3,
			-1, -1, -1, 11, 4, 7, 1, 4, 11, 1, 11, 10, 1, 0, 4, 3, 8, 0, 7, 11,
			4, 11, 9, 4, 11, 10, 9, 7, 11, 4, 4, 11, 9, 11, 10, 9, -1, -1, -1,
			9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, 0, 8, 4, 9, 5, -1,
			-1, -1, -1, -1, -1, 5, 4, 0, 5, 0, 1, -1, -1, -1, -1, -1, -1, 4, 8,
			5, 8, 3, 5, 5, 3, 1, -1, -1, -1, 11, 2, 3, 9, 5, 4, -1, -1, -1, -1,
			-1, -1, 9, 5, 4, 8, 11, 2, 8, 2, 0, -1, -1, -1, 3, 11, 2, 1, 5, 4,
			1, 4, 0, -1, -1, -1, 8, 5, 4, 2, 5, 8, 2, 8, 11, 2, 1, 5, 2, 10, 1,
			9, 5, 4, -1, -1, -1, -1, -1, -1, 0, 8, 3, 5, 4, 9, 10, 1, 2, -1, -1,
			-1, 10, 5, 2, 5, 4, 2, 2, 4, 0, -1, -1, -1, 3, 4, 8, 3, 2, 4, 2, 5,
			4, 2, 10, 5, 5, 4, 9, 1, 3, 11, 1, 11, 10, -1, -1, -1, 0, 9, 1, 4,
			8, 5, 8, 10, 5, 8, 11, 10, 3, 4, 0, 3, 10, 4, 4, 10, 5, 3, 11, 10,
			4, 8, 5, 5, 8, 10, 8, 11, 10, -1, -1, -1, 9, 5, 7, 9, 7, 8, -1, -1,
			-1, -1, -1, -1, 0, 9, 3, 9, 5, 3, 3, 5, 7, -1, -1, -1, 8, 0, 7, 0,
			1, 7, 7, 1, 5, -1, -1, -1, 1, 7, 3, 1, 5, 7, -1, -1, -1, -1, -1, -1,
			11, 2, 3, 8, 9, 5, 8, 5, 7, -1, -1, -1, 9, 2, 0, 9, 7, 2, 2, 7, 11,
			9, 5, 7, 0, 3, 8, 2, 1, 11, 1, 7, 11, 1, 5, 7, 2, 1, 11, 11, 1, 7,
			1, 5, 7, -1, -1, -1, 1, 2, 10, 5, 7, 8, 5, 8, 9, -1, -1, -1, 9, 1,
			0, 10, 5, 2, 5, 3, 2, 5, 7, 3, 5, 2, 10, 8, 2, 5, 8, 5, 7, 8, 0, 2,
			10, 5, 2, 2, 5, 3, 5, 7, 3, -1, -1, -1, 3, 9, 1, 3, 8, 9, 7, 11, 10,
			7, 10, 5, 9, 1, 0, 10, 7, 11, 10, 5, 7, -1, -1, -1, 3, 8, 0, 7, 10,
			5, 7, 11, 10, -1, -1, -1, 11, 5, 7, 11, 10, 5, -1, -1, -1, -1, -1,
			-1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 8, 3, 11, 7, 6,
			-1, -1, -1, -1, -1, -1, 9, 0, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1,
			7, 6, 11, 3, 1, 9, 3, 9, 8, -1, -1, -1, 2, 3, 7, 2, 7, 6, -1, -1,
			-1, -1, -1, -1, 8, 7, 0, 7, 6, 0, 0, 6, 2, -1, -1, -1, 1, 9, 0, 3,
			7, 6, 3, 6, 2, -1, -1, -1, 7, 6, 2, 7, 2, 9, 2, 1, 9, 7, 9, 8, 1, 2,
			10, 6, 11, 7, -1, -1, -1, -1, -1, -1, 2, 10, 1, 7, 6, 11, 8, 3, 0,
			-1, -1, -1, 11, 7, 6, 10, 9, 0, 10, 0, 2, -1, -1, -1, 7, 6, 11, 3,
			2, 8, 8, 2, 10, 8, 10, 9, 6, 10, 7, 10, 1, 7, 7, 1, 3, -1, -1, -1,
			6, 10, 1, 6, 1, 7, 7, 1, 0, 7, 0, 8, 9, 0, 3, 6, 9, 3, 6, 10, 9, 6,
			3, 7, 6, 10, 7, 7, 10, 8, 10, 9, 8, -1, -1, -1, 8, 4, 6, 8, 6, 11,
			-1, -1, -1, -1, -1, -1, 11, 3, 6, 3, 0, 6, 6, 0, 4, -1, -1, -1, 0,
			1, 9, 4, 6, 11, 4, 11, 8, -1, -1, -1, 1, 9, 4, 11, 1, 4, 11, 3, 1,
			11, 4, 6, 3, 8, 2, 8, 4, 2, 2, 4, 6, -1, -1, -1, 2, 0, 4, 2, 4, 6,
			-1, -1, -1, -1, -1, -1, 1, 9, 0, 3, 8, 2, 2, 8, 4, 2, 4, 6, 9, 4, 1,
			1, 4, 2, 4, 6, 2, -1, -1, -1, 10, 1, 2, 11, 8, 4, 11, 4, 6, -1, -1,
			-1, 10, 1, 2, 11, 3, 6, 6, 3, 0, 6, 0, 4, 0, 2, 10, 0, 10, 9, 4, 11,
			8, 4, 6, 11, 2, 11, 3, 6, 9, 4, 6, 10, 9, -1, -1, -1, 8, 4, 6, 8, 6,
			1, 6, 10, 1, 8, 1, 3, 1, 0, 10, 10, 0, 6, 0, 4, 6, -1, -1, -1, 8, 0,
			3, 9, 6, 10, 9, 4, 6, -1, -1, -1, 10, 4, 6, 10, 9, 4, -1, -1, -1,
			-1, -1, -1, 9, 5, 4, 7, 6, 11, -1, -1, -1, -1, -1, -1, 4, 9, 5, 3,
			0, 8, 11, 7, 6, -1, -1, -1, 6, 11, 7, 4, 0, 1, 4, 1, 5, -1, -1, -1,
			6, 11, 7, 4, 8, 5, 5, 8, 3, 5, 3, 1, 4, 9, 5, 6, 2, 3, 6, 3, 7, -1,
			-1, -1, 9, 5, 4, 8, 7, 0, 0, 7, 6, 0, 6, 2, 4, 0, 1, 4, 1, 5, 6, 3,
			7, 6, 2, 3, 7, 4, 8, 5, 2, 1, 5, 6, 2, -1, -1, -1, 6, 11, 7, 1, 2,
			10, 9, 5, 4, -1, -1, -1, 11, 7, 6, 8, 3, 0, 1, 2, 10, 9, 5, 4, 11,
			7, 6, 10, 5, 2, 2, 5, 4, 2, 4, 0, 7, 4, 8, 2, 11, 3, 10, 5, 6, -1,
			-1, -1, 4, 9, 5, 6, 10, 7, 7, 10, 1, 7, 1, 3, 5, 6, 10, 0, 9, 1, 8,
			7, 4, -1, -1, -1, 5, 6, 10, 7, 0, 3, 7, 4, 0, -1, -1, -1, 10, 5, 6,
			4, 8, 7, -1, -1, -1, -1, -1, -1, 5, 6, 9, 6, 11, 9, 9, 11, 8, -1,
			-1, -1, 0, 9, 5, 0, 5, 3, 3, 5, 6, 3, 6, 11, 0, 1, 5, 0, 5, 11, 5,
			6, 11, 0, 11, 8, 11, 3, 6, 6, 3, 5, 3, 1, 5, -1, -1, -1, 9, 5, 6, 3,
			9, 6, 3, 8, 9, 3, 6, 2, 5, 6, 9, 9, 6, 0, 6, 2, 0, -1, -1, -1, 0, 3,
			8, 2, 5, 6, 2, 1, 5, -1, -1, -1, 1, 6, 2, 1, 5, 6, -1, -1, -1, -1,
			-1, -1, 1, 2, 10, 5, 6, 9, 9, 6, 11, 9, 11, 8, 1, 0, 9, 6, 10, 5,
			11, 3, 2, -1, -1, -1, 6, 10, 5, 2, 8, 0, 2, 11, 8, -1, -1, -1, 3, 2,
			11, 10, 5, 6, -1, -1, -1, -1, -1, -1, 10, 5, 6, 9, 3, 8, 9, 1, 3,
			-1, -1, -1, 0, 9, 1, 5, 6, 10, -1, -1, -1, -1, -1, -1, 8, 0, 3, 10,
			5, 6, -1, -1, -1, -1, -1, -1, 10, 5, 6, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, 3, 0, 10,
			6, 5, -1, -1, -1, -1, -1, -1, 0, 1, 9, 5, 10, 6, -1, -1, -1, -1, -1,
			-1, 10, 6, 5, 9, 8, 3, 9, 3, 1, -1, -1, -1, 3, 11, 2, 10, 6, 5, -1,
			-1, -1, -1, -1, -1, 6, 5, 10, 2, 0, 8, 2, 8, 11, -1, -1, -1, 1, 9,
			0, 6, 5, 10, 11, 2, 3, -1, -1, -1, 1, 10, 2, 5, 9, 6, 9, 11, 6, 9,
			8, 11, 1, 2, 6, 1, 6, 5, -1, -1, -1, -1, -1, -1, 0, 8, 3, 2, 6, 5,
			2, 5, 1, -1, -1, -1, 5, 9, 6, 9, 0, 6, 6, 0, 2, -1, -1, -1, 9, 6, 5,
			3, 6, 9, 3, 9, 8, 3, 2, 6, 11, 6, 3, 6, 5, 3, 3, 5, 1, -1, -1, -1,
			0, 5, 1, 0, 11, 5, 5, 11, 6, 0, 8, 11, 0, 5, 9, 0, 3, 5, 3, 6, 5, 3,
			11, 6, 5, 9, 6, 6, 9, 11, 9, 8, 11, -1, -1, -1, 10, 6, 5, 4, 7, 8,
			-1, -1, -1, -1, -1, -1, 5, 10, 6, 7, 3, 0, 7, 0, 4, -1, -1, -1, 5,
			10, 6, 0, 1, 9, 8, 4, 7, -1, -1, -1, 4, 5, 9, 6, 7, 10, 7, 1, 10, 7,
			3, 1, 7, 8, 4, 2, 3, 11, 10, 6, 5, -1, -1, -1, 11, 6, 7, 10, 2, 5,
			2, 4, 5, 2, 0, 4, 11, 6, 7, 8, 0, 3, 1, 10, 2, 9, 4, 5, 6, 7, 11, 1,
			10, 2, 9, 4, 5, -1, -1, -1, 7, 8, 4, 5, 1, 2, 5, 2, 6, -1, -1, -1,
			4, 1, 0, 4, 5, 1, 6, 7, 3, 6, 3, 2, 9, 4, 5, 8, 0, 7, 0, 6, 7, 0, 2,
			6, 4, 5, 9, 6, 3, 2, 6, 7, 3, -1, -1, -1, 6, 7, 11, 4, 5, 8, 5, 3,
			8, 5, 1, 3, 6, 7, 11, 4, 1, 0, 4, 5, 1, -1, -1, -1, 4, 5, 9, 3, 8,
			0, 11, 6, 7, -1, -1, -1, 9, 4, 5, 7, 11, 6, -1, -1, -1, -1, -1, -1,
			10, 6, 4, 10, 4, 9, -1, -1, -1, -1, -1, -1, 8, 3, 0, 9, 10, 6, 9, 6,
			4, -1, -1, -1, 1, 10, 0, 10, 6, 0, 0, 6, 4, -1, -1, -1, 8, 6, 4, 8,
			1, 6, 6, 1, 10, 8, 3, 1, 2, 3, 11, 6, 4, 9, 6, 9, 10, -1, -1, -1, 0,
			10, 2, 0, 9, 10, 4, 8, 11, 4, 11, 6, 10, 2, 1, 11, 6, 3, 6, 0, 3, 6,
			4, 0, 10, 2, 1, 11, 4, 8, 11, 6, 4, -1, -1, -1, 9, 1, 4, 1, 2, 4, 4,
			2, 6, -1, -1, -1, 1, 0, 9, 3, 2, 8, 2, 4, 8, 2, 6, 4, 2, 4, 0, 2, 6,
			4, -1, -1, -1, -1, -1, -1, 3, 2, 8, 8, 2, 4, 2, 6, 4, -1, -1, -1, 1,
			4, 9, 11, 4, 1, 11, 1, 3, 11, 6, 4, 0, 9, 1, 4, 11, 6, 4, 8, 11, -1,
			-1, -1, 11, 6, 3, 3, 6, 0, 6, 4, 0, -1, -1, -1, 8, 6, 4, 8, 11, 6,
			-1, -1, -1, -1, -1, -1, 6, 7, 10, 7, 8, 10, 10, 8, 9, -1, -1, -1, 9,
			3, 0, 6, 3, 9, 6, 9, 10, 6, 7, 3, 6, 1, 10, 6, 7, 1, 7, 0, 1, 7, 8,
			0, 6, 7, 10, 10, 7, 1, 7, 3, 1, -1, -1, -1, 7, 11, 6, 3, 8, 2, 8,
			10, 2, 8, 9, 10, 11, 6, 7, 10, 0, 9, 10, 2, 0, -1, -1, -1, 2, 1, 10,
			7, 11, 6, 8, 0, 3, -1, -1, -1, 1, 10, 2, 6, 7, 11, -1, -1, -1, -1,
			-1, -1, 7, 2, 6, 7, 9, 2, 2, 9, 1, 7, 8, 9, 1, 0, 9, 3, 6, 7, 3, 2,
			6, -1, -1, -1, 8, 0, 7, 7, 0, 6, 0, 2, 6, -1, -1, -1, 2, 7, 3, 2, 6,
			7, -1, -1, -1, -1, -1, -1, 7, 11, 6, 3, 9, 1, 3, 8, 9, -1, -1, -1,
			9, 1, 0, 11, 6, 7, -1, -1, -1, -1, -1, -1, 0, 3, 8, 11, 6, 7, -1,
			-1, -1, -1, -1, -1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			11, 7, 5, 11, 5, 10, -1, -1, -1, -1, -1, -1, 3, 0, 8, 7, 5, 10, 7,
			10, 11, -1, -1, -1, 9, 0, 1, 10, 11, 7, 10, 7, 5, -1, -1, -1, 3, 1,
			9, 3, 9, 8, 7, 10, 11, 7, 5, 10, 10, 2, 5, 2, 3, 5, 5, 3, 7, -1, -1,
			-1, 5, 10, 2, 8, 5, 2, 8, 7, 5, 8, 2, 0, 9, 0, 1, 10, 2, 5, 5, 2, 3,
			5, 3, 7, 1, 10, 2, 5, 8, 7, 5, 9, 8, -1, -1, -1, 2, 11, 1, 11, 7, 1,
			1, 7, 5, -1, -1, -1, 0, 8, 3, 2, 11, 1, 1, 11, 7, 1, 7, 5, 9, 0, 2,
			9, 2, 7, 2, 11, 7, 9, 7, 5, 11, 3, 2, 8, 5, 9, 8, 7, 5, -1, -1, -1,
			1, 3, 7, 1, 7, 5, -1, -1, -1, -1, -1, -1, 8, 7, 0, 0, 7, 1, 7, 5, 1,
			-1, -1, -1, 0, 3, 9, 9, 3, 5, 3, 7, 5, -1, -1, -1, 9, 7, 5, 9, 8, 7,
			-1, -1, -1, -1, -1, -1, 4, 5, 8, 5, 10, 8, 8, 10, 11, -1, -1, -1, 3,
			0, 4, 3, 4, 10, 4, 5, 10, 3, 10, 11, 0, 1, 9, 4, 5, 8, 8, 5, 10, 8,
			10, 11, 5, 9, 4, 1, 11, 3, 1, 10, 11, -1, -1, -1, 3, 8, 4, 3, 4, 2,
			2, 4, 5, 2, 5, 10, 10, 2, 5, 5, 2, 4, 2, 0, 4, -1, -1, -1, 0, 3, 8,
			5, 9, 4, 10, 2, 1, -1, -1, -1, 2, 1, 10, 9, 4, 5, -1, -1, -1, -1,
			-1, -1, 8, 4, 5, 2, 8, 5, 2, 11, 8, 2, 5, 1, 3, 2, 11, 1, 4, 5, 1,
			0, 4, -1, -1, -1, 9, 4, 5, 8, 2, 11, 8, 0, 2, -1, -1, -1, 11, 3, 2,
			9, 4, 5, -1, -1, -1, -1, -1, -1, 4, 5, 8, 8, 5, 3, 5, 1, 3, -1, -1,
			-1, 5, 0, 4, 5, 1, 0, -1, -1, -1, -1, -1, -1, 3, 8, 0, 4, 5, 9, -1,
			-1, -1, -1, -1, -1, 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7,
			4, 11, 4, 9, 11, 11, 9, 10, -1, -1, -1, 3, 0, 8, 7, 4, 11, 11, 4, 9,
			11, 9, 10, 11, 7, 4, 1, 11, 4, 1, 10, 11, 1, 4, 0, 8, 7, 4, 11, 1,
			10, 11, 3, 1, -1, -1, -1, 2, 3, 7, 2, 7, 9, 7, 4, 9, 2, 9, 10, 4, 8,
			7, 0, 10, 2, 0, 9, 10, -1, -1, -1, 2, 1, 10, 0, 7, 4, 0, 3, 7, -1,
			-1, -1, 10, 2, 1, 8, 7, 4, -1, -1, -1, -1, -1, -1, 2, 11, 7, 2, 7,
			1, 1, 7, 4, 1, 4, 9, 3, 2, 11, 4, 8, 7, 9, 1, 0, -1, -1, -1, 7, 4,
			11, 11, 4, 2, 4, 0, 2, -1, -1, -1, 2, 11, 3, 7, 4, 8, -1, -1, -1,
			-1, -1, -1, 9, 1, 4, 4, 1, 7, 1, 3, 7, -1, -1, -1, 1, 0, 9, 8, 7, 4,
			-1, -1, -1, -1, -1, -1, 3, 4, 0, 3, 7, 4, -1, -1, -1, -1, -1, -1, 8,
			7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, 9, 10, 8, 10, 11, -1,
			-1, -1, -1, -1, -1, 0, 9, 3, 3, 9, 11, 9, 10, 11, -1, -1, -1, 1, 10,
			0, 0, 10, 8, 10, 11, 8, -1, -1, -1, 10, 3, 1, 10, 11, 3, -1, -1, -1,
			-1, -1, -1, 3, 8, 2, 2, 8, 10, 8, 9, 10, -1, -1, -1, 9, 2, 0, 9, 10,
			2, -1, -1, -1, -1, -1, -1, 8, 0, 3, 1, 10, 2, -1, -1, -1, -1, -1,
			-1, 10, 2, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, 11, 1, 1, 11,
			9, 11, 8, 9, -1, -1, -1, 11, 3, 2, 0, 9, 1, -1, -1, -1, -1, -1, -1,
			11, 0, 2, 11, 8, 0, -1, -1, -1, -1, -1, -1, 11, 3, 2, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, 8, 1, 3, 8, 9, 1, -1, -1, -1, -1, -1, -1, 9,
			1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, 0, 3, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

const static uint16_t edge[256] =
	{0, 265, 515, 778, 2060, 2309, 2575, 2822, 1030, 1295, 1541, 1804, 3082,
			3331, 3593, 3840, 400, 153, 915, 666, 2460, 2197, 2975, 2710, 1430,
			1183, 1941, 1692, 3482, 3219, 3993, 3728, 560, 825, 51, 314, 2620,
			2869, 2111, 2358, 1590, 1855, 1077, 1340, 3642, 3891, 3129, 3376,
			928, 681, 419, 170, 2988, 2725, 2479, 2214, 1958, 1711, 1445, 1196,
			4010, 3747, 3497, 3232, 2240, 2505, 2755, 3018, 204, 453, 719, 966,
			3270, 3535, 3781, 4044, 1226, 1475, 1737, 1984, 2384, 2137, 2899,
			2650, 348, 85, 863, 598, 3414, 3167, 3925, 3676, 1370, 1107, 1881,
			1616, 2800, 3065, 2291, 2554, 764, 1013, 255, 502, 3830, 4095, 3317,
			3580, 1786, 2035, 1273, 1520, 2912, 2665, 2403, 2154, 876, 613, 367,
			102, 3942, 3695, 3429, 3180, 1898, 1635, 1385, 1120, 1120, 1385,
			1635, 1898, 3180, 3429, 3695, 3942, 102, 367, 613, 876, 2154, 2403,
			2665, 2912, 1520, 1273, 2035, 1786, 3580, 3317, 4095, 3830, 502,
			255, 1013, 764, 2554, 2291, 3065, 2800, 1616, 1881, 1107, 1370,
			3676, 3925, 3167, 3414, 598, 863, 85, 348, 2650, 2899, 2137, 2384,
			1984, 1737, 1475, 1226, 4044, 3781, 3535, 3270, 966, 719, 453, 204,
			3018, 2755, 2505, 2240, 3232, 3497, 3747, 4010, 1196, 1445, 1711,
			1958, 2214, 2479, 2725, 2988, 170, 419, 681, 928, 3376, 3129, 3891,
			3642, 1340, 1077, 1855, 1590, 2358, 2111, 2869, 2620, 314, 51, 825,
			560, 3728, 3993, 3219, 3482, 1692, 1941, 1183, 1430, 2710, 2975,
			2197, 2460, 666, 915, 153, 400, 3840, 3593, 3331, 3082, 1804, 1541,
			1295, 1030, 2822, 2575, 2309, 2060, 778, 515, 265, 0};

const static int8_t cap[144] =
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, 7, 1, 0, -1, -1, -1, -1, -1, -1, 3, 2,
			1, -1, -1, -1, -1, -1, -1, 3, 2, 0, 7, 3, 0, -1, -1, -1, 5, 4, 3,
			-1, -1, -1, -1, -1, -1, 7, 1, 0, 5, 4, 3, -1, -1, -1, 5, 2, 1, 5, 4,
			2, -1, -1, -1, 0, 7, 2, 5, 4, 2, 7, 5, 2, 6, 5, 7, -1, -1, -1, -1,
			-1, -1, 6, 1, 0, 6, 5, 1, -1, -1, -1, 3, 2, 1, 7, 6, 5, -1, -1, -1,
			3, 2, 0, 5, 3, 0, 6, 5, 0, 4, 3, 7, 6, 4, 7, -1, -1, -1, 1, 0, 6, 3,
			1, 6, 4, 3, 6, 2, 1, 4, 1, 7, 4, 7, 6, 4, 4, 2, 0, 6, 4, 0, -1, -1,
			-1};

void Volume::CalcSurface(void)
{
//	setlocale(LC_ALL, "C"); // To get a 3.1415 instead 3,1415 or else on every computer.
//	wxTextFile temp(_T("~/octave/oneslice.m"));
//	if(!temp.Exists())
//		temp.Create();
//	else
//		temp.Open();
//	temp.Clear();
//	temp.AddLine(_T("M=[ ..."));

	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	geometry.Clear();
	if(buffer == NULL) return;
	Vector3 p(0, 0, 0);
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	Vector3 p3;
	Vector3 p4;
	Vector3 p5;
	Vector3 p6;
	Vector3 p7;
	Vector3 p8;
	Vector3 p9;
	Vector3 p10;
	Vector3 p11;
	Triangle t;
	unsigned int c = 0;
	for(size_t k = 0; k < Nz - 1; k++){
		for(size_t j = 0; j < Ny - 1; j++){
			for(size_t i = 0; i < Nx - 1; i++){
//				if(k == 60) temp.AddLine(
//						wxString::Format(_T("%.3f,..."), buffer[c]));

				const double v0 = buffer[c];
				const double v1 = buffer[c + 1];
				const double v2 = buffer[c + Nx];
				const double v3 = buffer[c + 1 + Nx];
				const double v4 = buffer[c + Nx * Ny];
				const double v5 = buffer[c + 1 + Nx * Ny];
				const double v6 = buffer[c + Nx * (1 + Ny)];
				const double v7 = buffer[c + 1 + Nx * (1 + Ny)];
				uint8_t v = 0;
				if(v0 > surface) v |= 1;
				if(v1 > surface) v |= 2;
				if(v2 > surface) v |= 4;
				if(v3 > surface) v |= 8;
				if(v4 > surface) v |= 16;
				if(v5 > surface) v |= 32;
				if(v6 > surface) v |= 64;
				if(v7 > surface) v |= 128;
				if(v != 0 && v != 255){

					uint16_t h = edge[v];
					if(h & ((uint16_t) 1 << 0)){
						const float x = (surface - v0) / (v1 - v0);
						p0.x = p.x;
						p0.y = p.y;
						p0.z = p.z;
						p0.x += dx * x;
					}
					if(h & ((uint16_t) 1 << 1)){
						const float x = (surface - v1) / (v3 - v1);
						p1.x = p.x + dx;
						p1.y = p.y;
						p1.z = p.z;
						p1.y += dy * x;
					}
					if(h & ((uint16_t) 1 << 2)){
						const float x = (surface - v2) / (v3 - v2);
						p2.x = p.x;
						p2.y = p.y + dy;
						p2.z = p.z;
						p2.x += dx * x;
					}
					if(h & ((uint16_t) 1 << 3)){
						const float x = (surface - v0) / (v2 - v0);
						p3.x = p.x;
						p3.y = p.y;
						p3.z = p.z;
						p3.y += dy * x;
					}
					if(h & ((uint16_t) 1 << 4)){
						const float x = (surface - v4) / (v5 - v4);
						p4.x = p.x;
						p4.y = p.y;
						p4.z = p.z + dz;
						p4.x += dx * x;
					}
					if(h & ((uint16_t) 1 << 5)){
						const float x = (surface - v5) / (v7 - v5);
						p5.x = p.x + dx;
						p5.y = p.y;
						p5.z = p.z + dz;
						p5.y += dy * x;
					}
					if(h & ((uint16_t) 1 << 6)){
						const float x = (surface - v6) / (v7 - v6);
						p6.x = p.x;
						p6.y = p.y + dy;
						p6.z = p.z + dz;
						p6.x += dx * x;
					}
					if(h & ((uint16_t) 1 << 7)){
						const float x = (surface - v4) / (v6 - v4);
						p7.x = p.x;
						p7.y = p.y;
						p7.z = p.z + dz;
						p7.y += dy * x;
					}
					if(h & ((uint16_t) 1 << 8)){
						const float x = (surface - v0) / (v4 - v0);
						p8.x = p.x;
						p8.y = p.y;
						p8.z = p.z;
						p8.z += dz * x;
					}
					if(h & ((uint16_t) 1 << 9)){
						const float x = (surface - v1) / (v5 - v1);
						p9.x = p.x + dx;
						p9.y = p.y;
						p9.z = p.z;
						p9.z += dz * x;
					}
					if(h & ((uint16_t) 1 << 10)){
						const float x = (surface - v3) / (v7 - v3);
						p10.x = p.x + dx;
						p10.y = p.y + dy;
						p10.z = p.z;
						p10.z += dz * x;
					}
					if(h & ((uint16_t) 1 << 11)){
						const float x = (surface - v2) / (v6 - v2);
						p11.x = p.x;
						p11.y = p.y + dy;
						p11.z = p.z;
						p11.z += dz * x;
					}

					uint16_t h2 = v * 12;
					for(uint_fast8_t n = 0; n < 12; n++){
						if(tri[h2] == -1) break;
						switch(tri[h2]){
						case 0:
							t.p[2 - (n % 3)] = p0;
							break;
						case 1:
							t.p[2 - (n % 3)] = p1;
							break;
						case 2:
							t.p[2 - (n % 3)] = p2;
							break;
						case 3:
							t.p[2 - (n % 3)] = p3;
							break;
						case 4:
							t.p[2 - (n % 3)] = p4;
							break;
						case 5:
							t.p[2 - (n % 3)] = p5;
							break;
						case 6:
							t.p[2 - (n % 3)] = p6;
							break;
						case 7:
							t.p[2 - (n % 3)] = p7;
							break;
						case 8:
							t.p[2 - (n % 3)] = p8;
							break;
						case 9:
							t.p[2 - (n % 3)] = p9;
							break;
						case 10:
							t.p[2 - (n % 3)] = p10;
							break;
						case 11:
							t.p[2 - (n % 3)] = p11;
							break;
						}

//					if(t.p[2 - (n % 3)].Abs() < 0.001){
//						break;
//					}

						if(n % 3 == 2) geometry.AddTriangle(t, false);
						h2++;
					}
				}

				if(i == 0){
					uint8_t v = 0;
					if(v0 > surface) v |= 1;
					if(v2 > surface) v |= 2;
					if(v6 > surface) v |= 4;
					if(v4 > surface) v |= 8;
					if(v > 0){
						uint8_t h = v * 9;
						for(uint_fast8_t n = 0; n < 9; n++){
							if(cap[h] == -1) break;
							switch(cap[h]){
							case 0:
								t.p[n % 3] = p;
								break;
							case 1:
								t.p[n % 3] = p3;
								break;
							case 2:
								t.p[n % 3].Set(p.x, p.y + dy, p.z);
								break;
							case 3:
								t.p[n % 3] = p11;
								break;
							case 4:
								t.p[n % 3].Set(p.x, p.y + dy, p.z + dz);
								break;
							case 5:
								t.p[n % 3] = p7;
								break;
							case 6:
								t.p[n % 3].Set(p.x, p.y, p.z + dz);
								break;
							case 7:
								t.p[n % 3] = p8;
								break;
							}
							if(n % 3 == 2) geometry.AddTriangle(t, false);
							h++;
						}

					}

				}

				if(i + 2 == Nx){
					uint8_t v = 0;
					if(v1 > surface) v |= 1;
					if(v5 > surface) v |= 2;
					if(v7 > surface) v |= 4;
					if(v3 > surface) v |= 8;
					if(v > 0){
						uint8_t h = v * 9;
						for(uint_fast8_t n = 0; n < 9; n++){
							if(cap[h] == -1) break;
							switch(cap[h]){
							case 0:
								t.p[n % 3].Set(p.x + dx, p.y, p.z);
								break;
							case 1:
								t.p[n % 3] = p9;
								break;
							case 2:
								t.p[n % 3].Set(p.x + dx, p.y, p.z + dz);
								break;
							case 3:
								t.p[n % 3] = p5;
								break;
							case 4:
								t.p[n % 3].Set(p.x + dx, p.y + dy, p.z + dz);
								break;
							case 5:
								t.p[n % 3] = p10;
								break;
							case 6:
								t.p[n % 3].Set(p.x + dx, p.y + dy, p.z);
								break;
							case 7:
								t.p[n % 3] = p1;
								break;
							}
							if(n % 3 == 2) geometry.AddTriangle(t, false);
							h++;
						}

					}

				}

				if(j == 0){
					uint8_t v = 0;
					if(v0 > surface) v |= 1;
					if(v4 > surface) v |= 2;
					if(v5 > surface) v |= 4;
					if(v1 > surface) v |= 8;
					if(v > 0){
						uint8_t h = v * 9;
						for(uint_fast8_t n = 0; n < 9; n++){
							if(cap[h] == -1) break;
							switch(cap[h]){
							case 0:
								t.p[n % 3] = p;
								break;
							case 1:
								t.p[n % 3] = p8;
								break;
							case 2:
								t.p[n % 3].Set(p.x, p.y, p.z + dz);
								break;
							case 3:
								t.p[n % 3] = p4;
								break;
							case 4:
								t.p[n % 3].Set(p.x + dx, p.y, p.z + dz);
								break;
							case 5:
								t.p[n % 3] = p9;
								break;
							case 6:
								t.p[n % 3].Set(p.x + dx, p.y, p.z);
								break;
							case 7:
								t.p[n % 3] = p0;
								break;
							}
							if(n % 3 == 2) geometry.AddTriangle(t, false);
							h++;
						}

					}

				}

				if(j + 2 == Ny){
					uint8_t v = 0;
					if(v2 > surface) v |= 1;
					if(v3 > surface) v |= 2;
					if(v7 > surface) v |= 4;
					if(v6 > surface) v |= 8;
					if(v > 0){
						uint8_t h = v * 9;
						for(uint_fast8_t n = 0; n < 9; n++){
							if(cap[h] == -1) break;
							switch(cap[h]){
							case 0:
								t.p[n % 3].Set(p.x, p.y + dy, p.z);
								break;
							case 1:
								t.p[n % 3] = p2;
								break;
							case 2:
								t.p[n % 3].Set(p.x + dx, p.y + dy, p.z);
								break;
							case 3:
								t.p[n % 3] = p10;
								break;
							case 4:
								t.p[n % 3].Set(p.x + dx, p.y + dy, p.z + dz);
								break;
							case 5:
								t.p[n % 3] = p6;
								break;
							case 6:
								t.p[n % 3].Set(p.x, p.y + dy, p.z + dz);
								break;
							case 7:
								t.p[n % 3] = p11;
								break;
							}
							if(n % 3 == 2) geometry.AddTriangle(t, false);
							h++;
						}

					}

				}

				if(k == 0){
					uint8_t v = 0;
					if(v0 > surface) v |= 1;
					if(v1 > surface) v |= 2;
					if(v3 > surface) v |= 4;
					if(v2 > surface) v |= 8;
					if(v > 0){
						uint8_t h = v * 9;
						for(uint_fast8_t n = 0; n < 9; n++){
							if(cap[h] == -1) break;
							switch(cap[h]){
							case 0:
								t.p[n % 3] = p;
								break;
							case 1:
								t.p[n % 3] = p0;
								break;
							case 2:
								t.p[n % 3].Set(p.x + dx, p.y, p.z);
								break;
							case 3:
								t.p[n % 3] = p1;
								break;
							case 4:
								t.p[n % 3].Set(p.x + dx, p.y + dy, p.z);
								break;
							case 5:
								t.p[n % 3] = p2;
								break;
							case 6:
								t.p[n % 3].Set(p.x, p.y + dy, p.z);
								break;
							case 7:
								t.p[n % 3] = p3;
								break;
							}
							if(n % 3 == 2) geometry.AddTriangle(t, false);
							h++;
						}

					}

				}

				if(k + 2 == Nz){
					uint8_t v = 0;
					if(v4 > surface) v |= 1;
					if(v6 > surface) v |= 2;
					if(v7 > surface) v |= 4;
					if(v5 > surface) v |= 8;
					if(v > 0){
						uint8_t h = v * 9;
						for(uint_fast8_t n = 0; n < 9; n++){
							if(cap[h] == -1) break;
							switch(cap[h]){
							case 0:
								t.p[n % 3].Set(p.x, p.y, p.z + dz);
								break;
							case 1:
								t.p[n % 3] = p7;
								break;
							case 2:
								t.p[n % 3].Set(p.x, p.y + dy, p.z + dz);
								break;
							case 3:
								t.p[n % 3] = p6;
								break;
							case 4:
								t.p[n % 3].Set(p.x + dx, p.y + dy, p.z + dz);
								break;
							case 5:
								t.p[n % 3] = p5;
								break;
							case 6:
								t.p[n % 3].Set(p.x + dx, p.y, p.z + dz);
								break;
							case 7:
								t.p[n % 3] = p4;
								break;
							}
							if(n % 3 == 2) geometry.AddTriangle(t, false);
							h++;
						}

					}

				}

				p.x += dx;
				c++;
			}
			c++;
			p.x = 0;
			p.y += dy;
		}
		c += Nx;
		p.y = 0;
		p.z += dz;
	}
//	for(n = 0; n < triangles.GetCount(); n++)
//		triangles[n].CalculateNormal();
//	temp.AddLine(_T("];"));
//	temp.AddLine(_T("M=reshape(M,149,[]);"));
//	temp.AddLine(_T("%M=M-min(min(M));"));
//	temp.AddLine(_T("%M=M/max(max(M));"));
//	temp.AddLine(
//			_T(
//					"[X,Y] = ndgrid(linspace(0,0.3,149)-0.075,linspace(0,0.2,99)-0.075);"));
//	temp.Write();
//	setlocale(LC_ALL, "");

}

void Volume::Paint(void) const
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	const uint_fast8_t NDim = ((Nx > 1)? 1 : 0) + ((Ny > 1)? 1 : 0)
			+ ((Nz > 1)? 1 : 0);

	glPushMatrix();
	glTranslatef(origin.x, origin.y, origin.z);
	glColor4f(color.x, color.y, color.z, 0.8);

	if(NDim == 2){
		switch(display2D){
		case Points2D:
			{
				glPointSize(2.0);
				glBegin(GL_POINTS);
				Vector3 p(0, 0, 0);
				unsigned int c = 0;
				for(size_t k = 0; k < Nz; k++){
					for(size_t j = 0; j < Ny; j++){
						for(size_t i = 0; i < Nx; i++){
							const double v0 = buffer[c];
							if(v0 > surface){
								glColor3f(v0 * 5, v0 * 5, v0 * 5);
								glVertex3f(p.x, p.y, p.z);
							}
							p.x += dx;
							c++;
						}
						p.x = 0;
						p.y += dy;
					}
					p.y = 0;
					p.z += dz;
				}
				glEnd();
				break;
			}
		case Grid:
			{
				glDisable(GL_CULL_FACE);
				glBegin(GL_QUADS);
				glColor3f(1, 1, 1);
				if(Ny == 1){
					for(size_t x = 0; x < (Nx - 1); x++){
						for(size_t z = 0; z < (Nz - 1); z++){
							const double v0 = MatlabMatrix::GetValue(x, 0, z);
							const double v1 = MatlabMatrix::GetValue(x, 0,
									z + 1);
							const double v2 = MatlabMatrix::GetValue(x + 1, 0,
									z + 1);
							const double v3 = MatlabMatrix::GetValue(x + 1, 0,
									z);
							if(v0 == DBL_MAX || v1 == DBL_MAX || v2 == DBL_MAX
									|| v3 == DBL_MAX) continue;
							glNormal3f(0, 0, 1);
							glVertex3f((x) * dx, v0, (z) * dz);
							glVertex3f((x) * dx, v3, (z + 1) * dz);
							glVertex3f((x + 1) * dx, v2, (z + 1) * dz);
							glVertex3f((x + 1) * dx, v1, (z) * dz);
						}
					}
				}
				if(Nz == 1){
					for(size_t x = 0; x < (Nx - 1); x++){
						for(size_t y = 0; y < (Ny - 1); y++){
							const double v0 = MatlabMatrix::GetValue(x, y, 0);
							const double v1 = MatlabMatrix::GetValue(x + 1, y,
									0);
							const double v2 = MatlabMatrix::GetValue(x + 1,
									y + 1, 0);
							const double v3 = MatlabMatrix::GetValue(x, y + 1,
									0);
							if(v0 == DBL_MAX || v1 == DBL_MAX || v2 == DBL_MAX
									|| v3 == DBL_MAX) continue;
							glNormal3f(0, 0, 1);
							glVertex3f((x) * dx, (y) * dy, v0);
							glVertex3f((x + 1) * dx, (y) * dy, v1);
							glVertex3f((x + 1) * dx, (y + 1) * dy, v2);
							glVertex3f((x) * dx, (y + 1) * dy, v3);
						}
					}
				}
				glEnd();
				glEnable(GL_CULL_FACE);
				break;
			}
		case Image:
			{
				const double min = this->Min();
				const double max = this->Max();
				const double a = (max != min)? (1 / (max - min)) : 1.0;
				const double b = -min * a;
				glNormal3f(0, 0, 1);
				glBegin(GL_QUADS);
				if(Ny == 1){
					for(size_t x = 0; x < (Nx - 1); x++){
						for(size_t z = 0; z < (Nz - 1); z++){
							const double v0 = MatlabMatrix::GetValue(x, 0, z);
							const double v1 = MatlabMatrix::GetValue(x, 0,
									z + 1);
							const double v2 = MatlabMatrix::GetValue(x + 1, 0,
									z + 1);
							const double v3 = MatlabMatrix::GetValue(x + 1, 0,
									z);
							if(v0 == DBL_MAX || v1 == DBL_MAX || v2 == DBL_MAX
									|| v3 == DBL_MAX) continue;
							const double c0 = a * v0 + b;
							const double c1 = a * v1 + b;
							const double c2 = a * v2 + b;
							const double c3 = a * v3 + b;
							glNormal3f(0, 0, 1);
							glColor3d(c0, c0, c0);
							glVertex3f((x) * dx, 0, (z) * dz);
							glColor3d(c1, c1, c1);
							glVertex3f((x) * dx, 0, (z + 1) * dz);
							glColor3d(c2, c2, c2);
							glVertex3f((x + 1) * dx, 0, (z + 1) * dz);
							glColor3d(c3, c3, c3);
							glVertex3f((x + 1) * dx, 0, (z) * dz);
						}
					}
				}
				if(Nz == 1){
					for(size_t x = 0; x < (Nx - 1); x++){
						for(size_t y = 0; y < (Ny - 1); y++){
							const double v0 = MatlabMatrix::GetValue(x, y, 0);
							const double v1 = MatlabMatrix::GetValue(x + 1, y,
									0);
							const double v2 = MatlabMatrix::GetValue(x + 1,
									y + 1, 0);
							const double v3 = MatlabMatrix::GetValue(x, y + 1,
									0);
							if(v0 == DBL_MAX || v1 == DBL_MAX || v2 == DBL_MAX
									|| v3 == DBL_MAX) continue;
							const double c0 = a * v0 + b;
							const double c1 = a * v1 + b;
							const double c2 = a * v2 + b;
							const double c3 = a * v3 + b;
							glColor3d(c0, c0, c0);
							glVertex3f((x) * dx, (y) * dy, 0);
							glColor3d(c1, c1, c1);
							glVertex3f((x + 1) * dx, (y) * dy, 0);
							glColor3d(c2, c2, c2);
							glVertex3f((x + 1) * dx, (y + 1) * dy, 0);
							glColor3d(c3, c3, c3);
							glVertex3f((x) * dx, (y + 1) * dy, 0);
						}
					}
				}
				glEnd();
				break;
			}
		}
	}

	if(NDim == 3){
		switch(display3D){
		case MarchingCubes:
			{
				geometry.Paint(geometryColorNone);
				break;
			}
		case Points3D:
			{
				glPointSize(2.0);
				glBegin(GL_POINTS);
				Vector3 p(0, 0, 0);
				unsigned int c = 0;
				for(size_t k = 0; k < Nz; k++){
					for(size_t j = 0; j < Ny; j++){
						for(size_t i = 0; i < Nx; i++){
							const double v0 = buffer[c];
							if(v0 > surface){
								glColor3f(v0 * 5, v0 * 5, v0 * 5);
								glVertex3f(p.x, p.y, p.z);
							}
							p.x += dx;
							c++;
						}
						p.x = 0;
						p.y += dy;
					}
					p.y = 0;
					p.z += dz;
				}
				glEnd();
				break;
			}
		}
	}

	glPopMatrix();
}

double Volume::GetValue(Vector3 p) const
{
	return GetValue(p.x, p.y, p.z);
}

double Volume::GetValue(double x, double y, double z) const
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);
	const double hx = (x - origin.x) / dx;
	const double hy = (y - origin.y) / dy;
	const double hz = (z - origin.z) / dz;
	const double px = floor(hx);
	const double py = floor(hy);
	const double pz = floor(hz);
	const double mx = hx - px;
	const double my = hy - py;
	const double mz = hz - pz;
	const int ix = (int) px;
	const int iy = (int) py;
	const int iz = (int) pz;
	if(ix < 0 || iy < 0 || iz < 0 || ix + 2 > Nx || iy + 2 > Ny || iz + 2 > Nz) return 0.0;
	const int pos = ix + (iy + iz * Ny) * Nx;
	double v = 0.0;
	v += buffer[pos] * (1 - mx) * (1 - my) * (1 - mz);
	v += buffer[pos + 1] * (mx) * (1 - my) * (1 - mz);
	v += buffer[pos + Nx] * (1 - mx) * (my) * (1 - mz);
	v += buffer[pos + 1 + Nx] * (mx) * (my) * (1 - mz);
	v += buffer[pos + Nx * Ny] * (1 - mx) * (1 - my) * (mz);
	v += buffer[pos + 1 + Nx * Ny] * (mx) * (1 - my) * (mz);
	v += buffer[pos + Nx + Nx * Ny] * (1 - mx) * (my) * (mz);
	v += buffer[pos + 1 + Nx + Nx * Ny] * (mx) * (my) * (mz);
	return v;
}

Vector3 Volume::GetSurface(Vector3 p0, Vector3 n) const
{
	double d0 = 0;
	double d1 = 1;
	double d = 0.5;
	for(uint_fast8_t c = 0; c < 50; c++){
		const double v0 = GetValue(p0 + n * d0);
		const double v1 = GetValue(p0 + n * d1);
		if(fabs(v0 - v1) < 1e-5) break;
		d = (d0 * v1 - d1 * v0 + (d1 - d0) * surface) / (v1 - v0);
		const double v = GetValue(p0 + n * d);
		if(fabs(v - surface) < 1e-5) break;
		if(v > surface){
			d0 = d;
		}else{
			d1 = d;
		}
	}
	return (p0 + n * d);
}

Vector3 Volume::GetGrad(Vector3 p) const
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);
	const double hx = (p.x - origin.x) / dx;
	const double hy = (p.y - origin.y) / dy;
	const double hz = (p.z - origin.z) / dz;
	const double px = floor(hx);
	const double py = floor(hy);
	const double pz = floor(hz);
	const double mx = hx - px;
	const double my = hy - py;
	const double mz = hz - pz;
	const int ix = (int) px;
	const int iy = (int) py;
	const int iz = (int) pz;

	Vector3 temp;
	if(ix < 0 || iy < 0 || iz < 0 || ix + 2 > Nx || iy + 2 > Ny || iz + 2 > Nz) return temp;
	const size_t pos = ix + (iy + iz * Ny) * Nx;
	const double v0 = buffer[pos];
	const double v1 = buffer[pos + 1];
	const double v2 = buffer[pos + Nx];
	const double v3 = buffer[pos + 1 + Nx];
	const double v4 = buffer[pos + Nx * Ny];
	const double v5 = buffer[pos + 1 + Nx * Ny];
	const double v6 = buffer[pos + Nx + Nx * Ny];
	const double v7 = buffer[pos + 1 + Nx + Nx * Ny];

	//  Maxima:
	//  v(x,y,z):= v0*(1-x)*(1-y)*(1-z)+v1*x*(1-y)*(1-z)+v2*(1-x)*y*(1-z)+v3*x*y*(1-z)+v4*(1-x)*(1-y)*z+v5*x*(1-y)*z+v6*(1-x)*y*z+v7*x*y*z;
	//	diff(v(x,y,z),x);
	//	diff(v(x,y,z),y);
	//	diff(v(x,y,z),z);

	temp.x = v7 * my * mz - v6 * my * mz + v5 * (1 - my) * mz
			- v4 * (1 - my) * mz + v3 * my * (1 - mz) - v2 * my * (1 - mz)
			+ v1 * (1 - my) * (1 - mz) - v0 * (1 - my) * (1 - mz);
	temp.y = v7 * mx * mz - v5 * mx * mz + v6 * (1 - mx) * mz
			- v4 * (1 - mx) * mz + v3 * mx * (1 - mz) - v1 * mx * (1 - mz)
			+ v2 * (1 - mx) * (1 - mz) - v0 * (1 - mx) * (1 - mz);
	temp.z = v7 * mx * my - v3 * mx * my + v6 * (1 - mx) * my
			- v2 * (1 - mx) * my + v5 * mx * (1 - my) - v1 * mx * (1 - my)
			+ v4 * (1 - mx) * (1 - my) - v0 * (1 - mx) * (1 - my);

	return temp;
}

void Volume::Rotate(Axis a, int quarters)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	quarters %= 4;
	if(quarters < 0) quarters += 4;
	if(quarters == 0) return;
	if(quarters == 2){
		switch(a){
		case X:
			for(size_t i = 0; i < Nx; i++){
				for(size_t n = i; n < (size / 2); n += Nx){
					std::swap(buffer[n], buffer[(size - Nx) - n + 2 * i]);
				}
			}
			break;
		case Y:
			for(size_t j = 0; j < Ny; j++){
				size_t n = j * Nx;
				size_t m = size - 1 - (Ny - 1) * Nx + j * Nx;
				for(size_t k = 0; k < (Nx * Nz / 2); k++){
					std::swap(buffer[n], buffer[m]);
					n = (n + Nx * Ny) % (size - 1);
					m = (m + (size - Nx * Ny - 1)) % (size - 1);
				}
			}
			break;
		case Z:
			const size_t m = Nx * Ny;
			for(size_t k = 0; k < Nz; k++){
				for(size_t n = 0; n < (m / 2); n++){
					std::swap(buffer[k * Nx * Ny + n],
							buffer[k * Nx * Ny + (m - n - 1)]);
				}
			}
			break;
		}
		return;
	}
	assert(quarters == 1 || quarters == 3);
	double* temp = new double[size];
	if(temp == NULL) throw("Out of memory!");

	switch(a){
	case X:
		{
			if(quarters == 1){
				const size_t mo = size + Nx;
				const size_t ad = size - (Nx * (Ny - 1));
				for(size_t i = 0; i < Nx; i++){
					size_t m = size - Ny * Nx + i;
					for(size_t n = 0; n < (Ny * Nz); n++){
						temp[n * Nx + i] = buffer[m];
						m = (m + ad) % mo;
					}
				}
			}
			if(quarters == 3){
				const size_t mo = size + Nx;
				const size_t ad = Nx * Ny;
				for(size_t i = 0; i < Nx; i++){
					size_t m = (Ny - 1) * Nx + i;
					for(size_t n = 0; n < (Ny * Nz); n++){
						temp[n * Nx + i] = buffer[m];
						m = (m + ad) % mo;
					}
				}
			}

//		std::swap(Ny, Nz);
			MatlabMatrix::Reshape(Nx, Nz, Ny);
			std::swap(dy, dz);
			break;
		}
	case Y:
		{
			if(quarters == 1){
//			Nx = 4;
//			Ny = 5;
//			Nz = 5;
//			size = Nx * Ny * Nz;
				size_t n = 0;
				size_t m = Nx - 1;
				for(size_t i = 0; i < Nx; i++){
					for(size_t j = 0; j < Ny; j++){
						for(size_t k = 0; k < Nz; k++){
							temp[n] = buffer[m];
							n++;
							m += Nx * Ny;
						}
						m = m + Nx - size;
					}
					m = m - Nx * Ny - 1;
				}
			}
			if(quarters == 3){
				size_t n = 0;
				size_t m = size;
				for(size_t i = 0; i < Nx; i++){
					for(size_t j = 0; j < Ny; j++){
						for(size_t k = 0; k < Nz; k++){
							m -= Nx * Ny;
							temp[n] = buffer[m];
							n++;
						}
						m = m + size + Nx;
					}
					m = m - Nx * Ny + 1;
				}
			}
			MatlabMatrix::Reshape(Nz, Ny, Nx);
//		std::swap(Nz, Nx);
			std::swap(dz, dx);
			break;
		}
	case Z:
		{
			const size_t mo = Nx * Ny + 1;
			size_t ad;
			if(quarters == 1) ad = Nx * (Ny - 1) + 1;
			if(quarters == 3) ad = Nx;
			for(size_t k = 0; k < Nz; k++){
				size_t n = 0;
				for(size_t m = ad - 1; m != mo - 1; m = (m + ad) % mo){
					temp[n + k * Nx * Ny] = buffer[m + k * Nx * Ny];
					n++;
				}
			}
//		std::swap(Nx, Ny);
			MatlabMatrix::Reshape(Ny, Nx, Nz);
			std::swap(dx, dy);
			break;
		}
	}

	delete[] buffer;
	buffer = temp;
}

void Volume::Mirror(Axis a)
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	switch(a){
	case X:
		for(size_t i = 0; i < (Nx / 2); i++){
			for(size_t j = 0; j < Ny; j++){
				for(size_t k = 0; k < Nz; k++){
					const size_t n = i + Nx * (j + Ny * k);
					const size_t m = (Nx - i - 1) + Nx * (j + Ny * k);
					std::swap(buffer[n], buffer[m]);
				}
			}
		}
		break;
	case Y:
		for(size_t i = 0; i < Nx; i++){
			for(size_t j = 0; j < (Ny / 2); j++){
				for(size_t k = 0; k < Nz; k++){
					const size_t n = i + Nx * (j + Ny * k);
					const size_t m = i + Nx * ((Ny - j - 1) + Ny * k);
					std::swap(buffer[n], buffer[m]);
				}
			}
		}
		break;
	case Z:
		for(size_t i = 0; i < Nx; i++){
			for(size_t j = 0; j < Ny; j++){
				for(size_t k = 0; k < (Nz / 2); k++){
					const size_t n = i + Nx * (j + Ny * k);
					const size_t m = i + Nx * (j + Ny * (Nz - k - 1));
					std::swap(buffer[n], buffer[m]);
				}
			}
		}
		break;
	}
}

Volume Volume::SurfaceField(void) const
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	Volume temp;
	temp.SetCount(Nx, Ny, 1, dx);
	temp.SetOrigin(Vector3(origin.x, origin.y, origin.z));
	temp.SetInsertPosition(0);
	const size_t h = Nx * Ny;
	for(size_t i = 0; i < h; i++){
		double v0 = buffer[i];
		size_t j = i;
		double v = DBL_MAX;
		for(size_t k = 1; k < Nz; k++){
			j += h;
			if(buffer[j] > 0.5){
				if(v0 > 0.5){
					v = (double) (k - 1) * dz;
				}else{
					const double c = fmin(
							fmax((0.5 - v0) / (buffer[j] - v0), 0), 1);
					v = ((double) (k - 1) + c) * dz;
				}
				break;
			}
			v0 = buffer[j];
		}
		temp.Insert(v);
	}
	return temp;
}

Volume Volume::XRay(Method method) const
{
	const size_t Nx = Size(1);
	const size_t Ny = Size(2);
	const size_t Nz = Size(3);

	Volume temp;
	temp.SetCount(Nx, 1, Nz, dx);
	temp.SetOrigin(Vector3(origin.x, origin.y, origin.z));
	temp.SetInsertPosition(0);
	for(size_t z = 0; z < Nz; z++){
		for(size_t x = 0; x < Nx; x++){
			switch(method){
			case MaxValue:
				{
					double vm = -DBL_MAX;
					for(size_t y = 0; y < Ny; y++){
						const double v = MatlabMatrix::GetValue(x, y, z);
						if(v > vm) vm = v;
					}
					temp.Insert(vm);
					break;
				}
			case MinValue:
				{
					double vm = DBL_MAX;
					for(size_t y = 0; y < Ny; y++){
						const double v = MatlabMatrix::GetValue(x, y, z);
						if(v < vm) vm = v;
					}
					temp.Insert(vm);
					break;
				}
			case MeanValue:
				{
					double vm = 0;
					for(size_t y = 0; y < Ny; y++){
						const double v = MatlabMatrix::GetValue(x, y, z);
						vm += v;
					}
					temp.Insert(vm / (double) Ny);
					break;
				}
			case Sum:
				{
					double vm = 0;
					for(size_t y = 0; y < Ny; y++){
						const double v = MatlabMatrix::GetValue(x, y, z);
						vm += v;
					}
					temp.Insert(vm);
					break;
					break;
				}
			}
		}
	}
	return temp;
}

Polygon3 Volume::ToPolygon(void) const
{
	Polygon3 temp;
	// TODO: Conversion to Polygon
	return temp;
}

double Volume::Min(void) const
{
	double m = DBL_MAX;
	for(size_t n = 0; n < size; n++){
		const double v = buffer[n];
		if(v == DBL_MAX || v == -DBL_MAX) continue;
		m = fmin(m, v);
	}
	return m;
}

double Volume::Max(void) const
{
	double m = -DBL_MAX;
	for(size_t n = 0; n < size; n++){
		const double v = buffer[n];
		if(v == DBL_MAX || v == -DBL_MAX) continue;
		m = fmax(m, v);
	}
	return m;
}

double Volume::MaxAbs(void) const
{
	double v = -DBL_MAX;
	for(size_t n = 0; n < size; n++)
		v = fmax(v, fabs(buffer[n]));
	return v;
}

void Volume::AlignAtZero(void)
{
	const double m = this->Min();
	for(size_t n = 0; n < size; n++)
		buffer[n] -= m;
}

void Volume::Normalize(double max)
{
	double m = this->MaxAbs();
	if(m == 0.0) return;
	m = max / m;
	for(size_t n = 0; n < size; n++)
		buffer[n] *= m;
}

void Volume::Normalize(double min, double max)
{
	if(max == min){
		memset(buffer, 0, sizeof(double) * size);
		return;
	}
	this->AlignAtZero();
	double m = this->Max();
	if(m == 0.0) return;
	m = (max - min) / m;
	for(size_t n = 0; n < size; n++){
		buffer[n] *= m;
		buffer[n] += min;
	}
}
