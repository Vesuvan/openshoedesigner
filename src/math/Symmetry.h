///////////////////////////////////////////////////////////////////////////////
// Name               : Symmetry.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 27.05.2019
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

#ifndef SRC_MATH_SYMMETRY_H_
#define SRC_MATH_SYMMETRY_H_

/*!\class Symmetry
 * \brief Fourier-transform-based symmetry search
 *
 * Uses the result of the FourierTransform class to find symmetries in polygons.
 * Allows for adding multiple testing Polygon3%s and combining the result.
 *
 * The symmetry axes are found by calculating a core desity estimation on the
 * symmetry axes provided at each frequency.
 */

#include <vector>
#include "../3D/Vector3.h"
#include "FourierTransform.h"

class Symmetry {
public:
	Symmetry();
	virtual ~Symmetry();

	void InitSupport(size_t N);

	void AddTransform(const FourierTransform &transform);

	void FindPeaks(void);

	void Paint(void) const;

public:
	double minsymmetry;
	double sigma;
	Vector3 center;
	Vector3 localx;
	Vector3 localy;
	std::vector <double> support;
	std::vector <double> angle;
	std::vector <double> strength;

private:
	static double Epanechnikov(double x);

};

#endif /* SRC_MATH_SYMMETRY_H_ */
