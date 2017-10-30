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
 * \brief Polynom up to an order of 4.
 *
 * This class contains a polynom with an order of 4. This polynom is intended for Spline3
 * interpolation. The setting functions support a number of one to four points.
 *
 * All formulas are calculated with the AXIOM computer algebra system.
 */

class Polynom {
public:
	Polynom();
	virtual ~Polynom();

	double c0;
	double c1;
	double c2;
	double c3;

	void Set4(double r0, double v0, double r1, double v1, double r2, double v2,
			double r3, double v3);
	void Set4(double r0, double v0, double dv0, double r1, double v1,
			double dv1);
	void Set3(double r0, double v0, double r1, double v1, double r2, double v2);
	void Set3(double r0, double v0, double dv0, double r1, double v1);
	void Set2(double r0, double v0, double r1, double v1);
	void Set2(double r0, double v0, double dv0);
	void Set1(double r0, double v0);

	Polynom Derive() const;
	Polynom Derive2() const;
	Polynom Derive3() const;

	double Evaluate(double r) const;
};

#endif /* POLYNOM_H_ */
