///////////////////////////////////////////////////////////////////////////////
// Name               : CommandFootMeasurementSet.cpp
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

#include "CommandFootMeasurementSet.h"
#include "../../gui/guipanels.h"

CommandFootMeasurementSet::CommandFootMeasurementSet(const wxString& name,
		Project* project, ProjectView::Side active, int parameter,
		wxString value) :
		wxCommand(true, name), project(project), active(active), parameter(
				parameter), value(value) {
}

bool CommandFootMeasurementSet::Do(void) {
	if (project == NULL)
		return false;
	FootMeasurements *meas;
	if (active == ProjectView::Left)
		meas = &(project->measL);
	if (active == ProjectView::Right)
		meas = &(project->measR);

	oldValue = Replace(active, parameter, value);
	const bool hasChanged = !value.IsSameAs(oldValue);
	if (hasChanged) {
		meas->Modify(true);
		project->Update();
	}

	return hasChanged;

//	if(active == Project::Left || active == Project::Both){
//		switch(param){
//		case FootModel::Length:
//			oldValueL = project->footL.length;
//			project->footL.length = value;
//			break;
//		case FootModel::BallWidth:
//			oldValueL = project->footL.ballwidth;
//			project->footL.ballwidth = value;
//			break;
//		case FootModel::AnkleWidth:
////			oldValueL = project->footL.anklewidth;
////			project->footL.anklewidth = value;
//			break;
//		case FootModel::HeelWidth:
////			oldValueL = project->footL.heelwidth;
////			project->footL.heelwidth = value;
//			break;
//		case FootModel::Mixing:
//			oldValueL = project->footL.mixing;
//			project->footL.mixing = value;
//			break;
//		}
//	}
//	if(active == Project::Right || active == Project::Both){
//		switch(param){
//		case FootModel::Length:
//			oldValueR = project->footR.length;
//			project->footR.length = value;
//			break;
//		case FootModel::BallWidth:
//			oldValueR = project->footR.ballwidth;
//			project->footR.ballwidth = value;
//			break;
//		case FootModel::AnkleWidth:
////			oldValueR = project->footR.anklewidth;
////			project->footR.anklewidth = value;
//			break;
//		case FootModel::HeelWidth:
////			oldValueR = project->footR.heelwidth;
////			project->footR.heelwidth = value;
//			break;
//		case FootModel::Mixing:
//			oldValueR = project->footR.mixing;
//			project->footR.mixing = value;
//			break;
//		}
//	}
//	project->Update(Project::UpdateFoot, active);
//	return true;
}

bool CommandFootMeasurementSet::Undo(void) {
	if (project == NULL)
		return false;

	FootMeasurements *meas;
	if (active == ProjectView::Left)
		meas = &(project->measL);
	if (active == ProjectView::Right)
		meas = &(project->measR);
	wxString currentValue;

	currentValue = Replace(active, parameter, oldValue);
	const bool hasChanged = !currentValue.IsSameAs(oldValue);
	if (hasChanged) {
		meas->Modify(true);
		project->Update();
	}

	return true;

//	if(active == Project::Left || active == Project::Both){
//		switch(param){
//		case FootModel::Length:
//			project->footL.length = oldValueL;
//			break;
//		case FootModel::BallWidth:
//			project->footL.ballwidth = oldValueL;
//			break;
//		case FootModel::AnkleWidth:
////			project->footL.anklewidth = oldValueL;
//			break;
//		case FootModel::HeelWidth:
////			project->footL.heelwidth = oldValueL;
//			break;
//		case FootModel::Mixing:
//			project->footL.mixing = oldValueL;
//			break;
//		}
//	}
//	if(active == Project::Right || active == Project::Both){
//		switch(param){
//		case FootModel::Length:
//			project->footR.length = oldValueR;
//			break;
//		case FootModel::BallWidth:
//			project->footR.ballwidth = oldValueR;
//			break;
//		case FootModel::AnkleWidth:
////			project->footR.anklewidth = oldValueR;
//			break;
//		case FootModel::HeelWidth:
////			project->footR.heelwidth = oldValueR;
//			break;
//		case FootModel::Mixing:
//			project->footR.mixing = oldValueR;
//			break;
//		}
//	}
//	project->Update(Project::UpdateFoot, active);
//	return true;
}

wxString CommandFootMeasurementSet::Replace(ProjectView::Side active,
		int parameter, wxString newValue) {
	wxString lastValue;
	FootMeasurements *meas;
	if (active == ProjectView::Left)
		meas = &(project->measL);
	if (active == ProjectView::Right)
		meas = &(project->measR);
	ParameterFormula *param = GetParameterByID(meas, parameter);
	lastValue = param->formula;
	param->formula = newValue;
	return lastValue;
}

ParameterFormula* CommandFootMeasurementSet::GetParameterByID(
		FootMeasurements *meas, int id) {
	switch (id) {
	case ID_MEASUREMENT_FOOTLENGTH:
		return &(meas->footLength);
	case ID_MEASUREMENT_BALLGIRTH:
		return &(meas->ballGirth);
	case ID_MEASUREMENT_WAISTGIRTH:
		return &(meas->waistGirth);
	case ID_MEASUREMENT_INSTEPGIRTH:
		return &(meas->instepGirth);
	case ID_MEASUREMENT_LONGHEELGIRTH:
		return &(meas->longHeelGirth);
	case ID_MEASUREMENT_SHORTHEELGIRTH:
		return &(meas->shortHeelGirth);
	case ID_MEASUREMENT_ANGLEMIXING:
		return &(meas->angleMixing);
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
		return &(meas->legLengthDifference);
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		return &(meas->belowCrutchGirth);
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		return &(meas->belowCrutchLevel);
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		return &(meas->middleOfCalfGirth);
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		return &(meas->middleOfCalfLevel);
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		return &(meas->aboveKneeGirth);
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		return &(meas->aboveKneeLevel);
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		return &(meas->overKneeCapGirth);
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		return &(meas->overKneeCapLevel);
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		return &(meas->belowKneeGirth);
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		return &(meas->belowKneeLevel);
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		return &(meas->middleOfShankGirth);
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		return &(meas->middleOfShankLevel);
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		return &(meas->aboveAnkleGirth);
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		return &(meas->aboveAnkleLevel);
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		return &(meas->overAnkleBoneGirth);
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return &(meas->overAnkleBoneLevel);
	default:
		throw(std::invalid_argument(
				std::string(__FILE__)
						+ " : Replace() : Passed invalid/unhandled ID ("
						+ std::to_string(parameter) + ")."));
	}
	return NULL;
}
