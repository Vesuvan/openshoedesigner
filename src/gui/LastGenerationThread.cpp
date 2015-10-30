///////////////////////////////////////////////////////////////////////////////
// Name               : LastGenerationThread.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 05.10.2015
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

#include "LastGenerationThread.h"
#include "IDs.h"

LastGenerationThread::LastGenerationThread(wxFrame* frame, Foot * foot,
		Volume * volume) :
		wxThread(wxTHREAD_JOINABLE)
{
	this->frame = frame;
	this->foot = foot;
	this->volume = volume;
}

LastGenerationThread::~LastGenerationThread()
{
}

void* LastGenerationThread::Entry()
{
	volume->Clear();
	if(TestDestroy()) return NULL;
	foot->AddToVolume(volume);
	if(TestDestroy()) return NULL;
	volume->MarchingCubes(0.5);

	wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, ID_VOLUMEDONE);
	wxPostEvent(frame, event);

	return NULL;
}

void LastGenerationThread::OnExit()
{
}
