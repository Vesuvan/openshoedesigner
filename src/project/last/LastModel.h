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
/*!\class LastModel
 * \brief Rescales and handles a last
 *
 * This class reads in a list from a STL or OBJ (Wavefront) file and displays the result.
 * It analyses and normalises the form of the last. This last is the rescaled and adapted
 * to the foot measurements and the shoe form.
 *
 * This last is used as the starting point for the upper pattern and the sole generation.
 *
 * Alternatively this class takes over the data from the bone model and provides the data
 * to the abovementioned steps. In this case the data is not transformed and adapted. This
 * step has already been done on the foot-model.
 */

#include "../../3D/AffineTransformMatrix.h"
#include "../../3D/Hull.h"
#include "../../3D/Polygon3.h"
#include "../../3D/Vector3.h"
#include "../../math/BendLine.h"
#include "../../math/FormFinder.h"
#include "../../math/KernelDensityEstimator.h"
#include "../../math/Symmetry.h"

#include <string>

class FootMeasurements;
class Shoe;
class LastModel {
public:
	std::string filename;

	std::vector <double> scalevalues;

//	double sx;
//	double sy;
//	double sz;

	Polygon3 loop;
	Polygon3 test;

	Polygon3 left;
	Polygon3 right;
	Polygon3 bottom;
	Polygon3 top;
	Polygon3 center;

	Symmetry symmetry;
	FormFinder formfinder;
	KernelDensityEstimator kde;
	AffineTransformMatrix coordsys;

	Hull hull;
	Hull resized;
	bool mirrored;

	LastModel();
	virtual ~LastModel();
	bool LoadModel(std::string filename);

	bool AnalyseForm(void);

	void UpdateForm(const FootMeasurements &measurements);
	void UpdatePosition(const Shoe &shoe, double offset = 0.0);
	void Paint(void) const;

	bool IsModified(void) const;
	void Modify(bool modified = true);
	bool modified;
private:
	static bool Vector3XLess(const Vector3 a, const Vector3 b);
};

#endif /* SRC_PROJECT_LAST_LASTMODEL_H_ */
