///////////////////////////////////////////////////////////////////////////////
// Name               : main.h
// Purpose            : Main entry point
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.08.2015
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

#ifndef MAIN_H_
#define MAIN_H_

#include "StdInclude.h"
#include "project/Project.h"
#include "project/ProjectView.h"

#include <wx/app.h>
#include <wx/intl.h>
#include <wx/config.h>

class FrameMain;

class openshoedesigner:public wxApp {
public:
	openshoedesigner();
	virtual ~openshoedesigner();
	// Member variables
public:
//	FrameMain* frame;

protected:
	wxLocale locale;
	wxConfig* config;

	// Methods
public:
	virtual bool OnInit();
	virtual int OnExit();
	wxFrame* CreateChildFrame(wxView* view, ProjectView::FrameType frametype);
	wxDECLARE_NO_COPY_CLASS(openshoedesigner);
};
DECLARE_APP(openshoedesigner)

#endif /* MAIN_H_ */
