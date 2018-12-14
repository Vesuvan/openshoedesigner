///////////////////////////////////////////////////////////////////////////////
// Name               : PanelFootMeasurements.cpp
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

#include "PanelFootMeasurements.h"

#include <wx/cmdproc.h>
#include <wx/defs.h>
#include <wx/docview.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/object.h>
#include <wx/string.h>
#include <wx/translation.h>
#include <wx/windowid.h>
#include <math.h>
#include <cfloat>

#include "../project/command/CommandFootMeasurementSet.h"
#include "../project/foot/FootModel.h"
#include "../project/Project.h"
#include "DialogQuickInitFoot.h"

PanelFootMeasurements::PanelFootMeasurements(wxWindow* parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style)
		: GUIPanelFootMeasurements(parent, id, pos, size, style)
{
	settings = NULL;
	doc = NULL;
	view = NULL;
}

PanelFootMeasurements::~PanelFootMeasurements()
{
}

void PanelFootMeasurements::SetDocView(wxDocument* doc, wxView* view)
{
	this->doc = doc;
	this->view = view;
}
void PanelFootMeasurements::SetDisplaySettings(DisplaySettings* settings)
{
	this->settings = settings;
}

bool PanelFootMeasurements::TransferDataToWindow(void)
{
	ProjectView* projectview = wxStaticCast(view, ProjectView);
	const FootMeasurements *foot = projectview->GetActiveFootMeasurements();

	if(m_textCtrlFootLength->HasFocus())
		m_textCtrlFootLength->SetValue(foot->footLength.formula);
	else
		m_textCtrlFootLength->SetValue(
				settings->Distance.TextFromSIWithUnit(foot->footLength.value,
						1));

	if(m_textCtrlBallGirth->HasFocus())
		m_textCtrlBallGirth->SetValue(foot->ballGirth.formula);
	else
		m_textCtrlBallGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(foot->ballGirth.value,
						1));

	if(m_textCtrlWaistGirth->HasFocus())
		m_textCtrlWaistGirth->SetValue(foot->waistGirth.formula);
	else
		m_textCtrlWaistGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(foot->waistGirth.value,
						1));

	if(m_textCtrlInstepGirth->HasFocus())
		m_textCtrlInstepGirth->SetValue(foot->instepGirth.formula);
	else
		m_textCtrlInstepGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(foot->instepGirth.value,
						1));

	if(m_textCtrlLongHeelGirth->HasFocus())
		m_textCtrlLongHeelGirth->SetValue(foot->longHeelGirth.formula);
	else
		m_textCtrlLongHeelGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(foot->longHeelGirth.value,
						1));

	if(m_textCtrlShortHeelGirth->HasFocus())
		m_textCtrlShortHeelGirth->SetValue(foot->shortHeelGirth.formula);
	else
		m_textCtrlShortHeelGirth->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->shortHeelGirth.value, 1));

	if(m_textCtrlAngleMixing->HasFocus())
		m_textCtrlAngleMixing->SetValue(foot->angleMixing.formula);
	else
		m_textCtrlAngleMixing->SetValue(
				wxString::Format(_T("%g %%"), foot->angleMixing.value*100));

	if(m_textCtrlLegLengthDifference->HasFocus())
		m_textCtrlLegLengthDifference->SetValue(
				foot->legLengthDifference.formula);
	else
		m_textCtrlLegLengthDifference->SetValue(
				settings->Distance.TextFromSIWithUnit(
						foot->legLengthDifference.value, 1));

	m_textCtrlShoeSizeEU->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::EU))));
	m_textCtrlShoeSizeUS->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::US))));
	m_textCtrlShoeSizeUK->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::UK))));
	m_textCtrlShoeSizeCN->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::CN))));
	m_textCtrlShoeSizeJP->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::JP))));
	m_textCtrlShoeSizeAU->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::AU))));

	return true;
}

void PanelFootMeasurements::OnSetFocus(wxFocusEvent& event)
{
	TransferDataToWindow();
}
void PanelFootMeasurements::OnKillFocus(wxFocusEvent& event)
{
	TransferDataToWindow();
}

