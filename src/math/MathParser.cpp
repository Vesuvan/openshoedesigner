///////////////////////////////////////////////////////////////////////////////
// Name               : MathParser.cpp
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

#define _USE_MATH_DEFINES

#include "MathParser.h"

#include <cassert>
#include <cmath>

MathParser::MathParser(bool autoEvaluate)
{
	assert(maxStackDepth > 5);

	this->autoEvaluate = autoEvaluate;
	addUnit = false;
	ignorecase = false;
	number = 0.0;
	ResetVariables(true);
}

std::string MathParser::Lower(const std::string& s)
{
	std::string temp(s);
	for(auto & c : temp)
		if(c >= 'A' && c <= 'Z') c += ('a' - 'A');
	return temp;
}

void MathParser::SetString(const std::string & expression)
{
	text = expression;
	if(autoEvaluate) Evaluate();
}

std::string MathParser::GetString(void) const
{
	return text;
}

std::string MathParser::GetString(const double& number)
{
	this->number = number;
	text = std::to_string(number);
	return text;
}

void MathParser::SetNumber(const double& number)
{
	this->number = number;
	text = std::to_string(this->number);
	if(addUnit && !unit.empty()) text = text + " " + unit;
}

double MathParser::GetNumber(void) const
{
	return number;
}

double MathParser::GetNumber(const std::string& expression)
{
	text = expression;
	Evaluate();
	return number;
}

std::string MathParser::GetError(void) const
{
	return error;
}

void MathParser::SetUnit(const std::string& unit)
{
	this->unit = unit;
}

std::string MathParser::GetUnit(void) const
{
	return unit;
}

void MathParser::ResetVariables(bool setStandard)
{
	globals.clear();
	if(setStandard){
		globals["pi"] = M_PI;
		globals["e"] = M_E;
	}
}

void MathParser::SetVariable(const std::string& variable, double value)
{
	if(ignorecase)
		globals[Lower(variable)] = value;
	else
		globals[variable] = value;
}

double MathParser::GetVariable(const std::string & variable) const
{
	double x;
	if(ignorecase)
		x = globals.at(Lower(variable));
	else
		x = globals.at(variable);
	return x;
}

void MathParser::ResetAllowedUnits(void)
{
	allowedUnits.clear();
}

void MathParser::AddAllowedUnit(const std::string& unit, double factor)
{
	allowedUnits[unit] = factor;
}

bool MathParser::GetNextToken(void)
{
	if(posStack >= maxStackDepth){
		error = "Stack full.";
		return false;
	}

	// Remove spaces in front
	while(posText < strLength && text[posText] == ' ')
		posText++;

	// If nothing is left of the string, add expressionType::expressionType::expressionEnd and return.
	if(posText >= strLength){
		if(posStack > 0 && stackType[posStack - 1] == Expr::End) return false;
		stackStartPos[posStack] = 0;
		stackCharCount[posStack] = 0;
		stackType[posStack] = Expr::End;
		stackNumber[posStack] = 0.0;
		posStack++;
		return true;
	}

	// TODO: Put in counters to keep the numberparser from overflowing. Otherwise it may return wrong numbers.
	Expr type = Expr::Empty;
	Expr newType = Expr::Empty;
	size_t num = 0;
	int exp = 0;
	int shift = 0;
	bool negativeExponent = false;
	int state = 0;

	stackStartPos[posStack] = posText;

	while(posText < strLength){
		auto c = text[posText];

		if(c == ' ') newType = Expr::End;
		if(c == '(') newType = Expr::BracketOpen;
		if(c == ')') newType = Expr::BracketClose;
		if((c >= '0' && c <= '9') || c == '.' || c == ',') newType =
				Expr::Number;
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
				|| c == '%') newType = Expr::Text;
		if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^') newType =
				Expr::Operation;

		if(type == Expr::Number && state < 2 && (c == 'e' || c == 'E')) newType =
				Expr::Number;
		if(type == Expr::Number && state == 2 && (c == '-' || c == '+')) newType =
				Expr::Number;

		if(newType == Expr::Empty){
			error = "Unknown characters in string.";
			return false;
		}

		if(type == Expr::Empty){
			type = newType;
		}else{
			if(type != newType){
				break;
			}
		}
		if(type == Expr::Number){

			if(state == 1 && (c == '.' || c == ',')){
				error = "Multiple '.' or ',' in a number.";
				return false;
			}
			if(state > 1 && (c == '.' || c == ',')){
				error = "'.' or ',' inside the exponent of a number.";
				return false;
			}

			switch(state){
			case 0:
				if(c == '.' || c == ',') state = 1;
				if(c == 'e' || c == 'E') state = 2;
				if(c >= '0' && c <= '9'){
					num *= 10;
					num += c - '0';
				}
				break;
			case 1:
				if(c == 'e' || c == 'E') state = 2;
				if(c >= '0' && c <= '9'){
					num *= 10;
					num += c - '0';
					shift--;
				}
				break;
			case 2:
				if(c == '-') negativeExponent = true;
				if(c >= '0' && c <= '9'){
					exp *= 10;
					exp += c - '0';
				}
				state = 3;
				break;
			case 3:
				if(c >= '0' && c <= '9'){
					exp *= 10;
					exp += c - '0';
				}
				break;
			}

		}
		posText++;
		if(type == Expr::BracketOpen || type == Expr::BracketClose
				|| type == Expr::Operation) break;
	}

	if(type != Expr::Empty){
		stackCharCount[posStack] = posText - stackStartPos[posStack];
		stackType[posStack] = type;
		if(type == Expr::Number){
			if(negativeExponent) exp = -exp;
			stackNumber[posStack] = (double) num
					* pow(10, double(exp) + (double) shift);
		}else{
			stackNumber[posStack] = 0.0;
		}
		posStack++;
	}

	return true;
}

