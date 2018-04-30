///////////////////////////////////////////////////////////////////////////////
// Name               : Skeleton.cpp
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

#include "Skeleton.h"

#include <GL/gl.h>

Skeleton::Skeleton()
{
	mirrored = false;
	m_gllist = 0;
	update = true;
}

Skeleton::~Skeleton()
{
	if(m_gllist != 0) glDeleteLists(m_gllist, 1);
}

Bone* Skeleton::AddBone(wxString name)
{
	bones.push_back(Bone(name));
	return &(bones[bones.size() - 1]);
}

size_t Skeleton::GetBoneCount(void) const
{
	return bones.size();
}

bool Skeleton::Connect(wxString name1, wxString name2)
{
	size_t index1, index2;
	for(index1 = 0; index1 < bones.size(); index1++){
		if(bones[index1].name.Cmp(name1) == 0) break;
	}
	if(index1 == bones.size()) return false;
	for(index2 = 0; index2 < bones.size(); index2++){
		if(bones[index2].name.Cmp(name2) == 0) break;
	}
	if(index2 == bones.size()) return false;

	if(index1 < index2){
		bones[index2].connectTo = index1;
	}else{
		bones[index1].connectTo = index2;
	}
	return true;
}

void Skeleton::Setup(void)
{
	for(size_t n = 0; n < bones.size(); n++){
		if(bones[n].connectTo < n){
			bones[n].Setup(&(bones[bones[n].connectTo]));
		}else{
			bones[n].Setup(NULL);
		}
	}
	update = true;
}

void Skeleton::Render(void) const
{
	if(m_gllist == 0){
		m_gllist = glGenLists(1);
		update = true;
	}
	if(update){
		glNewList(m_gllist, GL_COMPILE_AND_EXECUTE);
		for(size_t n = 0; n < bones.size(); n++){
			::glPushName(n);
			bones[n].Render();
			::glPopName();
		}
		glEndList();
		update = false;
	}else{
		glCallList(m_gllist);
	}
}

void Skeleton::UpdateBonesFromFormula(MathParser *parser)
{
	for(size_t n = 0; n < bones.size(); n++){
		bones[n].anchorN.x = parser->GetNumber(bones[n].anchorNx);
		bones[n].anchorN.y = parser->GetNumber(bones[n].anchorNy);
		bones[n].anchorN.z = parser->GetNumber(bones[n].anchorNz);
		bones[n].link.x = parser->GetNumber(bones[n].linkx);
		bones[n].link.y = parser->GetNumber(bones[n].linky);
		bones[n].link.z = parser->GetNumber(bones[n].linkz);
		bones[n].normal.x = parser->GetNumber(bones[n].normalx);
		bones[n].normal.y = parser->GetNumber(bones[n].normaly);
		bones[n].normal.z = parser->GetNumber(bones[n].normalz);
		bones[n].anchorD = parser->GetNumber(bones[n].anchorDv);
		bones[n].length = parser->GetNumber(bones[n].lengthv);
		bones[n].r1 = parser->GetNumber(bones[n].r1v);
		bones[n].r2 = parser->GetNumber(bones[n].r2v);
		bones[n].s1 = parser->GetNumber(bones[n].s1v);
		bones[n].s2 = parser->GetNumber(bones[n].s2v);

		if(mirrored){
			bones[n].anchorN.y = -bones[n].anchorN.y;
			bones[n].link.y = -bones[n].link.y;
			bones[n].normal.y = -bones[n].normal.y;
		}
	}
	update = true;
}
