///////////////////////////////////////////////////////////////////////////////
// Name               : ParameterFormula.h
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

#ifndef SRC_PROJECT_FOOT_PARAMETERFORMULA_H_
#define SRC_PROJECT_FOOT_PARAMETERFORMULA_H_
/*!\class ParameterFormula
 * \brief Parameter with the cpability of keeping a separate formula and value.
 *
 */

#include <wx/string.h>
#include "../../math/MathParser.h"

class ParameterFormula {
public:
	ParameterFormula(const wxString name, const wxString formula = _T(""));
	virtual ~ParameterFormula();

	const wxString name;
	wxString formula;
	double value; //!< Calculated value
	bool modified; //!< True if the value has changed by more than FLT_EPSILON in the last call to Update.
	bool errorFlag; //!< \b True if an error occured during evaluation of the formula.
	wxString errorStr; //!< Errorstring if an error occured otherwise empty.

	/*! \brief Calculates the value from the formula
	 *
	 * The formula and the variables in the MathParser are used to calculate the value
	 * The parser is extended with the result of the calculation in the end
	 *
	 * \param parser Pointer to a Mathparser
	 * \return Calculated value
	 */
	double Update(MathParser &parser);
	bool IsModified(void) const;
};

#endif /* SRC_PROJECT_FOOT_PARAMETERFORMULA_H_ */
