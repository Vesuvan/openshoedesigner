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
#include <wx/aboutdlg.h>

#include <wx/docview.h>
#include <wx/cmdline.h>
#include <cstdlib>

IMPLEMENT_APP(openshoedesigner)

wxBEGIN_EVENT_TABLE(openshoedesigner, wxApp) EVT_MENU(wxID_ABOUT, openshoedesigner::OnAbout)
wxEND_EVENT_TABLE()

void openshoedesigner::OnAbout(wxCommandEvent&)
{
	wxAboutDialogInfo aboutInfo;

	aboutInfo.SetName(_T("OpenShoeDesigner"));
	aboutInfo.SetVersion(_T("0.1"));
	aboutInfo.SetDescription(_("Design software for Lasts and Shoes"));
	aboutInfo.SetCopyright(_T("(C) 2018-2020"));
	aboutInfo.SetWebSite(
			_T("https://sourceforge.net/projects/openshoedesigner/"));
	aboutInfo.SetLicence(
			_T(
					"GNU General Public License version 3.0 (GPLv3)\n\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\n\nYou should have received a copy of the GNU General Public License along with this program.\nIf not, see http://www.gnu.org/licenses/."));
	aboutInfo.AddDeveloper(_T("Tobias Schäfer"));

	wxAboutBox(aboutInfo);
}

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

// The Commandline is parsed before OnInit is called.
void openshoedesigner::OnInitCmdLine(wxCmdLineParser& parser)
{
	parser.AddParam(_("<filepath of document to open>"), wxCMD_LINE_VAL_STRING,
			wxCMD_LINE_PARAM_OPTIONAL);
//	parser.AddSwitch("t", "test", "Runs unit tests on some of the classes.");
	wxApp::OnInitCmdLine(parser);
}

bool openshoedesigner::OnCmdLineParsed(wxCmdLineParser& parser)
{
	int count = parser.GetParamCount();
	if(count == 1){
		wxString str = parser.GetParam(0);
		//		if(_DEBUGMODE) wxLogMessage(_T("cmd line param: ") + str);
		loadOnStartup = str;
	}
	return true;
}

bool openshoedesigner::OnInit()
{
	if(!wxApp::OnInit()) return false;
	::wxInitAllImageHandlers(); // Load all image handlers for reading in background images.

	SetAppName("openshoedesigner");
	SetAppDisplayName("Open Shoe Designer");

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

	try{
		Project* project;
		if(loadOnStartup.IsEmpty()){
			project = (Project*) docManager->CreateDocument(wxEmptyString,
					wxDOC_NEW);
		}else{
			project = (Project*) docManager->CreateDocument(loadOnStartup,
					wxDOC_SILENT);
		}
	}
	catch(std::exception &exception){
		std::cerr << "Exeption caught on first CreateDocument:\n"
				<< exception.what() << "\n";
	}

	return true;
}

bool openshoedesigner::OnExceptionInMainLoop()
{
	std::string error;
	try{
		throw; // Rethrow the current exception.
	}
	catch(const std::exception& e){
		error = e.what();
	}
	catch(...){
		error = "unknown error.";
	}
	std::cout << "Unexpected exception has occurred: " << error
			<< ", the program will terminate.\n";
	return false;
}

void openshoedesigner::OnUnhandledException()
{
	std::cout << "Unhandled Exception.\n";
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
	case ProjectView::FrameType::mainframe:
		subframe = new FrameMain(doc, view, config,
				wxStaticCast(GetTopWindow(), wxDocParentFrame));
		break;

	default:
		throw(std::logic_error("CreateChildFrame - Unsupported windowtype."));
	}
	return subframe;
}
