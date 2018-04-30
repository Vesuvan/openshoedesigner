///////////////////////////////////////////////////////////////////////////////
// Name               : CommandFootSetSize.h
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.04.2018
// Copyright          : (C) 2018 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef __COMMANDFOOTSETSIZE_H__
#define __COMMANDFOOTSETSIZE_H__

#include <wx/cmdproc.h>
#include <wx/string.h>

#include "../Project.h"

class CommandFootSetSize:public wxCommand {
public:
	CommandFootSetSize(const wxString& name, Project* project, Foot::sizeparameter param, double value);

	bool Do(void);
	bool Undo(void);

protected:
	Project* project;
	Project::Side active;
	Foot::sizeparameter param;
	double value;
	double oldValueL;
	double oldValueR;
};

#endif /* __COMMANDFOOTSETSIZE_H__ */
