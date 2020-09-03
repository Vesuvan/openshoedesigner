///////////////////////////////////////////////////////////////////////////////
// Name               : Last.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 10.06.2017
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

#ifndef LAST_H_
#define LAST_H_

/*!\class Last
 * \brief Last (coordinate system)
 *
 * The last is described as a cylindical coordinate system. All modelling takes place in this
 * Coordinate system.
 *
 * The mapping is from U,V,W into X,Y,Z of the normal carthesian 3D space.
 *
 */

#include "../../3D/Surface.h"

class FootModel;
class LastModel;

class Last {
public:
	Last();

	bool IsModified(void) const;
	void Modify(bool modified = true);
	bool modified;

	void Setup(const LastModel & model);
	void Setup(const FootModel & model);

	void Paint(void) const;

	Surface surface;

};

#endif /* LAST_H_ */
