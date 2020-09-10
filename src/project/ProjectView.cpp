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

#include "../3D/OpenGLMaterial.h"
#include "../gui/FrameMain.h"
#include "../gui/FrameParent.h"
#include "../main.h"

#include "../math/Polynom2D.h"
#include "../3D/NagataPatch.h"
#include "../3D/Surface.h"
#include "../3D/TestGrid.h"

IMPLEMENT_DYNAMIC_CLASS(ProjectView, wxView)

ProjectView::ProjectView()
		: wxView()
{
	active = Side::Both;

	showLeft = false;
	showRight = true;

	showFootScan = false;
	showBones = false;
	showSkin = false;
	showLeg = false;

	showLastScan = false;
	showLast = true;
	showInsole = true;
	showSole = false;
	showUpper = false;
	showCutaway = false;
	showFloor = false;
	showCoordinateSystem = true;
	showBackground = false;

}

ProjectView::~ProjectView()
{
	printf("ProjectView: Destructor called...\n");
}

bool ProjectView::OnCreate(wxDocument* doc, long flags)
{
	printf("ProjectView::OnCreate(...) called...\n");

	if(!wxView::OnCreate(doc, flags)) return false;
	wxFrame* frame = wxGetApp().CreateChildFrame(this, FrameType::mainframe);
	wxASSERT(frame == GetFrame());

	BackgroundImage temp;
	temp.LoadFile(_T("references/bones/Skel_right.jpg"), wxBITMAP_TYPE_JPEG);
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

//	glColor3f(0.8, 0.5, 0.0);
	OpenGLMaterial matBones(OpenGLMaterial::Preset::Pearl);
	OpenGLMaterial matFoot(OpenGLMaterial::Preset::RedRubber, 0.3);
	matFoot.SetSimpleColor(0.8, 0.5, 0);
	OpenGLMaterial matLast(OpenGLMaterial::Preset::CyanPlastic);
	OpenGLMaterial matFloor(OpenGLMaterial::Preset::WhitePlastic);
	OpenGLMaterial matInsole(OpenGLMaterial::Preset::YellowPlastic, 0.3);
//	matFloor.SetSimpleColor(0.9, 0.9, 0.9);
	OpenGLMaterial matLines;
	matLines.SetSimpleColor(1, 1, 1, 0.6);
	OpenGLMaterial matScan;
	matScan.SetSimpleColor(0.4, 0.9, 0.6);

	matBones.UseColor();

//	NagataPatch p0;
//
//	Vector3 v1(0, 0, 0);
//	Vector3 v2(1, 0, 0.3);
//	Vector3 v3(1, 1, 0);
//	Vector3 v4(0, 1, 0);
//
//	Vector3 n1(-0.5, 0, 1);
//	Vector3 n2(0, 0.4, 1);
//	Vector3 n3(0, 0.0, 1);
//	Vector3 n4(-0.4, 0.4, 1);
//
//	n1.Normalize();
//	n2.Normalize();
//	n3.Normalize();
//	n4.Normalize();
//
//	p0.Set(v1, n1, v2, n2, v3, n3, v4, n4);
//	p0.Paint();
//
////	std::cout << "(1,0): " << p0(1, 0).ToString() << " - "
////			<< p0.Normal(1, 0).ToString() << "\n";
//
//	Vector3 d(+1, 0, 0);
//
//	p0.Set(v2, n2, v1 + d * 2, n1.Scale( {-1, 1, 1}), v4 + d * 2, n4.Scale( {-1,
//			1, 1}), v3, n3);
//	p0.Paint();
//
////	std::cout << "(0,0): " << p0(0, 0).ToString() << " - "
////			<< p0.Normal(0, 0).ToString() << "\n";
//
//	Vector3 d2(0, -1, 0);
//	p0.Set(v4 + d2 * 2, n4.Scale( {1, -1, 1}), v3 + d2 * 2,
//			n3.Scale( {1, -1, 1}), v2, n2, v1, n1);
//	p0.Paint();
//
//	p0.Set(v3 + d2 * 2, n3.Scale( {1, -1, 1}), v4 + (d + d2) * 2, n4.Scale( {-1,
//			-1, 1}), v1 + d * 2, n1.Scale( {-1, 1, 1}), v2, n2);
//	p0.Paint();

//	Surface s;
//	s.SetSize(3, 3);
//	s.P(0, 0).p.Set(0, 0, 0.1);
//	s.P(1, 0).p.Set(1, 0, 0.4);
//	s.P(2, 0).p.Set(2, 0, -0.3);
//	s.P(0, 1).p.Set(0, 1, 0.3);
//	s.P(1, 1).p.Set(1, 1, 0.7);
//	s.P(2, 1).p.Set(2, 1, 0.4);
//	s.P(0, 2).p.Set(0, 2, 0.1);
//	s.P(1, 2).p.Set(1, 2, 0.5);
//	s.P(2, 2).p.Set(2, 2, 0.1);
//	s.Calculate();
//	s.Paint();
//
//	glPushMatrix();
//	glTranslatef(0, -2, 0);
//	s.CalculateDirections();
//	s.Calculate();
//	s.Paint();
//	glPopMatrix();

	if(showLeft){

		glPushMatrix();
		if(shiftapart) glTranslatef(0,
				project->measL.littleToeGirth.value / M_PI, 0);

		glLoadName(0); // Left

		if(project->measurementsource
				== Project::MeasurementSource::fromFootScan && showFootScan){
			glPushName(0);
			matScan.UseColor(0.5);
			glNormal3f(1, 0, 0);
			project->footScan.Paint();
			glPopName();
		}

		if(project->measurementsource
				== Project::MeasurementSource::fromMeasurements && showBones){
			glPushName(1);
			matBones.UseMaterial();
			project->footL.PaintBones();
			glPopName();
		}

		if(project->modeltype == Project::ModelType::boneBased && showSkin
				&& !usePicking){
			glPushName(2);
			matFoot.UseMaterial();
			project->footL.PaintSkin();
			glPopName();
		}

		if(project->modeltype == Project::ModelType::lastBased && showLast){
			glPushName(3);
			matScan.UseMaterial();
			project->lastModelL.Paint();
			glPopName();
		}

//		if(showLast){
//			glPushName(3);
//			matLast.UseMaterial();
//			project->lastL.Paint();
//			glPopName();
//		}

		if(showInsole){
			glPushName(4);
//			matLines.UseMaterial();
//			project->bow.Paint();
			matInsole.UseMaterial();
			project->insoleL.Paint();
			glPopName();
		}

		if(showSole){
			glPushName(12);
			PaintSole();
			glPopName();
		}
		if(showUpper){
			glPushName(13);
			PaintUpper();
			glPopName();
		}

		if(showCutaway){
			OpenGLMaterial::EnableColors();
			glPushName(14);
			PaintCutaway();
			glPopName();
		}

		glPopMatrix();
	}
	if(showRight){
		glPushMatrix();
		if(shiftapart) glTranslatef(0,
				-project->measR.littleToeGirth.value / M_PI, 0);

		glLoadName(1); // Right

		if(project->measurementsource
				== Project::MeasurementSource::fromFootScan && showFootScan){
			glPushName(0);
			matScan.UseColor(0.5);
			glNormal3f(1, 0, 0);
			project->footScan.Paint();
			glPopName();
		}

		if(project->measurementsource
				== Project::MeasurementSource::fromMeasurements && showBones){
			glPushName(1);
			matBones.UseMaterial();
			project->footR.PaintBones();
			glPopName();
		}

		if(project->modeltype == Project::ModelType::boneBased && showSkin
				&& !usePicking){
			glPushName(2);
			matFoot.UseMaterial();
			project->footR.PaintSkin();
			glPopName();
		}

		if(project->modeltype == Project::ModelType::lastBased && showLast){
			glPushName(3);
			matScan.UseMaterial();
			project->lastModelR.Paint();
			glPopName();
		}

//		if(showLast){
//			glPushName(3);
//			matLast.UseMaterial();
//			project->lastR.Paint();
//			glPopName();
//		}

		if(showInsole){
			glPushName(4);
			matInsole.UseMaterial();
			project->insoleR.Paint();
			glPopName();
		}

		if(showSole){
			glPushName(12);
			PaintSole();
			glPopName();
		}
		if(showUpper){
			glPushName(13);
			PaintUpper();
			glPopName();
		}

		if(showCutaway){
			OpenGLMaterial::EnableColors();
			glPushName(14);
			PaintCutaway();
			glPopName();
		}

		glPopMatrix();
	}

	if(!usePicking){
		glLoadName(16);
		matFloor.UseMaterial();
		if(showFloor) PaintFloor();
		glLoadName(17);
		OpenGLMaterial::EnableColors();
		if(showBackground) PaintBackground(false);
	}
	OpenGLMaterial::EnableColors();
}

