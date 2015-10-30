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
	volume.SetSize(0.40, 0.3, 0.4, 0.005);
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

	this->Connect(ID_UPDATELAST, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateLast));
	this->Connect(ID_VOLUMEDONE, wxEVT_COMMAND_MENU_SELECTED,
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
	this->Disconnect(ID_VOLUMEDONE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Repaint));
	this->Disconnect(ID_UPDATELAST, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateLast));
}

bool FrameMain::TransferDataFromWindow()
{
	return true;
}

bool FrameMain::TransferDataToWindow()
{
	m_menuView->Check(ID_STEREO3D, m_canvas->stereoMode != stereoOff);
	return true;
}

void FrameMain::OnQuit(wxCommandEvent& event)
{
	Close();
}

void FrameMain::UpdateGUI(wxCommandEvent& event)
{
	m_toolBar->ToggleTool(ID_TOOLSETUPLAST, dialogLastParameter->IsShown());
	m_toolBar->ToggleTool(ID_TOOLSETUPFOOT, dialogFootParameter->IsShown());
}

void FrameMain::OnToolClicked(wxCommandEvent& event)
{
	if(m_toolBar->GetToolState(ID_TOOLSETUPLAST)){
		dialogLastParameter->Show();
	}else{
		dialogLastParameter->Hide();
	}
	if(m_toolBar->GetToolState(ID_TOOLSETUPFOOT)){
		dialogFootParameter->Show();
	}else{
		dialogFootParameter->Hide();
	}
}

void FrameMain::UpdateLast(wxCommandEvent& event)
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
	thread->Wait();
	delete thread;
	thread = NULL;
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
	dialogFootParameter->Show();
}

void FrameMain::OnSetupLast(wxCommandEvent& event)
{
	dialogLastParameter->Show();
}

void FrameMain::OnDefineWalkCycle(wxCommandEvent& event)
{
	dialogWalkcycleSupport->Show();
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
}
