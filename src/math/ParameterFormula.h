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

#ifndef _PARAMETERFORMULA_H_
#define _PARAMETERFORMULA_H_
/*!\class ParameterFormula
 * \brief Parameter with the capability of keeping a separate formula and value.
 *
 */

#include "MathParser.h"

#include <string>

class ParameterFormula {
public:
	ParameterFormula(const std::string & name, const std::string & formula = std::string(""));
	virtual ~ParameterFormula();

	// Copy assignment, because of const-name. (Copy constructors have no problems with the const.)
	ParameterFormula& operator=(const ParameterFormula & other);

	const std::string name;
	std::string formula;
	double value; //!< Calculated value
	bool modified; //!< True if the value has changed by more than FLT_EPSILON in the last call to Update.
	bool errorFlag; //!< \b True if an error occured during evaluation of the formula.
	std::string errorStr; //!< Errorstring if an error occured otherwise empty.

	/*! \brief Calculates the value from the formula
	 *
	 * The formula and the variables in the MathParser are used to calculate the value
	 * The parser is extended with the result of the calculation in the end
	 *
	 * \param parser Pointer to a Mathparser
	 * \return Calculated value
	 */
	double Update(MathParser & parser);
	void Modify(bool modify = true);
	bool IsModified(void) const;
};

#endif /* _PARAMETERFORMULA_H_ */
