///////////////////////////////////////////////////////////////////////////////
// Name               : Canvas3D.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.08.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef CANVAS3D_H_
#define CANVAS3D_H_

/*!\class Canvas3D
 * \brief ...
 *
 * ...
 */

#include "../3D/OpenGLCanvas.h"
#include "../3D/Vector3.h"
#include "../3D/Bone.h"

class Canvas3D:public OpenGLCanvas {
public:
	Canvas3D(wxFrame* parent);
	virtual ~Canvas3D();

	void SetBones(Bone* const bone);

	void Render();

private:
	Bone* bone;
};

#endif /* CANVAS3D_H_ */
