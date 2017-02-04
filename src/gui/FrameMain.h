///////////////////////////////////////////////////////////////////////////////
// Name               : FrameMain.h
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

#ifndef FRAMEMAIN_H_
#define FRAMEMAIN_H_

/*!\class FrameMain
 * \brief Main Window
 *
 * Main window of the application. Has the main 3D display and work area.
 * All other windows and dialogs are children of this frame.
 */

#include "gui.h"

#include "FrameFoot.h"
#include "FrameShoe.h"
#include "FrameWalkcycleSupport.h"
#include "DialogSetupStereo3D.h"
#include "FrameDebugParser.h"
#include "DisplaySettings.h"

#include "../project/Project.h"

#include "LastGenerationThread.h"

#include <wx/help.h>
#include <wx/intl.h>
#include <wx/config.h>

class FrameMain:public GUIFrameMain {
public:
	FrameMain(wxWindow* parent, wxLocale* locale, wxConfig* config);
	virtual ~FrameMain();

	bool TransferDataToWindow();
	bool TransferDataFromWindow();

	void RefreshMain(wxCommandEvent& event);
	void UpdateMainGUI(wxCommandEvent& event);
	void UpdateFullGUI(wxCommandEvent& event);
	void UpdateProject(wxCommandEvent& event);
	void LastCalculationDone(wxCommandEvent& event);

	virtual void OnLoadFootModel(wxCommandEvent& event);
	virtual void OnSaveFootModel(wxCommandEvent& event);
	virtual void OnLoadShoe(wxCommandEvent& event);
	virtual void OnSaveShoe(wxCommandEvent& event);
	virtual void OnQuit(wxCommandEvent& event);
	virtual void OnInitializeFootModel(wxCommandEvent& event);
	virtual void OnSetupFoot(wxCommandEvent& event);
	virtual void OnSetupShoe(wxCommandEvent& event);
	virtual void OnEditWalkCycle(wxCommandEvent& event);
	virtual void OnSaveLast(wxCommandEvent& event);
	virtual void OnSaveInsole(wxCommandEvent& event);
	virtual void OnSaveSole(wxCommandEvent& event);
	virtual void OnSaveCutaway(wxCommandEvent& event);
	virtual void OnPackZip(wxCommandEvent& event);
	virtual void OnToggleStereo3D(wxCommandEvent& event);
	virtual void OnViewChange(wxCommandEvent& event);
	virtual void OnSetupStereo3D(wxCommandEvent& event);
	virtual void OnSetupUnits(wxCommandEvent& event);
	virtual void OnAbout(wxCommandEvent& event);
	virtual void OnSelectLanguage(wxCommandEvent& event);
	virtual void OnDebug(wxCommandEvent& event);
	virtual void OnToolClicked(wxCommandEvent& event);
	virtual void OnHelp(wxCommandEvent& event);

	wxConfig *config;
	wxLocale *locale;
	DisplaySettings settings;
	wxHelpController* m_helpController;
	Project project;
	ProjectView projectview;

	FrameShoe* dialogShoe;
	FrameFoot* dialogFoot;
	FrameWalkcycleSupport* dialogWalkcycleSupport;
	DialogSetupStereo3D* dialogSetupStereo3D;
	FrameDebugParser* dialogDebugParser;

	LastGenerationThread* thread;

private:
	bool updateVolume;

};

#endif /* FRAMEMAIN_H_ */
