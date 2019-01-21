///////////////////////////////////////////////////////////////////////////////
// Name               : Shoe.h
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

#ifndef SHOE_H_
#define SHOE_H_

/*!\class Shoe
 * \brief Definition of a shoe
 *
 * Objects of this class keep a list of all the parameters describing
 * the bones. Furthermore the skin surrounding the bones is describes.
 * The third group of parameters describes the angles of the bones, thus
 * the position of the foot.
 *
 * The foots position is not part of the dataset, but has to be kept here,
 * because the functions generating the last need these informations as
 * well.
 */

#include <wx/string.h>
#include "foot/ParameterFormula.h"

class Shoe {
public:
	Shoe();
	virtual ~Shoe();

	bool IsModified(void) const; //!< Returns \b true if the measurements have been modified since last update.
	void Modify(bool modify = true);
	void Update(void);
	void Update(MathParser &parser);

public:
	ParameterFormula heelHeight;
	ParameterFormula ballHeight;
	ParameterFormula heelPitch;
	ParameterFormula toeSpring;

	ParameterFormula upperLevel;
	ParameterFormula extraLength;
	ParameterFormula footCompression;

private:
	bool modified;
};

#endif /* SHOE_H_ */
