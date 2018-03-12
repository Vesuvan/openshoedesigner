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

Last::Last()
{
	nurbs.Initialize(5, 3, true, false, true, false);
	nurbs.InsertData(Vector3(0, -1, -1), 1);
	nurbs.InsertData(Vector3(-1, -1, -1), 0.354);
	nurbs.InsertData(Vector3(-1, 0, -1), 1);
	nurbs.InsertData(Vector3(-1, 1, -1), 0.354);
	nurbs.InsertData(Vector3(0, 1, -1), 1);

	nurbs.InsertData(Vector3(0, -1, 1), 1);
	nurbs.InsertData(Vector3(-1, -1, 1), 3.354);
	nurbs.InsertData(Vector3(-1, 0, 1), 1);
	nurbs.InsertData(Vector3(-1, 1, 1), 0.354);
	nurbs.InsertData(Vector3(0, 1, 1), 1);

	nurbs.InsertData(Vector3(0, -1, 2), 1);
	nurbs.InsertData(Vector3(-1, -1, 2), 0.001);
	nurbs.InsertData(Vector3(-3, 0, 3), 1);
	nurbs.InsertData(Vector3(-1, 1, 2), 1);
	nurbs.InsertData(Vector3(0, 1, 2), 1);

}

Last::~Last()
{
}

void Last::Paint(void) const
{
	glColor3f(0.6, 0, 0.3);
	nurbs.Paint();
}
