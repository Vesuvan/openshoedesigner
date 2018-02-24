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
	shoe = NULL;

	showLeft = false;
	showRight = true;
	side = Both;
	showBackground = false;
	showFootScan = false;
	showFootModel = false;
	showLastScan = false;
	showLast = false;
	showBones = true;
	showInsole = false;
	showSole = false;
	showUpper = false;
	showCutaway = false;
	showFloor = false;
	floorLevel = 0.0;
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
	glPushMatrix();
	glTranslated(0, 0, floorLevel);
	if(showBones) PaintBones();
	if(showInsole) PaintInsole();
	if(showSole) PaintSole();
	if(showUpper) PaintUpper();
	if(showCutaway) PaintCutaway();
	if(showFloor) PaintFloor();
	if(showLast) PaintLast();
	if(showBackground) PaintBackground(false);
	glPopMatrix();
}

void ProjectView::PaintBackground(bool showBehind) const
{
	if(!showBackground) return;
	for(std::vector <BackgroundImage>::const_iterator image =
			background.begin(); image != background.end(); ++image){
		if(image->showBehindGeometry == showBehind) image->Paint();
	}
}

void ProjectView::PaintBones(void) const
{
	Project* project = wxStaticCast(this->GetDocument(), Project);
	project->footL.Paint();
}

void ProjectView::PaintLast(void) const
{
	Project* project = wxStaticCast(this->GetDocument(), Project);

	project->lastvol.Paint();
	project->lastvol.PaintSurface();
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
	Project* project = wxStaticCast(this->GetDocument(), Project);

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
	Project* project = wxStaticCast(this->GetDocument(), Project);

	const double lev = project->footL.GetHeelHeight()
			- project->shoe.heelHeight;
	const float d = 0.5;

	glPushMatrix();
	glTranslated(0, 0, lev);
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(-d, -d, 0);
	glVertex3f(d, -d, 0);
	glVertex3f(d, d, 0);
	glVertex3f(-d, d, 0);
	glEnd();
	glPopMatrix();
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
