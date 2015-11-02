///////////////////////////////////////////////////////////////////////////////
// Name               : FrameFootParameter.h
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

#ifndef FRAMEFOOTPARAMETER_H_
#define FRAMEFOOTPARAMETER_H_

/*!\class FrameFootParameter
 * \brief GUI for setting up the foots parameter
 */

#include "gui.h"

class FrameFootParameter:public GUIFrameFootParameter {
public:
	FrameFootParameter(wxWindow* parent);
	virtual ~FrameFootParameter();

	virtual void OnClose(wxCloseEvent& event);
	virtual void OnCalculate(wxCommandEvent& event);
};

#endif /* FRAMEFOOTPARAMETER_H_ */