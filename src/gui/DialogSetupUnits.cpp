///////////////////////////////////////////////////////////////////////////////
// Name               : DialogSetupUnits.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 03.07.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "DialogSetupUnits.h"
#include "IDs.h"
#include "../StdInclude.h"

DialogSetupUnits::DialogSetupUnits(wxWindow* parent, DisplaySettings * settings)
		: GUIFrameSetupUnits(parent)
{
	this->settings = settings;

	TransferDataToWindow();
}

DialogSetupUnits::~DialogSetupUnits()
{
}

void DialogSetupUnits::OnClose(wxCommandEvent& event)
{
	Hide();
}

bool DialogSetupUnits::TransferDataToWindow(void)
{
	int i;

	m_choiceUnitLength->Clear();
	m_choiceUnitLength->Append(settings->unitsOfLength);
	i = m_choiceUnitLength->FindString(settings->Distance.GetOtherName());
	if(i == wxNOT_FOUND) i = 6;
	m_choiceUnitLength->SetSelection(i);

	m_choiceUnitSmallDistance->Clear();
	m_choiceUnitSmallDistance->Append(settings->unitsOfLength);
	i = m_choiceUnitSmallDistance->FindString(
			settings->SmallDistance.GetOtherName());
	if(i == wxNOT_FOUND) i = 6;
	m_choiceUnitSmallDistance->SetSelection(i);

	m_choiceUnitAngle->Clear();
	m_choiceUnitAngle->Append(settings->unitsOfAngle);
	i = m_choiceUnitAngle->FindString(settings->Angle.GetOtherName());
	if(i == wxNOT_FOUND) i = 0;
	m_choiceUnitAngle->SetSelection(i);

	return true;
}
bool DialogSetupUnits::TransferDataFromWindow(void)
{
	int i;

	i = m_choiceUnitLength->GetSelection();
	settings->Distance.Setup(_T("m"), settings->unitsOfLength[i],
			settings->factorofLength[i]);

	i = m_choiceUnitSmallDistance->GetSelection();
	settings->SmallDistance.Setup(_T("m"), settings->unitsOfLength[i],
			settings->factorofLength[i]);

	i = m_choiceUnitAngle->GetSelection();
	settings->Angle.Setup(_T("rad"), settings->unitsOfAngle[i],
			settings->factorofAngle[i]);

	return true;
}

void DialogSetupUnits::OnCloseX(wxCloseEvent& event)
{
	Hide();
}

void DialogSetupUnits::OnChangeUnit(wxCommandEvent& event)
{
	TransferDataFromWindow();
	wxCommandEvent selectEvent(wxEVT_COMMAND_MENU_SELECTED, ID_REFRESH);
	ProcessEvent(selectEvent);
}
