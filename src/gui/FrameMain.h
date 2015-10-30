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
 * \brief ...
 *
 * ...
 */

#include "FrameLastParameter.h"
#include "FrameFootParameter.h"
#include "FrameWalkcycleSupport.h"

#include "gui.h"
#include "LastGenerationThread.h"

class FrameMain:public GUIFrameMain {
public:
	FrameMain(wxWindow* parent);
	virtual ~FrameMain();

	bool TransferDataFromWindow();
	bool TransferDataToWindow();

	void UpdateLast(wxCommandEvent& event);
	void UpdateGUI(wxCommandEvent& event);
	void Repaint(wxCommandEvent& event);

	virtual void OnQuit(wxCommandEvent& event);
	virtual void OnSetupFoot(wxCommandEvent& event);
	virtual void OnSetupLast(wxCommandEvent& event);
	virtual void OnDefineWalkCycle(wxCommandEvent& event);
	virtual void OnSaveLast(wxCommandEvent& event);
	virtual void OnSaveInsole(wxCommandEvent& event);
	virtual void OnSaveShoe(wxCommandEvent& event);
	virtual void OnSaveCutaway(wxCommandEvent& event);
	virtual void OnPackZip(wxCommandEvent& event);
	virtual void OnToggleStereo3D(wxCommandEvent& event);
	virtual void OnViewChange(wxCommandEvent& event);
	virtual void OnSetupStereo3D(wxCommandEvent& event);
	virtual void OnSetupUnits(wxCommandEvent& event);
	virtual void OnToolClicked(wxCommandEvent& event);

	FrameLastParameter * dialogLastParameter;
	FrameFootParameter * dialogFootParameter;
	FrameWalkcycleSupport * dialogWalkcycleSupport;

	LastGenerationThread * thread;
	FootParameters setup;

private:
	Foot foot;
	Volume volume;

};

#endif /* FRAMEMAIN_H_ */
