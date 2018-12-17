///////////////////////////////////////////////////////////////////////////////
// Name               : IniFile.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.11.2018
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

#ifndef SRC_PROJECT_INIFILE_H_
#define SRC_PROJECT_INIFILE_H_

/*!\class IniFile
 * \brief ...
 *
 * ...
 */

#include <string>
#include <vector>
#include <map>

class IniFile {
public:
	IniFile();
	IniFile(std::string filename);
	virtual ~IniFile();
	bool ReadFile(std::string filename);


private:
	std::vector<std::string>sectionname;
	std::vector<std::map<std::string,std::string>> section;
};

#endif /* SRC_PROJECT_INIFILE_H_ */
