///////////////////////////////////////////////////////////////////////////////
// Name               : FrameParent.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 26.10.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "FrameParent.h"

#include "gui.h"
#include <cstdio>
wxBEGIN_EVENT_TABLE(FrameParent, wxDocParentFrame)
EVT_MENU(wxID_ABOUT, FrameParent::OnAbout)
EVT_MENU(wxID_HELP, FrameParent::OnHelp)
wxEND_EVENT_TABLE()

FrameParent::FrameParent(wxDocManager *manager, wxFrame *parent, wxWindowID id,
		const wxString& title)
		: wxDocParentFrame(manager, parent, id, title)
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(wxID_NEW);
	menuFile->Append(wxID_OPEN);
	menuFile->AppendSeparator();
	menuFile->Append(wxID_PRINT_SETUP, "Print &Setup...");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_HELP, _("&Help") + wxT("\tF1"));
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menubar = new wxMenuBar;
	menubar->Append(menuFile, wxGetStockLabel(wxID_FILE));
	menubar->Append(menuHelp, wxGetStockLabel(wxID_HELP));

	SetMenuBar(menubar);

	m_helpController = new wxHelpController();

	//TODO Logging is disable here, because the SESSION_MANAGER variable is not defined since Ubuntu 16.04.
	// The initialisation of the help controller will always lead to the message:
	// 	Debug: Failed to connect to session manager: SESSION_MANAGER environment variable not defined
	wxLog::EnableLogging(false);
	m_helpController->Initialize(_T("doc/help/OpenShoeDesigner.hhp"));
	wxLog::EnableLogging(true);
}

FrameParent::~FrameParent()
{
	delete m_helpController;
}

void FrameParent::OnAbout(wxCommandEvent&)
{
	GUIDialogAbout dialog(this);
	dialog.ShowModal();
}

void FrameParent::OnHelp(wxCommandEvent&)
{
	m_helpController->DisplayContents();
}
