///////////////////////////////////////////////////////////////////////////////
// Name               : DependentVector.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 17.06.2019
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

#ifndef SRC_MATH_DEPENDENTVECTOR_H_
#define SRC_MATH_DEPENDENTVECTOR_H_

/*!\class DependentVector
 * \brief
 *
 * ...
 */

// http://www.parashift.com/c++-faq-lite/operator-overloading.html
// http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
//
#include <stddef.h>
#include <string>
#include <vector>

class DependentVector {
public:
	DependentVector();

	void Clear(void);
	void Resize(size_t N);
	void PushBack(double x, double y);
	size_t Size(void) const; //!< Size of the array

	void XLinspace(double t0, double t1, size_t N);
	void XSetCyclic(double cyclelength);
	void XSetLinear(void);
	bool IsCyclic(void) const;
	double CycleLength(void) const;

	void YInit(double value = 0.0);

	double& X(size_t index);
	const double& X(size_t index) const;

	double& Y(size_t index);
	const double& Y(size_t index) const;

	double& operator[](size_t index); //!< Access operator to the Y array
	const double& operator[](size_t index) const; //!< Read-only access operator to the Y array

	DependentVector& operator +=(const double val);
	DependentVector& operator -=(const double val);
	DependentVector& operator *=(const double val);
	DependentVector& operator /=(const double val);

	void Sort(void);
	void Reverse(void);
	void Resample(size_t Nnew);

	void CumSum(void);
	void Integrate(void);
	void CumProd(void);

	double Area(void) const;

	size_t FindPeaks(const double minvalue = 0.001);
	size_t FindValleys(const double minvalue = 0.001);

	size_t ResultSize(void) const;
	double ResultX(size_t index) const;
	double ResultY(size_t index) const;

	void Paint(void) const;
	static void PaintCircle(double radius); //TODO This function is in the wrong place/class (again). It needs a better "home".

	void Export(std::string filename) const; ///< Export as a Matlab/Octave .mat file.

private:
	bool cyclic;
	double cyclelength;
	std::vector <double> x;
	std::vector <double> y;
	std::vector <double> resultx;
	std::vector <double> resulty;
};

#endif /* SRC_MATH_DEPENDENTVECTOR_H_ */
