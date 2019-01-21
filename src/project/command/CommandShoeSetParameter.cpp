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
#include "../../gui/gui.h"

CommandShoeSetParameter::CommandShoeSetParameter(const wxString& name,
		Project* project, int parameter, wxString value)
		: wxCommand(true, name), project(project), parameter(parameter), value(
				value)
{
}

bool CommandShoeSetParameter::Do(void)
{
	if(project == NULL) return false;
	Shoe *shoe = &(project->shoe);

	oldValue = Replace(parameter, value);
	const bool hasChanged = !value.IsSameAs(oldValue);
	if(hasChanged){
		shoe->Modify(true);
		project->Update();
	}

	return hasChanged;
}

bool CommandShoeSetParameter::Undo(void)
{
	if(project == NULL) return false;
	Shoe *shoe = &(project->shoe);

	wxString currentValue;
	currentValue = Replace(parameter, oldValue);
	const bool hasChanged = !currentValue.IsSameAs(oldValue);
	if(hasChanged){
		shoe->Modify(true);
		project->Update();
	}

	return true;
}

wxString CommandShoeSetParameter::Replace(int parameter, wxString newValue)
{
	wxString lastValue;
	Shoe *shoe = &(project->shoe);
	ParameterFormula *param = GetParameterByID(shoe, parameter);
	lastValue = param->formula;
	param->formula = newValue;
	return lastValue;
}

ParameterFormula* CommandShoeSetParameter::GetParameterByID(Shoe *shoe, int id)
{
	switch(id){
	case ID_HEELHEIGHT:
		return &(shoe->heelHeight);
	case ID_BALLHEIGHT:
		return &(shoe->ballHeight);
	case ID_HEELPITCH:
		return &(shoe->heelPitch);
	case ID_TOESPRING:
		return &(shoe->toeSpring);
	case ID_UPPERLEVEL:
		return &(shoe->upperLevel);
	case ID_EXTRALENGTH:
		return &(shoe->extraLength);
	case ID_FOOTCOMPRESSION:
		return &(shoe->footCompression);
	default:
		throw(std::invalid_argument(
				std::string(__FILE__)
						+ " : Replace() : Passed invalid/unhandled ID ("
						+ std::to_string(parameter) + ")."));
	}
	return NULL;
}
