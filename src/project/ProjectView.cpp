///////////////////////////////////////////////////////////////////////////////
// Name               : ProjectView.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.01.2017
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

#include "ProjectView.h"

ProjectView::ProjectView()
{
	project = NULL;
	floorLevel = 0.0;
	showFootScan = false;
	showFootModel = false;
	showLastScan = false;
	showLast = false;

	showBones = false;
	showInsole = false;
	showSole = false;
	showUpper = false;
	showCutaway = false;
	showFloor = false;
	
	BackgroundImage temp;
	temp.LoadFile(_T("blender/images/Skel_right.jpg"), wxBITMAP_TYPE_JPEG);
//	background.push_back(temp);
}

ProjectView::~ProjectView()
{
}

void ProjectView::SetProject(Project* const project)
{
	this->project = project;
}

void ProjectView::PaintBackground(void) const
{
	for(std::vector <BackgroundImage>::const_iterator image =
			background.begin(); image != background.end(); ++image)
		image->Paint();
}

void ProjectView::Paint(void) const
{
	if(project == NULL) return;

	project->test.Paint();

	if(showBones) PaintBones();
	if(showInsole) PaintInsole();
	if(showSole) PaintSole();
	if(showUpper) PaintUpper();
	if(showCutaway) PaintCutaway();
	if(showFloor) PaintFloor();
	if(showLast) PaintLast();
}

void ProjectView::PaintBones(void) const
{
	project->footmodel.Render();
}

void ProjectView::PaintLast(void) const
{
	project->last.Paint();
}

void ProjectView::PaintInsole(void) const
{
	project->bow.Paint();

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
//		glVertex3f(bow.elements[i].x + temp.x, bow.elements[i].y + temp.y,
//				bow.elements[i].z + temp.z);
//		glVertex3f(temp.x, temp.y, temp.z);
//	}
//	glEnd();
}

void ProjectView::PaintSole(void) const
{
	project->sole.Paint();
	project->xray.Paint();
}

void ProjectView::PaintUpper(void) const
{

}

void ProjectView::PaintCutaway(void) const
{
}

void ProjectView::PaintFloor(void) const
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

