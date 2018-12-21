///////////////////////////////////////////////////////////////////////////////
// Name               : PanelLegMeasurements.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 18.11.2018
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

#include "PanelLegMeasurements.h"

#include "../project/command/CommandFootMeasurementSet.h"
PanelLegMeasurements::PanelLegMeasurements(wxWindow* parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style) :
		GUIPanelLegMeasurements(parent, id, pos, size, style) {
	settings = NULL;
	doc = NULL;
	view = NULL;
}

PanelLegMeasurements::~PanelLegMeasurements() {
}

void PanelLegMeasurements::SetDocView(wxDocument* doc, wxView* view) {
	this->doc = doc;
	this->view = view;
}

void PanelLegMeasurements::SetDisplaySettings(DisplaySettings* settings) {
	this->settings = settings;
}

bool PanelLegMeasurements::TransferDataToWindow(void) {

	ProjectView* projectview = wxStaticCast(view, ProjectView);
	const FootMeasurements *foot = projectview->GetActiveFootMeasurements();

	TransferParameterToTextCtrl(foot->belowCrutchGirth,
			m_textCtrlBelowCrutchGirth);
	TransferParameterToTextCtrl(foot->belowCrutchLevel,
			m_textCtrlBelowCrutchLevel);
	TransferParameterToTextCtrl(foot->middleOfCalfGirth,
			m_textCtrlMiddleOfCalfGirth);
	TransferParameterToTextCtrl(foot->middleOfCalfLevel,
			m_textCtrlMiddleOfCalfLevel);
	TransferParameterToTextCtrl(foot->aboveKneeGirth, m_textCtrlAboveKneeGirth);
	TransferParameterToTextCtrl(foot->aboveKneeLevel, m_textCtrlAboveKneeLevel);
	TransferParameterToTextCtrl(foot->overKneeCapGirth,
			m_textCtrlOverKneeCapGirth);
	TransferParameterToTextCtrl(foot->overKneeCapLevel,
			m_textCtrlOverKneeCapLevel);
	TransferParameterToTextCtrl(foot->belowKneeGirth, m_textCtrlBelowKneeGirth);
	TransferParameterToTextCtrl(foot->belowKneeLevel, m_textCtrlBelowKneeLevel);
	TransferParameterToTextCtrl(foot->middleOfShankGirth,
			m_textCtrlMiddleOfShankGirth);
	TransferParameterToTextCtrl(foot->middleOfShankLevel,
			m_textCtrlMiddleOfShankLevel);
	TransferParameterToTextCtrl(foot->aboveAnkleGirth,
			m_textCtrlAboveAnkleGirth);
	TransferParameterToTextCtrl(foot->aboveAnkleLevel,
			m_textCtrlAboveAnkleLevel);
	TransferParameterToTextCtrl(foot->overAnkleBoneGirth,
			m_textCtrlOverAnkleBoneGirth);
	TransferParameterToTextCtrl(foot->overAnkleBoneLevel,
			m_textCtrlOverAnkleBoneLevel);

	return true;
}

void PanelLegMeasurements::OnKillFocus(wxFocusEvent& event) {
	TransferDataToWindow();
}

void PanelLegMeasurements::OnSetFocus(wxFocusEvent& event) {
	TransferDataToWindow();
}

void PanelLegMeasurements::OnTextEnter(wxCommandEvent& event) {
	Project* project = wxStaticCast(doc, Project);
	ProjectView* projectview = wxStaticCast(view, ProjectView);
	const wxString newFormula = event.GetString();
	project->GetCommandProcessor()->Submit(
			new CommandFootMeasurementSet(
					wxString::Format(_("Set %s to %s"),
							GetNameByID(event.GetId()), newFormula), project,
					projectview->active, event.GetId(), newFormula));
	Navigate();
}

void PanelLegMeasurements::TransferParameterToTextCtrl(
		const ParameterFormula parameter, wxTextCtrl* ctrl, bool isDistance) {
	if (ctrl->HasFocus()) {
		ctrl->SetValue(parameter.formula);
	} else {
		if (parameter.errorFlag) {
			ctrl->SetBackgroundColour(*wxRED);
			ctrl->SetValue(parameter.errorStr);
		} else {
			ctrl->SetBackgroundColour(wxNullColour);
			if(isDistance) {
				ctrl->SetValue(
						settings->Distance.TextFromSIWithUnit(parameter.value,
								1));
			} else {
				ctrl->SetValue(wxString::Format(_T("%g %%"), parameter.value*100));
			}
		}
	}
}

wxString PanelLegMeasurements::GetNameByID(int id) {
	switch (id) {
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		return _T("BelowCrutchGirth");
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		return _T("BelowCrutchLevel");
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		return _T("MiddleOfCalfGirth");
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		return _T("MiddleOfCalfLevel");
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		return _T("AboveKneeGirth");
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		return _T("AboveKneeLevel");
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		return _T("OverKneeCapGirth");
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		return _T("OverKneeCapLevel");
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		return _T("BelowKneeGirth");
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		return _T("BelowKneeLevel");
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		return _T("MiddleOfShankGirth");
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		return _T("MiddleOfShankLevel");
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		return _T("AboveAnkleGirth");
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		return _T("AboveAnkleLevel");
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		return _T("OverAnkleBoneGirth");
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return _T("OverAnkleBoneLevel");
	}
	return _T("");
}

wxTextCtrl* PanelLegMeasurements::GetTextCtrlByID(int id) {
	switch (id) {
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		return m_textCtrlBelowCrutchGirth;
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		return m_textCtrlBelowCrutchLevel;
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		return m_textCtrlMiddleOfCalfGirth;
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		return m_textCtrlMiddleOfCalfLevel;
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		return m_textCtrlAboveKneeGirth;
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		return m_textCtrlAboveKneeLevel;
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		return m_textCtrlOverKneeCapGirth;
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		return m_textCtrlOverKneeCapLevel;
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		return m_textCtrlBelowKneeGirth;
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		return m_textCtrlBelowKneeLevel;
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		return m_textCtrlMiddleOfShankGirth;
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		return m_textCtrlMiddleOfShankLevel;
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		return m_textCtrlAboveAnkleGirth;
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		return m_textCtrlAboveAnkleLevel;
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		return m_textCtrlOverAnkleBoneGirth;
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return m_textCtrlOverAnkleBoneLevel;
	}
	return NULL;
}
