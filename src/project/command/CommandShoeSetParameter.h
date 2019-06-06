///////////////////////////////////////////////////////////////////////////////
// Name               : CommandShoeSetParameter.h
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

#ifndef __COMMANDSHOESETPARAMETER_H__
#define __COMMANDSHOESETPARAMETER_H__

/*!\class CommandShoeSetParameter
 * \brief Command to set the parameters of the shoe
 *
 * ...
 */

#include <wx/cmdproc.h>
#include <wx/string.h>

#include "../../math/ParameterFormula.h"
#include "../Project.h"

class CommandShoeSetParameter:public wxCommand {
public:
	CommandShoeSetParameter(const wxString& name, Project* project,
			int parameter, wxString value);

	bool Do(void);
	bool Undo(void);

protected:
	wxString Replace(int parameter, wxString newValue);
	ParameterFormula* GetParameterByID(Shoe *shoe, int id);

	Project* project;
	int parameter;
	wxString value;
	wxString oldValue;
};

#endif /* __COMMANDSHOESETPARAMETER_H__ */

