///////////////////////////////////////////////////////////////////////////////
// Name               : main.cpp
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

#include "main.h"

#include "gui/FrameParent.h"
#include "gui/FrameMain.h"

#include "languages.h"

#include <wx/docview.h>
#include <wx/cmdline.h>
#include <cstdlib>

IMPLEMENT_APP(openshoedesigner)

openshoedesigner::openshoedesigner()
{
	config = new wxConfig(_T("openshoedesigner"));

	unsigned int selectedLanguage = wxLocale::GetSystemLanguage();
	if(selectedLanguage == wxLANGUAGE_UNKNOWN) selectedLanguage =
			wxLANGUAGE_DEFAULT;

	// Read language from config.
	wxString str;
	if(config->Read(_T("Language"), &str)){
		unsigned int i;
		for(i = 0; i < WXSIZEOF(langNames); i++)
			if(str.CmpNoCase(langNames[i]) == 0){
				selectedLanguage = langIds[i];
			}
	}

	if(!locale.Init(selectedLanguage, wxLOCALE_DONT_LOAD_DEFAULT)){
		wxLogWarning
		(_T("This language is not supported by the system."));
		return;
	}

	locale.AddCatalogLookupPathPrefix(_T("i18n"));
	bool catalogLoaded = locale.AddCatalog(_T("openshoedesigner"));
	if(!catalogLoaded){
		wxString temp;
		temp =
		_T("The translation catalog for ") + locale.GetCanonicalName() +
		_T(" was not loaded !");
		wxLogWarning
		(temp);
	}
	locale.AddCatalog("wxstd");
}

openshoedesigner::~openshoedesigner()
{
	printf("wxApp: Destructor called\n");
	delete config; // config is written back on deletion of object
}

bool openshoedesigner::OnInit()
{
	if(!wxApp::OnInit()) return false;
	::wxInitAllImageHandlers(); // Load all image handlers for reading in background images.

	SetAppName("openshoedesigner");
	SetAppDisplayName("Open Shoe Designer");

	static const wxCmdLineEntryDesc cmdLineDesc[] = { {wxCMD_LINE_SWITCH, "h",
			"help", "Show help", wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP}, {
			wxCMD_LINE_PARAM, NULL, NULL, "input file", wxCMD_LINE_VAL_STRING,
			wxCMD_LINE_PARAM_OPTIONAL}, {wxCMD_LINE_NONE}};

	wxCmdLineParser parser(cmdLineDesc, argc, argv);
	int cmd_found = parser.Parse();

	// -h or --help was requested.
	if(cmd_found == -1){
		return false;
	}

	wxDocManager *docManager = new wxDocManager;

	new wxDocTemplate(docManager, "Shoe Design", "*.dsn", "", "dsn", "Project",
			"Project View", CLASSINFO(Project), CLASSINFO(ProjectView));

#if defined( __WXMAC__ )  && wxOSX_USE_CARBON
	wxFileName::MacRegisterDefaultTypeAndCreator("dsn" , 'WXMB' , 'WXMA'); // ?
#endif

	docManager->FileHistoryLoad(*config);

	wxFrame* parent;
	parent = new FrameParent(docManager, config, NULL, wxID_ANY,
			GetAppDisplayName());

	SetTopWindow(parent);
	parent->Show(false);

	Project* project;
	if(cmd_found == 1){
		project = (Project*) docManager->CreateDocument(parser.GetParam(0),
				wxDOC_SILENT);
	}else{
		project = (Project*) docManager->CreateDocument(wxEmptyString,
				wxDOC_NEW);
	}

	return true;
}

int openshoedesigner::OnExit()
{
	wxDocManager* const docManager = wxDocManager::GetDocumentManager();
	docManager->FileHistorySave(*config);
	delete docManager;
	printf("wxApp: Exiting Application\n");
	return wxApp::OnExit();
}

wxFrame* openshoedesigner::CreateChildFrame(wxView* view,
		ProjectView::FrameType frametype)
{
	wxFrame *subframe;
	wxDocument *doc = view->GetDocument();

	switch(frametype){
	case ProjectView::mainframe:
		subframe = new FrameMain(doc, view, config,
				wxStaticCast(GetTopWindow(), wxDocParentFrame));
		break;

	default:
		throw(std::logic_error("CreateChildFrame - Unsupported windowtype."));
	}
	return subframe;
}
