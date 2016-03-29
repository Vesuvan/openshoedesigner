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
#include "../gui/MathParser.h"

#include <wx/wfstream.h>
#include <GL/gl.h>

Project::Project()
{
	Reset();
}

Project::~Project()
{
}

void Project::Reset(void)
{
	volume.SetSize(0.40, 0.3, 0.4, 0.0075);
	volume.SetOrigin(Vector3(-0.15, -0.1, -0.3));

//	volume.AddHalfplane(Vector3(0, 0, 1), -0.10, 0.01);
//	volume.AddSphere(Vector3(0, 0.1, 0), 0.15, 0.1);
//	volume.AddSphere(Vector3(0.13, 0, 0.0), 0.19, 0.01);
//	volume.AddCylinder(Vector3(0.0, 0, 0.0), Vector3(0.05 * 1, 0, -0.00), 0.04,
//			0.04, 0.02, 0.04);

	wxFileInputStream input(_T("data/FootModelDefault.txt"));
	wxTextInputStream text(input);
	foot.LoadModel(&text);

	Evaluate();
	UpdateVolume();
}

void Project::UpdateVolume(void)
{
	volume.Clear();
	foot.AddToVolume(&volume);
	volume.MarchingCubes();
	volume.FillHeightField(&sole);

	h.Clear();
	double p;
	for(int i = 0; i < 200; i++){
		p = (double) i / 300;
		h.InsertPoint(p - 0.2, 0, volume.GetValue(p - 0.2, 0, 0.0) * 0.01);
	}

}

bool Project::Evaluate(void)
{
	if(!shoe.Evaluate(foot.L, foot.W, foot.H, foot.A)) return false;
	foot.SetPosition(shoe.heelHeight - shoe.ballHeight, shoe.toeAngle,
			shoe.mixing);
	floorLevel = foot.GetHeelHeight() - shoe.heelHeight;
	return true;
}

Foot* Project::GetFoot(void)
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

	if(foot.LoadModel(&text))

	{
		foot.SetPosition(shoe.heelHeight, shoe.toeAngle, shoe.mixing);
		return true;
	}
	return false;
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
	volume.Paint();
}

void Project::PaintInsole(void) const
{
	h.Paint();
}

void Project::PaintSole(void) const
{
	sole.Paint();
}

void Project::PaintUpper(void) const
{
}

void Project::PaintCutaway(void) const
{
}

void Project::PaintFloor(void) const
{
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, floorLevel);
	glVertex3f(0.5, -0.5, floorLevel);
	glVertex3f(0.5, 0.5, floorLevel);
	glVertex3f(-0.5, 0.5, floorLevel);
	glEnd();
}
