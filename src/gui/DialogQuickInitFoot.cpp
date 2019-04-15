///////////////////////////////////////////////////////////////////////////////
// Name               : DialogQuickInitFoot.cpp
// Purpose            : Dialog to initialize foot and last settings
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : toby
// Created            : 01.11.2015
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

#include "DialogQuickInitFoot.h"

DialogQuickInitFoot::DialogQuickInitFoot(wxWindow* parent)
		: GUIDialogQuickInitFoot(parent)
{
	parser.ResetVariables(false);
	parser.autoEvaluate = true;
	length = 0;
	width = 0;
}

DialogQuickInitFoot::~DialogQuickInitFoot()
{
}

void DialogQuickInitFoot::OnTextEnter(wxCommandEvent& event)
{
	ParseText(event.GetString());

	//	m_textCtrlShoeSize->Navigate();
	m_buttonInit->SetFocus();
}

void DialogQuickInitFoot::OnClose(wxCommandEvent& event)
{
	ParseText(m_textCtrlShoeSize->GetValue());
	event.Skip();
}

void DialogQuickInitFoot::ParseText(wxString text)
{
	parser.SetString(text);
	const double num = parser.GetNumber();
	m_textCtrlShoeSize->SetValue(wxString::Format(_T("%g"), num));
	if(parser.HasUnit()){
		wxString unit = parser.GetUnit();
		if(unit.CmpNoCase(_T("EU")) == 0) m_choiceUnit->SetSelection(0);
		if(unit.CmpNoCase(_T("US")) == 0) m_choiceUnit->SetSelection(1);
		if(unit.CmpNoCase(_T("CN")) == 0) m_choiceUnit->SetSelection(2);
		if(unit.CmpNoCase(_T("UK")) == 0) m_choiceUnit->SetSelection(3);
		if(unit.CmpNoCase(_T("JP")) == 0) m_choiceUnit->SetSelection(4);
		if(unit.CmpNoCase(_T("AU")) == 0) m_choiceUnit->SetSelection(5);
		if(unit.CmpNoCase(_T("mm")) == 0) m_choiceUnit->SetSelection(6);
		if(unit.CmpNoCase(_T("cm")) == 0) m_choiceUnit->SetSelection(7);
		if(unit.CmpNoCase(_T("in")) == 0) m_choiceUnit->SetSelection(8);
		if(unit.CmpNoCase(_T("ft")) == 0) m_choiceUnit->SetSelection(9);
	}

	switch(m_choiceUnit->GetSelection()){
	case 0:
		length = num / 150 - 1.5e-2;
		break;
	case 1:
		length = (num + 21.5) / 3 * 2.54e-2;
		break;
	case 2:
		length = num / 100;
		break;
	case 3:
		length = ((num + 25) * 8.46e-3) - 1.5e-2;
		break;
	case 4:
		length = num / 1000;
		break;
	case 5:
		length = ((num + 25) * 8.46e-3) - 1.5e-2;
		break;
	case 6:
		length = num * 1e-3;
		break;
	case 7:
		length = num * 1e-2;
		break;
	case 8:
		length = num * 2.54e-2;
		break;
	case 9:
		length = num * 0.3048;
		break;
	}

	width = 0.9;
	if(m_radioBtnSmall->GetValue()) width = 0.8;
	if(m_radioBtnWide->GetValue()) width = 1.0;
}
