///////////////////////////////////////////////////////////////////////////////
// Name               : BoneToVolume.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 27.09.2015
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

#include "BoneToVolume.h"
#include <stdlib.h>
BoneToVolume::BoneToVolume()
{
	volume = NULL;
}

BoneToVolume::~BoneToVolume()
{
}

void BoneToVolume::SetVolume(Volume* volume)
{
	this->volume = volume;
}

void BoneToVolume::Visit(Bone& bone)
{
	if(volume == NULL) return;

	volume->AddCylinder(bone.p1, bone.p2, bone.r1, bone.r2, 0.01);
}
