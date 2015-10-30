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
#include <wx/panel.h>
#include <wx/notebook.h>
#include "PanelSupport.h"
#include <wx/checkbox.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_QUIT 1000
#define ID_SETUPFOOT 1001
#define ID_SETUPLAST 1002
#define ID_STEREO3D 1003
#define ID_SHOWBONES 1004
#define ID_SHOWLAST 1005
#define ID_SHOWINSOLE 1006
#define ID_SHOWSHOE 1007
#define ID_SHOWCUTAWAY 1008
#define ID_SHOWFLOOR 1009
#define ID_SETUPSTEREO3D 1010
#define ID_SETUPUNITS 1011
#define ID_TOOLSETUPFOOT 1012
#define ID_TOOLSETUPLAST 1013
#define ID_SLIDER1Y 1014
#define ID_TEXT1Y 1015
#define ID_SLIDER1X 1016
#define ID_TEXT1X 1017
#define ID_SLIDER2X 1018
#define ID_TEXT2X 1019
#define ID_SLIDER3Y 1020
#define ID_TEXT3Y 1021

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameMain
///////////////////////////////////////////////////////////////////////////////
class GUIFrameMain : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxMenu* m_menuFoot;
		wxMenu* m_menuShoe;
		wxMenu* m_menuGeometry;
		wxMenu* m_menuView;
		wxMenu* m_menuSystem;
		wxStatusBar* m_statusBar1;
		Canvas3D * m_canvas;
		wxToolBar* m_toolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnQuit( wxCommandEvent& event ) = 0;
		virtual void OnSetupFoot( wxCommandEvent& event ) = 0;
		virtual void OnSetupLast( wxCommandEvent& event ) = 0;
		virtual void OnDefineWalkCycle( wxCommandEvent& event ) = 0;
		virtual void OnSaveLast( wxCommandEvent& event ) = 0;
		virtual void OnSaveInsole( wxCommandEvent& event ) = 0;
		virtual void OnSaveShoe( wxCommandEvent& event ) = 0;
		virtual void OnSaveCutaway( wxCommandEvent& event ) = 0;
		virtual void OnPackZip( wxCommandEvent& event ) = 0;
		virtual void OnToggleStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnViewChange( wxCommandEvent& event ) = 0;
		virtual void OnSetupStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnSetupUnits( wxCommandEvent& event ) = 0;
		virtual void OnToolClicked( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LastGenerator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 537,421 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrameMain();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameLastParameter
///////////////////////////////////////////////////////////////////////////////
class GUIFrameLastParameter : public wxFrame 
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
		
		GUIFrameLastParameter( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Last Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 418,514 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		~GUIFrameLastParameter();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameFootParameter
///////////////////////////////////////////////////////////////////////////////
class GUIFrameFootParameter : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_panel1;
		wxPanel* m_panel2;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) = 0;
		
	
	public:
		
		GUIFrameFootParameter( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Foot Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		~GUIFrameFootParameter();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameWalkcycleSupport
///////////////////////////////////////////////////////////////////////////////
class GUIFrameWalkcycleSupport : public wxFrame 
{
	private:
	
	protected:
		PanelSupport* m_panelSupport;
		PanelSupport* m_panelCycle;
		wxCheckBox* m_checkBoxLockAnkle;
		PanelSupport* m_panelData;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) = 0;
		
	
	public:
		
		GUIFrameWalkcycleSupport( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Walkcycle Support"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 630,453 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		~GUIFrameWalkcycleSupport();
	
};

#endif //__gui__
