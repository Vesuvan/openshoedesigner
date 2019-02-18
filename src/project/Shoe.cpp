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
		: heelHeight(_T("heelHeight")), ballHeight(_T("ballHeight")), heelPitch(
				_T("heelPitch")), toeSpring(_T("toeSpring")), upperLevel(
				_T("upperLevel")), extraLength(_T("extraLength")), footCompression(
				_T("footCompression"))
{
	heelHeight.formula = _T("3 cm");
	ballHeight.formula = _T("1 cm");
	heelPitch.formula = _T("5 deg");
	toeSpring.formula = _T("10 deg");
	upperLevel.formula = _T("0.8");
	extraLength.formula = _T("2 cm");
	footCompression.formula = _T("5/100");

	modified = true;
	Update();
}

Shoe::~Shoe()
{
}

bool Shoe::IsModified(void) const
{
	return modified;
}

void Shoe::Modify(bool modify)
{
	this->modified = modify;
}
void Shoe::Update(void)
{
	MathParser parser;
	parser.ignorecase = true;
	parser.AddAllowedUnit(_T("mm"), 1e-3);
	parser.AddAllowedUnit(_T("cm"), 1e-2);
	parser.AddAllowedUnit(_T("m"), 1);
	parser.AddAllowedUnit(_T("in"), 2.54e-2);
	parser.AddAllowedUnit(_T("ft"), 0.3048);
	parser.AddAllowedUnit(_T("rad"), 1);
	parser.AddAllowedUnit(_T("deg"), 0.017453);
	parser.AddAllowedUnit(_T("gon"), 0.015708);
	Update(parser);
}

void Shoe::Update(MathParser& parser)
{
	heelHeight.Update(parser);
	ballHeight.Update(parser);
	heelPitch.Update(parser);
	toeSpring.Update(parser);
	upperLevel.Update(parser);
	extraLength.Update(parser);
	footCompression.Update(parser);

	modified |= heelHeight.IsModified() | ballHeight.IsModified()
			| heelPitch.IsModified() | toeSpring.IsModified()
			| upperLevel.IsModified() | extraLength.IsModified()
			| footCompression.IsModified();
}
