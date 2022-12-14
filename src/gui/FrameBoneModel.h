///////////////////////////////////////////////////////////////////////////////
// Name               : FrameBoneModel.h
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

#ifndef SRC_GUI_FRAMEBONEMODEL_H_
#define SRC_GUI_FRAMEBONEMODEL_H_

/*!\class FrameBoneModel
 * \brief ...
 *
 * ...
 */

#include "gui.h"

class FrameBoneModel:public GUIFrameBoneModel {
public:
	FrameBoneModel(wxWindow* parent, wxWindowID id = wxID_ANY,
			const wxString& title = _("Bone Model Setup"), const wxPoint& pos =
					wxDefaultPosition, const wxSize& size = wxSize(672, 458),
			long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	virtual ~FrameBoneModel();


	bool TransferDataToWindow();
	bool TransferDataFromWindow();

};

#endif /* SRC_GUI_FRAMEBONEMODEL_H_ */