bool MathParser::Evaluate(void)
{
	error.clear();
	if(text.empty()){
		error = "Expression empty.";
		return false;
	}

	strLength = text.size();
	posText = 0;
	posStack = 0;
	number = 0;
	bool flag;

	while(GetNextToken()){
		flag = true;
		while(flag){
			flag = false;

			// Replace variables
			if(posStack >= 2 && stackType[posStack - 2] == Expr::Text){
				std::string variable = text.substr(stackStartPos[posStack - 2],
						stackCharCount[posStack - 2]);
				if(ignorecase){
					if(globals.find(Lower(variable)) != globals.end()){
						stackNumber[posStack - 2] = globals[Lower(variable)];
						stackType[posStack - 2] = Expr::Number;
						flag = true;
					}
				}else{
					if(globals.count(variable) == 1){
						stackNumber[posStack - 2] = globals[variable];
						stackType[posStack - 2] = Expr::Number;
						flag = true;
					}
				}
			}

			// Replace units
			if(posStack >= 2 && stackType[posStack - 1] == Expr::Text
					&& !allowedUnits.empty()){
				std::string temp = text.substr(stackStartPos[posStack - 1],
						stackCharCount[posStack - 1]);
				if(allowedUnits.count(temp) == 1
						&& stackType[posStack - 2] == Expr::Number){
					stackNumber[posStack - 2] *= allowedUnits[temp];
					posStack--;
					flag = true;
				}
			}

			// Remove Brackets.
			if(posStack >= 4 && stackType[posStack - 2] == Expr::BracketClose
					&& stackType[posStack - 3] == Expr::Number
					&& stackType[posStack - 4] == Expr::BracketOpen){
				stackType[posStack - 4] = stackType[posStack - 3];
				stackNumber[posStack - 4] = stackNumber[posStack - 3];
				stackStartPos[posStack - 4] = stackStartPos[posStack - 3];
				stackCharCount[posStack - 4] = stackCharCount[posStack - 3];
				stackType[posStack - 3] = stackType[posStack - 1];
				stackNumber[posStack - 3] = stackNumber[posStack - 1];
				stackStartPos[posStack - 3] = stackStartPos[posStack - 1];
				stackCharCount[posStack - 3] = stackCharCount[posStack - 1];
				posStack -= 2;
				flag = true;
			}

			// Process functions.
			if(posStack >= 3 && stackType[posStack - 2] == Expr::Number
					&& stackType[posStack - 3] == Expr::Text){
				std::string command = text.substr(stackStartPos[posStack - 3],
						stackCharCount[posStack - 3]);
				const std::string cmdL = Lower(command);
				bool foundcommand = false;
				if(cmdL.compare("cos") == 0){
					stackNumber[posStack - 3] = cos(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("sin") == 0){
					stackNumber[posStack - 3] = sin(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("tan") == 0){
					stackNumber[posStack - 3] = tan(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("acos") == 0){
					stackNumber[posStack - 3] = acos(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("asin") == 0){
					stackNumber[posStack - 3] = asin(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("atan") == 0){
					stackNumber[posStack - 3] = atan(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("exp") == 0){
					stackNumber[posStack - 3] = exp(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("log") == 0){
					if(stackNumber[posStack - 2] <= 0.0){
						error = "log of a negative number.";
						return false;
					}
					stackNumber[posStack - 3] = log(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("sqrt") == 0){
					if(stackNumber[posStack - 2] < 0.0){
						error = "sqrt of a negative number.";
						return false;
					}
					stackNumber[posStack - 3] = sqrt(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("cbrt") == 0){
					stackNumber[posStack - 3] = cbrt(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("ceil") == 0){
					stackNumber[posStack - 3] = ceil(stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("floor") == 0){
					stackNumber[posStack - 3] = floor(
							stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("round") == 0){
					stackNumber[posStack - 3] = round(
							stackNumber[posStack - 2]);
					foundcommand = true;
				}
				if(cmdL.compare("abs") == 0){
					stackNumber[posStack - 3] = fabs(stackNumber[posStack - 2]);
					foundcommand = true;
				}

				if(foundcommand){
					stackType[posStack - 3] = Expr::Number;
					stackType[posStack - 2] = stackType[posStack - 1];
					stackNumber[posStack - 2] = stackNumber[posStack - 1];
					stackStartPos[posStack - 2] = stackStartPos[posStack - 1];
					stackCharCount[posStack - 2] = stackCharCount[posStack - 1];
					posStack -= 1;
					flag = true;
				}
			}

			// Negative numbers.
			if((posStack == 3 && stackType[posStack - 2] == Expr::Number
					&& stackType[posStack - 3] == Expr::Operation)
					|| (posStack >= 4 && stackType[posStack - 2] == Expr::Number
							&& stackType[posStack - 3] == Expr::Operation
							&& stackType[posStack - 4] != Expr::Number)){

				auto op = text.at(stackStartPos[posStack - 3]);
				if(op == '-'){
					stackNumber[posStack - 3] = -stackNumber[posStack - 2];
					stackType[posStack - 3] = Expr::Number;
					stackType[posStack - 2] = stackType[posStack - 1];
					stackNumber[posStack - 2] = stackNumber[posStack - 1];
					stackStartPos[posStack - 2] = stackStartPos[posStack - 1];
					stackCharCount[posStack - 2] = stackCharCount[posStack - 1];
					posStack -= 1;
					flag = true;
				}
			}

			// Add, Sub, Mult, Div, Power. (also '^' before '*', '/' before '+', '-')
			if(posStack >= 4 && stackType[posStack - 2] == Expr::Number
					&& stackType[posStack - 3] == Expr::Operation
					&& stackType[posStack - 4] == Expr::Number){
				// Current operation is in op, the next one is in op2. op2 is used to decide, if an
				// operation can be done right away or we have to do op2 first.
				auto op = text.at(stackStartPos[posStack - 3]);
				auto op2 = text.at(stackStartPos[posStack - 1]);
				if(stackType[posStack - 1] != Expr::Operation || (op == '^')
						|| ((op == '*' || op == '/') && (op2 != '^'))
						|| ((op == '+' || op == '-')
								&& (op2 != '*' && op2 != '/' && op2 != '^'))){
					if(op == '+') stackNumber[posStack - 4] =
							stackNumber[posStack - 4]
									+ stackNumber[posStack - 2];
					if(op == '-') stackNumber[posStack - 4] =
							stackNumber[posStack - 4]
									- stackNumber[posStack - 2];
					if(op == '*') stackNumber[posStack - 4] =
							stackNumber[posStack - 4]
									* stackNumber[posStack - 2];
					if(op == '/'){
						if(stackNumber[posStack - 2] == 0.0){
							error = "Division by 0.";
							return false;
						}
						stackNumber[posStack - 4] = stackNumber[posStack - 4]
								/ stackNumber[posStack - 2];
					}
					if(op == '^') stackNumber[posStack - 4] = pow(
							stackNumber[posStack - 4],
							stackNumber[posStack - 2]);
					stackType[posStack - 3] = stackType[posStack - 1];
					stackNumber[posStack - 3] = stackNumber[posStack - 1];
					stackStartPos[posStack - 3] = stackStartPos[posStack - 1];
					stackCharCount[posStack - 3] = stackCharCount[posStack - 1];
					posStack -= 2;
					flag = true;
				}
			}

		}
	}

	// Check if stack could be totally reduced into a Number + EndSymbol or Number + Text + EndSymbol.
	// In the second case, assume that the text is a unit.

	switch(posStack){
	case 0:
		error = "This should not be possible.";
		break;
	case 1:
		error = "Expression empty.";
		break;
	case 2:
		if(stackType[1] == Expr::End && stackType[0] == Expr::Number){
			number = stackNumber[0];
			unit.clear();
		}else{
			error = "Cannot be reduced to a number.";
		}
		break;
	case 3:
		if(allowedUnits.empty() && stackType[2] == Expr::End
				&& stackType[1] == Expr::Text && stackType[0] == Expr::Number){
			number = stackNumber[0];
			unit = text.substr(stackStartPos[1], stackCharCount[1]);
		}else{
			error = "Cannot be reduced to a number.";
		}
		break;
	default:
		error = "Could not parse expression completely.";
		break;
	}

	return !HasError();
}

