///////////////////////////////////////////////////////////////////////////////
// Name               : FrameFoot.cpp
// Purpose            : GUI for setting up the foots parameter
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.10.2015
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

#include "FrameFoot.h"
#include "IDs.h"

FrameFoot::FrameFoot(wxWindow* parent, Foot* foot) :
		GUIFrameFoot(parent)
{
	this->foot = foot;

	m_textCtrlFootLength->SetValue(
			wxString::Format(_T("%.1f cm"), foot->L * 100));
	m_textCtrlFootWidth->SetValue(
			wxString::Format(_T("%.1f cm"), foot->W * 100));
	m_textCtrlHeelWidth->SetValue(
			wxString::Format(_T("%.1f cm"), foot->H * 100));
	m_textCtrlAnkleWidth->SetValue(
			wxString::Format(_T("%.1f cm"), foot->A * 100));

	unsigned int N = foot->GetBoneCount();
	m_gridBoneLength->AppendRows(N);
	m_gridBoneDiameter->AppendRows(N);
	m_gridSkin->AppendRows(N);

	TransferDataToWindow();
}

FrameFoot::~FrameFoot()
{
}

void FrameFoot::OnCloseX(wxCloseEvent& event)
{
	this->Hide();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEGUI);
	ProcessEvent(selectEvent);
}

void FrameFoot::OnClose(wxCommandEvent& event)
{
	this->Hide();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEGUI);
	ProcessEvent(selectEvent);
}

void FrameFoot::OnText(wxCommandEvent& event)
{
}

void FrameFoot::OnCellChange(wxGridEvent& event)
{
	TransferDataFromWindow();
	foot->Setup();
	TransferDataToWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESHPROJECT);
	ProcessEvent(selectEvent);
}

bool FrameFoot::TransferDataToWindow(void)
{
	foot->AddToGrid(m_gridBoneLength, m_gridBoneDiameter, m_gridSkin);
	return true;
}

bool FrameFoot::TransferDataFromWindow(void)
{
	foot->GetFromGrid(m_gridBoneLength, m_gridBoneDiameter, m_gridSkin);
	return true;
}