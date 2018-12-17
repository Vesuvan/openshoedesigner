///////////////////////////////////////////////////////////////////////////////
// Name               : IniFile.cpp
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

#include "IniFile.h"

#include <iostream>
#include <fstream>
#include <string>

IniFile::IniFile()
{
}

IniFile::IniFile(std::string filename)
{
	ReadFile(filename);
}

IniFile::~IniFile()
{
}

bool IniFile::ReadFile(std::string filename)
{
	std::ifstream is(filename);
	std::string txt;
	while(!is.eof()){
		std::getline(is, txt);
		if(txt.empty())continue;
		size_t n0 = txt.find_first_not_of(' ');
		if(n0 == std::string::npos)continue;
		size_t n1 = txt.find_last_not_of(' ');
		txt = txt.substr(n0,n1-n0+1);
		if(txt.substr(0,1).compare(";")==0)continue;
		if(txt.substr(0,1).compare("[")==0){
			size_t n2 = txt.find_first_of(']');
			std::string name = txt.substr(1,n2-1);
			std::cout << "Section: " << name << '\n';
			continue;
		}
		size_t n3 = txt.find_first_of('=');
		if(n3==std::string::npos)
			return false; // This is not a INI file (or it is broken)

		std::string key = txt.substr(0,n3);
		size_t n4 = key.find_first_of(' ');
		if(n4 != std::string::npos)
			key = key.substr(0,n4);
		std::string value = txt.substr(n3+1,txt.length()-n3-1);
		size_t n5 = value.find_first_not_of(' ');
		if(n5 != std::string::npos)
			value = value.substr(n5,value.length()-n5);

		std::cout << '\t' << key << '\t' << "= " << value << '\n';
	}

	is.close();
	return true;
}
