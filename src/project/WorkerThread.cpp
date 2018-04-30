///////////////////////////////////////////////////////////////////////////////
// Name               : WorkerThread.cpp
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

#include "WorkerThread.h"
#include "Project.h"
#include "../gui/IDs.h"

WorkerThread::WorkerThread(Project * project, size_t threadNr)
		: wxThread(wxTHREAD_JOINABLE)
{
	this->project = project;
	this->threadNr = threadNr;
}

WorkerThread::~WorkerThread()
{
}

wxThread::ExitCode WorkerThread::Entry()
{
	if(threadNr > 1) return (wxThread::ExitCode) 1;
	if(TestDestroy()) return (wxThread::ExitCode) 2;
	while(project->ThreadNeedsCalculations(threadNr) && !TestDestroy()){
		project->ThreadCalculate(threadNr);
		wxQueueEvent(project,
				new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH));
	}
	if(threadNr == 0){
		wxQueueEvent(project, new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_THREADDONE_0));
	}
	if(threadNr == 1){
		wxQueueEvent(project, new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED,
		ID_THREADDONE_1));
	}
	return (wxThread::ExitCode) 0;
}
