///////////////////////////////////////////////////////////////////////////////
// Name               : TestGrid.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 02.06.2020
// Copyright          : (C) 2020 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_3D_TESTGRID_H_
#define SRC_3D_TESTGRID_H_

/*!\class TestGrid
 * \brief ...
 *
 * ...
 */

#include "BoundingBox.h"
#include "Vector3.h"
#include <vector>

class TestGrid:public BoundingBox {
public:
	TestGrid() = default;
	TestGrid(const Vector3 & v1, const Vector3 & v2);
	virtual ~TestGrid() = default;

	void SetCellSize(double d);
	void Reset(void);
	void PaintPoints(void) const;
	void PaintLines(void) const;

	std::vector <Vector3> p;
	size_t U = 0;
	size_t V = 0;
	size_t W = 0;
	double d = 0.0;
};

#endif /* SRC_3D_TESTGRID_H_ */
