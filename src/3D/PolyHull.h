///////////////////////////////////////////////////////////////////////////////
// Name               : PolyHull.h
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

#ifndef POLYHULL_H_
#define POLYHULL_H_

/*!\class PolyHull
 * \brief ...
 *
 * ...
 */

#include "Spline3.h"
#include <vector>

class PolyHull {
public:

	class Level:public Spline3 {
	public:
		Level();
	};

	PolyHull();
	virtual ~PolyHull();

	std::vector <Level> levels;

	void Paint(void) const;
};

#endif /* POLYHULL_H_ */
