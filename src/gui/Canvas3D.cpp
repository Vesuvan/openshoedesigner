///////////////////////////////////////////////////////////////////////////////
// Name               : Canvas3D.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.08.2015
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

#include "Canvas3D.h"
#include <GL/gl.h>

Canvas3D::Canvas3D(wxWindow* parent) :
		OpenGLCanvas(parent)
{
	bone = NULL;
	volume = NULL;
}

Canvas3D::~Canvas3D()
{
}

void Canvas3D::SetBones(Foot* const bone)
{
	this->bone = bone;
}

void Canvas3D::SetVolume(Volume* const volume)
{
	this->volume = volume;
}

void Canvas3D::Render()
{

	glBegin(GL_LINES);
	glNormal3f(0, -0.707, 0.707);
	glColor3f(0.8, 0.0, 0.0);
	glVertex3f(-0.3, 0, 0);
	glVertex3f(0.3, 0, 0);

	glNormal3f(-0.707, 0.0, 0.707);
	glColor3f(0.0, 0.8, 0.0);
	glVertex3f(0, -0.3, 0);
	glVertex3f(0, 0.3, 0);

	glNormal3f(0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.8);
	glVertex3f(0, 0, -0.3);
	glVertex3f(0, 0, 0.3);

	glEnd();

	unsigned int n;
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for(n = 0; n < 64; n++){
		glVertex3d(0, 0.04 * cos(M_PI / 32 * (double) n),
				0.04 * sin(M_PI / 32 * (double) n));
	}
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);
	for(n = 0; n < 64; n++){
		glVertex3d(0.04 * cos(M_PI / 32 * (double) n), 0,
				0.04 * sin(M_PI / 32 * (double) n));
	}
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	for(n = 0; n < 64; n++){
		glVertex3d(0.04 * cos(M_PI / 32 * (double) n),
				0.04 * sin(M_PI / 32 * (double) n), 0);
	}
	glEnd();

	if(bone != NULL) bone->Render();
	if(volume != NULL) volume->Render();

}
