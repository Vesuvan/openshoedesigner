///////////////////////////////////////////////////////////////////////////////
// Name               : PanelFootMeasurements.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 18.11.2018
// Copyright          : (C) 2018 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_GUI_PANELFOOTMEASUREMENTS_H_
#define SRC_GUI_PANELFOOTMEASUREMENTS_H_

/*!\class PanelFootMeasurements
 * \brief ...
 *
 * ...
 */

#include <wx/docview.h>

#include "DisplaySettings.h"
#include "guipanels.h"

class PanelFootMeasurements:public GUIPanelFootMeasurements {
public:
	PanelFootMeasurements(wxWindow* parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxSize(-1, -1), long style = wxTAB_TRAVERSAL);
	virtual ~PanelFootMeasurements();

	void SetDocView(wxDocument* doc, wxView* view);
	void SetDisplaySettings(DisplaySettings* settings);

	bool TransferDataToWindow(void);

	void OnQuickSetup(wxCommandEvent& event);
	void OnKillFocus(wxFocusEvent& event);
	void OnSetFocus(wxFocusEvent& event);
	void OnTextEnter(wxCommandEvent& event);

	wxDocument *doc;
	wxView *view;
	DisplaySettings *settings;
};

#endif /* SRC_GUI_PANELFOOTMEASUREMENTS_H_ */
