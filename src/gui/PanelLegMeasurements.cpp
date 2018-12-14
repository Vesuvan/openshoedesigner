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
		const wxPoint& pos, const wxSize& size, long style)
		: GUIPanelLegMeasurements(parent, id, pos, size, style)
{
	settings = NULL;
	doc = NULL;
	view = NULL;
}

PanelLegMeasurements::~PanelLegMeasurements()
{
}

void PanelLegMeasurements::SetDocView(wxDocument* doc, wxView* view)
{
	this->doc = doc;
	this->view = view;
}

void PanelLegMeasurements::SetDisplaySettings(DisplaySettings* settings)
{
	this->settings = settings;
}

bool PanelLegMeasurements::TransferDataToWindow(void)
{

	ProjectView* projectview = wxStaticCast(view, ProjectView);
	const FootMeasurements *foot = projectview->GetActiveFootMeasurements();

	if(m_textCtrlBelowCrutchGirth->HasFocus())
		m_textCtrlBelowCrutchGirth->SetValue(foot->belowCrutchGirth.formula);
	else
		m_textCtrlBelowCrutchGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->belowCrutchGirth.value, 1));

	if(m_textCtrlBelowCrutchLevel->HasFocus())
		m_textCtrlBelowCrutchLevel->SetValue(foot->belowCrutchLevel.formula);
	else
		m_textCtrlBelowCrutchLevel->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->belowCrutchLevel.value, 1));

	if(m_textCtrlMiddleOfCalfGirth->HasFocus())
		m_textCtrlMiddleOfCalfGirth->SetValue(foot->middleOfCalfGirth.formula);
	else
		m_textCtrlMiddleOfCalfGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->middleOfCalfGirth.value, 1));

	if(m_textCtrlMiddleOfCalfLevel->HasFocus())
		m_textCtrlMiddleOfCalfLevel->SetValue(foot->middleOfCalfLevel.formula);
	else
		m_textCtrlMiddleOfCalfLevel->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->middleOfCalfLevel.value, 1));

	if(m_textCtrlAboveKneeGirth->HasFocus())
		m_textCtrlAboveKneeGirth->SetValue(foot->aboveKneeGirth.formula);
	else
		m_textCtrlAboveKneeGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->aboveKneeGirth.value, 1));

	if(m_textCtrlAboveKneeLevel->HasFocus())
		m_textCtrlAboveKneeLevel->SetValue(foot->aboveKneeLevel.formula);
	else
		m_textCtrlAboveKneeLevel->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->aboveKneeLevel.value, 1));

	if(m_textCtrlOverKneeCapGirth->HasFocus())
		m_textCtrlOverKneeCapGirth->SetValue(foot->overKneeCapGirth.formula);
	else
		m_textCtrlOverKneeCapGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->overKneeCapGirth.value, 1));

	if(m_textCtrlOverKneeCapLevel->HasFocus())
		m_textCtrlOverKneeCapLevel->SetValue(foot->overKneeCapLevel.formula);
	else
		m_textCtrlOverKneeCapLevel->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->overKneeCapLevel.value, 1));

	if(m_textCtrlBelowKneeGirth->HasFocus())
		m_textCtrlBelowKneeGirth->SetValue(foot->belowKneeGirth.formula);
	else
		m_textCtrlBelowKneeGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->belowKneeGirth.value, 1));

	if(m_textCtrlBelowKneeLevel->HasFocus())
		m_textCtrlBelowKneeLevel->SetValue(foot->belowKneeLevel.formula);
	else
		m_textCtrlBelowKneeLevel->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->belowKneeLevel.value, 1));

	if(m_textCtrlMiddleOfShankGirth->HasFocus())
		m_textCtrlMiddleOfShankGirth->SetValue(
				foot->middleOfShankGirth.formula);
	else
		m_textCtrlMiddleOfShankGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->middleOfShankGirth.value, 1));

	if(m_textCtrlMiddleOfShankLevel->HasFocus())
		m_textCtrlMiddleOfShankLevel->SetValue(
				foot->middleOfShankLevel.formula);
	else
		m_textCtrlMiddleOfShankLevel->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->middleOfShankLevel.value, 1));

	if(m_textCtrlAboveAnkleGirth->HasFocus())
		m_textCtrlAboveAnkleGirth->SetValue(foot->aboveAnkleGirth.formula);
	else
		m_textCtrlAboveAnkleGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->aboveAnkleGirth.value, 1));

	if(m_textCtrlAboveAnkleLevel->HasFocus())
		m_textCtrlAboveAnkleLevel->SetValue(foot->aboveAnkleLevel.formula);
	else
		m_textCtrlAboveAnkleLevel->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->aboveAnkleLevel.value, 1));

	if(m_textCtrlOverAnkleBoneGirth->HasFocus())
		m_textCtrlOverAnkleBoneGirth->SetValue(
				foot->overAnkleBoneGirth.formula);
	else
		m_textCtrlOverAnkleBoneGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->overAnkleBoneGirth.value, 1));

	if(m_textCtrlOverAnkleBoneLevel->HasFocus())
		m_textCtrlOverAnkleBoneLevel->SetValue(
				foot->overAnkleBoneLevel.formula);
	else
		m_textCtrlOverAnkleBoneLevel->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->overAnkleBoneLevel.value, 1));

	return true;
}

void PanelLegMeasurements::OnKillFocus(wxFocusEvent& event)
{
	TransferDataToWindow();
}

void PanelLegMeasurements::OnSetFocus(wxFocusEvent& event)
{
	TransferDataToWindow();
}

void PanelLegMeasurements::OnTextEnter(wxCommandEvent& event)
{
	Project* project = wxStaticCast(doc, Project);
	ProjectView* projectview = wxStaticCast(view, ProjectView);
	const FootMeasurements *foot = projectview->GetActiveFootMeasurements();

	const wxString newFormula = event.GetString();

	wxString parameter;
	switch(event.GetId()){
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		parameter = _T("BelowCrutchGirth");
		break;
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		parameter = _T("BelowCrutchLevel");
		break;
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		parameter = _T("MiddleOfCalfGirth");
		break;
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		parameter = _T("MiddleOfCalfLevel");
		break;
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		parameter = _T("AboveKneeGirth");
		break;
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		parameter = _T("AboveKneeLevel");
		break;
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		parameter = _T("OverKneeCapGirth");
		break;
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		parameter = _T("OverKneeCapLevel");
		break;
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		parameter = _T("BelowKneeGirth");
		break;
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		parameter = _T("BelowKneeLevel");
		break;
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		parameter = _T("MiddleOfSkankGirth");
		break;
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		parameter = _T("MiddleOfSkankLevel");
		break;
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		parameter = _T("AboveAnkleGirth");
		break;
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		parameter = _T("AboveAnkleLevel");
		break;
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		parameter = _T("OverAnkelConeGirth");
		break;
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		parameter = _T("OverAnkleBoneLevel");
		break;
	}

	project->GetCommandProcessor()->Submit(
			new CommandFootMeasurementSet(
					wxString::Format(_("Set %s to %s"), parameter, newFormula),
					project, projectview->active, event.GetId(), newFormula));
}
