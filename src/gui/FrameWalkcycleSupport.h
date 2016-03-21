///////////////////////////////////////////////////////////////////////////////
// Name               : FrameWalkcycleSupport.h
// Purpose            : GUI for setting up the walkcycle supports
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

#ifndef FRAMEWALKCYCLESUPPORT_H_
#define FRAMEWALKCYCLESUPPORT_H_

/*!\class FrameWalkcycleSupport
 * \brief GUI for setting up the walkcycle supports
 */

#include "gui.h"
#include "../project/Shoe.h"

class FrameWalkcycleSupport:public GUIFrameWalkcycleSupport {
public:
	FrameWalkcycleSupport(wxWindow* parent, Project* project);
	virtual ~FrameWalkcycleSupport();

	virtual void OnCloseX(wxCloseEvent& event);
	virtual void OnToggleAnkleLock(wxCommandEvent& event);
	virtual void OnChoiceDisplay(wxCommandEvent& event);

	Project* project;
};

#endif /* FRAMEWALKCYCLESUPPORT_H_ */
