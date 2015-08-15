///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include "Canvas3D.h"
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_QUIT 1000

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameMain
///////////////////////////////////////////////////////////////////////////////
class GUIFrameMain : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxStatusBar* m_statusBar1;
		Canvas3D * m_canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnQuit( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LastGenerator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 537,421 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrameMain();
	
};

#endif //__gui__
