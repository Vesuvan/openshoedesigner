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
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/checkbox.h>
#include "PanelSupport.h"
#include "PanelWalkcycle.h"
#include <wx/statbox.h>
#include "PanelPlotSimple.h"
#include "PanelPattern.h"
#include <wx/slider.h>

///////////////////////////////////////////////////////////////////////////

#define ID_LOADFOOTMODEL 1000
#define ID_SAVEFOOTMODEL 1001
#define ID_LOADSHOE 1002
#define ID_SAVESHOE 1003
#define ID_INITIALIZEFOOTMODEL 1004
#define ID_SETUPFOOT 1005
#define ID_SETUPSHOE 1006
#define ID_EDITPATTERN 1007
#define ID_EDITWALKCYCLE 1008
#define ID_STEREO3D 1009
#define ID_SHOWBONES 1010
#define ID_SHOWLAST 1011
#define ID_SHOWINSOLE 1012
#define ID_SHOWSOLE 1013
#define ID_SHOWUPPER 1014
#define ID_SHOWCUTAWAY 1015
#define ID_SHOWFLOOR 1016
#define ID_SETUPSTEREO3D 1017
#define ID_SETUPUNITS 1018
#define ID_TOOLSETUPFOOT 1019
#define ID_TOOLSETUPSHOE 1020
#define ID_TEXTFOOTLENGTH 1021
#define ID_TEXTFOOTWIDTH 1022
#define ID_TEXTHEELWIDTH 1023
#define ID_ANKLEWIDTH 1024
#define ID_GRIDLENGTH 1025
#define ID_GRIDDIAMETER 1026
#define ID_GRIDSKIN 1027
#define ID_GRIDLEG 1028
#define ID_PRESETFLATS 1029
#define ID_PRESETHHLOW 1030
#define ID_PRESETPLATFORM 1031
#define ID_PRESETHIKING 1032
#define ID_PRESETHHMID 1033
#define ID_PRESETPONY 1034
#define ID_PRESETPLATEAU 1035
#define ID_PRESETHHHIGH 1036
#define ID_PRESETBALLET 1037

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
		wxMenu* m_menuSettings;
		wxMenu* m_menuHelp;
		wxStatusBar* m_statusBar1;
		Canvas3D * m_canvas;
		wxToolBar* m_toolBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLoadFootModel( wxCommandEvent& event ) = 0;
		virtual void OnSaveFootModel( wxCommandEvent& event ) = 0;
		virtual void OnLoadShoe( wxCommandEvent& event ) = 0;
		virtual void OnSaveShoe( wxCommandEvent& event ) = 0;
		virtual void OnQuit( wxCommandEvent& event ) = 0;
		virtual void OnInitializeFootModel( wxCommandEvent& event ) = 0;
		virtual void OnSetupFoot( wxCommandEvent& event ) = 0;
		virtual void OnSetupShoe( wxCommandEvent& event ) = 0;
		virtual void OnEditPattern( wxCommandEvent& event ) = 0;
		virtual void OnEditWalkCycle( wxCommandEvent& event ) = 0;
		virtual void OnSaveLast( wxCommandEvent& event ) = 0;
		virtual void OnSaveInsole( wxCommandEvent& event ) = 0;
		virtual void OnSaveSole( wxCommandEvent& event ) = 0;
		virtual void OnSaveCutaway( wxCommandEvent& event ) = 0;
		virtual void OnPackZip( wxCommandEvent& event ) = 0;
		virtual void OnToggleStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnViewChange( wxCommandEvent& event ) = 0;
		virtual void OnSetupStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnSetupUnits( wxCommandEvent& event ) = 0;
		virtual void OnSelectLanguage( wxCommandEvent& event ) = 0;
		virtual void OnAbout( wxCommandEvent& event ) = 0;
		virtual void OnDebug( wxCommandEvent& event ) = 0;
		virtual void OnToolClicked( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LastGenerator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 537,421 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIFrameMain();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialogQuickInitFoot
///////////////////////////////////////////////////////////////////////////////
class GUIDialogQuickInitFoot : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText37;
		wxTextCtrl* m_textCtrlShoeSize;
		wxChoice* m_choiceUnit;
		wxRadioButton* m_radioBtnSmall;
		wxRadioButton* m_radioBtnMedium;
		wxRadioButton* m_radioBtnWide;
		wxButton* m_buttonInit;
		wxButton* m_buttonAbort;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnText( wxCommandEvent& event ) = 0;
		virtual void OnChoice( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIDialogQuickInitFoot( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Initialize Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
		~GUIDialogQuickInitFoot();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameFoot
///////////////////////////////////////////////////////////////////////////////
class GUIFrameFoot : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_notebook;
		wxPanel* m_panelMeasurements;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textCtrlFootLength;
		wxStaticText* m_staticText23;
		wxTextCtrl* m_textCtrlFootWidth;
		wxStaticText* m_staticText25;
		wxTextCtrl* m_textCtrlHeelWidth;
		wxStaticText* m_staticText27;
		wxTextCtrl* m_textCtrlAnkleWidth;
		wxPanel* m_panelBone;
		wxGrid* m_gridBoneLength;
		wxPanel* m_panelBoneDiameter;
		wxGrid* m_gridBoneDiameter;
		wxPanel* m_panelSkin;
		wxGrid* m_gridSkin;
		wxPanel* m_panelLeg;
		wxGrid* m_gridLeg;
		wxStaticText* m_staticText38;
		wxMenuBar* m_menubar;
		wxMenu* m_menuFoot;
		wxMenu* m_menuSettings;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) = 0;
		virtual void OnText( wxCommandEvent& event ) = 0;
		virtual void OnCellChange( wxGridEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameFoot( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Foot Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 709,321 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIFrameFoot();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameShoe
///////////////////////////////////////////////////////////////////////////////
class GUIFrameShoe : public wxFrame 
{
	private:
	
	protected:
		wxCheckBox* m_checkBoxHeelHeight;
		wxTextCtrl* m_textCtrlHeelHeight;
		wxCheckBox* m_checkBoxPlateauHeight;
		wxTextCtrl* m_textCtrlPlateauHeight;
		wxCheckBox* m_checkBoxHeelAngle;
		wxTextCtrl* m_textCtrlHeelAngle;
		wxCheckBox* m_checkBoxToeAngle;
		wxTextCtrl* m_textCtrlToeAngle;
		wxButton* m_buttonFlats;
		wxButton* m_buttonHHLow;
		wxButton* m_buttonPlatform;
		wxButton* m_buttonHiking;
		wxButton* m_buttonHHMid;
		wxButton* m_buttonPony;
		wxButton* m_buttonPlateau;
		wxButton* m_buttonHHHigh;
		wxButton* m_buttonBallet;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) = 0;
		virtual void OnClick( wxCommandEvent& event ) = 0;
		virtual void OnText( wxCommandEvent& event ) = 0;
		virtual void OnPreset( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameShoe( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Basic Shoe Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIFrameShoe();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameWalkcycleSupport
///////////////////////////////////////////////////////////////////////////////
class GUIFrameWalkcycleSupport : public wxFrame 
{
	private:
	
	protected:
		PanelSupport* m_panelSupport;
		PanelWalkcycle* m_panelCycle;
		wxCheckBox* m_checkBoxLockAnkle;
		PanelPlotSimple* m_panelPlot;
		wxChoice* m_choiceDisplay;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) = 0;
		virtual void OnToggleAnkleLock( wxCommandEvent& event ) = 0;
		virtual void OnChoiceDisplay( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameWalkcycleSupport( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Walkcycle Support"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 630,453 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIFrameWalkcycleSupport();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFramePattern
///////////////////////////////////////////////////////////////////////////////
class GUIFramePattern : public wxFrame 
{
	private:
	
	protected:
		PanelPattern* m_panel;
		wxStaticText* m_staticText17;
		wxChoice* m_choicePreset;
		wxStaticText* m_staticText18;
		wxChoice* m_choiceStyle;
		wxStaticText* m_staticText19;
		wxSlider* m_sliderBootLength;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) = 0;
		virtual void OnChoicePreset( wxCommandEvent& event ) = 0;
		virtual void OnChoiceStyle( wxCommandEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		
	
	public:
		
		GUIFramePattern( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Pattern"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIFramePattern();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameDebugParser
///////////////////////////////////////////////////////////////////////////////
class GUIFrameDebugParser : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText10;
		wxTextCtrl* m_textCtrlExpression;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textCtrlNumber;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textCtrlError;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrlUnit;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textCtrlSIBase;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) = 0;
		virtual void OnText( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameDebugParser( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Test Parser and Units"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		~GUIFrameDebugParser();
	
};

#endif //__gui__
