///////////////////////////////////////////////////////////////////////////////
// Name               : CommandFootModelSetValue.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 19.02.2018
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

#include "CommandFootModelSetValue.h"

//#include <wx/event.h>
//#include "../../gui/IDs.h"

CommandFootModelSetValue::CommandFootModelSetValue(const wxString& name,
		Project* project, size_t boneNr, Bone::stringIdentifier field,
		wxString newFormula)
		: wxCommand(true, name)
{
	this->project = project;
	this->boneNr = boneNr;
	this->field = field;
	this->newFormula = newFormula;
}

bool CommandFootModelSetValue::Do(void)
{
	if(project == NULL) return false;
	if(boneNr >= project->footL.bones.size()) return false;
	switch(field){

	// BoneLength
	case Bone::stringIdentifier::stringLength:
		oldFormula = project->footL.bones[boneNr].lengthv;
		project->footL.bones[boneNr].lengthv = newFormula;
		break;
	case Bone::stringIdentifier::stringR1:
		oldFormula = project->footL.bones[boneNr].r1v;
		project->footL.bones[boneNr].r1v = newFormula;
		break;
	case Bone::stringIdentifier::stringR2:
		oldFormula = project->footL.bones[boneNr].r2v;
		project->footL.bones[boneNr].r2v = newFormula;
		break;
	case Bone::stringIdentifier::stringS1:
		oldFormula = project->footL.bones[boneNr].s1v;
		project->footL.bones[boneNr].s1v = newFormula;
		break;
	case Bone::stringIdentifier::stringS2:
		oldFormula = project->footL.bones[boneNr].s2v;
		project->footL.bones[boneNr].s2v = newFormula;
		break;
//	case 3:{
//		// Leg
//
//		break;}
	default:
		return false;
	}

	project->Update();
	return true;
}

bool CommandFootModelSetValue::Undo(void)
{
	if(project == NULL) return false;
	if(boneNr >= project->footL.bones.size()) return false;
	switch(field){
	case Bone::stringIdentifier::stringLength:
		project->footL.bones[boneNr].lengthv = oldFormula;
		break;
	case Bone::stringIdentifier::stringR1:
		project->footL.bones[boneNr].r1v = oldFormula;
		break;
	case Bone::stringIdentifier::stringR2:
		project->footL.bones[boneNr].r2v = oldFormula;
		break;
	case Bone::stringIdentifier::stringS1:
		project->footL.bones[boneNr].s1v = oldFormula;
		break;
	case Bone::stringIdentifier::stringS2:
		project->footL.bones[boneNr].s2v = oldFormula;
		break;

//	case 3:{
//		// Leg
//
//		break;}

	default:
		return false;
	}

	project->Update();
	return true;
}
