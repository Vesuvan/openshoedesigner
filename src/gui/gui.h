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
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_QUIT 1000
#define ID_STEREO3D 1001
#define ID_SETUPSTEREO3D 1002
#define ID_SETUPUNITS 1003
#define ID_FOOTDEFINITION 1004
#define ID_LASTPOSITION 1005
#define ID_SLIDER1Y 1006
#define ID_TEXT1Y 1007
#define ID_SLIDER1X 1008
#define ID_TEXT1X 1009
#define ID_SLIDER2X 1010
#define ID_TEXT2X 1011
#define ID_SLIDER3Y 1012
#define ID_TEXT3Y 1013

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameMain
///////////////////////////////////////////////////////////////////////////////
class GUIFrameMain : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxMenu* m_menuSetup;
		wxStatusBar* m_statusBar1;
		Canvas3D * m_canvas;
		wxToolBar* m_toolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnQuit( wxCommandEvent& event ) = 0;
		virtual void OnToggleStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnSetupStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnSetupUnits( wxCommandEvent& event ) = 0;
		virtual void OnToolClicked( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LastGenerator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 537,421 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrameMain();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameLastPosition
///////////////////////////////////////////////////////////////////////////////
class GUIFrameLastPosition : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		
		wxStaticText* m_staticText2;
		
		wxStaticText* m_staticText3;
		wxSlider* m_slider1Y;
		
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrl1Y;
		wxStaticText* m_staticText111;
		
		wxStaticText* m_staticText211;
		
		wxStaticText* m_staticText311;
		wxSlider* m_slider1X;
		
		wxStaticText* m_staticText42;
		wxTextCtrl* m_textCtrl1X;
		wxStaticText* m_staticText11;
		
		wxStaticText* m_staticText21;
		
		wxStaticText* m_staticText31;
		wxSlider* m_slider2X;
		
		wxStaticText* m_staticText41;
		wxTextCtrl* m_textCtrl2X;
		wxStaticText* m_staticText112;
		
		wxStaticText* m_staticText212;
		
		wxStaticText* m_staticText312;
		wxSlider* m_slider3Y;
		
		wxStaticText* m_staticText411;
		wxTextCtrl* m_textCtrl3Y;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		virtual void OnText( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameLastPosition( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Last Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 418,514 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		~GUIFrameLastPosition();
	
};

#endif //__gui__
