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
#include <map>
#include <string>

class ParameterFormula;
class Project;
class Shoe;

class CommandShoeSetParameter:public wxCommand {
public:
	CommandShoeSetParameter(const wxString& name, Project* project);

	void AddValue(const int key, const std::string value);

	bool Do(void);
	bool Undo(void);

protected:
	bool SetNew(const std::pair <int, std::string> & kv, ParameterFormula & pf);
	void SetOld(const std::pair <int, std::string> & kv, ParameterFormula & pf);

//	ParameterFormula* GetParameterByID(Shoe *shoe, int id);

	Project* project;

	std::map <int, std::string> newParameter;
	std::map <int, std::string> oldParameter;
};

#endif /* __COMMANDSHOESETPARAMETER_H__ */

