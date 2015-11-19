///////////////////////////////////////////////////////////////////////////////
// Name               : FrameFoot.h
// Purpose            : GUI for setting up the foots parameter
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.10.2015
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

#ifndef FRAMEFOOT_H_
#define FRAMEFOOT_H_

/*!\class FrameFoot
 * \brief GUI for setting up the foots parameter
 */

#include "gui.h"

#include "../project/Foot.h"

class FrameFoot:public GUIFrameFoot {
public:
	FrameFoot(wxWindow* parent, Foot* foot);
	virtual ~FrameFoot();
	virtual void OnClose(wxCommandEvent& event);
	virtual void OnCloseX(wxCloseEvent& event);
	virtual void OnText(wxCommandEvent& event);
	virtual void OnCellChange(wxGridEvent& event);

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

private:
	Foot* foot;
};

#endif /* FRAMEFOOT_H_ */
