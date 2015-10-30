///////////////////////////////////////////////////////////////////////////////
// Name               : FrameLastParameter.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 04.10.2015
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

#ifndef FRAMELASTPARAMETER_H_
#define FRAMELASTPARAMETER_H_

/*!\class FrameLastParameter
 * \brief GUI for setting up a last
 */

#include "gui.h"

class FrameLastParameter:public GUIFrameLastParameter {
public:
	FrameLastParameter(wxWindow* parent, FootParameters * param);
	virtual ~FrameLastParameter();

	bool TransferDataToWindow();
	virtual void OnClose(wxCloseEvent& event);
	virtual void OnScroll(wxScrollEvent& event);
	virtual void OnText(wxCommandEvent& event);

private:
	FootParameters * param;
};

#endif /* FRAMELASTPARAMETER_H_ */
