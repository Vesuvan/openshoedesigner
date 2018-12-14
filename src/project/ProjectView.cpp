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

#include "../gui/FrameMain.h"
#include "../main.h"

IMPLEMENT_DYNAMIC_CLASS(ProjectView, wxView)

ProjectView::ProjectView()
		: wxView()
{
	active = Left;

	showLeft = true;
	showRight = true;
	showBones = true;
	showSkin = true;
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
	printf("ProjectView: Destructor called...\n");
}

bool ProjectView::OnCreate(wxDocument* doc, long flags)
{
	printf("ProjectView::OnCreate(...) called...\n");

	if(!wxView::OnCreate(doc, flags)) return false;
	wxFrame* frame = wxGetApp().CreateChildFrame(this, mainframe);
	wxASSERT(frame == GetFrame());

	BackgroundImage temp;
	temp.LoadFile(_T("blender/images/Skel_right.jpg"), wxBITMAP_TYPE_JPEG);
	background.push_back(temp);

//	Project* project = wxStaticCast(this->GetDocument(), Project);
//	foot = &(project->footL);

	frame->Show();
	return true;
}

void ProjectView::Paint(bool usePicking) const
{
	const bool shiftapart = (showLeft && showRight);

	Project* project = wxStaticCast(this->GetDocument(), Project);

	glColor3f(0.8, 0.5, 0.0);
//	project->vol.PaintSurface();

	if(showLeft){
		glPushMatrix();

		if(shiftapart) glTranslatef(0, project->measL.ballGirth.value / M_PI,
				0);

		glLoadName(0); // Left
		glPushName(1);
		if(showBones) project->footL.PaintBones();
		glPopName();
		glPushName(2);
		if(showSkin && !usePicking) project->footL.PaintSkin();
		glPopName();
		glPushName(3);
		if(showLast) project->lastL.Paint();
		glPopName();
		glPushName(4);
		if(showInsole) project->bow.Paint();
		glPopName();
		glPopMatrix();
	}
	if(showRight){
		glPushMatrix();
		if(shiftapart) glTranslatef(0, -project->measR.ballGirth.value / M_PI,
				0);

		glLoadName(1); // Right
		glPushName(1);
		if(showBones) project->footR.PaintBones();
		glPopName();
		glPushName(2);
		if(showSkin && !usePicking) project->footR.PaintSkin();
		glPopName();
		glPushName(3);
		if(showLast) project->lastR.Paint();
		glPopName();
		glPopMatrix();
	}

	glLoadName(11);
	if(showInsole) PaintInsole();
	glLoadName(12);
	if(showSole) PaintSole();
	glLoadName(13);
	if(showUpper) PaintUpper();
	glLoadName(14);
	if(showCutaway) PaintCutaway();

	if(!usePicking){
		glLoadName(16);
		if(showFloor) PaintFloor();
		glLoadName(17);
		if(showBackground) PaintBackground(false);
	}
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

const FootMeasurements* ProjectView::GetActiveFootMeasurements(void) const
{
	const Project* project = wxStaticCast(this->GetDocument(), Project);
	switch(active){
	case Left:
		return &(project->measL);
	case Right:
		return &(project->measR);
	}
	return NULL;
}

void ProjectView::OnDraw(wxDC* dc)
{
	printf("ProjectView::OnDraw(...) called...\n");

}

void ProjectView::OnUpdate(wxView* sender, wxObject* hint)
{
	FrameMain* temp = wxStaticCast(GetFrame(), FrameMain);
	temp->TransferDataToWindow();
	temp->Refresh();
	wxView::OnUpdate(sender, hint);
}

bool ProjectView::OnClose(bool deleteWindow)
{
	printf("ProjectView::OnClose(%s) called...\n",
			deleteWindow? "true" : "false");
	wxDocument* doc = GetDocument();
	wxDocManager* manager = doc->GetDocumentManager();
	wxList tempDocs = manager->GetDocuments();
	wxList tempViews = doc->GetViews();

	printf("ProjectView: %lu docs, %lu views\n", tempDocs.GetCount(),
			tempViews.GetCount());

	if(!wxView::OnClose(deleteWindow)) return false;
	Activate(false);
//	GetDocument()->DeleteContents();
	wxWindow* frame = this->GetFrame();
	if(tempDocs.GetCount() <= 1 && tempViews.GetCount() <= 1 && frame != NULL){
		wxWindow* parent = frame->GetParent();
		printf("ProjectView: Posting wxID_EXIT to parent\n");
		wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, wxID_EXIT);
		wxPostEvent(parent, event);
	}

	if(deleteWindow){
		printf("ProjectView: Request destruction of associated Frame\n");
		frame->Destroy();
		SetFrame(NULL);
	}
	return true;
}
