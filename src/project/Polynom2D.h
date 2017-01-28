///////////////////////////////////////////////////////////////////////////////
// Name               : Polynom2D.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 23.01.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef POLYNOM2D_H_
#define POLYNOM2D_H_

/*!\class Polynom2D
 * \brief ...
 *
 * ...
 */

#include <cstdbool>
#include <vector>

class Polynom2D {
private:
	class Point {
	public:
		Point();
		double x;
		double y;
		bool corner;
	};
	class Polynom{
		double a0;
		double a1;
		double a2;
		double a3;
	};



	std::vector <Point> points;
	bool closed;

public:
	Polynom2D();
	virtual ~Polynom2D();

	void Paint(void) const;
};

#endif /* POLYNOM2D_H_ */
