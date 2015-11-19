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
#include "../3D/FileSTL.h"
#include "DialogQuickInitFoot.h"
//#include <wx/file.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/filename.h>

FrameMain::FrameMain(wxWindow* parent, wxLocale* locale, wxConfig* config) :
		GUIFrameMain(parent)
{
	this->config = config;
	this->locale = locale;
	settings.GetConfigFrom(config);

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

	wxFileInputStream input(_T("data/FootModelDefault.txt"));
	wxTextInputStream text(input);
	foot.LoadModel(&text);
	foot.Setup();
	foot.AddToVolume(&volume);
	volume.MarchingCubes(0.5);

//		m_canvas->stereoMode = stereoAnaglyph;
	settings.WriteToCanvas(m_canvas);

	thread = NULL;

	dialogShoe = new FrameShoe(this, &shoe);
	dialogFoot = new FrameFoot(this, &foot);
	dialogWalkcycleSupport = new FrameWalkcycleSupport(this, &shoe);
	dialogPattern = new FramePattern(this, &pattern);
	dialogSetupStereo3D = new DialogSetupStereo3D(this, &settings);
	dialogDebugParser = new FrameDebugParser(this);

	TransferDataToWindow();
	this->Connect(ID_REFRESH, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshMain));
	this->Connect(ID_UPDATE3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Update3DView));
	this->Connect(ID_UPDATEGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateGUI));
	this->Connect(ID_REFRESHPROJECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshProject));
	this->Connect(ID_CALCULATELAST, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::CalculateLast));
	this->Connect(ID_THREADLASTDONE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::LastCalculationDone));
}

FrameMain::~FrameMain()
{
	if(thread != NULL){
		thread->Wait();
		delete thread;
	}
	this->Disconnect(ID_THREADLASTDONE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::LastCalculationDone));
	this->Disconnect(ID_CALCULATELAST, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::CalculateLast));
	this->Disconnect(ID_REFRESHPROJECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshProject));
	this->Disconnect(ID_UPDATEGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateGUI));
	this->Disconnect(ID_UPDATE3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::Update3DView));
	this->Disconnect(ID_REFRESH, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshMain));

	settings.WriteConfigTo(config);
	delete config; // config is written back on deletion of object
}

bool FrameMain::TransferDataToWindow()
{
	m_toolBar->ToggleTool(ID_TOOLSETUPFOOT, dialogFoot->IsShown());
	m_toolBar->ToggleTool(ID_TOOLSETUPSHOE, dialogShoe->IsShown());

	m_menuFoot->Check(ID_SETUPFOOT, dialogFoot->IsShown());
	m_menuShoe->Check(ID_SETUPSHOE, dialogShoe->IsShown());
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

void FrameMain::RefreshMain(wxCommandEvent& event)
{
	Refresh();
}

void FrameMain::UpdateGUI(wxCommandEvent& event)
{
	TransferDataToWindow();
}

void FrameMain::Update3DView(wxCommandEvent& event)
{
	foot.Setup();

	settings.WriteToCanvas(m_canvas);
	m_canvas->Refresh();

	Refresh();
}

void FrameMain::RefreshProject(wxCommandEvent& event)
{
	//dialogFoot->TransferDataToWindow();
	dialogShoe->TransferDataToWindow();
//	dialogPattern->TransferDataToWindow();
//	dialogWalkcycleSupport->TransferDataToWindow();

	this->Refresh(); // FIXME: Recursive refresh not work with GTK1. Call Refresh on every child-dialog by hand.
}

void FrameMain::CalculateLast(wxCommandEvent& event)
{
	if(thread == NULL){
		thread = new LastGenerationThread(this, &foot, &volume);
		thread->Create();
		thread->Run();
	}
}

void FrameMain::LastCalculationDone(wxCommandEvent& event)
{
	if(thread != NULL){
		thread->Wait();
		delete thread;
		thread = NULL;
	}
	Refresh();
}

void FrameMain::OnToolClicked(wxCommandEvent& event)
{
	if(m_toolBar->GetToolState(ID_TOOLSETUPFOOT)){
		dialogFoot->Show();
	}else{
		dialogFoot->Hide();
	}
	if(m_toolBar->GetToolState(ID_TOOLSETUPSHOE)){
		dialogShoe->Show();
	}else{
		dialogShoe->Hide();
	}
	TransferDataToWindow();
}

void FrameMain::OnLoadFootModel(wxCommandEvent& event)
{
}

void FrameMain::OnSaveFootModel(wxCommandEvent& event)
{
}

void FrameMain::OnLoadShoe(wxCommandEvent& event)
{
}

void FrameMain::OnSaveShoe(wxCommandEvent& event)
{
}

void FrameMain::OnQuit(wxCommandEvent& event)
{
	Close();
}

void FrameMain::OnInitializeFootModel(wxCommandEvent& event)
{
	DialogQuickInitFoot dialog(this);
	dialog.ShowModal();
}

void FrameMain::OnSetupFoot(wxCommandEvent& event)
{
	dialogFoot->Show();
	dialogFoot->Raise();
	TransferDataToWindow();
}

void FrameMain::OnSetupShoe(wxCommandEvent& event)
{
	dialogShoe->Show();
	dialogShoe->Raise();
	TransferDataToWindow();
}

void FrameMain::OnEditPattern(wxCommandEvent& event)
{
	dialogPattern->Show();
	dialogPattern->Raise();
	TransferDataToWindow();
}

void FrameMain::OnEditWalkCycle(wxCommandEvent& event)
{
	dialogWalkcycleSupport->Show();
	dialogWalkcycleSupport->Raise();
	TransferDataToWindow();
}

void FrameMain::OnSaveLast(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Save last..."), _T(""), _T(""),
			_("STL file (*.stl)|*.stl|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName;
		fileName = dialog.GetPath();
		wxFFileOutputStream outStream(fileName.GetFullPath());
		FileSTL temp;
		temp.WriteStream(outStream, volume.geometry);
	}
}

void FrameMain::OnSaveInsole(wxCommandEvent& event)
{
}

void FrameMain::OnSaveSole(wxCommandEvent& event)
{
}

void FrameMain::OnSaveCutaway(wxCommandEvent& event)
{
}

void FrameMain::OnPackZip(wxCommandEvent& event)
{
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

void FrameMain::OnViewChange(wxCommandEvent& event)
{
	TransferDataFromWindow();
	Refresh();
}

void FrameMain::OnSetupStereo3D(wxCommandEvent& event)
{
	dialogSetupStereo3D->Show();
	dialogSetupStereo3D->Raise();
}

void FrameMain::OnSetupUnits(wxCommandEvent& event)
{
}

void FrameMain::OnAbout(wxCommandEvent& event)
{
}

void FrameMain::OnSelectLanguage(wxCommandEvent& event)
{
}

void FrameMain::OnDebug(wxCommandEvent& event)
{
	dialogDebugParser->Show();
}

