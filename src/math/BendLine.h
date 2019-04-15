///////////////////////////////////////////////////////////////////////////////
// Name               : BendLine.h
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

#ifndef SRC_3D_BENDLINE_H_
#define SRC_3D_BENDLINE_H_

/*!\class BendLine
 * \brief Bend line with kernels for smooth bending
 *
 * kg = @(x) exp(-(x.^2)/2)/sqrt(2*pi);
 *
 * kp = @(x) exp(-abs(x))/2;
 *
 * ke = @(x) 3/4*max((1-x.^2),0);
 *
 * kc = @(x) 1./(pi*(1+x.^2));
 *
 */

#include <cstddef>
#include <vector>

class BendLine {
public:
	BendLine();
	virtual ~BendLine();

	enum Kernel {
		Gauss, Picard, Epanechnikov, Cauchy
	};

	void SetCount(size_t N);
	void InitAngle(double a = 0);
	void SetBend(double angle, double x0, double sigma = 0.1, Kernel kernel =
			Gauss);
	void Finish(double L = 1.0);

	size_t N;
	std::vector <double> angle;
	std::vector <double> x;
	std::vector <double> y;
};

#endif /* SRC_3D_BENDLINE_H_ */
