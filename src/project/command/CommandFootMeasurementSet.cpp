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
#include "../../gui/gui.h"

CommandFootMeasurementSet::CommandFootMeasurementSet(const wxString& name,
		Project* project, ProjectView::Side active, int parameter,
		wxString value)
		: wxCommand(true, name), project(project), active(active), parameter(
				parameter), value(value)
{
}

bool CommandFootMeasurementSet::Do(void)
{
	if(project == NULL) return false;

	bool hasChanged = false;
	if(active == ProjectView::Left || active == ProjectView::Both){
		FootMeasurements *meas = &(project->measL);
		oldValueLeft = Replace(meas, parameter, value);
		bool temp = !value.IsSameAs(oldValueLeft);
		if(temp) meas->Modify(true);
		hasChanged |= temp;
	}
	if(active == ProjectView::Right || active == ProjectView::Both){
		FootMeasurements *meas = &(project->measR);
		oldValueRight = Replace(meas, parameter, value);
		bool temp = !value.IsSameAs(oldValueRight);
		if(temp) meas->Modify(true);
		hasChanged |= temp;
	}
	if(hasChanged) project->Update();

	return hasChanged;
}

bool CommandFootMeasurementSet::Undo(void)
{
	if(project == NULL) return false;

	bool hasChanged = false;
	if(active == ProjectView::Left || active == ProjectView::Both){
		FootMeasurements *meas = &(project->measL);
		wxString currentValue;
		currentValue = Replace(meas, parameter, oldValueLeft);
		bool temp = !currentValue.IsSameAs(oldValueLeft);
		if(temp) meas->Modify(true);
		hasChanged |= temp;

	}
	if(active == ProjectView::Right || active == ProjectView::Both){
		FootMeasurements *meas = &(project->measR);
		wxString currentValue;
		currentValue = Replace(meas, parameter, oldValueRight);
		bool temp = !currentValue.IsSameAs(oldValueRight);
		if(temp) meas->Modify(true);
		hasChanged |= temp;
	}
	if(hasChanged) project->Update();
	return true;
}

wxString CommandFootMeasurementSet::Replace(FootMeasurements *meas,
		int parameter, wxString newValue)
{
	wxString lastValue;
	ParameterFormula *param = GetParameterByID(meas, parameter);
	lastValue = param->formula;
	param->formula = newValue;
	return lastValue;
}

ParameterFormula* CommandFootMeasurementSet::GetParameterByID(
		FootMeasurements *meas, int id)
{
	switch(id){
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
						+ " : Replace() : Passed invalid/unhandled ID,"));
	}
	return NULL;
}
