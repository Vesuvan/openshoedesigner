///////////////////////////////////////////////////////////////////////////////
// Name               : LastModel.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 02.03.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_PROJECT_LAST_LASTMODEL_H_
#define SRC_PROJECT_LAST_LASTMODEL_H_

#include <string>

#include "../../3D/Geometry.h"
#include "../../math/BendLine.h"
#include "../foot/FootMeasurements.h"
#include "../Shoe.h"
#include "PolyCylinder.h"

/*!\class LastModel
 * \brief ...
 *
 * ...
 */

class LastModel {
public:
	std::string filename;
	PolyCylinder data;
	double sx;
	double sy;
	double sz;

	Geometry geometry;

	BendLine center;
	bool mirrored;

	LastModel();
	virtual ~LastModel();
	bool LoadModel(std::string filename);

	void UpdateForm(const FootMeasurements &measurements);
	void UpdatePosition(const Shoe &shoe, double offset = 0.0);
	void UpdateGeometry(void);
	void Paint(void) const;

	bool IsModified(void) const;
	void Modify(bool modified = true);
	bool modified;
};

#endif /* SRC_PROJECT_LAST_LASTMODEL_H_ */
