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
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <string>
#include <vector>

class DependentVector {
public:

	enum class Direction {
		first_risingabove,
		last_risingabove,
		first_fallingbelow,
		last_fallingbelow,
		first_passing,
		last_passing
	};

	struct Point {
		Point() = default;
		Point(size_t idx, double x, double y)
				: idx(idx), x(x), y(y)
		{
		}
		size_t idx = 0;
		double x = 0.0;
		double y = 0.0;
	};

	DependentVector() = default;
	virtual ~DependentVector() = default;

	void Clear(void);
	void Resize(size_t N);
	void PushBack(double x, double y);
	size_t Size(void) const; //!< Size of the array

	void XLinspace(double x0, double x1, size_t N = 0);
	void XSetCyclic(double cyclelength);
	void XSetLinear(void);
	bool IsCyclic(void) const;
	double CycleLength(void) const;

	void YInit(double value = 0.0);
	void YLinspace(double y0, double y1);

	double YatX(const double xval) const;
	double XatY(const double yval, Direction direction, size_t xstart = 0,
			size_t xend = (size_t) -1) const;
	size_t IatX(const double xval) const;
	size_t IatY(const double yval, Direction direction, size_t xstart = 0,
			size_t xend = (size_t) -1) const;

	double& X(size_t index);
	const double& X(size_t index) const;

	double& Y(size_t index);
	const double& Y(size_t index) const;

	double& operator[](size_t index); //!< Access operator to the Y array
	double operator[](size_t index) const; //!< Read-only access operator to the Y array

	DependentVector& operator-=(const DependentVector& a);
	friend DependentVector operator-(DependentVector a,
			const DependentVector& b)
	{
		a -= b;
		return a;
	}
	DependentVector operator-() const;

	DependentVector& operator +=(const double val);
	DependentVector& operator -=(const double val);
	DependentVector& operator *=(const double val);
	DependentVector& operator /=(const double val);

	void YLimit(double ymin, double ymax);

	DependentVector Range(size_t xstart = 0, size_t xend = (size_t) -1) const;
	void Sort(void);
	void Reverse(void);
	void Resample(size_t Nnew);
	void Unwrap(double tol = M_PI);

	void CumSum(void);
	void CumProd(void);
	void Integrate(void);
	void Derive(void);

	void Normalize(size_t xstart = 0, size_t xend = (size_t) -1);
	Point Max(size_t xstart = 0, size_t xend = (size_t) -1) const;
	Point Min(size_t xstart = 0, size_t xend = (size_t) -1) const;
	double Mean(void) const;
	double Area(void) const;

	std::vector <Point> FindPeaks(const double minvalue = -DBL_MAX,
			size_t xstart = 0, size_t xend = (size_t) -1);
	std::vector <Point> FindValleys(const double maxvalue = DBL_MAX,
			size_t xstart = 0, size_t xend = (size_t) -1);

	void Paint(void) const;
	static void PaintCircle(double radius); //TODO This function is in the wrong place/class (again). It needs a better "home".

	void Export(std::string filename) const; ///< Export as a Matlab/Octave .mat file.

private:
	bool cyclic = false;
	double cyclelength = 0;
	std::vector <double> x;
	std::vector <double> y;

private:
	mutable size_t searchspeedup = 0;
};

#endif /* SRC_MATH_DEPENDENTVECTOR_H_ */
