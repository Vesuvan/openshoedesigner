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

#include "../../gui/gui.h"

#include <cmath>

FootMeasurements::FootMeasurements()
		: footLength("footLength"), ballWidth("ballWidth"), bigToeGirth(
				"bigToeGirth"), littleToeGirth("littleToeGirth"), waistGirth(
				"waistGirth"), heelGirth("heelGirth"), heelWidth("heelWidth"), angleMixing(
				"angleMixing"), belowCrutchGirth("belowCrutchGirth"), belowCrutchLevel(
				"belowCrutchLevel"), middleOfCalfGirth("middleOfCalfGirth"), middleOfCalfLevel(
				"middleOfCalfLevel"), aboveKneeGirth("aboveKneeGirth"), aboveKneeLevel(
				"aboveKneeLevel"), overKneeCapGirth("overKneeCapGirth"), overKneeCapLevel(
				"overKneeCapLevel"), belowKneeGirth("belowKneeGirth"), belowKneeLevel(
				"belowKneeLevel"), middleOfShankGirth("middleOfShankGirth"), middleOfShankLevel(
				"middleOfShankLevel"), aboveAnkleGirth("aboveAnkleGirth"), aboveAnkleLevel(
				"aboveAnkleLevel"), overAnkleBoneGirth("overAnkleBoneGirth"), overAnkleBoneLevel(
				"overAnkleBoneLevel")
{
	SetDefaults();
	Update();
}

void FootMeasurements::Modify(bool modify)
{
	modified = modify;
}

bool FootMeasurements::IsModified(void) const
{
	return modified;
}

void FootMeasurements::SetDefaults(void)
{
	footLength.formula = "(39/3*2-1.5)/100";
	ballWidth.formula = "footLength/2.5";
	bigToeGirth.formula = "ballWidth*2.1";
	littleToeGirth.formula = "ballWidth*2.1";
	waistGirth.formula = "bigToeGirth*0.9";
	heelGirth.formula = "waistGirth*1.3";
	heelWidth.formula = "ballWidth*3/4";

	angleMixing.formula = "0.1";

	belowCrutchGirth.formula = "footLength*2.5";
	belowCrutchLevel.formula = "footlength*3";
	middleOfCalfGirth.formula = "(belowCrutchGirth+footLength)/2";
	middleOfCalfLevel.formula = "belowCrutchLevel*0.825";
	aboveKneeGirth.formula = "footLength*1.4";
	aboveKneeLevel.formula = "middleOfCalfLevel*0.785";
	overKneeCapGirth.formula = "footLength*1.5";
	overKneeCapLevel.formula = "aboveKneeLevel-footLength/6";
	belowKneeGirth.formula = "footLength*1.2";
	belowKneeLevel.formula = "overKneeCapLevel-footLength/6";
	middleOfShankGirth.formula = "footLength*1.3";
	middleOfShankLevel.formula = "overKneeCapLevel*0.7";
	aboveAnkleGirth.formula = "footLength*0.8";
	aboveAnkleLevel.formula = "footLength/2";
	overAnkleBoneGirth.formula = "footLength";
	overAnkleBoneLevel.formula = "footLength/3";

}

void FootMeasurements::Update(void)
{
	MathParser parser;
	parser.ignorecase = true;
	parser.AddAllowedUnit("mm", 1e-3);
	parser.AddAllowedUnit("cm", 1e-2);
	parser.AddAllowedUnit("m", 1);
	parser.AddAllowedUnit("in", 2.54e-2);
	parser.AddAllowedUnit("ft", 0.3048);
	parser.AddAllowedUnit("rad", 1);
	parser.AddAllowedUnit("deg", 0.017453);
	parser.AddAllowedUnit("gon", 0.015708);
	Update(parser);
}

void FootMeasurements::Update(MathParser &parser)
{

	footLength.Update(parser);
	ballWidth.Update(parser);
	bigToeGirth.Update(parser);
	littleToeGirth.Update(parser);
	waistGirth.Update(parser);
	heelGirth.Update(parser);
	heelWidth.Update(parser);
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

	modified |= footLength.IsModified() | ballWidth.IsModified()
			| bigToeGirth.IsModified() | littleToeGirth.IsModified()
			| waistGirth.IsModified() | heelGirth.IsModified()
			| heelWidth.IsModified() | angleMixing.IsModified()
			| belowCrutchGirth.IsModified() | belowCrutchLevel.IsModified()
			| middleOfCalfGirth.IsModified() | middleOfCalfLevel.IsModified()
			| aboveKneeGirth.IsModified() | aboveKneeLevel.IsModified()
			| overKneeCapGirth.IsModified() | overKneeCapLevel.IsModified()
			| belowKneeGirth.IsModified() | belowKneeLevel.IsModified()
			| middleOfShankGirth.IsModified() | middleOfShankLevel.IsModified()
			| aboveAnkleGirth.IsModified() | aboveAnkleLevel.IsModified()
			| overAnkleBoneGirth.IsModified() | overAnkleBoneLevel.IsModified();
}

double FootMeasurements::GetSize(Type type) const
{
	switch(type){
	case Type::EU:
		return (footLength.value + 1.5e-2) * 150;
	case Type::US:
		return (footLength.value) / 2.54e-2 * 3 - 21.5;
	case Type::CN:
		return round((footLength.value * 100) / 0.5) * 0.5;
	case Type::UK:
		return (footLength.value + 1.5e-2) / 8.46e-3 - 25;
	case Type::JP:
		return round((footLength.value * 1000) / 5) * 5;
	case Type::AU:
		return (footLength.value + 1.5e-2) / 8.46e-3 - 25;
	case Type::mm:
		return footLength.value * 1000.0;
	case Type::cm:
		return footLength.value * 100.0;
	case Type::in:
		return footLength.value / 0.0254;
	case Type::ft:
		return footLength.value / 0.3048;
	}
	return 0;
}

