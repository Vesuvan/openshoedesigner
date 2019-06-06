///////////////////////////////////////////////////////////////////////////////
// Name               : CoordSys.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.05.2019
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

#ifndef SRC_3D_COORDSYS_H_
#define SRC_3D_COORDSYS_H_
#include "Vector3.h"

/*!\class CoordSys
 * \brief Coordinate system in 3D space
 *
 * Class for keeping track of a coordinate system and mapping Vector3%s into it.
 */

class CoordSys {
public:
	enum orientation {
		rhs, ///< Right handed side system
		lsh  ///< Left handed side system
	} side;

public:
	CoordSys();
	virtual ~CoordSys();

	void SetOrientation(orientation side);

	void SetCenter(const Vector3 & center);
	void SetX(const Vector3 &x);
	void SetY(const Vector3 &y);
	void SetZ(const Vector3 &z);

	void RecalculateX(void);
	void RecalculateY(void);
	void RecalculateZ(void);

	double GetLocalX(const Vector3 &vec) const;
	double GetLocalY(const Vector3 &vec) const;
	double GetLocalZ(const Vector3 &vec) const;

	Vector3 GetGlobal(double x, double y = 0.0, double z = 0.0) const;

public:
	Vector3 center;
	Vector3 ex;
	Vector3 ey;
	Vector3 ez;

private:
	enum {
		none, xWasSet, yWasSet, zWasSet
	} lastSet;
};

#endif /* SRC_3D_COORDSYS_H_ */
