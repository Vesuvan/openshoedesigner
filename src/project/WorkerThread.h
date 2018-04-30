///////////////////////////////////////////////////////////////////////////////
// Name               : WorkerThread.h
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

#ifndef __WORKERTHREAD_H__
#define __WORKERTHREAD_H__

#include <stddef.h>
#include <wx/thread.h>

class Project;

/*!\class LastGenerationThread
 * \brief Thread for the loadheavy calculation of the volume
 *
 * This thread inscribes the volume with the bones of the foot.
 */

class WorkerThread:public wxThread {
public:
	WorkerThread(Project* project, size_t threadNr);
	virtual ~WorkerThread();

	wxThread::ExitCode Entry();

public:
	Project * project;
	size_t threadNr;
};

#endif /* __WORKERTHREAD_H__ */
