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

#include <GL/gl.h>

#include <wx/wx.h>

Volume::Volume()
{
	dx = 1.0;
	dy = 1.0;
	dz = 1.0;
	Nx = 0;
	Ny = 0;
	Nz = 0;
	N = 0;
	value = NULL;
}

Volume::~Volume()
{
	if(value != NULL) delete[] value;
}

void Volume::SetCount(unsigned int nx, unsigned int ny, unsigned int nz,
		float resolution)
{
	if(value != NULL) delete[] value;
	this->Nx = nx;
	this->Ny = ny;
	this->Nz = nz;
	this->N = nx * ny * nz;
	value = new float[this->N];
	dx = resolution;
	dy = resolution;
	dz = resolution;
	Clear();
}

void Volume::SetSize(float x, float y, float z, float resolution)
{
	if(value != NULL) delete[] value;
	Nx = (unsigned int) ceil(x / resolution);
	Ny = (unsigned int) ceil(y / resolution);
	Nz = (unsigned int) ceil(z / resolution);
	this->N = Nx * Ny * Nz;
	value = new float[this->N];
	dx = resolution;
	dy = resolution;
	dz = resolution;
	Clear();
}

void Volume::Clear(void)
{
	if(value == NULL) return;
	unsigned int i;
	for(i = 0; i < N; i++)
		value[i] = 0.0;
}

void Volume::Render(void)
{
	if(value == NULL) return;

	glPushMatrix();
	glMultMatrixd(matrix.a);
	glColor3f(color.x, color.y, color.z);

	unsigned i, j, k, p;

	glPointSize(2.0);
	glBegin(GL_POINTS);

	for(k = 0; k < Nz; k++){
		for(j = 0; j < Ny; j++){
			for(i = 0; i < Nx; i++){

				glVertex3f((float) i * dx, (float) j * dy, (float) k * dz);

				p++;
			}
		}
	}
	glEnd();
	glPopMatrix();
}
