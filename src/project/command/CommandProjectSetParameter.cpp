///////////////////////////////////////////////////////////////////////////////
// Name               : CommandProjectSetParameter.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.04.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CommandProjectSetParameter.h"

#include "../../gui/gui.h"

CommandProjectSetParameter::CommandProjectSetParameter(const wxString& name,
		Project* project, int parameter, int value)
		: wxCommand(true, name), project(project), parameter(parameter), value(
				value)
{
	std::cout << "CommandProjectSetParameter: " << name << "\n";
	oldValue = 0;
}

bool CommandProjectSetParameter::Do(void)
{
	switch(parameter){
	case ID_MEASUREMENTSYMMETRY:
		oldMeasurements = project->measR;
		oldValue = project->measurementsSymmetric? -1 : 0;
		project->measR = project->measL;
		project->measR.Modify(true);
		project->measurementsSymmetric = (value != 0);
		break;
	case ID_FOOTMODEL:
		oldValue = (int) project->modeltype;
		project->modeltype = (Project::ModelType) value;
		break;
	case ID_MEASUREMENTSOURCE:
		oldValue = (int) project->measurementsource;
		project->measurementsource = (Project::MeasurementSource) value;
		break;
	case ID_SELECTCONSTRUCTION:
		oldValue = (int) project->generator;
		project->generator = (Project::Generator) value;
		break;
	default:
		return false;
	}
	std::cout << "Do.\n";
	project->Update();
	return true;
}

bool CommandProjectSetParameter::Undo(void)
{

	switch(parameter){
	case ID_MEASUREMENTSYMMETRY:
		project->measR = oldMeasurements;
		project->measR.Modify(true);
		project->measurementsSymmetric = (oldValue != 0);
		break;
	case ID_FOOTMODEL:
		project->modeltype = (Project::ModelType) oldValue;
		break;
	case ID_MEASUREMENTSOURCE:
		project->measurementsource = (Project::MeasurementSource) oldValue;
		break;
	case ID_SELECTCONSTRUCTION:
		project->generator = (Project::Generator) oldValue;
		break;
	default:
		return false;
	}
	std::cout << "Undo.\n";
	project->Update();
	return true;
}
