///////////////////////////////////////////////////////////////////////////////
// Name               : Bone.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.08.2015
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

#ifndef BONE_H_
#define BONE_H_
#include "Linkage.h"

/*!\class Bone
 * \brief ...
 *
 * ...
 */

class Bone:public Linkage {
public:
	Bone();
	virtual ~Bone();

	Vector3 p1;
	Vector3 p2;
	float r1;
	float r2;

	void Render(void) const;

private:
	void Normal(const Vector3 v) const;
	void Vertex(const Vector3 v) const;
};

#endif /* BONE_H_ */
