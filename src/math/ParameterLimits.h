///////////////////////////////////////////////////////////////////////////////
// Name               : ParameterLimits.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 02.07.2019
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

#ifndef SRC_MATH_PARAMETERLIMITS_H_
#define SRC_MATH_PARAMETERLIMITS_H_

/*!\class ParameterLimits
 * \brief Additional errors for optimizers, if parameters leave the valid range
 *
 * The NelderMeadOptimizer does not care for the form of the error function, as
 * long as the gradient points to the minimum. This class provides a term, that
 * can be added to the error returned to the optimizer. This term forces the
 * parameters to stay within a well defined range by adding a penalty outside
 * the allowed area.
 * If the parameter is outside an error of a*(paramvalue-limit)+b is added.
 */

#include <cstddef>
#include <vector>

class ParameterLimits {
private:
	class Limit {
	public:
		Limit();
		size_t index;
		double minval;
		double maxval;
		double a;
		double b;
	};
public:
	ParameterLimits();
	virtual ~ParameterLimits();

	void Clear();

	void AddLimit(size_t index, double min, double max, double a = 1.0,
			double b = 1e3);
	void AddLimitMin(size_t index, double min, double a = 1.0,
			double b = 1e3);
	void AddLimitMax(size_t index, double max, double a = 1.0,
			double b = 1e3);

	double Evaluate(const std::vector <double> &param) const;

private:
	std::vector <Limit> limits;
};

#endif /* SRC_MATH_PARAMETERLIMITS_H_ */
