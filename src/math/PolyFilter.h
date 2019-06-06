///////////////////////////////////////////////////////////////////////////////
// Name               : PolyFilter.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.06.2019
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

#ifndef SRC_MATH_POLYFILTER_H_
#define SRC_MATH_POLYFILTER_H_
#include <cstddef>
#include <vector>

/*!\class PolyFilter
 * \brief Polynom interpolator
 *
 * This class sets up filter for polynom interpolation up to order 3.
 *
 * The basis formula is \f$ a\cdot x^3 + b\cdot x^2 + c\cdot x + d \f$
 *
 * For lower order polynoms the higher factors are set to zero.
 *
 * The result i.e. the filters as columns of a matrix
 * ~~~{.m}
 *  [filter_a(:), filter_b(:), filter_c(:), filter_d(:)]
 * ~~~
 * is identical to the Matlab / Octave command
 * ~~~{.m}
 *  transpose(pinv(vander(0:(size-1),order)))
 * ~~~
 */

class PolyFilter {
public:
	PolyFilter();
	virtual ~PolyFilter();

	void Init(size_t order, size_t N);

	size_t GetSize(void) const;
	size_t GetOrder(void) const;

	double FilterA(const std::vector <double> &vec, size_t pos) const;
	double FilterB(const std::vector <double> &vec, size_t pos) const;
	double FilterC(const std::vector <double> &vec, size_t pos) const;
	double FilterD(const std::vector <double> &vec, size_t pos) const;

	bool GetExtremum(double &pos, const double a, const double b,
			const double c, const double d) const;
	bool GetExtremum2(double &pos, const double a, const double b,
			const double c, const double d) const;
	bool GetInflectionPoint(double &pos, const double a, const double b,
			const double c, const double d) const;

private:
	size_t order;
	std::vector <double> filter_a;
	std::vector <double> filter_b;
	std::vector <double> filter_c;
	std::vector <double> filter_d;
};

#endif /* SRC_MATH_POLYFILTER_H_ */
