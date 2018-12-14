///////////////////////////////////////////////////////////////////////////////
// Name               : FootMeasurements.h
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

#ifndef SRC_PROJECT_FOOT_FOOTMEASUREMENTS_H_
#define SRC_PROJECT_FOOT_FOOTMEASUREMENTS_H_

/*!\class FootMeasurements
 * \brief Measurements for the foot and the leg
 *
 * This class contains all measurements for the foot and the leg. It is also
 * used to calculate default values for all measurements.
 * In the case that only some basic measurements are recorded, this class uses
 * functions (MathParser) supplied for each measurement to calculate all
 * missing values.
 *
 * \image html "../../src/icons/FootMeasurements.svg"
 *
 * \image html "../../src/icons/LegMeasurements.svg"
 *
 */

#include "../../math/MathParser.h"
#include "ParameterFormula.h"
#include <wx/string.h>

class FootMeasurements {

public:
	enum sizetype {
		EU, //!< European shoe size in Paris Point
		US, //!< US shoe size, Brannok scale
		CN, //!< Chinese shoe size
		UK, //!< United Kingdom shoe size
		JP, //!< Japanese shoe size
		AU, //!< Australian shoe size
		mm, //!< Foot length in mm
		cm, //!< Foot length in cm
		in, //!< Foot length in inch
		ft  //!< Foot length in feet
	};

public:
	FootMeasurements();
	virtual ~FootMeasurements();

	bool IsModified(void) const; //!< Returns \b true if the measurements have been modified since last update.
	void Modify(bool modify = true);
	void Update(void);
	void Update(MathParser &parser);

	void SetDefaults(void);
	double GetSize(sizetype type) const;

private:
	bool modified;

public:

	ParameterFormula legLengthDifference; // The shorter leg has a negative reading. The other leg has 0.

	// Measurements for the foot
	ParameterFormula footLength;
	ParameterFormula ballGirth;
	ParameterFormula waistGirth;
	ParameterFormula instepGirth;
	ParameterFormula longHeelGirth;
	ParameterFormula shortHeelGirth;
	ParameterFormula angleMixing;

	// Measurements for the leg
	ParameterFormula belowCrutchGirth;
	ParameterFormula belowCrutchLevel;
	ParameterFormula middleOfCalfGirth;
	ParameterFormula middleOfCalfLevel;
	ParameterFormula aboveKneeGirth;
	ParameterFormula aboveKneeLevel;
	ParameterFormula overKneeCapGirth;
	ParameterFormula overKneeCapLevel;
	ParameterFormula belowKneeGirth;
	ParameterFormula belowKneeLevel;
	ParameterFormula middleOfShankGirth;
	ParameterFormula middleOfShankLevel;
	ParameterFormula aboveAnkleGirth;
	ParameterFormula aboveAnkleLevel;
	ParameterFormula overAnkleBoneGirth;
	ParameterFormula overAnkleBoneLevel;
};

#endif /* SRC_PROJECT_FOOT_FOOTMEASUREMENTS_H_ */
