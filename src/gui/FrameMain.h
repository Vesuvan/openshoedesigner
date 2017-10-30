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

#include <wx/intl.h>
#include <wx/config.h>

class FrameMain:public GUIFrameMain {
public:
	FrameMain(wxDocument* doc, wxView* view, wxConfig* config,
			wxDocParentFrame* parent);
	virtual ~FrameMain();

	bool TransferDataToWindow();
	bool TransferDataFromWindow();

	void RefreshMain(wxCommandEvent& event);
	void UpdateMainGUI(wxCommandEvent& event);
	void UpdateFullGUI(wxCommandEvent& event);
	void UpdateProject(wxCommandEvent& event);
	void LastCalculationDone(wxCommandEvent& event);

	void OnInitializeFootModel(wxCommandEvent& event);
	void OnLoadFootModel(wxCommandEvent& event);
	void OnSaveFootModel(wxCommandEvent& event);
	void OnSetupFoot(wxCommandEvent& event);
	void OnSetupShoe(wxCommandEvent& event);
	void OnConstructionSelection(wxCommandEvent& event);
	void OnEditWalkCycle(wxCommandEvent& event);
	void OnLoadShoe(wxCommandEvent& event);
	void OnSaveShoe(wxCommandEvent& event);
	void OnSaveLast(wxCommandEvent& event);
	void OnSaveInsole(wxCommandEvent& event);
	void OnSaveSole(wxCommandEvent& event);
	void OnSaveCutaway(wxCommandEvent& event);
	void OnPackZip(wxCommandEvent& event);
	void OnToggleStereo3D(wxCommandEvent& event);
	void OnViewChange(wxCommandEvent& event);
	void OnSetupStereo3D(wxCommandEvent& event);
	void OnSetupUnits(wxCommandEvent& event);
	void OnSelectLanguage(wxCommandEvent& event);
	void OnDebugParser(wxCommandEvent& event);

	void OnToolClicked(wxCommandEvent& event);

	wxConfig *config;
	wxLocale *locale;

	DisplaySettings settings;

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