void ProjectView::PaintLast(void) const
{
//	Project* project = wxStaticCast(this->GetDocument(), Project);

//	project->lastvol.Paint();
//	project->lastvol.PaintSurface();
}

void ProjectView::PaintSole(void) const
{
//	Project* project = wxStaticCast(this->GetDocument(), Project);

//	project->sole.Paint();
}

void ProjectView::PaintUpper(void) const
{
	Project* project = wxStaticCast(this->GetDocument(), Project);
	glColor3f(0.1, 0.4, 0.0);
	project->lastModelL.PaintAnalysis();

}

void ProjectView::PaintCutaway(void) const
{
	Project* project = wxStaticCast(this->GetDocument(), Project);
	project->xray.Paint();
}

void ProjectView::PaintFloor(void) const
{
	const float d = 0.5;
	const int N = 10;
	const float dd = d / (float) N;
	glNormal3f(0, 0, 1);
//	glColor3f(0.4, 0.4, 0.4);

	glBegin(GL_QUADS);

	for(int n = -N; n < N; ++n){
		for(int m = -N; m < N; ++m){

			glVertex3f((n - 1) * dd, (m - 1) * dd, 0);
			glVertex3f((n + 1) * dd, (m - 1) * dd, 0);
			glVertex3f((n + 1) * dd, (m + 1) * dd, 0);
			glVertex3f((n - 1) * dd, (m + 1) * dd, 0);

		}
	}

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
	case Side::Both:
	case Side::Left:
		return &(project->measL);
	case Side::Right:
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

void ProjectView::OnUpdate3D(void)
{
	FrameMain* frame = wxStaticCast(GetFrame(), FrameMain);
	FrameParent* parentframe = wxStaticCast(frame->GetParent(), FrameParent);
	parentframe->settingsStereo3D.WriteToCanvas(frame->m_canvas3D);
	frame->m_canvas3D->Refresh();
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
