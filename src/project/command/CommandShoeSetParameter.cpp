///////////////////////////////////////////////////////////////////////////////
// Name               : CommandShoeSetParameter.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.05.2018
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

#include "CommandShoeSetParameter.h"

CommandShoeSetParameter::CommandShoeSetParameter(const wxString& name,
		Project* project, int fieldNr, wxString newExpression)
		: wxCommand(true, name)
{
	this->project = project;
	this->fieldNr = fieldNr;
	this->newExpression = newExpression;
}

bool CommandShoeSetParameter::Do(void)
{
	if(project == NULL) return false;
	switch(fieldNr){
	case 0:
		oldExpression = project->shoe.heelHeight.formula;
		project->shoe.heelHeight.formula = newExpression;
		break;
	case 1:
		oldExpression = project->shoe.ballHeight.formula;
		project->shoe.ballHeight.formula = newExpression;
		break;
	case 2:
		oldExpression = project->shoe.toeSpring.formula;
		project->shoe.toeSpring.formula = newExpression;
		break;
	default:
		return false;
	}
//	project->Update(Project::UpdateFoot, Project::Both);
	return true;
}

bool CommandShoeSetParameter::Undo(void)
{
	if(project == NULL) return false;
	switch(fieldNr){
	case 0:
		project->shoe.heelHeight.formula = oldExpression;
		break;
	case 1:
		project->shoe.ballHeight.formula = oldExpression;
		break;
	case 2:
		project->shoe.toeSpring.formula = oldExpression;
		break;
	default:
		return false;
	}
//	project->Update(Project::UpdateFoot, Project::Both);
	return true;
}

