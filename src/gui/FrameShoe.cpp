///////////////////////////////////////////////////////////////////////////////
// Name               : FrameShoe.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 04.10.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "FrameShoe.h"

#include <math.h>
#include "IDs.h"

FrameShoe::FrameShoe(wxWindow* parent, Project* project) :
		GUIFrameShoe(parent)
{
	this->project = project;
	TransferDataToWindow();
}

FrameShoe::~FrameShoe()
{
}

bool FrameShoe::TransferDataToWindow()
{
	Shoe * shoe = &(project->shoe);
	m_textCtrlHeelHeight->SetValue(shoe->exprHeelHeight);
	m_textCtrlBallHeight->SetValue(shoe->exprBallHeight);
	m_textCtrlToeAngle->SetValue(shoe->exprToeAngle);
	m_sliderMixing->SetValue(shoe->mixing * 100.0);
	m_textCtrlResultHeelHeight->SetValue(
			wxString::Format(_T("%.1f cm"), shoe->heelHeight * 100.0));
	m_textCtrlResultBallHeight->SetValue(
			wxString::Format(_T("%.1f cm"), shoe->ballHeight * 100.0));
	m_textCtrlResultToeAngle->SetValue(
			wxString::Format(_T("%.1f deg"), shoe->toeAngle * 180 / M_PI));
	m_textCtrlResultMixing->SetValue(
			wxString::Format(_T("%.0f %%"), shoe->mixing * 100.0));
	return true;
}

void FrameShoe::OnCloseX(wxCloseEvent& event)
{
	this->Hide();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHMAINGUI);
	ProcessEvent(selectEvent);
}

void FrameShoe::OnTextEnter(wxCommandEvent& event)
{
	TransferDataFromWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEPROJECT);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void FrameShoe::OnPreset(wxCommandEvent& event)
{
	Shoe * shoe = &(project->shoe);
	// 0.26 m is the average footlength (= size EU 39).
	switch(event.GetId()){
	case ID_PRESETFLATS:
		shoe->exprHeelHeight = _T("0 cm");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETCLASSIC:
		shoe->exprHeelHeight = _T("3 cm");
		shoe->exprBallHeight = _T("1.5 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETPLATEAU:
		shoe->exprHeelHeight = _T("11 cm");
		shoe->exprBallHeight = _T("9 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHLOW:
		shoe->exprHeelHeight = _T("7 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHMID:
		shoe->exprHeelHeight = _T("10 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHHIGH:
		shoe->exprHeelHeight = _T("13 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETPLATFORM:
		shoe->exprHeelHeight = _T("15 cm * (L/26cm)");
		shoe->exprBallHeight = _T("5 cm * (L/26cm)");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETPONY:
		shoe->exprHeelHeight = _T("16 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("45 deg");
		break;
	case ID_PRESETBALLET:
		shoe->exprHeelHeight = _T("20 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("90 deg");
		break;
	}
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEPROJECT);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}

void FrameShoe::OnScroll(wxScrollEvent& event)
{
	Shoe * shoe = &(project->shoe);
	shoe->mixing = ((double) event.GetPosition()) / 100.0;
	TransferDataToWindow();
}

void FrameShoe::OnScrollChange(wxScrollEvent& event)
{
	Shoe * shoe = &(project->shoe);
	shoe->mixing = ((double) event.GetPosition()) / 100.0;
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEPROJECT);
	ProcessEvent(selectEvent);
	TransferDataToWindow();
}
