///////////////////////////////////////////////////////////////////////////////
// Name               : VisitorBoneToGrid.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 19.11.2015
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

#ifndef VISITORBONETOGRID_H_
#define VISITORBONETOGRID_H_

/*!\class VisitorBoneToGrid
 * \brief ...
 *
 * ...
 */

#include "../../StdInclude.h"
#include "Bone.h"
#include <wx/grid.h>


class VisitorBoneToGrid:public LinkageVisitor {
public:
	VisitorBoneToGrid(wxGrid* gridLength, wxGrid* gridDiameter,wxGrid* gridSkin );
	virtual ~VisitorBoneToGrid();

	void Visit(Bone &bone);

private:
	wxGrid* gridLength;
	wxGrid* gridDiameter;
	wxGrid* gridSkin;
	unsigned int row;
};

#endif /* VISITORBONETOGRID_H_ */
