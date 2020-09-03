///////////////////////////////////////////////////////////////////////////////
// Name               : Last.cpp
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

#include "Last.h"

#include <GL/gl.h>

#include "../foot/FootModel.h"
#include "LastModel.h"

Last::Last()
{
	modified = true;



}

bool Last::IsModified(void) const
{
	return modified;
}

void Last::Modify(bool modified)
{
	this->modified = modified;
}

void Last::Setup(const LastModel& model)
{

}

void Last::Setup(const FootModel& model)
{
}

void Last::Paint(void) const
{
	glColor3f(0.6, 0, 0.3);
	surface.Paint();
}

