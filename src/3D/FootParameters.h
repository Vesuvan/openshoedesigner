///////////////////////////////////////////////////////////////////////////////
// Name               : FootParameters.h
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

#ifndef FOOTPARAMETERS_H_
#define FOOTPARAMETERS_H_

/*!\class FootParameters
 * \brief Parameters describing the shape of the last
 * Objects of this class keep a list of all the parameters describing
 * the bones. Furthermore the skin surrounding the bones is describes.
 * The third group of parameters describes the angles of the bones, thus
 * the position of the foot.
 *
 * The foots position is not part of the dataset, but has to be kept here,
 * because the functions generating the last need these informations as
 * well.
 */

class FootParameters {
public:
	FootParameters();
	virtual ~FootParameters();

	float angle_1X;
	float angle_1Y;
	float angle_2X;
	float angle_3Y;
};

#endif /* FOOTPARAMETERS_H_ */
