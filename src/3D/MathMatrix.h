///////////////////////////////////////////////////////////////////////////////
// Name               : MathMatrix.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 05.11.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef MATHMATRIX_H_
#define MATHMATRIX_H_

/*!\class MathMatrix
 * \brief Additional mathematical function for MatlabMatrix
 *
 */

#include "MatlabMatrix.h"

class MathMatrix:public MatlabMatrix {
public:
	enum Axis {
		X, Y, Z
	};
	enum Method {
		MaxValue, MinValue, MeanValue, Sum
	};
public:
	MathMatrix();
	virtual ~MathMatrix();

	double Min(void) const;
	double Max(void) const;
	double MaxAbs(void) const;

	void AlignAtZero(void);
	void Normalize(double max = 1.0);
	void Normalize(double min, double max);

	double Interp1(const double x) const;

	/*! \brief Mirror Volume
	 *
	 * Mirror the volume along an axis.
	 */
	void Mirror(Axis a);

	/*! \brief Rotate Volume
	 *
	 * Rotate the Volume around an axis. Some functions use this feature to access the model from all sides.
	 *
	 * @param a Axis of rotation (enum X,Y or Z).
	 * @param quarters Number of 90 degree turns to do.
	 */
	void Rotate(Axis a, int quarters);

	MathMatrix XRay(Method method) const;
};

#endif /* MATHMATRIX_H_ */
