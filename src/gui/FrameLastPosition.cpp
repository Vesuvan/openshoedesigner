///////////////////////////////////////////////////////////////////////////////
// Name               : FrameLastPosition.cpp
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

#include "FrameLastPosition.h"

#include <math.h>

#include "IDs.h"

FrameLastPosition::FrameLastPosition(wxWindow* parent, FootParameters * param) :
		GUIFrameLastPosition(parent)
{
	this->param = param;
	TransferDataToWindow();
}

FrameLastPosition::~FrameLastPosition()
{
}

void FrameLastPosition::OnScroll(wxScrollEvent& event)
{
	switch(event.GetId()){
	case ID_SLIDER1X:
		param->angle_1X = (float) m_slider1X->GetValue() / 180 * M_PI;
		m_textCtrl1X->SetValue(
				wxString::Format(_T("%.1f"), param->angle_1X / M_PI * 180));
		break;
	case ID_SLIDER1Y:
		param->angle_1Y = (float) m_slider1Y->GetValue() / 180 * M_PI;
		m_textCtrl1Y->SetValue(
				wxString::Format(_T("%.1f"), param->angle_1Y / M_PI * 180));
		break;
	case ID_SLIDER2X:
		param->angle_2X = (float) m_slider2X->GetValue() / 180 * M_PI;
		m_textCtrl2X->SetValue(
				wxString::Format(_T("%.1f"), param->angle_2X / M_PI * 180));
		break;
	case ID_SLIDER3Y:
		param->angle_3Y = (float) m_slider3Y->GetValue() / 180 * M_PI;
		m_textCtrl3Y->SetValue(
				wxString::Format(_T("%.1f"), param->angle_3Y / M_PI * 180));
		break;
	}
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATELAST);
	ProcessEvent(selectEvent);
}

bool FrameLastPosition::TransferDataToWindow()
{
	m_slider1X->SetValue(param->angle_1X / M_PI * 180);
	m_slider1Y->SetValue(param->angle_1Y / M_PI * 180);
	m_slider2X->SetValue(param->angle_2X / M_PI * 180);
	m_slider3Y->SetValue(param->angle_3Y / M_PI * 180);
	m_textCtrl1X->SetValue(
			wxString::Format(_T("%.1f"), param->angle_1X / M_PI * 180));
	m_textCtrl1Y->SetValue(
			wxString::Format(_T("%.1f"), param->angle_1Y / M_PI * 180));
	m_textCtrl2X->SetValue(
			wxString::Format(_T("%.1f"), param->angle_2X / M_PI * 180));
	m_textCtrl3Y->SetValue(
			wxString::Format(_T("%.1f"), param->angle_3Y / M_PI * 180));
	return true;
}

void FrameLastPosition::OnClose(wxCloseEvent& event)
{
	this->Hide();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATEBUTTONS);
	ProcessEvent(selectEvent);
}

void FrameLastPosition::OnText(wxCommandEvent& event)
{
	TransferDataFromWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_UPDATELAST);
	ProcessEvent(selectEvent);
}
