///////////////////////////////////////////////////////////////////////////////
// Name               : HeightField.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 23.03.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef HEIGHTFIELD_H_
#define HEIGHTFIELD_H_

/*!\class HeightField
 * \brief Planar 2.5D heightfield
 *
 * Grid of points with a height. This class provides some operations to generate some Polygon3 objects from it.
 */

#include "AffineTransformMatrix.h"
#include "Vector3.h"

class HeightField {
public:
	HeightField();
	virtual ~HeightField();

	void SetCount(unsigned int nx, unsigned int ny, float resolution);
	void SetSize(float x, float y, float resolution);

	void SetValues(double *v, unsigned int size);

	void Clear(void);

	void Paint(void) const;

	AffineTransformMatrix matrix;
	Vector3 color;

private:

	double * value;

	unsigned int Nx;
	unsigned int Ny;
	unsigned int N;
	float dx;
	float dy;
};

#endif /* HEIGHTFIELD_H_ */
