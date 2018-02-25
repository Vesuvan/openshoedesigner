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

#include <cstdio>
#include "../main.h"

IMPLEMENT_DYNAMIC_CLASS(ProjectView, wxView)

ProjectView::ProjectView()
		: wxView()
{
	m_frame = NULL;
	foot = NULL;

	showLeft = true;
	showRight = false;
	showBones = true;
	showSkin = false;
	showLeg = false;
	showLast = false;
	showInsole = false;
	showSole = false;
	showUpper = false;
	showCutaway = false;
	showFloor = false;
	showCoordinateSystem = true;
	showBackground = false;

	showFootScan = false;
	showLastScan = false;
}

ProjectView::~ProjectView()
{
	printf("Destructing view\n");
}

bool ProjectView::OnCreate(wxDocument* doc, long flags)
{
	if(!wxView::OnCreate(doc, flags)) return false;
	wxFrame* frame = wxGetApp().CreateChildFrame(this, mainframe);
	wxASSERT(frame == GetFrame());

	BackgroundImage temp;
	temp.LoadFile(_T("blender/images/Skel_right.jpg"), wxBITMAP_TYPE_JPEG);
	background.push_back(temp);

	Project* project = wxStaticCast(this->GetDocument(), Project);
	foot = &(project->footL);

	frame->Show();
	return true;
}

void ProjectView::Paint(void) const
{
	const bool shiftapart = (showLeft && showRight);

	Project* project = wxStaticCast(this->GetDocument(), Project);

	if(showLeft){
		glPushMatrix();

		if(shiftapart) glTranslatef(0, project->footL.ballwidth, 0);

		glLoadName(0);
		glPushName(1);
		if(showBones) project->footL.PaintBones();
		glPopName();
		glPushName(2);
		if(showSkin) project->footL.PaintSkin();
		glPopName();

		glPopMatrix();
	}
	if(showRight){
		glPushMatrix();
		if(shiftapart) glTranslatef(0, -project->footR.ballwidth, 0);

		glLoadName(1);
		glPushName(1);
		if(showBones) project->footR.PaintBones();
		glPopName();
		glPushName(2);
		if(showSkin) project->footR.PaintSkin();
		glPopName();

		glPopMatrix();
	}

	glLoadName(10);
	if(showLast) PaintLast();
	glLoadName(11);
	if(showInsole) PaintInsole();
	glLoadName(12);
	if(showSole) PaintSole();
	glLoadName(13);
	if(showUpper) PaintUpper();
	glLoadName(14);
	if(showCutaway) PaintCutaway();

	glLoadName(16);
	if(showFloor) PaintFloor();
	glLoadName(17);
	if(showBackground) PaintBackground(false);
}

void ProjectView::PaintLast(void) const
{
//	Project* project = wxStaticCast(this->GetDocument(), Project);

//	project->lastvol.Paint();
//	project->lastvol.PaintSurface();
}

void ProjectView::PaintInsole(void) const
{
	Project* project = wxStaticCast(this->GetDocument(), Project);

	project->bow.Paint();

//	glColor3f(0.0, 0.75, 0.0);
//	glBegin(GL_LINES);
//	for(unsigned int i = 0; i < bow.elements.GetCount() - 1; i++){
//		Vector3 temp = bow.elements[i + 1] - bow.elements[i];
//		temp.Normalize();
//		glNormal3f(temp.x, temp.y, temp.z);
//		temp = temp * Vector3(0, -1, 0);
//		temp = lastvol.GetSurface(bow.elements[i], temp);
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
//	Project* project = wxStaticCast(this->GetDocument(), Project);

//	project->sole.Paint();
}

void ProjectView::PaintUpper(void) const
{

}

void ProjectView::PaintCutaway(void) const
{
	Project* project = wxStaticCast(this->GetDocument(), Project);
	project->xray.Paint();
}

void ProjectView::PaintFloor(void) const
{
	const float d = 0.5;

	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(-d, -d, 0);
	glVertex3f(d, -d, 0);
	glVertex3f(d, d, 0);
	glVertex3f(-d, d, 0);
	glEnd();
}

void ProjectView::PaintBackground(bool showBehind) const
{
	if(!showBackground) return;
	for(std::vector <BackgroundImage>::const_iterator image =
			background.begin(); image != background.end(); ++image){
		if(image->showBehindGeometry == showBehind) image->Paint();
	}
}

void ProjectView::OnDraw(wxDC* dc)
{
	printf("ProjectView::OnDraw called...\n");

}

void ProjectView::OnUpdate(wxView* sender, wxObject* hint)
{
	wxView::OnUpdate(sender, hint);
	printf("ProjectView::OnUpdate called...\n");
}

bool ProjectView::OnClose(bool deleteWindow)
{
	wxDocument* doc = GetDocument();
	wxDocManager* manager = doc->GetDocumentManager();
	wxList tempDocs = manager->GetDocuments();
	wxList tempViews = doc->GetViews();

	printf("In view: %u docs, %u views\n", tempDocs.GetCount(),
			tempViews.GetCount());
	printf("Closing View\n");

	if(!wxView::OnClose(deleteWindow)) return false;
	Activate(false);
//	GetDocument()->DeleteContents();
	wxWindow* frame = this->GetFrame();
	if(tempDocs.GetCount() <= 1 && tempViews.GetCount() <= 1 && frame != NULL){
		wxWindow* parent = frame->GetParent();
		printf("Closing Application from Frame\n");
		wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, wxID_EXIT);
		wxPostEvent(parent, event);
	}

	if(deleteWindow){
		printf("Request destruction of Frame\n");
		frame->Destroy();
		SetFrame(NULL);
	}
	return true;
}
