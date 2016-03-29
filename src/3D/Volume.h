///////////////////////////////////////////////////////////////////////////////
// Name               : Volume.h
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

#ifndef VOLUME_H_
#define VOLUME_H_

#include "HeightField.h"
#include "AffineTransformMatrix.h"
#include "Geometry.h"
#include "Vector3.h"

/*!\class Volume
 * \brief Marching Cube Volume
 *
 * Sets up a density map by using morph-objects.
 * Applies the marching cubes algorithm to convert the density map into a surface.
 */

class Volume {
public:
	Volume();
	//TODO: Add copy constructor, becaus it has a pointer.
	virtual ~Volume();
	void SetOrigin(Vector3 origin);
	void SetCount(unsigned int nx, unsigned int ny, unsigned int nz,
			float resolution);
	void SetSize(float x, float y, float z, float resolution);

	void Clear(void);

	void AddHalfplane(const Vector3 &p1, float d0, float k0);
	void AddSphere(const Vector3 &p1, float r1, float k1);
	void AddCylinder(const Vector3 &p1, const Vector3 &p2, const float r1,
			const float k1);
	void AddCylinder(const Vector3 &p1, const Vector3 &p2, const float r1,
			const float r2, const float k1);
	void AddCylinder(const Vector3 &p1, const Vector3 &p2, const float r1,
			const float r2, const float k1, const float k2);

	void MarchingCubes(void);
	void Paint(void) const;
	double GetValue(Vector3 p) const;
	double GetValue(double x, double y, double z) const;
	void FillHeightField(HeightField *heightfield) const;
	Vector3 GetSurface(Vector3 p0, Vector3 n);

	Vector3 color;
	Geometry geometry;
private:

	double surface;

	Vector3 origin;

	double * value;

	unsigned int Nx;
	unsigned int Ny;
	unsigned int Nz;
	unsigned int N;
	float dx;
	float dy;
	float dz;
};

#endif /* VOLUME_H_ */
