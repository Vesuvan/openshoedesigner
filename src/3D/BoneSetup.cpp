///////////////////////////////////////////////////////////////////////////////
// Name               : BoneSetup.cpp
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

#include "BoneSetup.h"

BoneSetup::BoneSetup()
{
}

BoneSetup::~BoneSetup()
{
}

void BoneSetup::Visit(Bone& bone)
{
	bone.anchorN.x = parser.GetNumber(bone.anchorNx);
	bone.anchorN.y = parser.GetNumber(bone.anchorNy);
	bone.anchorN.z = parser.GetNumber(bone.anchorNz);
	bone.link.x = parser.GetNumber(bone.linkx);
	bone.link.y = parser.GetNumber(bone.linky);
	bone.link.z = parser.GetNumber(bone.linkz);
	bone.normal.x = parser.GetNumber(bone.normalx);
	bone.normal.y = parser.GetNumber(bone.normaly);
	bone.normal.z = parser.GetNumber(bone.normalz);
	bone.anchorD = parser.GetNumber(bone.anchorDv);
	bone.length = parser.GetNumber(bone.lengthv);
	bone.r1 = parser.GetNumber(bone.r1v);
	bone.r2 = parser.GetNumber(bone.r2v);
	bone.s1 = parser.GetNumber(bone.s1v);
	bone.s2 = parser.GetNumber(bone.s2v);

	bone.Setup();
}
