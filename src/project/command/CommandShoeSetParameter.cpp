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
#include "../../math/ParameterFormula.h"
#include "../Project.h"

CommandShoeSetParameter::CommandShoeSetParameter(const wxString& name,
		Project* project)
		: wxCommand(true, name), project(project)
{
}

void CommandShoeSetParameter::AddValue(const int key, const std::string value)
{
	newParameter[key] = value;
}
bool CommandShoeSetParameter::SetNew(const std::pair <int, std::string> & kv,
		ParameterFormula & pf)
{
	bool changed = pf.formula.compare(kv.second) != 0;
	oldParameter[kv.first] = pf.formula;
	pf.formula = kv.second;
	return changed;
}

void CommandShoeSetParameter::SetOld(const std::pair <int, std::string> & kv,
		ParameterFormula & pf)
{
	pf.formula = oldParameter[kv.first];
}

bool CommandShoeSetParameter::Do(void)
{
	if(project == NULL) return false;
	Shoe *shoe = &(project->shoe);

	bool hasChanged = false;
	for(auto & kv : newParameter){
		ParameterFormula & p = shoe->GetParameter(kv.first);
		hasChanged |= SetNew(kv, p);
	}
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
	for(auto & kv : oldParameter){
		ParameterFormula & p = shoe->GetParameter(kv.first);
		SetOld(kv, p);
	}
	shoe->Modify(true);
	project->Update();
	return true;
}

