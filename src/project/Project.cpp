///////////////////////////////////////////////////////////////////////////////
// Name               : Project.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.01.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Project.h"

#include "../3D/FileSTL.h"
#include <wx/wfstream.h>

Project::Project()
{
	Reset();
}

Project::~Project()
{
	// TODO Auto-generated destructor stub
}

void Project::Reset(void)
{
	volume.SetSize(0.40, 0.3, 0.4, 0.0075);
	volume.matrix.TranslateGlobal(-0.1, -0.15, -0.3);

	//	volume.AddHalfplane(Vector3(0, 0, 1), -0.10, 0.01);
	//	volume.AddSphere(Vector3(0, 0.10, 0), 0.02, 0.1);
	//	volume.AddSphere(Vector3(0.1, 0, 0.0), 0.04, 0.01);
	//	volume.AddCylinder(Vector3(0.0, 0, 0.0), Vector3(0.05 * 1, 0, -0.00), 0.04,
	//			0.04, 0.02,0.04);

	volume.Clear();

	wxFileInputStream input(_T("data/FootModelDefault.txt"));
	wxTextInputStream text(input);
	foot.LoadModel(&text);
	foot.Setup();
	foot.AddToVolume(&volume);
	volume.MarchingCubes(0.5);

}

void Project::Update(void)
{
	foot.Setup();
}

void Project::UpdateVolume(void)
{
	volume.Clear();
	foot.AddToVolume(&volume);
	volume.MarchingCubes(0.5);
}

const Foot* Project::GetFoot(void) const
{
	return &foot;
}

Shoe* Project::GetShoe(void)
{
	return &shoe;
}
void Project::AddFootToGrid(wxGrid* gridLength, wxGrid* gridDiameter,
		wxGrid* gridSkin)
{
	foot.AddToGrid(gridLength, gridDiameter, gridSkin);
}

void Project::GetFootFromGrid(wxGrid* gridLength, wxGrid* gridDiameter,
		wxGrid* gridSkin)
{
	foot.GetFromGrid(gridLength, gridDiameter, gridSkin);
}

bool Project::LoadModel(wxString fileName)
{
	wxFileInputStream input(fileName);
	wxTextInputStream text(input);
	return foot.LoadModel(&text);
}

bool Project::SaveModel(wxString fileName)
{
	wxFileOutputStream output(fileName);
	wxTextOutputStream text(output);
	return foot.SaveModel(&text);
}

bool Project::SaveLast(wxString fileName)
{
	wxFFileOutputStream outStream(fileName);
	FileSTL temp;
	temp.WriteStream(outStream, volume.geometry);
	return true;
}

void Project::PaintBones(void) const
{
	foot.Render();
}

void Project::PaintLast(void) const
{
	volume.Render();
}

void Project::PaintInsole(void) const
{
}

void Project::PaintSole(void) const
{
}

void Project::PaintUpper(void) const
{
}

void Project::PaintCutaway(void) const
{
}

