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

#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include <cstdio>

IniFile::Section::Parameter::Parameter(wxString name, wxString value) :
		name(name), value(value) {
}

IniFile::Section::Section(wxString name) :
		name(name) {
}

IniFile::IniFile(bool casesensitive) :
		casesensitive(casesensitive) {
}

IniFile::IniFile(wxString filename, bool casesensitive) :
		casesensitive(casesensitive) {
	ReadFile(filename);
}

IniFile::~IniFile() {
}

bool IniFile::ReadFile(wxString filename) {

	wxFileInputStream input(filename);
	if (!input.IsOk() || !input.CanRead())
		return false;

	wxTextInputStream text(input);
	wxString sectionName("default");

	section.clear();

	size_t lineCount = 0;
	while (!input.Eof()) {
		const wxString x = text.ReadLine();
		lineCount++;
		if (x.IsEmpty())
			continue;
		const int posFirstChar = x.find_first_not_of(" \f\n\r\t");
		const int posComment = x.find_first_of(";#-%");
		if (posFirstChar == std::string::npos)
			continue;
		if (posComment != std::string::npos && posComment == posFirstChar)
			continue;
		const int posLeftBracket = x.find_first_of('[');
		if (posLeftBracket != std::string::npos
				&& posLeftBracket == posFirstChar) {
			int posRightBracket = x.find_last_of(']');
			if (posRightBracket == std::string::npos) {
				printf("INI-File has a broken section header in line %lu.\n",
						lineCount);
				posRightBracket = x.length();
			}
			sectionName = x.substr(posLeftBracket + 1,
					posRightBracket - posLeftBracket - 1);
			continue;
		}
		int posEqual = x.find_first_of('=');
		if (posEqual != std::string::npos) {
			if (posEqual == 0) {
				printf(
						"In line %lu of the INI file there is no key before the equal sign.\n",
						lineCount);
				return false;
			}
			if (posEqual == x.length() - 1) {
				printf(
						"In line %lu of the INI file there is no value after the equal sign.\n",
						lineCount);
				return false;
			}
			const int poskey0 = x.find_first_not_of(" \f\n\r\t");
			const int poskey1 = x.find_last_not_of(" \f\n\r\t", posEqual - 1);
			const int posvalue0 = x.find_first_not_of(" \f\n\r\t",
					posEqual + 1);
			const int posvalue1 = x.find_last_not_of(" \f\n\r\t");

			wxString key = CleanString(
					x.substr(poskey0, poskey1 - poskey0 + 1));
			wxString value = CleanString(
					x.substr(posvalue0, posvalue1 - posvalue0 + 1));

			if (section.empty()
					|| (casesensitive
							&& section.back().name.Cmp(sectionName) != 0)
					|| (!casesensitive
							&& section.back().name.CmpNoCase(sectionName) != 0)) {
				IniFile::Section temp(sectionName);
				section.push_back(temp);
			}
			IniFile::Section::Parameter param(key, value);
			section.back().param.push_back(param);
		}
	}
	return true;
}

wxString IniFile::CleanString(wxString text) {
	const int n0 = text.find_first_of("\"");
	const int n1 = text.find_last_of("\"");
	if (n0 == std::string::npos || n1 == std::string::npos)
		return text;
	if (n0 == n1)
		return text;
	text = text.substr(n0, n1 - n0);
	return text;
}
