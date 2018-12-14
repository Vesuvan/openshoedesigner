///////////////////////////////////////////////////////////////////////////////
// Name               : CommandFootModelSetParameter.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 19.02.2018
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

#ifndef __COMMANDFOOTMODELSETPARAMETER_H__
#define __COMMANDFOOTMODELSETPARAMETER_H__

#include <wx/cmdproc.h>
#include <wx/string.h>

#include "../Project.h"
#include "../ProjectView.h"

class CommandFootModelSetParameter:public wxCommand {
public:
	CommandFootModelSetParameter(const wxString& name, Project* project,
			size_t boneNr, Bone::stringIdentifier field, wxString newFormula);

	bool Do(void);
	bool Undo(void);

protected:
	Project* project;
	ProjectView::Side activeSide;
	size_t boneNr;
	Bone::stringIdentifier field;
	wxString newFormula;
	wxString oldFormulaL;
	wxString oldFormulaR;
};

#endif /* __COMMANDFOOTMODELSETPARAMETER_H__ */
