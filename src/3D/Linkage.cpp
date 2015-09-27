///////////////////////////////////////////////////////////////////////////////
// Name               : Linkage.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.08.2015
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

#include "Linkage.h"
#include <GL/gl.h>

Linkage::Linkage()
{
	children = NULL;
	next = NULL;
	color.Set(0.8, 0.5, 0.1);
}

Linkage::~Linkage()
{
	if(children != NULL) delete children;
	Linkage* temp = this->next;
	this->next = NULL;
	Linkage* temp2;
	while(temp != NULL){
		temp2 = temp->next;
		temp->next = NULL;
		delete temp;
		temp = temp2;
	}
}

void Linkage::Accept(LinkageVisitor& visitor)
{
	Process(visitor);
	Linkage* temp = children;
	while(temp != NULL){
		temp->Accept(visitor);
		temp = temp->next;
	}
}

void Linkage::Paint(void)
{
	glPushMatrix();
	glMultMatrixd(matrix.a);
	::glColor3f(color.x, color.y, color.z);
	Render();
	Linkage* temp = children;
	while(temp != NULL){
		temp->Paint();
		temp = temp->next;
	}
	glPopMatrix();
}

Linkage * Linkage::AddChild(Linkage* child)
{
	if(this->children == NULL){
		this->children = child;
	}else{
		Linkage* temp2 = this->children;
		while(temp2->next != NULL)
			temp2 = temp2->next;
		temp2->next = child;
	}
	return child;
}


//Linkage* Linkage::AddChild(void)
//{
//	Linkage* temp = new Linkage;
//	AddChild(temp);
//	return temp;
//}
//
//Linkage * Linkage::AddChild(const Vector3& position)
//{
//	Linkage* temp = new Linkage;
//	temp->matrix.TranslateGlobal(position.x, position.y, position.z);
//	AddChild(temp);
//	return temp;
//}

//void Linkage::Render(void)
//{
//	float sx, sy, sz;
//	sx = 0.01;
//	sy = 0.01;
//	sz = 0.01;
//
//	::glBegin(GL_QUADS);
//	::glNormal3f(1, 0, 0);
//	::glVertex3f(sx, sy, sz);
//	::glVertex3f(sx, 0, sz);
//	::glVertex3f(sx, 0, 0);
//	::glVertex3f(sx, sy, 0);
//	::glNormal3f(-1, 0, 0);
//	::glVertex3f(0, sy, sz);
//	::glVertex3f(0, sy, 0);
//	::glVertex3f(0, 0, 0);
//	::glVertex3f(0, 0, sz);
//	::glNormal3f(0, 1, 0);
//	::glVertex3f(sx, sy, sz);
//	::glVertex3f(sx, sy, 0);
//	::glVertex3f(0, sy, 0);
//	::glVertex3f(0, sy, sz);
//	::glNormal3f(0, -1, 0);
//	::glVertex3f(sx, 0, sz);
//	::glVertex3f(0, 0, sz);
//	::glVertex3f(0, 0, 0);
//	::glVertex3f(sx, 0, 0);
//	::glNormal3f(0, 0, 1);
//	::glVertex3f(sx, sy, sz);
//	::glVertex3f(0, sy, sz);
//	::glVertex3f(0, 0, sz);
//	::glVertex3f(sx, 0, sz);
//	::glNormal3f(0, 0, -1);
//	::glVertex3f(sx, sy, 0);
//	::glVertex3f(sx, 0, 0);
//	::glVertex3f(0, 0, 0);
//	::glVertex3f(0, sy, 0);
//	::glEnd();
//}
