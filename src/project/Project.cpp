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
#include <float.h>

Project::Project()
{
	generator = Basic;
	Reset();
}

Project::~Project()
{
}

void Project::Reset(void)
{
	last.SetSize(0.40, 0.3, 0.4, 0.0075);
	last.SetOrigin(Vector3(-0.15, -0.1, -0.3));

//	last.AddHalfplane(Vector3(0, 0, 1), -0.10, 0.01);
//	last.AddSphere(Vector3(0, 0.1, 0), 0.15, 0.1);
//	last.AddSphere(Vector3(0.13, 0, 0.0), 0.19, 0.01);
//	last.AddCylinder(Vector3(0.0, 0, 0.0), Vector3(0.05 * 1, 0, -0.00), 0.04,
//			0.04, 0.02, 0.04);

	wxFileInputStream input(_T("data/FootModelDefault.txt"));
	wxTextInputStream text(input);
	footmodel.LoadModel(&text);

	UpdateFootPosition();
	UpdateAndGenerate();
}

bool Project::UpdateFootPosition(void)
{
	if(!shoe.Evaluate(footmodel.L, footmodel.W, footmodel.H, footmodel.A)) return false;
	footmodel.SetPosition(shoe.heelHeight - shoe.ballHeight, shoe.toeAngle,
			shoe.mixing);
	floorLevel = footmodel.GetHeelHeight() - shoe.heelHeight;
	return true;
}

void Project::UpdateAndGenerate(void)
{
	// Calculate the Footmodel
	last.Clear();
	footmodel.AddToVolume(&last);
//	last.Rotate(Volume::Z, 2);
//	last.Rotate(Volume::Z, -1);
//	last.Rotate(Volume::Z, -1);
	last.CalcSurface();

	heightfield = last.SurfaceField();
	OrientedMatrix temp = heightfield.XRay(Volume::MinValue);

	bow.Clear();
	for(unsigned int i = 0; i < temp.Numel(); i++){
		if(temp[i] < DBL_MAX){
			bow.InsertPoint(i * temp.dx + temp.origin.x, 0,
					temp[i] + temp.origin.z);
		}
	}

//	sole.origin.z -= 0.1;

	xray = last.XRay(Volume::MeanValue);

//	bow = footmodel.GetCenterline();
//	bow.elements[0] = last.GetSurface(bow.elements[1],
//			(bow.elements[0] - bow.elements[1]) * 2);
//	size_t M = bow.elements.GetCount();
//	bow.elements[M - 1] = last.GetSurface(bow.elements[M - 2],
//			(bow.elements[M - 1] - bow.elements[M - 2]) * 2);
//
//	bow.Resample(50);
//	bow.Filter(20);

}

Foot* Project::GetFoot(void)
{
	return &footmodel;
}

Shoe* Project::GetShoe(void)
{
	return &shoe;
}
void Project::AddFootToGrid(wxGrid* gridLength, wxGrid* gridDiameter,
		wxGrid* gridSkin)
{
	footmodel.AddToGrid(gridLength, gridDiameter, gridSkin);
}

void Project::GetFootFromGrid(wxGrid* gridLength, wxGrid* gridDiameter,
		wxGrid* gridSkin)
{
	footmodel.GetFromGrid(gridLength, gridDiameter, gridSkin);
}

bool Project::LoadModel(wxString fileName)
{
	wxFileInputStream input(fileName);
	wxTextInputStream text(input);

	if(footmodel.LoadModel(&text))

	{
		footmodel.SetPosition(shoe.heelHeight, shoe.toeAngle, shoe.mixing);
		return true;
	}
	return false;
}

bool Project::SaveModel(wxString fileName)
{
	wxFileOutputStream output(fileName);
	wxTextOutputStream text(output);
	return footmodel.SaveModel(&text);
}

bool Project::SaveLast(wxString fileName)
{
	wxFFileOutputStream outStream(fileName);
	FileSTL temp;
	temp.WriteStream(outStream, last.geometry);
	return true;
}

void Project::PaintBones(void) const
{
	footmodel.Render();
}

void Project::PaintLast(void) const
{
	last.Paint();
}

void Project::PaintInsole(void) const
{
	bow.Paint();

//	glColor3f(0.0, 0.75, 0.0);
//	glBegin(GL_LINES);
//	for(unsigned int i = 0; i < bow.elements.GetCount() - 1; i++){
//		Vector3 temp = bow.elements[i + 1] - bow.elements[i];
//		temp.Normalize();
//		glNormal3f(temp.x, temp.y, temp.z);
//		temp = temp * Vector3(0, -1, 0);
//		temp = last.GetSurface(bow.elements[i], temp);
//
//		glVertex3f(bow.elements[i].x, bow.elements[i].y, bow.elements[i].z);
////		glVertex3f(bow.elements[i].x + temp.x, bow.elements[i].y + temp.y,
////				bow.elements[i].z + temp.z);
//		glVertex3f(temp.x, temp.y, temp.z);
//	}
//	glEnd();
}

void Project::PaintSole(void) const
{
	sole.Paint();
	xray.Paint();
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
