///////////////////////////////////////////////////////////////////////////////
// Name               : FrameMain.cpp
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

#include "FrameMain.h"
#include "IDs.h"

FrameMain::FrameMain(wxWindow* parent) :
		GUIFrameMain(parent)
{
	volume.SetSize(0.40, 0.3, 0.4, 0.0075);
	volume.matrix.TranslateGlobal(-0.1, -0.15, -0.3);

//	volume.AddHalfplane(Vector3(0, 0, 1), -0.10, 0.01);
//	volume.AddSphere(Vector3(0, 0.10, 0), 0.02, 0.1);
//	volume.AddSphere(Vector3(0.1, 0, 0.0), 0.04, 0.01);
//	volume.AddCylinder(Vector3(0.0, 0, 0.0), Vector3(0.05 * 1, 0, -0.00), 0.04,
//			0.04, 0.02,0.04);

	m_canvas->SetVolume(&volume);

	m_canvas->SetBones(&foot);

	volume.Clear();
	foot.Setup(&setup);
	foot.AddToVolume(&volume);
	volume.MarchingCubes(0.5);

//		m_canvas->stereoMode = stereoAnaglyph;
	m_canvas->eyeDistance = 0.005;
	m_canvas->leftEyeR = 0;
	m_canvas->leftEyeG = 109;
	m_canvas->leftEyeB = 0;
	m_canvas->rightEyeR = 106;
	m_canvas->rightEyeG = 0;
	m_canvas->rightEyeB = 0;

	thread = NULL;

	dialogLastParameter = new FrameLastParameter(this, &setup);
	dialogFootParameter = new FrameFootParameter(this);
	dialogWalkcycleSupport = new FrameWalkcycleSupport(this);
	dialogPattern = new FramePattern(this);

	TransferDataToWindow();

	this->Connect(ID_UPDATELAST, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Update3DView));
	this->Connect(ID_THREADLASTDONE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Repaint));
	this->Connect(ID_UPDATEGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateGUI));
}

FrameMain::~FrameMain()
{
	if(thread != NULL){
		thread->Wait();
		delete thread;
	}
	this->Disconnect(ID_UPDATEGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateGUI));
	this->Disconnect(ID_THREADLASTDONE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Repaint));
	this->Disconnect(ID_UPDATELAST, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Update3DView));
}

bool FrameMain::TransferDataToWindow()
{
	m_toolBar->ToggleTool(ID_TOOLSETUPLAST, dialogLastParameter->IsShown());
	m_toolBar->ToggleTool(ID_TOOLSETUPFOOT, dialogFootParameter->IsShown());

	m_menuFoot->Check(ID_SETUPFOOT, dialogFootParameter->IsShown());
	m_menuShoe->Check(ID_SETUPLAST, dialogLastParameter->IsShown());
	m_menuShoe->Check(ID_EDITPATTERN, dialogPattern->IsShown());
	m_menuShoe->Check(ID_EDITWALKCYCLE, dialogWalkcycleSupport->IsShown());

	m_menuView->Check(ID_STEREO3D, m_canvas->stereoMode != stereoOff);

	m_menuView->Check(ID_SHOWBONES, m_canvas->showBones);
	m_menuView->Check(ID_SHOWLAST, m_canvas->showLast);
	m_menuView->Check(ID_SHOWINSOLE, m_canvas->showInsole);
	m_menuView->Check(ID_SHOWSOLE, m_canvas->showSole);
	m_menuView->Check(ID_SHOWUPPER, m_canvas->showUpper);
	m_menuView->Check(ID_SHOWCUTAWAY, m_canvas->showCutaway);
	m_menuView->Check(ID_SHOWFLOOR, m_canvas->showFloor);

	return true;
}

bool FrameMain::TransferDataFromWindow()
{
	m_canvas->showBones = m_menuView->IsChecked(ID_SHOWBONES);
	m_canvas->showLast = m_menuView->IsChecked(ID_SHOWLAST);
	m_canvas->showInsole = m_menuView->IsChecked(ID_SHOWINSOLE);
	m_canvas->showUpper = m_menuView->IsChecked(ID_SHOWUPPER);
	m_canvas->showSole = m_menuView->IsChecked(ID_SHOWSOLE);
	m_canvas->showCutaway = m_menuView->IsChecked(ID_SHOWCUTAWAY);
	m_canvas->showFloor = m_menuView->IsChecked(ID_SHOWFLOOR);

	return true;
}

void FrameMain::OnQuit(wxCommandEvent& event)
{
	Close();
}

void FrameMain::UpdateGUI(wxCommandEvent& event)
{
	TransferDataToWindow();
}

void FrameMain::OnEditPattern(wxCommandEvent& event)
{
	if(dialogPattern->IsShown()){
		dialogPattern->Hide();
	}else{
		dialogPattern->Show();
	}
	TransferDataToWindow();
}

void FrameMain::OnToolClicked(wxCommandEvent& event)
{
	if(m_toolBar->GetToolState(ID_TOOLSETUPFOOT)){
		dialogFootParameter->Show();
	}else{
		dialogFootParameter->Hide();
	}
	if(m_toolBar->GetToolState(ID_TOOLSETUPLAST)){
		dialogLastParameter->Show();
	}else{
		dialogLastParameter->Hide();
	}
	TransferDataToWindow();
}

void FrameMain::Update3DView(wxCommandEvent& event)
{
	foot.Setup(&setup);

	if(thread == NULL){
		thread = new LastGenerationThread(this, &foot, &volume);
		thread->Create();
		thread->Run();
	}

	Refresh();
}
void FrameMain::Repaint(wxCommandEvent& event)
{
	if(thread != NULL){
		thread->Wait();
		delete thread;
		thread = NULL;
	}
	Refresh();
}

void FrameMain::OnToggleStereo3D(wxCommandEvent& event)
{
	if(m_canvas->stereoMode == stereoOff){
		m_canvas->stereoMode = stereoAnaglyph;
	}else{
		m_canvas->stereoMode = stereoOff;
	}
	m_menuView->Check(ID_STEREO3D, m_canvas->stereoMode != stereoOff);
	Refresh();
}

void FrameMain::OnSetupStereo3D(wxCommandEvent& event)
{
}

void FrameMain::OnSetupUnits(wxCommandEvent& event)
{
}

void FrameMain::OnSetupFoot(wxCommandEvent& event)
{

	if(dialogFootParameter->IsShown()){
		dialogFootParameter->Hide();
	}else{
		dialogFootParameter->Show();
	}

	TransferDataToWindow();
}

void FrameMain::OnSetupLast(wxCommandEvent& event)
{

	if(dialogLastParameter->IsShown()){
		dialogLastParameter->Hide();
	}else{
		dialogLastParameter->Show();
	}

	TransferDataToWindow();
}

void FrameMain::OnEditWalkCycle(wxCommandEvent& event)
{
	if(dialogWalkcycleSupport->IsShown()){
		dialogWalkcycleSupport->Hide();
	}else{
		dialogWalkcycleSupport->Show();
	}

	TransferDataToWindow();
}

void FrameMain::OnSaveLast(wxCommandEvent& event)
{
}

void FrameMain::OnSaveInsole(wxCommandEvent& event)
{
}

void FrameMain::OnSaveShoe(wxCommandEvent& event)
{
}

void FrameMain::OnSaveCutaway(wxCommandEvent& event)
{
}

void FrameMain::OnPackZip(wxCommandEvent& event)
{
}

void FrameMain::OnViewChange(wxCommandEvent& event)
{
	TransferDataFromWindow();
	Refresh();
}
