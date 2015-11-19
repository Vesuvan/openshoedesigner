///////////////////////////////////////////////////////////////////////////////
// Name               : FrameShoe.h
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

#ifndef FRAMESHOE_H_
#define FRAMESHOE_H_

/*!\class FrameShoe
 * \brief GUI for setting up a last
 */

#include "../project/Shoe.h"
#include "gui.h"

class FrameShoe:public GUIFrameShoe {
public:
	FrameShoe(wxWindow* parent, Shoe* shoe);
	virtual ~FrameShoe();

	bool TransferDataToWindow();
	virtual void OnCloseX(wxCloseEvent& event);
	virtual void OnText(wxCommandEvent& event);
	virtual void OnClick(wxCommandEvent& event);
	virtual void OnPreset(wxCommandEvent& event);

private:
	Shoe* shoe;
};

#endif /* FRAMESHOE_H_ */
