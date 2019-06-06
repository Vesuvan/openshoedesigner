///////////////////////////////////////////////////////////////////////////////
// Name               : ParameterFormula.cpp
// Purpose            : Store a parameter with a formula
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.11.2018
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

#include "ParameterFormula.h"

#include <cfloat>
#include <cmath>

ParameterFormula::ParameterFormula(const wxString name, const wxString formula)
		: name(name), formula(formula)
{
	value = 0.0;
	errorFlag = false;
	modified = false;
}

ParameterFormula::~ParameterFormula()
{
}

ParameterFormula& ParameterFormula::operator=(const ParameterFormula& other)
{
	formula = other.formula;
	value = other.value;
	modified = other.modified;
	errorFlag = other.errorFlag;
	errorStr = other.errorStr;
	return *this;
}

void ParameterFormula::Modify(bool modify)
{
	this->modified = modify;
}

bool ParameterFormula::IsModified(void) const
{
	return modified;
}

double ParameterFormula::Update(MathParser& parser)
{
	const double oldValue = value;
	value = parser.GetNumber(formula);
	errorStr = parser.GetError();
	errorFlag = !errorStr.IsEmpty();
	if(errorFlag){
		value = oldValue;
		modified = false;
	}else{
		modified = (fabs(value - oldValue) > FLT_EPSILON);
	}
	parser.SetVariable(name, value);
	return value;
}
