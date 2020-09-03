///////////////////////////////////////////////////////////////////////////////
// Name               : Insole.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.09.2020
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

#ifndef SRC_PROJECT_INSOLE_H_
#define SRC_PROJECT_INSOLE_H_

/*!\class Insole
 * \brief ...
 *
 * ...
 */

#include "../3D/Vector3.h"
#include "../math/Polynom.h"

class FootMeasurements;
class Shoe;

class Insole {
public:
	void Construct(const Shoe & shoe, const FootMeasurements & measurements);
	void Paint(void) const;

	bool IsModified(void) const;
	void Modify(bool modify = true);

private:
	struct Point {
	public:
		Vector3 p;
		Vector3 n;
		void SetNormal(const Point & p0, const Point & p1);
	};
	struct Line {
	public:
		// Bezier-Circle: sqrt(2) * f = 0.551915024494 --> f = 0.39
		void Setup(const Point & p0, const Point & p1, double f0 = 0.39,
				double f1 = 0.39);
		void Paint(void) const;
		Polynom x;
		Polynom y;
		Polynom z;
	};

	std::vector <Line> inside;
	std::vector <Line> outside;

private:
	bool modified = true;
};

#endif /* SRC_PROJECT_INSOLE_H_ */
