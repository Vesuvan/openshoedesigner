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
	m_textCtrlHeelHeight->SetValue(project->HeelHeight);
	m_textCtrlPlateauHeight->SetValue(project->PlateauHeight);
	m_textCtrlHeelAngle->SetValue(project->HeelAngle);
	m_textCtrlToeAngle->SetValue(project->ToeAngle);
	return true;
}

void FrameShoe::OnCloseX(wxCloseEvent& event)
{
	this->Hide();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEGUI);
	ProcessEvent(selectEvent);
}

void FrameShoe::OnText(wxCommandEvent& event)
{
	TransferDataFromWindow();
	project->Evaluate();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_CALCULATELAST);
	ProcessEvent(selectEvent);
}

void FrameShoe::OnClick(wxCommandEvent& event)
{
}

void FrameShoe::OnPreset(wxCommandEvent& event)
{
	// 0.26 m is the average footlength (= size EU 39).
	switch(event.GetId()){
	case ID_PRESETFLATS:
		project->HeelHeight = _T("0 cm");
		project->PlateauHeight = _T("0 cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("0 deg");
		break;
	case ID_PRESETHIKING:
		project->HeelHeight = _T("4 cm");
		project->PlateauHeight = _T("1 cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("0 deg");
		break;
	case ID_PRESETPLATEAU:
		project->HeelHeight = _T("11 cm");
		project->PlateauHeight = _T("9 cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHLOW:
		project->HeelHeight = _T("7*(L/0.26) cm");
		project->PlateauHeight = _T("0 cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHMID:
		project->HeelHeight = _T("10*(L/0.26) cm");
		project->PlateauHeight = _T("0 cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHHIGH:
		project->HeelHeight = _T("13*(L/0.26) cm");
		project->PlateauHeight = _T("0 cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("0 deg");
		break;
	case ID_PRESETPLATFORM:
		project->HeelHeight = _T("15*(L/0.26) cm");
		project->PlateauHeight = _T("5*(L/0.26) cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("0 deg");
		break;
	case ID_PRESETPONY:
		project->HeelHeight = _T("16*(L/0.26) cm");
		project->PlateauHeight = _T("0 cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("45 deg");
		break;
	case ID_PRESETBALLET:
		project->HeelHeight = _T("20*(L/0.26) cm");
		project->PlateauHeight = _T("0 cm");
		project->HeelAngle = _T("0 deg");
		project->ToeAngle = _T("90 deg");
		break;
	}
	project->Evaluate();
	TransferDataToWindow();
}
