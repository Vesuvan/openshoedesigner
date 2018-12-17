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

#include <wx/cmdproc.h>
#include "gui.h"

#include "DialogSetupStereo3D.h"
#include "DisplaySettings.h"

#include "../project/Project.h"

#include <wx/intl.h>
#include <wx/config.h>

#include "DialogSetupUnits.h"
#include "MidiPort.h"

class FrameMain:public GUIFrameMain {
public:
	FrameMain(wxDocument* doc, wxView* view, wxConfig* config,
			wxDocParentFrame* parent);
	virtual ~FrameMain();

	bool TransferDataToWindow();
	bool TransferDataFromWindow();

	void On3DSelect(wxCommandEvent& event);
	void RefreshCanvas(wxCommandEvent& event);
	void RefreshView(wxCommandEvent& event);

	void OnClose(wxCloseEvent& event);
	void OnIdle(wxIdleEvent& event);
	void OnQuickSetupMeasurements(wxCommandEvent& event);
	void OnSetSymmetry(wxCommandEvent& event);
	void OnCopyMeasurements(wxCommandEvent& event);
	void OnChangeModel(wxCommandEvent& event);
	void OnLoadFootSTL(wxCommandEvent& event);
	void OnEditBoneModel(wxCommandEvent& event);
	void OnLoadBoneModel(wxCommandEvent& event);
	void OnSaveBoneModel(wxCommandEvent& event);
	void OnSetupShoe(wxCommandEvent& event);
	void OnConstructionSelection(wxCommandEvent& event);
	void OnEditWalkCycle(wxCommandEvent& event);
	void OnLoadPattern(wxCommandEvent& event);
	void OnSavePattern(wxCommandEvent& event);
	void OnSaveLast(wxCommandEvent& event);
	void OnSaveInsole(wxCommandEvent& event);
	void OnSaveSole(wxCommandEvent& event);
	void OnSaveCutaway(wxCommandEvent& event);
	void OnPackZip(wxCommandEvent& event);
	void OnToggleStereo3D(wxCommandEvent& event);
	void OnViewChange(wxCommandEvent& event);
	void OnSetupBackgroundImages(wxCommandEvent& event);
	void OnSetupStereo3D(wxCommandEvent& event);
	void OnSetupUnits(wxCommandEvent& event);
	void OnSelectLanguage(wxCommandEvent& event);
	void OnDebugParser(wxCommandEvent& event);
	void OnPageChange( wxNotebookEvent& event);
	void OnToggleButton(wxCommandEvent& event);
	void OnFileChangedScanFile(wxFileDirPickerEvent& event);
	void OnFileChangedLastFile(wxFileDirPickerEvent& event);
	void OnChoice(wxCommandEvent& event);
	void OnTextEnter(wxCommandEvent& event);
	void OnCheckBox(wxCommandEvent& event);
	void OnToggleAnkleLock(wxCommandEvent& event);
	void OnChoiceDisplay(wxCommandEvent& event);

	wxConfig *config;
//	wxLocale *locale;

	DisplaySettings settings;

	DialogSetupStereo3D* dialogSetupStereo3D;
	DialogSetupUnits* dialogSetupUnits;

//	MidiPort midi;
//	wxTimer timer;
//	void OnTimer(wxTimerEvent& event);
};

#endif /* FRAMEMAIN_H_ */
