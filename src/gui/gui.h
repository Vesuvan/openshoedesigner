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
#include "ExtendedTextCtrl.h"

#include <wx/string.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/statbmp.h>
#include <wx/panel.h>
#include <wx/filepicker.h>
#include <wx/choicebk.h>
#include <wx/choice.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/treelist.h>
#include <wx/listbox.h>
#include <wx/notebook.h>
#include "Canvas3D.h"
#include "PanelPattern.h"
#include "PanelSupport.h"
#include "PanelWalkcycle.h"
#include "PanelPlotSimple.h"
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/radiobut.h>
#include <wx/dialog.h>
#include <wx/dataview.h>
#include <wx/listctrl.h>
#include <wx/spinbutt.h>

///////////////////////////////////////////////////////////////////////////

#define ID_QUICKSETUPMEASUREMENTS 1000
#define ID_FULLSYMMETRY 1001
#define ID_SYMMETRICMODEL 1002
#define ID_INDIVIDUALMODEL 1003
#define ID_COPYLEFTTORIGHT 1004
#define ID_COPYRIGHTTOLEFT 1005
#define ID_USEFOOTMEASUREMENTS 1006
#define ID_USEFOOTSCAN 1007
#define ID_USEBONEBASEDMODEL 1008
#define ID_USELASTBASEDMODEL 1009
#define ID_EDITBONEMODEL 1010
#define ID_LOADFOOTMODEL 1011
#define ID_SAVEFOOTMODEL 1012
#define ID_CONSTRUCTIONEXPERIMENTAL 1013
#define ID_CONSTRUCTIONWELDED 1014
#define ID_CONSTRUCTIONCEMENTED 1015
#define ID_CONSTRUCTIONMOLDED 1016
#define ID_CONSTRUCTIONDUTCH 1017
#define ID_LOADPATTERN 1018
#define ID_SAVEPATTERN 1019
#define ID_STEREO3D 1020
#define ID_SHOWLEFT 1021
#define ID_SHOWRIGHT 1022
#define ID_SHOWBONES 1023
#define ID_SHOWSKIN 1024
#define ID_SHOWLEG 1025
#define ID_SHOWLAST 1026
#define ID_SHOWINSOLE 1027
#define ID_SHOWSOLE 1028
#define ID_SHOWUPPER 1029
#define ID_SHOWCUTAWAY 1030
#define ID_SHOWFLOOR 1031
#define ID_SHOWCOORDINATESYSTEM 1032
#define ID_SHOWBACKGROUND 1033
#define ID_EDITLEFT 1034
#define ID_EDITRIGHT 1035
#define ID_MEASUREMENT_FOOTLENGTH 1036
#define ID_MEASUREMENT_BALLGIRTH 1037
#define ID_MEASUREMENT_WAISTGIRTH 1038
#define ID_MEASUREMENT_INSTEPGIRTH 1039
#define ID_MEASUREMENT_LONGHEELGIRTH 1040
#define ID_MEASUREMENT_SHORTHEELGIRTH 1041
#define ID_MEASUREMENT_ANGLEMIXING 1042
#define ID_MEASUREMENT_LEGLENGTHDIFFERENCE 1043
#define ID_IMAGEFOOT 1044
#define ID_MEASUREMENT_BELOWCRUTCHGIRTH 1045
#define ID_MEASUREMENT_BELOWCRUTCHLEVEL 1046
#define ID_MEASUREMENT_MIDDLEOFCALFGIRTH 1047
#define ID_MEASUREMENT_MIDDLEOFCALFLEVEL 1048
#define ID_MEASUREMENT_ABOVEKNEEGIRTH 1049
#define ID_MEASUREMENT_ABOVEKNEELEVEL 1050
#define ID_MEASUREMENT_OVERKNEECAPGIRTH 1051
#define ID_MEASUREMENT_OVERKNEECAPLEVEL 1052
#define ID_MEASUREMENT_BELOWKNEEGIRTH 1053
#define ID_MEASUREMENT_BELOWKNEELEVEL 1054
#define ID_MEASUREMENT_MIDDLEOFSHANKGIRTH 1055
#define ID_MEASUREMENT_MIDDLEOFSHANKLEVEL 1056
#define ID_MEASUREMENT_ABOVEANKLEGIRTH 1057
#define ID_MEASUREMENT_ABOVEANKLELEVEL 1058
#define ID_MEASUREMENT_OVERANKLEBONEGIRTH 1059
#define ID_MEASUREMENT_OVERANKLEBONELEVEL 1060
#define ID_PRESETSHOETYPE 1061
#define ID_HEELHEIGHT 1062
#define ID_BALLHEIGHT 1063
#define ID_HEELPITCH 1064
#define ID_TOESPRING 1065
#define ID_PRESETSHOEHEIGHT 1066
#define ID_UPPERLEVEL 1067
#define ID_TIPSYMMETRY 1068
#define ID_TIPPOINTEDNESS 1069
#define ID_TIPSHARPNESS 1070
#define ID_EXTRALENGTH 1071
#define ID_FOOTCOMPRESSION 1072
#define ID_CHECKSEPARATEDHEEL 1073
#define ID_SLIDERTOESUPPORTRADIUS 1074
#define ID_SLIDERTOESUPPORTOFFSET 1075
#define ID_GRIDLENGTH 1076
#define ID_GRIDDIAMETER 1077
#define ID_GRIDSKIN 1078
#define ID_SPINSCALE 1079
#define ID_SPINOFFSHOR 1080
#define ID_SPINOFFSVERT 1081
#define ID_CLOSE 1082

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
		wxMenu* m_menuSymmetry;
		wxMenu* m_menuFootParameters;
		wxMenu* m_menuFootModel;
		wxMenu* m_menuBoneModel;
		wxMenu* m_menuLast;
		wxMenu* m_menuShoe;
		wxMenu* m_menuConstruction;
		wxMenu* m_menuPattern;
		wxMenu* m_menuFabric;
		wxMenu* m_menuGeometry;
		wxMenu* m_menuView;
		wxMenu* m_menuPreferences;
		wxMenu* m_menuHelp;
		wxSplitterWindow* m_splitter;
		wxPanel* m_panelConfig;
		wxNotebook* m_notebook;
		wxPanel* m_panelPageFoot;
		wxToggleButton* m_toggleBtnEditLeft;
		wxToggleButton* m_toggleBtnEditRight;
		wxChoicebook* m_choicebookMeasurement;
		wxPanel* m_panelMeasurementBased;
		wxStaticText* m_staticTextFootLength;
		ExtendedTextCtrl* m_textCtrlFootLength;
		wxStaticText* m_staticTextBallGirth;
		ExtendedTextCtrl* m_textCtrlBallGirth;
		wxStaticText* m_staticTextWaistGirth;
		ExtendedTextCtrl* m_textCtrlWaistGirth;
		wxStaticText* m_staticTextInsteGirth;
		ExtendedTextCtrl* m_textCtrlInstepGirth;
		wxStaticText* m_staticTextLongHeelGirth;
		ExtendedTextCtrl* m_textCtrlLongHeelGirth;
		wxStaticText* m_staticTextShortHeelGirth;
		ExtendedTextCtrl* m_textCtrlShortHeelGirth;
		wxStaticText* m_staticTextAngleMixing;
		ExtendedTextCtrl* m_textCtrlAngleMixing;
		wxStaticText* m_staticTextLegLengthDifference;
		ExtendedTextCtrl* m_textCtrlLegLengthDifference;
		wxButton* m_buttonQuickSetup;
		wxStaticText* m_staticTextShoeSizeEU;
		ExtendedTextCtrl* m_textCtrlShoeSizeEU;
		wxStaticText* m_staticTextShoeSizeUS;
		ExtendedTextCtrl* m_textCtrlShoeSizeUS;
		wxStaticText* m_staticTextShoeSizeUK;
		ExtendedTextCtrl* m_textCtrlShoeSizeUK;
		wxStaticText* m_staticTextShoeSizeCN;
		ExtendedTextCtrl* m_textCtrlShoeSizeCN;
		wxStaticText* m_staticTextShoeSizeJP;
		ExtendedTextCtrl* m_textCtrlShoeSizeJP;
		wxStaticText* m_staticTextShoeSizeAU;
		ExtendedTextCtrl* m_textCtrlShoeSizeAU;
		wxStaticBitmap* m_bitmapFoot;
		wxPanel* m_panelScanBased;
		wxStaticText* m_staticTextScanFile;
		wxFilePickerCtrl* m_filePickerScanFile;
		wxChoicebook* m_choicebookFootModel;
		wxPanel* m_panelBoneBasedModel;
		wxButton* m_buttonEditBoneModel;
		wxPanel* m_panelLastBasedModel;
		wxStaticText* m_staticTextLastModel;
		wxFilePickerCtrl* m_filePickerLastModel;
		wxPanel* m_panelPageLeg;
		wxToggleButton* m_toggleBtnEditLeft1;
		wxToggleButton* m_toggleBtnEditRight1;
		wxStaticBitmap* m_bitmapLeg;
		wxStaticText* m_staticTextGirth;
		wxStaticText* m_staticTextLevel;
		ExtendedTextCtrl* m_textCtrlBelowCrutchGirth;
		ExtendedTextCtrl* m_textCtrlBelowCrutchLevel;
		ExtendedTextCtrl* m_textCtrlMiddleOfCalfGirth;
		ExtendedTextCtrl* m_textCtrlMiddleOfCalfLevel;
		ExtendedTextCtrl* m_textCtrlAboveKneeGirth;
		ExtendedTextCtrl* m_textCtrlAboveKneeLevel;
		ExtendedTextCtrl* m_textCtrlOverKneeCapGirth;
		ExtendedTextCtrl* m_textCtrlOverKneeCapLevel;
		ExtendedTextCtrl* m_textCtrlBelowKneeGirth;
		ExtendedTextCtrl* m_textCtrlBelowKneeLevel;
		ExtendedTextCtrl* m_textCtrlMiddleOfShankGirth;
		ExtendedTextCtrl* m_textCtrlMiddleOfShankLevel;
		ExtendedTextCtrl* m_textCtrlAboveAnkleGirth;
		ExtendedTextCtrl* m_textCtrlAboveAnkleLevel;
		ExtendedTextCtrl* m_textCtrlOverAnkleBoneGirth;
		ExtendedTextCtrl* m_textCtrlOverAnkleBoneLevel;
		wxPanel* m_panelPageShoe;
		wxChoice* m_choiceShoeType;
		wxStaticText* m_staticTextHeelHeight;
		ExtendedTextCtrl* m_textCtrlHeelHeight;
		wxStaticText* m_staticTextBallHeight;
		ExtendedTextCtrl* m_textCtrlBallHeight;
		wxStaticText* m_staticTextHeelPitch;
		ExtendedTextCtrl* m_textCtrlHeelPitch;
		wxStaticText* m_staticTextToeSpring;
		ExtendedTextCtrl* m_textCtrlToeSpring;
		wxChoice* m_choiceShoeHeight;
		wxStaticText* m_staticTextUpperLevel;
		ExtendedTextCtrl* m_textCtrlUpperLevel;
		wxStaticText* m_staticTextTipSymmetry;
		wxSlider* m_sliderSymmetry;
		wxStaticText* m_staticTextTipPointedness;
		wxSlider* m_sliderTipPointedness;
		wxStaticText* m_staticTextTipSharpness;
		wxSlider* m_sliderTipSharpness;
		wxStaticText* m_staticTextExtraLength;
		ExtendedTextCtrl* m_textCtrlExtraLength;
		wxStaticText* m_staticTextFootCompression;
		ExtendedTextCtrl* m_textCtrlFootCompression;
		wxPanel* m_panelPageSole;
		wxCheckBox* m_checkBoxSeparatedHeel;
		wxStaticText* m_staticText29;
		ExtendedTextCtrl* m_textCtrl29;
		wxStaticText* m_staticText30;
		ExtendedTextCtrl* m_textCtrl31;
		wxStaticText* m_staticText31;
		ExtendedTextCtrl* m_textCtrl35;
		wxStaticText* m_staticText32;
		ExtendedTextCtrl* m_textCtrl33;
		wxSlider* m_sliderSupportHeelRadius;
		wxSlider* m_sliderSupportHeelOffset;
		wxSlider* m_sliderSupportToeRadius;
		wxSlider* m_sliderSupportToeOffset;
		wxPanel* m_panelPagePattern;
		wxTreeListCtrl* m_treeListCtrl1;
		wxButton* m_button14;
		wxButton* m_button16;
		wxButton* m_button11;
		wxButton* m_button141;
		wxButton* m_button10;
		wxButton* m_button12;
		wxButton* m_button13;
		wxListBox* m_listBox1;
		wxPanel* m_panelPageFlattening;
		wxButton* m_button15;
		wxButton* m_button17;
		wxPanel* m_panelCanvas;
		Canvas3D * m_canvas3D;
		PanelPattern* m_panelPattern;
		wxPanel* m_panelCheck;
		PanelSupport* m_panelSupport;
		PanelWalkcycle* m_panelCycle;
		wxCheckBox* m_checkBoxLockAnkle;
		wxChoice* m_choiceDisplay;
		PanelPlotSimple* m_panelPlot;
		wxStatusBar* m_statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) = 0;
		virtual void OnQuickSetupMeasurements( wxCommandEvent& event ) = 0;
		virtual void OnSetSymmetry( wxCommandEvent& event ) = 0;
		virtual void OnCopyMeasurements( wxCommandEvent& event ) = 0;
		virtual void OnChangeModel( wxCommandEvent& event ) = 0;
		virtual void OnLoadFootSTL( wxCommandEvent& event ) = 0;
		virtual void OnEditBoneModel( wxCommandEvent& event ) = 0;
		virtual void OnLoadBoneModel( wxCommandEvent& event ) = 0;
		virtual void OnSaveBoneModel( wxCommandEvent& event ) = 0;
		virtual void OnConstructionSelection( wxCommandEvent& event ) = 0;
		virtual void OnLoadPattern( wxCommandEvent& event ) = 0;
		virtual void OnSavePattern( wxCommandEvent& event ) = 0;
		virtual void OnSaveLast( wxCommandEvent& event ) = 0;
		virtual void OnSaveInsole( wxCommandEvent& event ) = 0;
		virtual void OnSaveSole( wxCommandEvent& event ) = 0;
		virtual void OnSaveCutaway( wxCommandEvent& event ) = 0;
		virtual void OnPackZip( wxCommandEvent& event ) = 0;
		virtual void OnToggleStereo3D( wxCommandEvent& event ) = 0;
		virtual void OnViewChange( wxCommandEvent& event ) = 0;
		virtual void OnSetupBackgroundImages( wxCommandEvent& event ) = 0;
		virtual void OnDebugParser( wxCommandEvent& event ) = 0;
		virtual void OnPageChange( wxNotebookEvent& event ) = 0;
		virtual void OnMouseWheel( wxMouseEvent& event ) = 0;
		virtual void OnToggleButton( wxCommandEvent& event ) = 0;
		virtual void OnKillFocus( wxFocusEvent& event ) = 0;
		virtual void OnSetFocus( wxFocusEvent& event ) = 0;
		virtual void OnTextEnter( wxCommandEvent& event ) = 0;
		virtual void OnSize( wxSizeEvent& event ) = 0;
		virtual void OnFileChangedScanFile( wxFileDirPickerEvent& event ) = 0;
		virtual void OnFileChangedLastFile( wxFileDirPickerEvent& event ) = 0;
		virtual void OnChoice( wxCommandEvent& event ) = 0;
		virtual void OnCheckBox( wxCommandEvent& event ) = 0;
		virtual void OnScroll( wxScrollEvent& event ) = 0;
		virtual void OnToggleAnkleLock( wxCommandEvent& event ) = 0;
		virtual void OnChoiceDisplay( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameMain(wxDocument* doc, wxView* view, wxDocParentFrame* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Open Shoe Designer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 900,800 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIFrameMain();
		
		void m_splitterOnIdle( wxIdleEvent& )
		{
			m_splitter->SetSashPosition( 500 );
			m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( GUIFrameMain::m_splitterOnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameBoneModel
///////////////////////////////////////////////////////////////////////////////
class GUIFrameBoneModel : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_notebook;
		wxPanel* m_panelBone;
		wxGrid* m_gridBoneLength;
		wxPanel* m_panelBoneDiameter;
		wxGrid* m_gridBoneDiameter;
		wxPanel* m_panelSkinThickness;
		wxGrid* m_gridSkinThickness;
		wxMenuBar* m_menubar;
		wxMenu* m_menuFile;
		wxMenu* m_menuHelp;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCellChange( wxGridEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrameBoneModel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Bone Model Setup"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 672,458 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUIFrameBoneModel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialogQuickInitFoot
///////////////////////////////////////////////////////////////////////////////
class GUIDialogQuickInitFoot : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextShoeSize;
		ExtendedTextCtrl* m_textCtrlShoeSize;
		wxChoice* m_choiceUnit;
		wxRadioButton* m_radioBtnSmall;
		wxRadioButton* m_radioBtnMedium;
		wxRadioButton* m_radioBtnWide;
		wxButton* m_buttonInit;
		wxButton* m_buttonAbort;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTextEnter( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIDialogQuickInitFoot( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Initialize Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP ); 
		~GUIDialogQuickInitFoot();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameDebugParser
///////////////////////////////////////////////////////////////////////////////
class GUIFrameDebugParser : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText10;
		ExtendedTextCtrl* m_textCtrlExpression;
		wxStaticText* m_staticText11;
		ExtendedTextCtrl* m_textCtrlNumber;
		wxStaticText* m_staticText12;
		ExtendedTextCtrl* m_textCtrlError;
		wxStaticText* m_staticText14;
		ExtendedTextCtrl* m_textCtrlUnit;
		wxStaticText* m_staticText13;
		ExtendedTextCtrl* m_textCtrlSIBase;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) = 0;
		virtual void OnText( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameDebugParser( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Test Parser and Units"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~GUIFrameDebugParser();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameSetupUnits
///////////////////////////////////////////////////////////////////////////////
class GUIFrameSetupUnits : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText57;
		wxChoice* m_choiceUnitLength;
		wxStaticText* m_staticText110;
		wxChoice* m_choiceUnitSmallDistance;
		wxStaticText* m_staticText112;
		wxChoice* m_choiceUnitAngle;
		wxButton* m_buttonClose;
		wxStaticText* m_staticText64;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseX( wxCloseEvent& event ) = 0;
		virtual void OnChangeUnit( wxCommandEvent& event ) = 0;
		virtual void OnClose( wxCommandEvent& event ) = 0;
		
	
	public:
		
		GUIFrameSetupUnits( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup display units"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~GUIFrameSetupUnits();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialogAbout
///////////////////////////////////////////////////////////////////////////////
class GUIDialogAbout : public wxDialog 
{
	private:
	
	protected:
		ExtendedTextCtrl* m_textCtrl;
		wxButton* m_buttonClose;
	
	public:
		
		GUIDialogAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 288,200 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP ); 
		~GUIDialogAbout();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialogFormulaEditor
///////////////////////////////////////////////////////////////////////////////
class GUIDialogFormulaEditor : public wxDialog 
{
	private:
	
	protected:
		wxDataViewListCtrl* m_dataViewListCtrl;
		wxDataViewColumn* m_dataViewListColumnVariable;
		wxDataViewColumn* m_dataViewListColumnFormula;
		wxDataViewColumn* m_dataViewListColumnValue;
		wxStaticText* m_staticTextVariableName;
		ExtendedTextCtrl* m_textCtrlFormula;
		ExtendedTextCtrl* m_textCtrlUnit;
		ExtendedTextCtrl* m_textCtrlResult;
		wxButton* m_buttonClear;
		wxButton* m_buttonCopyResultFormula;
		wxButton* m_buttonCancel;
		wxButton* m_buttonOK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnItemActivated( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnClearFormula( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCopyResultToFormula( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIDialogFormulaEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Formula Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 650,450 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~GUIDialogFormulaEditor();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrameSetupBackgroundImages
///////////////////////////////////////////////////////////////////////////////
class GUIFrameSetupBackgroundImages : public wxFrame 
{
	private:
	
	protected:
		wxListCtrl* m_listCtrl;
		wxButton* m_buttonAdd;
		wxButton* m_buttonRemove;
		wxStaticText* m_staticTextFilename;
		wxFilePickerCtrl* m_filePicker;
		wxStaticText* m_staticTextDirection;
		wxCheckBox* m_checkBoxFront;
		wxCheckBox* m_checkBoxBack;
		wxCheckBox* m_checkBoxLeft;
		wxCheckBox* m_checkBoxRight;
		wxCheckBox* m_checkBoxTop;
		wxCheckBox* m_checkBoxBottom;
		wxStaticText* m_staticText46;
		ExtendedTextCtrl* m_textCtrlScale;
		wxSpinButton* m_spinBtnScale;
		wxStaticText* m_staticTextOffsHor;
		ExtendedTextCtrl* m_textCtrlOffsHor;
		wxSpinButton* m_spinBtnOffsHor;
		wxStaticText* m_staticTextOffsVert;
		ExtendedTextCtrl* m_textCtrlOffsVert;
		wxSpinButton* m_spinBtnOffsVert;
		wxStaticText* m_staticTextRotation;
		wxSlider* m_sliderRotation;
		wxButton* m_buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAddUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpin( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnRightDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnScroll( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrameSetupBackgroundImages( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Setup background images"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 582,561 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~GUIFrameSetupBackgroundImages();
	
};

#endif //__GUI_H__
