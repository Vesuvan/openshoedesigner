///////////////////////////////////////////////////////////////////////////////
// Name               : FrameDebugParser.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 16.11.2015
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

#include "FrameDebugParser.h"

FrameDebugParser::FrameDebugParser(wxWindow* parent)
		: GUIFrameDebugParser(parent)
{
	parser.autoEvaluate = true;
//	parser.AddAllowedUnit("mm", 1e-3);
//	parser.AddAllowedUnit("cm", 1e-2);
//	parser.AddAllowedUnit("m", 1);
//	parser.AddAllowedUnit("in", 2.54e-2);
//	parser.AddAllowedUnit("ft", 0.3048);
}

FrameDebugParser::~FrameDebugParser()
{
}

void FrameDebugParser::OnCloseX(wxCloseEvent& event)
{
	this->Hide();
}

void FrameDebugParser::OnText(wxCommandEvent& event)
{
	wxString text;
	text = m_textCtrlExpression->GetValue();
	parser.SetString(text.ToStdString());
	m_textCtrlError->SetValue(parser.GetError());
	if(parser.HasError()){
		m_textCtrlNumber->SetValue(_T(""));
		m_textCtrlUnit->SetValue(_T(""));
	}else{
		m_textCtrlNumber->SetValue(
				wxString::Format(_T("%g"), parser.GetNumber()));
		m_textCtrlUnit->SetValue(parser.GetUnit());
	}
}
