///////////////////////////////////////////////////////////////////////////////
// Name               : CommandProjectSetLegLengthDifference.cpp
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

#include "CommandProjectSetLegLengthDifference.h"

CommandProjectSetLegLengthDifference::CommandProjectSetLegLengthDifference(
		const wxString& name, Project* project, double value)
		: wxCommand(true, name)
{
	this->project = project;
	this->value = value;
	this->oldValue = 0.0;
}

bool CommandProjectSetLegLengthDifference::Do(void)
{
	if(project == NULL) return false;
	return false;
//	oldValue = project->legLengthDifference;
//	project->legLengthDifference = value;
//	project->Update(Project::UpdateFoot, Project::Both);
//	return true;
}

bool CommandProjectSetLegLengthDifference::Undo(void)
{
	if(project == NULL) return false;
	return false;

//	project->legLengthDifference = oldValue;
//	project->Update(Project::UpdateFoot, Project::Both);
//	return true;
}
