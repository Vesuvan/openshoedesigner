///////////////////////////////////////////////////////////////////////////////
// Name               : Surface.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.06.2020
// Copyright          : (C) 2020 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_3D_SURFACE_H_
#define SRC_3D_SURFACE_H_
#include "Vector3.h"

/*!\class Surface
 * \brief Patch-surface using cubic interpolation
 *
 * Points in a patch:
 *
 * \htmlonly
 * <svg width="92" height="85"><g transform ="translate(0,-967.32306)">
 * <path d="m 19.189407,1029.9748 47.973516,10.7729 1.851608,-60.09305 -50.83509,8.75305 z"  stroke="black"  stroke-width="2" fill="none" />
 * <text x="70" y="1049">1</text><text x="72" y="984.5">2</text><text x="6" y="990">3</text><text x="6" y="1042">0</text>
 * </g></svg>
 * \endhtmlonly
 *
 */

#include <array>
#include <vector>

class Surface {
public:
	struct Point {
		Point() = default;
		Vector3 p;
		Vector3 du = {1, 0, 0};
		Vector3 dv = {0, 1, 0};
	};
	struct Patch {
		Patch() = default;
		double u0 = 0.0;
		double u1 = 1.0;
		double v0 = 0.0;
		double v1 = 1.0;
		std::array <const Point *, 4> p;
		std::array <Vector3, 16> c;
		void Calculate(void);
		void Paint(void) const;
		Vector3 Normal(float u, float v) const;
		Vector3 operator()(float u, float v) const;
	};

	void SetSize(size_t U, size_t V);

	Point & P(const size_t idxu, const size_t idxv);
	const Point & P(const size_t idxu, const size_t idxv) const;

	Surface() = default;
	virtual ~Surface() = default;

	void CalculateDirections(void);
	void Calculate(void);
	void Paint(void) const;

	bool uCyclic = false;
	bool vCyclic = false;

private:
	std::vector <Point> p;
	std::vector <Patch> a;
	size_t U = 0;
	size_t V = 0;
};

#endif /* SRC_3D_SURFACE_H_ */
