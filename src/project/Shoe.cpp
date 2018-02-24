///////////////////////////////////////////////////////////////////////////////
// Name               : Shoe.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.09.2015
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

#include "Shoe.h"

#include "../math/MathParser.h"

Shoe::Shoe()
{
	exprHeelHeight = _T("2 cm");
	exprBallHeight = _T("0 deg");
	exprToeAngle = _T("0 deg");

	heelHeight = 0.02;
	ballHeight = 0.0;
	toeAngle = 0.0;

	mixing = 0.1;
}

Shoe::~Shoe()
{
}

bool Shoe::Evaluate(double L, double W, double H, double A)
{
	MathParser parser(false);
	parser.AddAllowedUnit(_T("mm"), 1e-3);
	parser.AddAllowedUnit(_T("cm"), 1e-2);
	parser.AddAllowedUnit(_T("m"), 1);
	parser.AddAllowedUnit(_T("in"), 2.54e-2);
	parser.AddAllowedUnit(_T("ft"), 0.3048);
	parser.AddAllowedUnit(_T("rad"), 1);
	parser.AddAllowedUnit(_T("deg"), 0.017453);
	parser.AddAllowedUnit(_T("gon"), 0.015708);

	parser.SetVariable(_T("L"), L);
	parser.SetVariable(_T("W"), W);
	parser.SetVariable(_T("H"), H);
	parser.SetVariable(_T("A"), A);

	parser.SetString(exprHeelHeight);
	if(!parser.Evaluate()) return false;
	heelHeight = parser.GetNumber();
	parser.SetString(exprBallHeight);
	if(!parser.Evaluate()) return false;
	ballHeight = parser.GetNumber();
	parser.SetString(exprToeAngle);
	if(!parser.Evaluate()) return false;
	toeAngle = parser.GetNumber();

	return true;
}
