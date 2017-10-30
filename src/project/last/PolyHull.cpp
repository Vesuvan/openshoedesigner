///////////////////////////////////////////////////////////////////////////////
// Name               : PolyHull.cpp
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

#include "PolyHull.h"

PolyHull::Level::Level()
{

}

PolyHull::PolyHull()
{
	Level temp;

	temp.AddVector(-0.04, 0, 0.12);
	temp.AddVector(0.0, 0, 0.11);
	temp.AddVector(0.1, 0, 0.003);
	temp.AddVector(0.15, 0, 0.0);
	temp.AddVector(0.1, 0.0, 0.2);
	temp.Normalize();
	temp.Calculate();

	levels.push_back(temp);
}

PolyHull::~PolyHull()
{
}

void PolyHull::Paint(void) const
{
	for(std::vector <Level>::const_iterator level = levels.begin();
			level != levels.end(); ++level)
		level->Paint();
}
