///////////////////////////////////////////////////////////////////////////////
// Name               : VisitorSetupBone.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.10.2015
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

#ifndef VISITORSETUPBONE_H_
#define VISITORSETUPBONE_H_

#include "../3D/LinkageVisitor.h"
#include "Bone.h"

/*!\class VisitorSetupBone
 * \brief Setup all bones
 *
 * eValuate the formulas and set up the bones.
 */

#include "../gui/MathParser.h"

class VisitorSetupBone:public LinkageVisitor {
public:
	VisitorSetupBone();
	virtual ~VisitorSetupBone();

	MathParser parser; ///< The mathparser stores the configuration.

	void Visit(Bone &bone);
};

#endif /* VISITORSETUPBONE_H_ */