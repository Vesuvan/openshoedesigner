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
#include "../gui/gui.h"

Shoe::Shoe()
		: heelHeight("heelHeight"), ballHeight("ballHeight"), heelPitch(
				"heelPitch"), toeSpring("toeSpring"), bigToeAngle(
				"bigToeAngle"), littleToeAngle("littleToeAngle"), ballMeasurementAngle(
				"ballMeasurementAngle"), heelDirectionAngle(
				"heelDirectionAngle"), upperLevel("upperLevel"), extraLength(
				"extraLength"), footCompression("footCompression")
{
	heelHeight.formula = "3 cm";
	ballHeight.formula = "1 cm";
	heelPitch.formula = "5 deg";
	toeSpring.formula = "10 deg";
	upperLevel.formula = "0.8";
	extraLength.formula = "footLength/15";
	footCompression.formula = "5/100";

	bigToeAngle.formula = "6 deg";
	littleToeAngle.formula = "2 deg";
	ballMeasurementAngle.formula = "10 deg";
	heelDirectionAngle.formula = "10 deg";

	Update();
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

void Shoe::Update(MathParser& parser)
{

	bigToeAngle.Update(parser);
	littleToeAngle.Update(parser);
	ballMeasurementAngle.Update(parser);
	heelDirectionAngle.Update(parser);
	extraLength.Update(parser);
	footCompression.Update(parser);

	heelHeight.Update(parser);
	ballHeight.Update(parser);
	heelPitch.Update(parser);
	toeSpring.Update(parser);
	upperLevel.Update(parser);

	modified |= heelHeight.IsModified() | ballHeight.IsModified()
			| heelPitch.IsModified() | toeSpring.IsModified()
			| upperLevel.IsModified() | extraLength.IsModified()
			| footCompression.IsModified();
}

bool Shoe::IsValidID(int id)
{
	switch(id){
	case ID_BIGTOEANGLE:
	case ID_LITTLETOEANGLE:
	case ID_BALLMEASUREMENTANGLE:
	case ID_HEELDIRECTIONANGLE:
	case ID_HEELHEIGHT:
	case ID_BALLHEIGHT:
	case ID_HEELPITCH:
	case ID_TOESPRING:
	case ID_UPPERLEVEL:
	case ID_EXTRALENGTH:
	case ID_FOOTCOMPRESSION:
		return true;
	}
	return false;
}

std::string Shoe::GetName(int id)
{
	switch(id){
	case ID_BIGTOEANGLE:
		return std::string("BigToeAngle");
	case ID_LITTLETOEANGLE:
		return std::string("LittleToeAngle");
	case ID_BALLMEASUREMENTANGLE:
		return std::string("BallMeasurementAngle");
	case ID_HEELDIRECTIONANGLE:
		return std::string("HeelDirectionAngle");
	case ID_HEELHEIGHT:
		return std::string("HeelHeight");
	case ID_BALLHEIGHT:
		return std::string("BallHeight");
	case ID_HEELPITCH:
		return std::string("HeelPitch");
	case ID_TOESPRING:
		return std::string("ToeSpring");
	case ID_UPPERLEVEL:
		return std::string("UpperLevel");
	case ID_EXTRALENGTH:
		return std::string("ExtraLenght");
	case ID_FOOTCOMPRESSION:
		return std::string("FootCompression");
	default:
		throw(std::invalid_argument(
				std::string(__FILE__) + " : GetName : Passed invalid ID."));
	}
}

ParameterFormula& Shoe::GetParameter(int id)
{
	switch(id){
	case ID_BIGTOEANGLE:
		return bigToeAngle;
	case ID_LITTLETOEANGLE:
		return littleToeAngle;
	case ID_BALLMEASUREMENTANGLE:
		return ballMeasurementAngle;
	case ID_HEELDIRECTIONANGLE:
		return heelDirectionAngle;
	case ID_HEELHEIGHT:
		return heelHeight;
	case ID_BALLHEIGHT:
		return ballHeight;
	case ID_HEELPITCH:
		return heelPitch;
	case ID_TOESPRING:
		return toeSpring;
	case ID_UPPERLEVEL:
		return upperLevel;
	case ID_EXTRALENGTH:
		return extraLength;
	case ID_FOOTCOMPRESSION:
		return footCompression;
	default:
		throw(std::invalid_argument(
				std::string(__FILE__) + " : GetParameter : Passed invalid ID."));
	}
}

const ParameterFormula& Shoe::GetParameter(int id) const
{
	switch(id){
	case ID_BIGTOEANGLE:
		return bigToeAngle;
	case ID_LITTLETOEANGLE:
		return littleToeAngle;
	case ID_BALLMEASUREMENTANGLE:
		return ballMeasurementAngle;
	case ID_HEELDIRECTIONANGLE:
		return heelDirectionAngle;
	case ID_HEELHEIGHT:
		return heelHeight;
	case ID_BALLHEIGHT:
		return ballHeight;
	case ID_HEELPITCH:
		return heelPitch;
	case ID_TOESPRING:
		return toeSpring;
	case ID_UPPERLEVEL:
		return upperLevel;
	case ID_EXTRALENGTH:
		return extraLength;
	case ID_FOOTCOMPRESSION:
		return footCompression;
	default:
		throw(std::invalid_argument(
				std::string(__FILE__) + " : GetParameter : Passed invalid ID."));
	}
}
