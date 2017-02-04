///////////////////////////////////////////////////////////////////////////////
// Name               : VisitorBoneToGrid.cpp
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

#include "VisitorBoneToGrid.h"

VisitorBoneToGrid::VisitorBoneToGrid(wxGrid* gridLength, wxGrid* gridDiameter,
		wxGrid* gridSkin)
{
	this->gridLength = gridLength;
	this->gridDiameter = gridDiameter;
	this->gridSkin = gridSkin;
	row = 0;
}

VisitorBoneToGrid::~VisitorBoneToGrid()
{
}

void VisitorBoneToGrid::Visit(Bone& bone)
{
	if(gridLength != NULL){
		gridLength->SetRowLabelValue(row, bone.name);
		gridLength->SetCellValue(row, 0, bone.lengthv);
		gridLength->SetCellValue(row, 1,
				wxString::Format(_T("%.1f mm"), bone.length * 1000.0));
		gridLength->SetReadOnly(row, 1);
		gridLength->SetCellAlignment(row, 1, wxALIGN_RIGHT, wxALIGN_TOP);
	}
	if(gridDiameter != NULL){
		gridDiameter->SetRowLabelValue(row, bone.name);
		gridDiameter->SetCellValue(row, 0, bone.r1v);
		gridDiameter->SetCellValue(row, 1,
				wxString::Format(_T("%.1f mm"), bone.r1 * 1000.0));
		gridDiameter->SetCellValue(row, 2, bone.r2v);
		gridDiameter->SetCellValue(row, 3,
				wxString::Format(_T("%.1f mm"), bone.r2 * 1000.0));
		gridDiameter->SetReadOnly(row, 1);
		gridDiameter->SetReadOnly(row, 3);
		gridDiameter->SetCellAlignment(row, 1, wxALIGN_RIGHT, wxALIGN_TOP);
		gridDiameter->SetCellAlignment(row, 3, wxALIGN_RIGHT, wxALIGN_TOP);
	}
	if(gridSkin != NULL){
		gridSkin->SetRowLabelValue(row, bone.name);
		gridSkin->SetCellValue(row, 0, bone.s1v);
		gridSkin->SetCellValue(row, 1,
				wxString::Format(_T("%.1f mm"), bone.s1 * 1000.0));
		gridSkin->SetCellValue(row, 2, bone.s2v);
		gridSkin->SetCellValue(row, 3,
				wxString::Format(_T("%.1f mm"), bone.s2 * 1000.0));
		gridSkin->SetReadOnly(row, 1);
		gridSkin->SetReadOnly(row, 3);
		gridSkin->SetCellAlignment(row, 1, wxALIGN_RIGHT, wxALIGN_TOP);
		gridSkin->SetCellAlignment(row, 3, wxALIGN_RIGHT, wxALIGN_TOP);
	}
	row++;
}
