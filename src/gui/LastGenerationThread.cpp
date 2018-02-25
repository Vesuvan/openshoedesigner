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

LastGenerationThread::LastGenerationThread(wxFrame* frame, Project * project)
		: wxThread(wxTHREAD_JOINABLE)
{
	this->frame = frame;
	this->project = project;
}

LastGenerationThread::~LastGenerationThread()
{
}

void* LastGenerationThread::Entry()
{
	if(TestDestroy()) return NULL;
	if(project->updateState < 1) return NULL;
	while(project->Update()){
		if(TestDestroy()){
			project->updateState = 1;
			return NULL;
		}
	}
	wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED, ID_THREADLASTDONE);
	wxPostEvent(frame, event);
	return NULL;
}

void LastGenerationThread::OnExit()
{
}
