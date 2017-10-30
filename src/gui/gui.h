///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/docview.h>
#include <wx/config.h>

#include <wx/string.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
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
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/slider.h>
#include "PanelSupport.h"
#include "PanelWalkcycle.h"
#include <wx/checkbox.h>
#include "PanelPlotSimple.h"

///////////////////////////////////////////////////////////////////////////

#define ID_INITIALIZEFOOTMODEL 1000
#define ID_LOADFOOTMODEL 1001
#define ID_SAVEFOOTMODEL 1002
#define ID_SETUPFOOT 1003
#define ID_SETUPSHOE 1004
#define ID_CONSTRUCTIONEXPERIMENTAL 1005
#define ID_CONSTRUCTIONWELDED 1006
#define ID_CONSTRUCTIONCEMENTED 1007
#define ID_CONSTRUCTIONMOLDED 1008
#define ID_CONSTRUCTIONDUTCH 1009
#define ID_EDITWALKCYCLE 1010
#define ID_LOADSHOE 1011
#define ID_SAVESHOE 1012
#define ID_STEREO3D 1013
#define ID_SHOWBONES 1014
#define ID_SHOWLAST 1015
#define ID_SHOWINSOLE 1016
#define ID_SHOWSOLE 1017
#define ID_SHOWUPPER 1018
#define ID_SHOWCUTAWAY 1019
#define ID_SHOWFLOOR 1020
#define ID_SETUPSTEREO3D 1021
#define ID_SETUPUNITS 1022
#define ID_TOOLSETUPFOOT 1023
#define ID_TOOLSETUPSHOE 1024
#define ID_SHOWLEFT 1025
#define ID_SHOWBOTH 1026
#define ID_SHOWRIGHT 1027
#define ID_TEXTFOOTLENGTH 1028
#define ID_TEXTFOOTWIDTH 1029
#define ID_TEXTHEELWIDTH 1030
#define ID_ANKLEWIDTH 1031
#define ID_GRIDLENGTH 1032
#define ID_GRIDDIAMETER 1033
#define ID_GRIDSKIN 1034
#define ID_GRIDLEG 1035
#define ID_PRESETFLATS 1036
#define ID_PRESETHHLOW 1037
#define ID_PRESETPLATFORM 1038
#define ID_PRESETCLASSIC 1039
#define ID_PRESETHHMID 1040
#define ID_PRESETPONY 1041
#define ID_PRESETPLATEAU 1042
#define ID_PRESETHHHIGH 1043
#define ID_PRESETBALLET 1044

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameMain
///////////////////////////////////////////////////////////////////////////////
class GUIFrameMain : public wxDocChildFrame
{
	private:
	
	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxMenu* m_menuEdit;
		wxMenu* m_menuFoot;
		wxMenu* m_menuFootModelType;
		wxMenu* m_menuLast;
		wxMenu* m_menuShoe;
		wxMenu* m_menuConstruction;
		wxMenu* m_menuPattern;
		wxMenu* m_menuGeometry;
		wxMenu* m_menuView;
		wxMenu* m_menuSettings;
		wxMenu* m_menuHelp;
		wxStatusBar* m_statusBar;
		Canvas3D * m_canvas;
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_toolFootDefinition; 
		wxToolBarToolBase* m_toolSetupShoe; 
		wxToolBarToolBase* m_toolShowLeft; 
		wxToolBarToolBase* m_toolShowBoth; 
		wxToolBarToolBase* m_toolShowRight; 
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitializeFootModel( wxCommandEvent& event ) = 0;
		virtual void OnLoadFootModel( wxCommandEvent& event ) = 0;
		virtual void OnSaveFootModel( wxCommandEvent& event ) = 0;
		virtual void OnSetupFoot( wxCommandEvent& event ) = 0;
		virtual void OnSetupShoe( wxCommandEvent& event ) = 0;
		virtual void OnConstructionSelection( wxCommandEvent& event ) = 0;
		virtual void OnEditWalkCycle( wxCommandEvent& event ) = 0;
		virtual void OnLoadShoe( wxCommandEvent& event ) = 0;
		virtual void OnSaveShoe( wxCommandEvent& event ) = 0;
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
		virtual void OnDebugParser( wxCommandEvent& event ) = 0;
		virtual void OnToolClicked( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameMain(wxDocument* doc, wxView* view, wxDocParentFrame* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Open Shoe Designer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 537,421 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
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
		
		GUIDialogQuickInitFoot( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Initialize Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP ); 
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
		wxButton* m_buttonSetByShoeSize;
		wxStaticText* m_staticTextShoeSizeEU;
		wxTextCtrl* m_textCtrlShoeSizeEU;
		wxStaticText* m_staticTextShoeSizeUS;
		wxTextCtrl* m_textCtrlShoeSizeUS;
		wxStaticText* m_staticTextShoeSizeUK;
		wxTextCtrl* m_textCtrlShoeSizeUK;
		wxStaticText* m_staticTextShoeSizeCN;
		wxTextCtrl* m_textCtrlShoeSizeCN;
		wxStaticText* m_staticTextShoeSizeJP;
		wxTextCtrl* m_textCtrlShoeSizeJP;
		wxStaticText* m_staticTextShoeSizeAU;
		wxTextCtrl* m_textCtrlShoeSizeAU;
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
		virtual void OnSetByShoeSize( wxCommandEvent& event ) = 0;
		virtual void OnCellChange( wxGridEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameFoot( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Foot Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 709,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~GUIFrameFoot();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameShoe
///////////////////////////////////////////////////////////////////////////////
class GUIFrameShoe : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticTextHeelHeight;
		wxTextCtrl* m_textCtrlHeelHeight;
		wxTextCtrl* m_textCtrlResultHeelHeight;
		wxStaticText* m_staticTextBallHeight;
		wxTextCtrl* m_textCtrlBallHeight;
		wxTextCtrl* m_textCtrlResultBallHeight;
		wxStaticText* m_staticTextToeAngle;
		wxTextCtrl* m_textCtrlToeAngle;
		wxTextCtrl* m_textCtrlResultToeAngle;
		wxStaticText* m_staticTextMixing;
		wxSlider* m_sliderMixing;
		wxTextCtrl* m_textCtrlResultMixing;
		wxButton* m_buttonFlats;
		wxButton* m_buttonHHLow;
		wxButton* m_buttonPlatform;
		wxButton* m_buttonClassic;
		wxButton* m_buttonHHMid;
		wxButton* m_buttonPony;
		wxButton* m_buttonPlateau;
		wxButton* m_buttonHHHigh;
		wxButton* m_buttonBallet;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) = 0;
		virtual void OnTextEnter( wxCommandEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		virtual void OnScrollChange( wxScrollEvent& event ) = 0;
		virtual void OnPreset( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameShoe( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Basic Shoe Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 436,287 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
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
		
		GUIFrameWalkcycleSupport( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Walkcycle Support"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 630,453 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIFrameWalkcycleSupport();
	
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
		
		GUIFrameDebugParser( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Test Parser and Units"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIFrameDebugParser();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialogAbout
///////////////////////////////////////////////////////////////////////////////
class GUIDialogAbout : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrl;
		wxButton* m_buttonClose;
	
	public:
		
		GUIDialogAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 288,200 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP ); 
		~GUIDialogAbout();
	
};

#endif //__GUI_H__
