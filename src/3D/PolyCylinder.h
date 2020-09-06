///////////////////////////////////////////////////////////////////////////////
// Name               : PolyCylinder.h
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

#ifndef SRC_PROJECT_LAST_POLYCYLINDER_H_
#define SRC_PROJECT_LAST_POLYCYLINDER_H_

/*!\class PolyCylinder
 * \brief DEPRECATED: Stores sections of polygonwise defined shapes
 *
 * Useless file format, that should not be used. Use stl instead.
 * Was a good idea back then, but it is easier to model a last based
 * on some imaged from the internet in Blender from scratch.
 *
 * Maybe there is some last-scanning system the produces a format that can be
 * interpreted by this class...
 */

#include <string>
#include <vector>

#include "Geometry.h"
#include "Vector3.h"
#include "../math/Polynom.h"

class PolyCylinder {
public:
	class CircleSection {
	public:
		class Segment {
		public:
			Polynom y0;
			Polynom z0;
			Polynom y;
			Polynom z;
			Polynom dy;
			Polynom dz;
			Segment();
			void Scale(double sy = 1.0, double sz = 1.0);
			void Paint(void) const;
			double GetLength(void) const;
		};
		std::vector <Segment> segments;
		CircleSection();
		void Scale(double sy = 1.0, double sz = 1.0);
		Vector3 Evaluate(double r);
		double GetLength(void) const;
		void Paint(void) const;
	};
	std::vector <CircleSection> sections;
	double dx;
	PolyCylinder();

	void Scale(double sx, double sy = 1.0, double sz = 1.0);

	bool Load(std::string filename);

	void Paint(void) const;
	void GenerateGeometry(Geometry &geometry, bool mirrored = false);
	// TODO: Write this function, if this class is really used.
	// void GenerateHull(Hull &hull, bool mirrored = false);
	void Test(void);
};

#endif /* SRC_PROJECT_LAST_POLYCYLINDER_H_ */
