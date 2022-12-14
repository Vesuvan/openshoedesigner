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
 */

#include "KernelDensityEstimator.h"

class BendLine:public KernelDensityEstimator {
public:
	BendLine() = default;

	void AngleToPos(void);
};

#endif /* SRC_3D_BENDLINE_H_ */
