///////////////////////////////////////////////////////////////////////////////
// Name               : CoreDensityEstimator.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 05.06.2019
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

#ifndef SRC_MATH_COREDENSITYESTIMATOR_H_
#define SRC_MATH_COREDENSITYESTIMATOR_H_

/*!\class CoreDensityEstimator
 * \brief Core density estimation
 *
 * This Class does a (cyclic) core density estimation.
 */

#include <cstddef>
#include <vector>

class CoreDensityEstimator {
public:
	CoreDensityEstimator();
	virtual ~CoreDensityEstimator();

	void SetRange(double t0, double t1, size_t N, bool cyclic = false);
	void Zero(void);

	enum coretype {
		Epanechnikov
	};

	void Add(coretype core, double sigma, double pos, double weight = 1.0);

	void Paint(void) const;

private:
	bool cyclic;
	std::vector <double> x;
	std::vector <double> y;
};

#endif /* SRC_MATH_COREDENSITYESTIMATOR_H_ */
