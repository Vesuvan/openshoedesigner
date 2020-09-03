///////////////////////////////////////////////////////////////////////////////
// Name               : Polynom.h
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : toby
// Created            : 28.01.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef POLYNOM_H_
#define POLYNOM_H_

/*!\class Polynom
 * \brief Polynom.
 *
 * This class contains a polynom of arbitrary order.
 *
 * The coefficients are stored Matlab / Octave style: The first coefficient is the one for the highest power.
 *
 * e.g. \f[
 * 	f(r) = c_0\cdot r^3 + c_1\cdot r^2 + c_2 \cdot r + c_3
 * \f]
 * The vector returned by the stream output << can be used directly in the Matlab/Octave polyval command.
 *
 * \htmlonly
 * <svg width="300" height="200">
 * <path transform="translate(0,-852.35945)" d="m 280,1032.3594 -15,5 0,-10 15,5 -260,0 -2e-6,-160.00001 4.999999,15 -9.999999,0 5,-15 c 0,0 61.281556,160.00001 129.999982,160.00001 68.71843,0 129.99999,-160.00001 129.99999,-160.00001"  stroke="black"  stroke-width="2" fill="none" />
 * </svg>
 * \endhtmlonly
 *
 */

#include <stddef.h>
#include <ostream>
#include <vector>

class Polynom {
public:
	explicit Polynom(size_t N = 0);
	explicit Polynom(const std::vector <double> &vec);
	static Polynom ByValue(double r0, double v0); ///< Initialize by 1 point with position and value (actually only the value is used, because it is a constant)
	static Polynom ByValue(double r0, double v0, double r1, double v1); ///< Initialize by 2 points with position and value
	static Polynom ByValue(double r0, double v0, double r1, double v1,
			double r2, double v2); ///< Initialize by 3 points with position and value
	static Polynom ByValue(double r0, double v0, double r1, double v1,
			double r2, double v2, double r3, double v3); ///< Initialize by 4 points with position and value

	static Polynom ByDerivative(double r0, double v0, double dv0); ///< Initialize by 1 point with position, value and derivative
	static Polynom ByDerivative(double r0, double v0, double dv0, double r1,
			double v1); ///< Initialize by 1 point with position, value and derivative and a second point only with position and value
	static Polynom ByDerivative(double r0, double v0, double dv0, double r1,
			double v1, double dv1); ///< Initialize by 2 points with position, value and derivative

	static Polynom ByBezier(double v0);
	static Polynom ByBezier(double v0, double v1);
	static Polynom ByBezier(double v0, double v1, double v2);
	static Polynom ByBezier(double v0, double v1, double v2, double v3);

	size_t Size(void) const;
	size_t Order(void) const;
	void Resize(size_t N);

	double& operator[](size_t index); ///< Access the coefficients
	double operator[](size_t index) const; ///< Const access the coefficients

	Polynom& operator+=(const double &b);
	const Polynom operator+(const double& b) const;
	Polynom& operator-=(const double &b);
	const Polynom operator-(const double& b) const;
	Polynom& operator*=(const double &b);
	const Polynom operator*(const double& b) const;
	Polynom& operator/=(const double &b);
	const Polynom operator/(const double& b) const;

	Polynom& operator+=(const Polynom &b);
	const Polynom operator+(const Polynom& b) const;
	Polynom& operator-=(const Polynom &b);
	const Polynom operator-(const Polynom& b) const;
	Polynom& operator*=(const Polynom &b);
	const Polynom operator*(const Polynom& b) const;

	void ScaleX(double val); ///< Increase the width of the graph by a factor of val
	void ScaleY(double val); ///< Increase the height of the graph by a factor of val
	void ShiftX(double val); ///< Shift the graph right by val
	void ShiftY(double val); ///< Shift the graph up by val

	Polynom Derivative(size_t order = 1) const; ///< Return the derivative without changing the polynom
	void Derive(size_t order = 1); ///< Derive the polynom itself

	double Integral(double a, double b) const; ///< Evaluate the integral of the polynom between a and b
	Polynom Integral(size_t order = 1) const; ///< Return the integral of the polynom without changing it itself
	void Integrate(size_t order = 1); ///< Integrate the polynom. (The integration constant has to be added simply by the operator+

	bool ExtremumPos(double &x) const; ///< Return the positive extremum, if there is any (up to an order of 3 (4 coefficients))
	bool ExtremumNeg(double &x) const; ///< Return the negative extremum, if there is any (up to an order of 3 (4 coefficients))
	bool InflectionPoint(double &pos) const; ///< Return the inflection point (only working for an order of exactly 3 (4 coefficients))

	void InvertLinear(void); ///< If the polynom is a line (2 coefficients) and is not a constant, it is inverted.

	Polynom Reduce(size_t newOrder, double a, double b) const; // Generate a Polynom of reduced order, that fits the original one as close as possible in the range from a to b.

	double operator()(double x) const;

	/*! \brief Output coefficients
	 *~~~~~
	 * Polynom p = Polynom::ByValue(-1,1, 0,0, 1,1);
	 * std::cout << p << "\n";
	 *~~~~~
	 */
	friend std::ostream &operator<<(std::ostream &os, const Polynom &p)
	{
		os << "[";
		for(size_t n = 0; n < p.Size(); ++n){
			if(n > 0) os << ", ";
			os << p[n];
		}
		os << "]";
		return os;
	}
private:
	std::vector <double> c;
};

#endif /* POLYNOM_H_ */
