///////////////////////////////////////////////////////////////////////////////
// Name               : VisitorBoneFromGrid.cpp
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

#include "VisitorBoneFromGrid.h"

VisitorBoneFromGrid::VisitorBoneFromGrid(wxGrid* gridLength,
		wxGrid* gridDiameter, wxGrid* gridSkin)
{
	this->gridLength = gridLength;
	this->gridDiameter = gridDiameter;
	this->gridSkin = gridSkin;
	row = 0;

}

VisitorBoneFromGrid::~VisitorBoneFromGrid()
{
}

void VisitorBoneFromGrid::Visit(Bone& bone)
{
	if(gridLength != NULL){
		wxString temp = gridLength->GetCellValue(row, 0);
		bone.lengthv = temp.Trim(false).Trim(true);
	}
	if(gridDiameter != NULL){
		wxString temp = gridDiameter->GetCellValue(row, 0);
		bone.r1v = temp.Trim(false).Trim(true);
		temp = gridDiameter->GetCellValue(row, 2);
		bone.r2v = temp.Trim(false).Trim(true);
	}
	if(gridSkin != NULL){
		wxString temp = gridSkin->GetCellValue(row, 0);
		bone.s1v = temp.Trim(false).Trim(true);
		temp = gridSkin->GetCellValue(row, 2);
		bone.s2v = temp.Trim(false).Trim(true);
	}
	row++;
}
