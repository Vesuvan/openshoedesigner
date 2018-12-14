///////////////////////////////////////////////////////////////////////////////
// Name               : Skeleton.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 18.02.2018
// Copyright          : (C) 2018 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_PROJECT_FOOT_SKELETON_H_
#define SRC_PROJECT_FOOT_SKELETON_H_

/*!\class Skeleton
 * \brief Collection of bones.
 *
 * Bones are enumerated for easier handling. A std::map<std::string, Bone> would be cleaner, but
 * in the end more difficult to use.
 */

#include "../../math/MathParser.h"
#include <wx/string.h>
#include <GL/gl.h>
#include <vector>

#include "../foot/Bone.h"

class Skeleton {
public:
	Skeleton();
	virtual ~Skeleton();

	Bone* AddBone(wxString name);

	bool Connect(wxString name1, wxString name2);

	void Setup(void);
	void Render(void) const;

	size_t GetBoneCount(void) const;

	void UpdateBonesFromFormula(MathParser* parser);

	void ResetRotation(void);
	void RestoreRotation(void);

	bool mirrored;

	std::vector <Bone> bones;
private:
	mutable GLuint m_gllist;
	mutable bool update;
};

#endif /* SRC_PROJECT_FOOT_SKELETON_H_ */
