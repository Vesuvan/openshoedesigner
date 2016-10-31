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
#include "DialogQuickInitFoot.h"
#include "../3D/FileSTL.h"
#include "../languages.h"
//#include <wx/file.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/dir.h>

FrameMain::FrameMain(wxWindow* parent, wxLocale* locale, wxConfig* config) :
		GUIFrameMain(parent)
{
	this->config = config;
	this->locale = locale;
	settings.GetConfigFrom(config);

	m_canvas->SetProject(&project);
	settings.WriteToCanvas(m_canvas);

	m_helpController = new wxHelpController;
	m_helpController->Initialize(_T("doc/LastGenerator.hhp"));

	thread = NULL;
	updateVolume = false;

	dialogShoe = new FrameShoe(this, &project);
	dialogFoot = new FrameFoot(this, &project);
	dialogWalkcycleSupport = new FrameWalkcycleSupport(this, &project);
	dialogPattern = new FramePattern(this, &project);
	dialogSetupStereo3D = new DialogSetupStereo3D(this, &settings);
	dialogDebugParser = new FrameDebugParser(this);

	TransferDataToWindow();
	this->Connect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshMain));
	this->Connect(ID_REFRESHMAINGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateMainGUI));
	this->Connect(ID_REFRESHALLGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateFullGUI));
	this->Connect(ID_UPDATEPROJECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateProject));
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
	this->Disconnect(ID_UPDATEPROJECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateProject));
	this->Disconnect(ID_REFRESHALLGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateFullGUI));
	this->Disconnect(ID_REFRESHMAINGUI, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::UpdateMainGUI));
	this->Disconnect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshMain));

	delete m_helpController;

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
	settings.WriteToCanvas(m_canvas);
	m_canvas->Refresh();
	Refresh();
}

void FrameMain::UpdateMainGUI(wxCommandEvent& event)
{
	TransferDataToWindow();
}

void FrameMain::UpdateFullGUI(wxCommandEvent& event)
{
	TransferDataToWindow();

//	dialogFoot->TransferDataToWindow();
	dialogShoe->TransferDataToWindow();
//	dialogPattern->TransferDataToWindow();
//	dialogWalkcycleSupport->TransferDataToWindow();

	this->Refresh(); // FIXME: Recursive refresh not work with GTK1. Call Refresh on every child-dialog by hand.
}

void FrameMain::UpdateProject(wxCommandEvent& event)
{
	project.UpdateFootPosition();

	if(thread == NULL){
		thread = new LastGenerationThread(this, &project);
		thread->Create();
		thread->Run();
		updateVolume = false;
	}else{
		updateVolume = true;
	}

	m_canvas->Refresh();
	Refresh();
}

void FrameMain::LastCalculationDone(wxCommandEvent& event)
{
	if(thread != NULL){
		thread->Wait();
		delete thread;
		thread = NULL;
	}
	if(updateVolume){
		thread = new LastGenerationThread(this, &project);
		thread->Create();
		thread->Run();
	}
	m_canvas->Refresh();
	Refresh();
	updateVolume = false;
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
	wxFileDialog dialog(this, _("Open Foot Model..."), _T(""), _T(""),
			_("Foot Model (*.fmd; *.txt)|*.fmd;*.txt|All Files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(settings.lastFootDirectory)){
		dialog.SetDirectory(settings.lastFootDirectory);
	}

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		if(project.LoadModel(fileName.GetFullPath())){
			project.UpdateFootPosition();
			settings.lastFootDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnSaveFootModel(wxCommandEvent& event)
{

	wxFileDialog dialog(this, _("Save Foot Model As..."), _T(""), _T(""),
			_("Foot Model (*.fmd; *.txt)|*.fmd;*.txt|All Files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(wxDir::Exists(settings.lastFootDirectory)){
		dialog.SetDirectory(settings.lastFootDirectory);
	}

//	if(project.fileName.IsOk()) dialog.SetFilename(
//			project.fileName.GetFullPath());

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		if(project.SaveModel(fileName.GetFullPath())){
			settings.lastFootDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
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
	if(dialog.ShowModal() == wxID_OK){

	}
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
		project.SaveLast(fileName.GetFullPath());
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

void FrameMain::OnSelectLanguage(wxCommandEvent& event)
{
	long lng =
			wxGetSingleChoiceIndex(
					_T(
							"Please choose language:\nChanges will take place after restart!"),
					_T("Language"), WXSIZEOF(langNames), langNames);
	if(lng >= 0) config->Write(_T("Language"), langNames[lng]);
}

void FrameMain::OnHelp(wxCommandEvent& event)
{
	m_helpController->DisplayContents();
}

void FrameMain::OnAbout(wxCommandEvent& event)
{
}

void FrameMain::OnDebug(wxCommandEvent& event)
{
	dialogDebugParser->Show();
}

