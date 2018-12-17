///////////////////////////////////////////////////////////////////////////////
// Name               : FootMeasurements.cpp
// Purpose            : Measurements for the foot (and the leg)
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.11.2018
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

#include "../foot/FootMeasurements.h"

#include <wx/chartype.h>
#include <math.h>

FootMeasurements::FootMeasurements()
		: legLengthDifference(_T("legLengthDifference")), footLength(
				_T("footLength")), ballGirth(_T("ballGirth")), waistGirth(
				_T("waistGirth")), instepGirth(_T("instepGirth")), longHeelGirth(
				_T("longHeelGirth")), shortHeelGirth(_T("shortHeelGirth")), angleMixing(
				_T("angleMixing")), belowCrutchGirth(_T("belowCrutchGirth")), belowCrutchLevel(
				_T("belowCrutchLevel")), middleOfCalfGirth(
				_T("middleOfCalfGirth")), middleOfCalfLevel(
				_T("middleOfCalfLevel")), aboveKneeGirth(_T("aboveKneeGirth")), aboveKneeLevel(
				_T("aboveKneeLevel")), overKneeCapGirth(_T("overKneeCapGirth")), overKneeCapLevel(
				_T("overKneeCapLevel")), belowKneeGirth(_T("belowKneeGirth")), belowKneeLevel(
				_T("belowKneeLevel")), middleOfShankGirth(
				_T("middleOfShankGirth")), middleOfShankLevel(
				_T("middleOfShankLevel")), aboveAnkleGirth(
				_T("aboveAnkleGirth")), aboveAnkleLevel(_T("aboveAnkleLevel")), overAnkleBoneGirth(
				_T("overAnkleBoneGirth")), overAnkleBoneLevel(
				_T("overAnkleBoneLevel"))
{
	modified = false;

	SetDefaults();
	Update();
}

FootMeasurements::~FootMeasurements()
{
}

void FootMeasurements::SetDefaults(void)
{
	legLengthDifference.formula = _T("0.0");
	footLength.formula = _T("(39/3*2 - 1.5)/100");
	ballGirth.formula = _T("footLength*0.93");
	waistGirth.formula = _T("ballGirth");
	instepGirth.formula = _T("waistGirth*1.05");
	longHeelGirth.formula = _T("instepGirth*1.3");
	shortHeelGirth.formula = _T("longHeelGirth*0.95");
	angleMixing.formula = _T("0.1");
	belowCrutchGirth.formula = _T("footLength*2.5");
	belowCrutchLevel.formula = _T("footlength*3");
	middleOfCalfGirth.formula = _T("(belowCrutchGirth+footLength)/2");
	middleOfCalfLevel.formula = _T("belowCrutchLevel*0.825");
	aboveKneeGirth.formula = _T("footLength*1.4");
	aboveKneeLevel.formula = _T("middleOfCalfLevel*0.785");
	overKneeCapGirth.formula = _T("footLength*1.5");
	overKneeCapLevel.formula = _T("aboveKneeLevel-footLength/6");
	belowKneeGirth.formula = _T("footLength*1.2");
	belowKneeLevel.formula = _T("overKneeCapLevel-footLength/6");
	middleOfShankGirth.formula = _T("footLength*1.3");
	middleOfShankLevel.formula = _T("overKneeCapLevel*0.7");
	aboveAnkleGirth.formula = _T("footLength*0.8");
	aboveAnkleLevel.formula = _T("footLength/2");
	overAnkleBoneGirth.formula = _T("footLength");
	overAnkleBoneLevel.formula = _T("footLength/3");
}

void FootMeasurements::Update(void)
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

void FootMeasurements::Update(MathParser &parser)
{
	legLengthDifference.Update(parser);
	footLength.Update(parser);
	ballGirth.Update(parser);
	waistGirth.Update(parser);
	instepGirth.Update(parser);
	longHeelGirth.Update(parser);
	shortHeelGirth.Update(parser);
	angleMixing.Update(parser);
	belowCrutchGirth.Update(parser);
	belowCrutchLevel.Update(parser);
	middleOfCalfGirth.Update(parser);
	middleOfCalfLevel.Update(parser);
	aboveKneeGirth.Update(parser);
	aboveKneeLevel.Update(parser);
	overKneeCapGirth.Update(parser);
	overKneeCapLevel.Update(parser);
	belowKneeGirth.Update(parser);
	belowKneeLevel.Update(parser);
	middleOfShankGirth.Update(parser);
	middleOfShankLevel.Update(parser);
	aboveAnkleGirth.Update(parser);
	aboveAnkleLevel.Update(parser);
	overAnkleBoneGirth.Update(parser);
	overAnkleBoneLevel.Update(parser);

	modified = legLengthDifference.IsModified() | footLength.IsModified()
			| ballGirth.IsModified() | waistGirth.IsModified()
			| instepGirth.IsModified() | longHeelGirth.IsModified()
			| shortHeelGirth.IsModified() | angleMixing.IsModified()
			| belowCrutchGirth.IsModified() | belowCrutchLevel.IsModified()
			| middleOfCalfGirth.IsModified() | middleOfCalfLevel.IsModified()
			| aboveKneeGirth.IsModified() | aboveKneeLevel.IsModified()
			| overKneeCapGirth.IsModified() | overKneeCapLevel.IsModified()
			| belowKneeGirth.IsModified() | belowKneeLevel.IsModified()
			| middleOfShankGirth.IsModified() | middleOfShankLevel.IsModified()
			| aboveAnkleGirth.IsModified() | aboveAnkleLevel.IsModified()
			| overAnkleBoneGirth.IsModified() | overAnkleBoneLevel.IsModified();
}

bool FootMeasurements::IsModified(void) const
{
	return modified;
}

void FootMeasurements::Modify(bool modify)
{
	modified = modify;
}

double FootMeasurements::GetSize(sizetype type) const
{
	switch(type){
	case EU:
		return (footLength.value + 1.5e-2) * 150;
	case US:
		return (footLength.value) / 2.54e-2 * 3 - 21.5;
	case CN:
		return round((footLength.value * 100) / 0.5) * 0.5;
	case UK:
		return (footLength.value + 1.5e-2) / 8.46e-3 - 25;
	case JP:
		return round((footLength.value * 1000) / 5) * 5;
	case AU:
		return (footLength.value + 1.5e-2) / 8.46e-3 - 25;
	case mm:
		return footLength.value * 1000.0;
	case cm:
		return footLength.value * 100.0;
	case in:
		return footLength.value / 0.0254;
	case ft:
		return footLength.value / 0.3048;
	}
	return 0;
}
