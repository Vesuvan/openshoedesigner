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

#include <stddef.h>
#include <functional>
#include <string>
#include <vector>

#include "../../3D/AffineTransformMatrix.h"
#include "../../3D/Hull.h"
#include "../../3D/Polygon3.h"
#include "../../3D/TestGrid.h"
#include "../../3D/Vector3.h"
#include "../../math/FormFinder.h"
#include "../../math/Symmetry.h"

class Insole;
class OpenGLText;
class FootMeasurements;
class Shoe;

class LastModel {
public:
	std::string filename;

private:
	Hull raw;
	BoundingBox rawBB;

	Polygon3 loop;

	Polygon3 planeXZ;
	DependentVector angleXZ;
	Polygon3 bottomleft;
	Polygon3 bottomright;

	Polygon3 bottom;
	Polygon3 top;

	Polygon3 HeelGirth;
	Polygon3 WaistGirth;
	Polygon3 LittleToeGirth;
	Polygon3 BigToeGirth;

	std::vector <double> scalevalues;
	Symmetry symmetry;
	FormFinder formfinder;
	AffineTransformMatrix coordsys;

private:
	// Class-global for debugging / painting during development
	KernelDensityEstimator kde;

	size_t idxZero = 0;
	size_t idxHeel = 0;
	size_t idxHeelPoint = 0;
	size_t idxHeelCenter = 0;
	size_t idxWaistBottom = 0;
	size_t idxLittleToeBottom = 0;
	size_t idxBigToeBottom = 0;
	size_t idxToeCenter = 0;
	size_t idxToePoint = 0;
	size_t idxToeTip = 0;
	size_t idxBigToeTop = 0;
	size_t idxLittleToeTop = 0;
	size_t idxWaistTop = 0;
	size_t idxTop = 0;

	double heela = 0.0;
	double toea = 0.0;

	DependentVector debug0;
	DependentVector debug1;
	DependentVector debug2;

	DependentVector debugA;
	DependentVector debugB;
	DependentVector debugC;

	TestGrid tg;

public:

	double param_soleangle = 35 * M_PI / 180;

	Hull resized;
	bool mirrored = false;

private:
	void PaintMarker(const size_t idx, const OpenGLText &font,
			const std::string & text) const;

public:
	LastModel();
	virtual ~LastModel() = default;

	bool LoadModel(std::string filename);

	void Transform(std::function <Vector3(Vector3)> func);

	void UpdateForm(const Insole & insole, const FootMeasurements & measurements);

	void Paint(void) const;
	void PaintAnalysis(void) const;

	void Mirror(void);

	bool IsModified(void) const;
	void Modify(bool modified = true);

private:
	bool modified = true;

	bool AnalyseForm(void);

	void ReorientPCA(void);
	bool ReorientSymmetry(void);
	bool ReorientSole(void);
	void ReorientFrontBack(void);
	void ReorientLeftRight(void);
	void FindAndReorientCenterplane(void);

	bool FindMarker(void);

	void FindOutline(void);

	void MarkMeasurements(void);

	void UpdateRawBoundingBox(void);
	DependentVector OrthogonalPoint(const Vector3 & p) const;
	size_t FindTopPoint(size_t idx, size_t idxStart, size_t idxEnd) const;

	static double RelValAt(const DependentVector & est, double x);

	static bool Vector3XLess(const Vector3 a, const Vector3 b);
};

#endif /* SRC_PROJECT_LAST_LASTMODEL_H_ */
