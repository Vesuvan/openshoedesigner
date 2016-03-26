///////////////////////////////////////////////////////////////////////////////
// Name               : FrameWalkcycleSupport.cpp
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

#include "FrameWalkcycleSupport.h"
#include "IDs.h"

FrameWalkcycleSupport::FrameWalkcycleSupport(wxWindow* parent, Project* project) :
		GUIFrameWalkcycleSupport(parent)
{
	this->project = project;
}

FrameWalkcycleSupport::~FrameWalkcycleSupport()
{
}

void FrameWalkcycleSupport::OnCloseX(wxCloseEvent& event)
{
	this->Hide();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHMAINGUI);
	ProcessEvent(selectEvent);
}

void FrameWalkcycleSupport::OnToggleAnkleLock(wxCommandEvent& event)
{
}

void FrameWalkcycleSupport::OnChoiceDisplay(wxCommandEvent& event)
{
}