void PanelFootMeasurements::OnQuickSetup(wxCommandEvent& event)
{
	DialogQuickInitFoot dialog(this);
	if(dialog.ShowModal() == wxID_OK){
//		Project* project = wxStaticCast(GetDocument(), Project);
//		const FootModel *foot = project->GetActiveFoot();
//		if (fabs(foot->length - dialog.length) > FLT_EPSILON)
//			project->GetCommandProcessor()->Submit(
//					new CommandFootSetSize(
//							wxString::Format(_("Set footlength to %g"),
//									dialog.length), project, FootModel::Length,
//							dialog.length));
//		if (fabs(foot->ballwidth - dialog.width) > FLT_EPSILON)
//			project->GetCommandProcessor()->Submit(
//					new CommandFootSetSize(
//							wxString::Format(_("Set ballwidth to %g"),
//									dialog.width), project,
//							FootModel::BallWidth, dialog.width));

//		if(fabs(foot->anklewidth - dialog.width) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set anklewidth to %g"),
//								dialog.width), project, FootModel::AnkleWidth,
//						dialog.width));
//		if(fabs(foot->heelwidth - dialog.width) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set heelwidth to %g"),
//								dialog.width), project, FootModel::HeelWidth,
//						dialog.width));
	}
}

void PanelFootMeasurements::OnTextEnter(wxCommandEvent& event)
{
	Project* project = wxStaticCast(doc, Project);
	ProjectView* projectview = wxStaticCast(view, ProjectView);
	const FootMeasurements *foot = projectview->GetActiveFootMeasurements();

	const wxString newFormula = event.GetString();

	wxString parameter;
	switch(event.GetId()){
	case ID_MEASUREMENT_FOOTLENGTH:
		parameter = _T("FootLength");
		break;
	case ID_MEASUREMENT_BALLGIRTH:
		parameter = _T("BallGirth");
		break;
	case ID_MEASUREMENT_WAISTGIRTH:
		parameter = _T("WaistGirth");
		break;
	case ID_MEASUREMENT_INSTEPGIRTH:
		parameter = _T("InstepGirth");
		break;
	case ID_MEASUREMENT_LONGHEELGIRTH:
		parameter = _T("LongHeelGirth");
		break;
	case ID_MEASUREMENT_SHORTHEELGIRTH:
		parameter = _T("ShortHeelGirth");
		break;
	case ID_MEASUREMENT_ANGLEMIXING:
		parameter = _T("AngleMixing");
		break;
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
		parameter = _T("LegLengthDifference");
		break;
	}

	project->GetCommandProcessor()->Submit(
			new CommandFootMeasurementSet(
					wxString::Format(_("Set %s to %s"), parameter, newFormula),
					project, projectview->active, event.GetId(), newFormula));
//
//		break;
//	case ID_TEXTFOOTWIDTH:
//		project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set ballwidth to %g"), temp),
//						project, FootModel::BallWidth, temp));
//		break;
//	case ID_TEXTHEELWIDTH:
//		project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set heelwidth to %g"), temp),
//						project, FootModel::HeelWidth, temp));
//		break;
//	case ID_TEXTANKLEWIDTH:
//		project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set anklewidth to %g"), temp),
//						project, FootModel::AnkleWidth, temp));
//		break;
//	case ID_TEXTLEGLENGTH:
//		project->GetCommandProcessor()->Submit(
//				new CommandProjectSetLegLengthDifference(
//						wxString::Format(_("Set leglengthdifference to %g"),
//								temp), project, temp));
//		break;
//	case ID_TEXTHEELHEIGHT:
//		project->GetCommandProcessor()->Submit(
//				new CommandShoeSetParameter(
//				_("Set heelheight to ") + event.GetString(), project, 0,
//						event.GetString()));
//		break;
//	case ID_TEXTBALLHEIGHT:
//		project->GetCommandProcessor()->Submit(
//				new CommandShoeSetParameter(
//				_("Set ballheight to ") + event.GetString(), project, 1,
//						event.GetString()));

//	case ID_TEXTTOEPITCH:
//		project->GetCommandProcessor()->Submit(
//				new CommandShoeSetParameter(
//				_("Set toe pitch to ") + event.GetString(), project, 2,
//						event.GetString()));
//		break;
//	case ID_TEXTMIXINGANGLE:
//		project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set mixing to %g"), temp), project,
//						FootModel::Mixing, temp));
//		break;

}

