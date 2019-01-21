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

#include "../icons/FootMeasurements.xpm"
#include "../icons/FootMeasurements_small.xpm"

PanelFootMeasurements::PanelFootMeasurements(wxWindow* parent, wxWindowID id,
		const wxPoint& pos, const wxSize& size, long style)
		: GUIPanelFootMeasurements(parent, id, pos, size, style), bm0(
				FootMeasurements_small_xpm), bm1(FootMeasurements_xpm)
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

	TransferParameterToTextCtrl(foot->footLength, m_textCtrlFootLength);
	TransferParameterToTextCtrl(foot->ballGirth, m_textCtrlBallGirth);
	TransferParameterToTextCtrl(foot->waistGirth, m_textCtrlWaistGirth);
	TransferParameterToTextCtrl(foot->instepGirth, m_textCtrlInstepGirth);
	TransferParameterToTextCtrl(foot->longHeelGirth, m_textCtrlLongHeelGirth);
	TransferParameterToTextCtrl(foot->shortHeelGirth, m_textCtrlShortHeelGirth);
	TransferParameterToTextCtrl(foot->angleMixing, m_textCtrlAngleMixing,
			false);
	TransferParameterToTextCtrl(foot->legLengthDifference,
			m_textCtrlLegLengthDifference);

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

void PanelFootMeasurements::TransferParameterToTextCtrl(
		const ParameterFormula parameter, wxTextCtrl* ctrl, bool isDistance)
{
	if(ctrl->HasFocus()){
		ctrl->SetValue(parameter.formula);
	}else{
		if(parameter.errorFlag){
			ctrl->SetBackgroundColour(*wxRED);
			ctrl->SetValue(parameter.errorStr);
		} else{
			ctrl->SetBackgroundColour(wxNullColour);
			if(isDistance){
				ctrl->SetValue(
						settings->Distance.TextFromSIWithUnit(parameter.value,
								1));
			} else{
				ctrl->SetValue(wxString::Format(_T("%g %%"), parameter.value*100));
			}
		}
	}
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
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED,
	ID_QUICKSETUPMEASUREMENTS);
	ProcessEvent(selectEvent);
}

void PanelFootMeasurements::OnTextEnter(wxCommandEvent& event)
{
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

wxString PanelFootMeasurements::GetNameByID(int id)
{
	switch(id){
	case ID_MEASUREMENT_FOOTLENGTH:
		return _T("FootLength");
	case ID_MEASUREMENT_BALLGIRTH:
		return _T("BallGirth");
	case ID_MEASUREMENT_WAISTGIRTH:
		return _T("WaistGirth");
	case ID_MEASUREMENT_INSTEPGIRTH:
		return _T("InstepGirth");
	case ID_MEASUREMENT_LONGHEELGIRTH:
		return _T("LongHeelGirth");
	case ID_MEASUREMENT_SHORTHEELGIRTH:
		return _T("ShortHeelGirth");
	case ID_MEASUREMENT_ANGLEMIXING:
		return _T("AngleMixing");
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
		return _T("LegLengthDifference");
	}
	return _T("");
}

wxTextCtrl* PanelFootMeasurements::GetTextCtrlByID(int id)
{
	switch(id){
	case ID_MEASUREMENT_FOOTLENGTH:
		return m_textCtrlFootLength;
	case ID_MEASUREMENT_BALLGIRTH:
		return m_textCtrlBallGirth;
	case ID_MEASUREMENT_WAISTGIRTH:
		return m_textCtrlWaistGirth;
	case ID_MEASUREMENT_INSTEPGIRTH:
		return m_textCtrlInstepGirth;
	case ID_MEASUREMENT_LONGHEELGIRTH:
		return m_textCtrlLongHeelGirth;
	case ID_MEASUREMENT_SHORTHEELGIRTH:
		return m_textCtrlShortHeelGirth;
	case ID_MEASUREMENT_ANGLEMIXING:
		return m_textCtrlAngleMixing;
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
		return m_textCtrlLegLengthDifference;
	}
	return NULL;
}

void PanelFootMeasurements::OnSize(wxSizeEvent& event)
{
	wxSize s = this->GetSize();
	if(s.GetWidth() > 460)
		m_bitmap->SetBitmap(bm1);
	else
		m_bitmap->SetBitmap(bm0);
//	this->Layout();
	event.Skip();
}