bool FootMeasurements::IsValidID(int id)
{
	switch(id){
	case ID_MEASUREMENT_FOOTLENGTH:
	case ID_MEASUREMENT_BALLWIDTH:
	case ID_MEASUREMENT_BIGTOEGIRTH:
	case ID_MEASUREMENT_LITTLETOEGIRTH:
	case ID_MEASUREMENT_WAISTGIRTH:
	case ID_MEASUREMENT_HEELGIRTH:
	case ID_MEASUREMENT_HEELWIDTH:
	case ID_MEASUREMENT_ANGLEMIXING:
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
	case ID_MEASUREMENT_BELOWKNEELEVEL:
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return true;
	}
	return false;
}

std::string FootMeasurements::GetName(int id)
{
	switch(id){
	case ID_MEASUREMENT_FOOTLENGTH:
		return std::string("FootLength");
	case ID_MEASUREMENT_BALLWIDTH:
		return std::string("BallWidth");
	case ID_MEASUREMENT_BIGTOEGIRTH:
		return std::string("BigToeGirth");
	case ID_MEASUREMENT_LITTLETOEGIRTH:
		return std::string("LittleToeGirth");
	case ID_MEASUREMENT_WAISTGIRTH:
		return std::string("WaistGirth");
	case ID_MEASUREMENT_HEELGIRTH:
		return std::string("HeelGirth");
	case ID_MEASUREMENT_HEELWIDTH:
		return std::string("HeelWidth");

	case ID_MEASUREMENT_ANGLEMIXING:
		return std::string("AngleMixing");

	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		return std::string("BelowCrutchGirth");
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		return std::string("BelowCrutchLevel");
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		return std::string("MiddleOfCalfGirth");
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		return std::string("MiddleOfCalfLevel");
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		return std::string("AboveKneeGirth");
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		return std::string("AboveKneeLevel");
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		return std::string("OverKneeCapGirth");
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		return std::string("OverKneeCapLevel");
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		return std::string("BelowKneeGirth");
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		return std::string("BelowKneeLevel");
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		return std::string("MiddleOfShankGirth");
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		return std::string("MiddleOfShankLevel");
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		return std::string("AboveAnkleGirth");
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		return std::string("AboveAnkleLevel");
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		return std::string("OverAnkleBoneGirth");
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return std::string("OverAnkleBoneLevel");
	default:
		throw(std::invalid_argument(
				std::string(__FILE__) + " : GetName : Passed invalid ID."));
	}
}

ParameterFormula& FootMeasurements::GetParameter(int id)
{
	switch(id){
	case ID_MEASUREMENT_FOOTLENGTH:
		return footLength;
	case ID_MEASUREMENT_BALLWIDTH:
		return ballWidth;
	case ID_MEASUREMENT_BIGTOEGIRTH:
		return bigToeGirth;
	case ID_MEASUREMENT_LITTLETOEGIRTH:
		return littleToeGirth;
	case ID_MEASUREMENT_WAISTGIRTH:
		return waistGirth;
	case ID_MEASUREMENT_HEELGIRTH:
		return heelGirth;
	case ID_MEASUREMENT_HEELWIDTH:
		return heelWidth;
	case ID_MEASUREMENT_ANGLEMIXING:
		return angleMixing;
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		return belowCrutchGirth;
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		return belowCrutchLevel;
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		return middleOfCalfGirth;
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		return middleOfCalfLevel;
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		return aboveKneeGirth;
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		return aboveKneeLevel;
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		return overKneeCapGirth;
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		return overKneeCapLevel;
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		return belowKneeGirth;
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		return belowKneeLevel;
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		return middleOfShankGirth;
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		return middleOfShankLevel;
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		return aboveAnkleGirth;
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		return aboveAnkleLevel;
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		return overAnkleBoneGirth;
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return overAnkleBoneLevel;
	default:
		throw(std::invalid_argument(
				std::string(__FILE__)
						+ " : Replace() : Passed invalid/unhandled ID."));
	}
}

const ParameterFormula& FootMeasurements::GetParameter(int id) const
{
	switch(id){
	case ID_MEASUREMENT_FOOTLENGTH:
		return footLength;
	case ID_MEASUREMENT_BALLWIDTH:
		return ballWidth;
	case ID_MEASUREMENT_BIGTOEGIRTH:
		return bigToeGirth;
	case ID_MEASUREMENT_LITTLETOEGIRTH:
		return littleToeGirth;
	case ID_MEASUREMENT_WAISTGIRTH:
		return waistGirth;
	case ID_MEASUREMENT_HEELGIRTH:
		return heelGirth;
	case ID_MEASUREMENT_HEELWIDTH:
		return heelWidth;
	case ID_MEASUREMENT_ANGLEMIXING:
		return angleMixing;
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		return belowCrutchGirth;
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		return belowCrutchLevel;
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		return middleOfCalfGirth;
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		return middleOfCalfLevel;
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		return aboveKneeGirth;
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		return aboveKneeLevel;
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		return overKneeCapGirth;
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		return overKneeCapLevel;
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		return belowKneeGirth;
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		return belowKneeLevel;
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		return middleOfShankGirth;
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		return middleOfShankLevel;
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		return aboveAnkleGirth;
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		return aboveAnkleLevel;
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		return overAnkleBoneGirth;
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return overAnkleBoneLevel;
	default:
		throw(std::invalid_argument(
				std::string(__FILE__)
						+ " : Replace() : Passed invalid/unhandled ID."));
	}
}

