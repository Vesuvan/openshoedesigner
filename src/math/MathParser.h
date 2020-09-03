///////////////////////////////////////////////////////////////////////////////
// Name               : MathParser.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 24.10.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef MATHPARSER_H_
#define MATHPARSER_H_
/*!\class MathParser
 * \brief Simple single-line math parser
 *
 * Parses a single line into a double number.
 *
 * Supported functions:
 *  - + - * / ^ ( )
 *  - cos sin tan acos asin atan
 *  - exp log
 *  - sqrt cbrt
 *  - ceil floor round
 *  - abs
 *
 *  Standard values:
 *  - e and pi (both lowercase)
 */

#include <string>
#include <cstdint>
#include <map>

class MathParser {
public:
	MathParser(bool autoEvaluate = true);

	// Member functions
public:
	void SetString(const std::string & expression);
	std::string GetString(void) const;
	std::string GetString(const double& number);

	void SetNumber(const double& number);
	double GetNumber(void) const;
	double GetNumber(const std::string & expression);

	void SetUnit(const std::string & unit);
	std::string GetUnit(void) const;
	inline bool HasUnit(void) const
	{
		return !unit.empty();
	}

	std::string GetError(void) const;
	inline bool HasError(void) const
	{
		return !error.empty();
	}

	void ResetVariables(bool setStandard = true);
	void SetVariable(const std::string & variable, double value);
	double GetVariable(const std::string & variable) const;

	void ResetAllowedUnits(void);
	void AddAllowedUnit(const std::string & unit, double factor);

	bool Evaluate(void);

private:

	/*! \brief Parse a single token off the string and add it to the stack
	 *
	 * @return (bool) Success of operation
	 */
	bool GetNextToken(void);

	// Member variables
public:
	bool autoEvaluate; ///< Boolean: Evaluate the string instantly when it is passed into a MathParser object.
	bool addUnit; ///< Boolean: Add a unit to generated string?
	bool ignorecase; ///< Boolean: Ignore the case for variables.

	std::map <std::string, double> globals;
	std::map <std::string, double> allowedUnits;

private:
	std::string text;
	double number;
	std::string unit;
	std::string error;

	// Variables for parser:
	unsigned int strLength;

	enum class Expr {
		Empty, Text, Number, Operation, BracketOpen, BracketClose, End
	};

	static const unsigned int maxStackDepth = 64;
	unsigned int stackStartPos[maxStackDepth];
	unsigned int stackCharCount[maxStackDepth];
	Expr stackType[maxStackDepth];
	double stackNumber[maxStackDepth];

	unsigned int posStack;
	unsigned int posText;
	static std::string Lower(const std::string & s);

};

#endif /* MATHPARSER_H_ */
