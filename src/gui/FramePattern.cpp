///////////////////////////////////////////////////////////////////////////////
// Name               : FramePattern.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : toby
// Created            : 31.10.2015
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
#include "FramePattern.h"

#include "IDs.h"

FramePattern::FramePattern(wxWindow* parent, Project* project) :
		GUIFramePattern(parent)
{
	this->project = project;
}

FramePattern::~FramePattern()
{
}

void FramePattern::OnCloseX(wxCloseEvent& event)
{
	this->Hide();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHMAINGUI);
	ProcessEvent(selectEvent);
}

void FramePattern::OnChoicePreset(wxCommandEvent& event)
{
}

void FramePattern::OnChoiceStyle(wxCommandEvent& event)
{
}

void FramePattern::OnScroll(wxScrollEvent& event)
{
}
