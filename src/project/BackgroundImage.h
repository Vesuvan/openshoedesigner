///////////////////////////////////////////////////////////////////////////////
// Name               : BackgroundImage.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.01.2017
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

#ifndef BACKGROUNDIMAGE_H_
#define BACKGROUNDIMAGE_H_
/*!\class BackgroundImage
 * \brief Image in 3D space for loading reference images
 *
 */

#include "../3D/OpenGLImage.h"

class BackgroundImage:public OpenGLImage {
public:
	enum Orientation {
		Front, Back, Right, Left, Top, Bottom
	};

	BackgroundImage();
	virtual ~BackgroundImage();

	void Paint(void) const;

	Orientation orientation;
	bool showFront;
	bool showBack;
	GLfloat scale;
	GLfloat centerx;
	GLfloat centery;
	GLfloat rotate;
};

#endif /* BACKGROUNDIMAGE_H_ */
