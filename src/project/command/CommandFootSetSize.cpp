///////////////////////////////////////////////////////////////////////////////
// Name               : CommandFootSetSize.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.04.2018
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

#include "CommandFootSetSize.h"

CommandFootSetSize::CommandFootSetSize(const wxString& name, Project* project,
		Foot::sizeparameter param, double value)
		: wxCommand(true, name)
{
	this->project = project;
	this->active = project->active;
	if(project->symmetry == Project::Full) this->active = Project::Both;
	this->param = param;
	this->value = value;
	this->oldValueL = 0;
	this->oldValueR = 0;
}

bool CommandFootSetSize::Do(void)
{
	if(project == NULL) return false;
	if(active == Project::Left || active == Project::Both){
		switch(param){
		case Foot::Length:
			oldValueL = project->footL.length;
			project->footL.length = value;
			break;
		case Foot::BallWidth:
			oldValueL = project->footL.ballwidth;
			project->footL.ballwidth = value;
			break;
		case Foot::AnkleWidth:
			oldValueL = project->footL.anklewidth;
			project->footL.anklewidth = value;
			break;
		case Foot::HeelWidth:
			oldValueL = project->footL.heelwidth;
			project->footL.heelwidth = value;
			break;
		case Foot::Mixing:
			oldValueL = project->footL.mixing;
			project->footL.mixing = value;
			break;
		}
	}
	if(active == Project::Right || active == Project::Both){
		switch(param){
		case Foot::Length:
			oldValueR = project->footR.length;
			project->footR.length = value;
			break;
		case Foot::BallWidth:
			oldValueR = project->footR.ballwidth;
			project->footR.ballwidth = value;
			break;
		case Foot::AnkleWidth:
			oldValueR = project->footR.anklewidth;
			project->footR.anklewidth = value;
			break;
		case Foot::HeelWidth:
			oldValueR = project->footR.heelwidth;
			project->footR.heelwidth = value;
			break;
		case Foot::Mixing:
			oldValueR = project->footR.mixing;
			project->footR.mixing = value;
			break;
		}
	}
	project->Update(Project::UpdateFoot, active);
	return true;
}

bool CommandFootSetSize::Undo(void)
{
	if(project == NULL) return false;
	if(active == Project::Left || active == Project::Both){
		switch(param){
		case Foot::Length:
			project->footL.length = oldValueL;
			break;
		case Foot::BallWidth:
			project->footL.ballwidth = oldValueL;
			break;
		case Foot::AnkleWidth:
			project->footL.anklewidth = oldValueL;
			break;
		case Foot::HeelWidth:
			project->footL.heelwidth = oldValueL;
			break;
		case Foot::Mixing:
			project->footL.mixing = oldValueL;
			break;
		}
	}
	if(active == Project::Right || active == Project::Both){
		switch(param){
		case Foot::Length:
			project->footR.length = oldValueR;
			break;
		case Foot::BallWidth:
			project->footR.ballwidth = oldValueR;
			break;
		case Foot::AnkleWidth:
			project->footR.anklewidth = oldValueR;
			break;
		case Foot::HeelWidth:
			project->footR.heelwidth = oldValueR;
			break;
		case Foot::Mixing:
			project->footR.mixing = oldValueR;
			break;
		}
	}
	project->Update(Project::UpdateFoot, active);
	return true;
}
