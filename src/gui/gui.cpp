///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../StdInclude.h"

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

GUIFrameMain::GUIFrameMain(wxDocument* doc, wxView* view, wxDocParentFrame* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDocChildFrame( doc, view, parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	m_menubar->Append( m_menuFile, _("&File") ); 
	
	m_menuEdit = new wxMenu();
	wxMenuItem* m_menuItemUndo;
	m_menuItemUndo = new wxMenuItem( m_menuEdit, ID_UNDO, wxString( _("&Undo") ) + wxT('\t') + wxT("Ctrl+Z"), _("Undo last command"), wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemUndo );
	
	wxMenuItem* m_menuItemRedo;
	m_menuItemRedo = new wxMenuItem( m_menuEdit, ID_REDO, wxString( _("&Redo") ) + wxT('\t') + wxT("Ctrl+Y"), _("Redo last undone command"), wxITEM_NORMAL );
	m_menuEdit->Append( m_menuItemRedo );
	
	m_menubar->Append( m_menuEdit, _("&Edit") ); 
	
	m_menuFoot = new wxMenu();
	wxMenuItem* m_menuItemInitalizeFootModel;
	m_menuItemInitalizeFootModel = new wxMenuItem( m_menuFoot, ID_INITIALIZEFOOTMODEL, wxString( _("Quick &Initialization") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemInitalizeFootModel );
	
	m_menuFoot->AppendSeparator();
	
	m_menuSymmetry = new wxMenu();
	wxMenuItem* m_menuSymmetryItem = new wxMenuItem( m_menuFoot, wxID_ANY, _("&Symmetry"), wxEmptyString, wxITEM_NORMAL, m_menuSymmetry );
	wxMenuItem* m_menuItemFullSymmetry;
	m_menuItemFullSymmetry = new wxMenuItem( m_menuSymmetry, ID_FULLSYMMETRY, wxString( _("Model and Measurements symmetric") ) , wxEmptyString, wxITEM_RADIO );
	m_menuSymmetry->Append( m_menuItemFullSymmetry );
	m_menuItemFullSymmetry->Check( true );
	
	wxMenuItem* m_menuItemSymmetricModel;
	m_menuItemSymmetricModel = new wxMenuItem( m_menuSymmetry, ID_SYMMETRICMODEL, wxString( _("Symmetric Model and Individual Measurements") ) , wxEmptyString, wxITEM_RADIO );
	m_menuSymmetry->Append( m_menuItemSymmetricModel );
	
	wxMenuItem* m_menuItemIndividualModel;
	m_menuItemIndividualModel = new wxMenuItem( m_menuSymmetry, ID_INDIVIDUALMODEL, wxString( _("Individual Model and Measurements") ) , wxEmptyString, wxITEM_RADIO );
	m_menuSymmetry->Append( m_menuItemIndividualModel );
	
	m_menuSymmetry->AppendSeparator();
	
	wxMenuItem* m_menuItemFootCopyLeftToRight;
	m_menuItemFootCopyLeftToRight = new wxMenuItem( m_menuSymmetry, ID_COPYLEFTTORIGHT, wxString( _("Copy Measurements from Left to Right") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSymmetry->Append( m_menuItemFootCopyLeftToRight );
	
	wxMenuItem* m_menuItemFootCopyRightToLeft;
	m_menuItemFootCopyRightToLeft = new wxMenuItem( m_menuSymmetry, ID_COPYRIGHTTOLEFT, wxString( _("Copy Measurements from Right to Left") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSymmetry->Append( m_menuItemFootCopyRightToLeft );
	
	m_menuFoot->Append( m_menuSymmetryItem );
	
	m_menuFoot->AppendSeparator();
	
	wxMenuItem* m_menuItemLoadFootModel;
	m_menuItemLoadFootModel = new wxMenuItem( m_menuFoot, ID_LOADFOOTMODEL, wxString( _("Load Footmodel") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemLoadFootModel );
	
	wxMenuItem* m_menuItemSaveFootModel;
	m_menuItemSaveFootModel = new wxMenuItem( m_menuFoot, ID_SAVEFOOTMODEL, wxString( _("Save foot model") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemSaveFootModel );
	
	m_menuFoot->AppendSeparator();
	
	m_menuFootModelType = new wxMenu();
	wxMenuItem* m_menuFootModelTypeItem = new wxMenuItem( m_menuFoot, wxID_ANY, _("Type of foot model"), wxEmptyString, wxITEM_NORMAL, m_menuFootModelType );
	wxMenuItem* m_menuItemFootModelScan;
	m_menuItemFootModelScan = new wxMenuItem( m_menuFootModelType, wxID_ANY, wxString( _("Purely scan-based") ) , wxEmptyString, wxITEM_RADIO );
	m_menuFootModelType->Append( m_menuItemFootModelScan );
	
	wxMenuItem* m_menuItemFootModelBone;
	m_menuItemFootModelBone = new wxMenuItem( m_menuFootModelType, wxID_ANY, wxString( _("Bone-based Footmodel") ) , wxEmptyString, wxITEM_RADIO );
	m_menuFootModelType->Append( m_menuItemFootModelBone );
	m_menuItemFootModelBone->Check( true );
	
	m_menuFoot->Append( m_menuFootModelTypeItem );
	
	m_menuFoot->AppendSeparator();
	
	wxMenuItem* m_menuItemFootModelLoadSTL;
	m_menuItemFootModelLoadSTL = new wxMenuItem( m_menuFoot, wxID_ANY, wxString( _("Load STL data") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemFootModelLoadSTL );
	m_menuItemFootModelLoadSTL->Enable( false );
	
	wxMenuItem* m_menuItemSetupFoot;
	m_menuItemSetupFoot = new wxMenuItem( m_menuFoot, ID_SETUPFOOT, wxString( _("Setup &Footmodel") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemSetupFoot );
	m_menuItemSetupFoot->Enable( false );
	
	m_menubar->Append( m_menuFoot, _("F&oot") ); 
	
	m_menuLast = new wxMenu();
	wxMenuItem* m_menuItemLastLoadSTL;
	m_menuItemLastLoadSTL = new wxMenuItem( m_menuLast, wxID_ANY, wxString( _("Load Last from STL") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuLast->Append( m_menuItemLastLoadSTL );
	m_menuItemLastLoadSTL->Enable( false );
	
	m_menubar->Append( m_menuLast, _("&Last") ); 
	
	m_menuShoe = new wxMenu();
	wxMenuItem* m_menuItemSetupShoe;
	m_menuItemSetupShoe = new wxMenuItem( m_menuShoe, ID_SETUPSHOE, wxString( _("Setup &Shoe") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuShoe->Append( m_menuItemSetupShoe );
	m_menuItemSetupShoe->Enable( false );
	
	m_menuConstruction = new wxMenu();
	wxMenuItem* m_menuConstructionItem = new wxMenuItem( m_menuShoe, wxID_ANY, _("&Construction method"), wxEmptyString, wxITEM_NORMAL, m_menuConstruction );
	wxMenuItem* m_menuItemTestGenerator;
	m_menuItemTestGenerator = new wxMenuItem( m_menuConstruction, ID_CONSTRUCTIONEXPERIMENTAL, wxString( _("&Experimental generator") ) , _("Generator for alogithm development"), wxITEM_RADIO );
	m_menuConstruction->Append( m_menuItemTestGenerator );
	
	wxMenuItem* m_menuItemConstructionClassic;
	m_menuItemConstructionClassic = new wxMenuItem( m_menuConstruction, ID_CONSTRUCTIONWELDED, wxString( _("Classic, &welded construction") ) , wxEmptyString, wxITEM_RADIO );
	m_menuConstruction->Append( m_menuItemConstructionClassic );
	
	wxMenuItem* m_menuItemConstructionCemented;
	m_menuItemConstructionCemented = new wxMenuItem( m_menuConstruction, ID_CONSTRUCTIONCEMENTED, wxString( _("&Cemented construction") ) , wxEmptyString, wxITEM_RADIO );
	m_menuConstruction->Append( m_menuItemConstructionCemented );
	
	wxMenuItem* m_menuItemConstructionMolded;
	m_menuItemConstructionMolded = new wxMenuItem( m_menuConstruction, ID_CONSTRUCTIONMOLDED, wxString( _("Injection-&molded sole") ) , wxEmptyString, wxITEM_RADIO );
	m_menuConstruction->Append( m_menuItemConstructionMolded );
	
	wxMenuItem* m_menuItemConstructionDutch;
	m_menuItemConstructionDutch = new wxMenuItem( m_menuConstruction, ID_CONSTRUCTIONDUTCH, wxString( _("&Dutch Clog") ) , wxEmptyString, wxITEM_RADIO );
	m_menuConstruction->Append( m_menuItemConstructionDutch );
	
	m_menuShoe->Append( m_menuConstructionItem );
	
	wxMenuItem* m_menuItemEditWalkCycle;
	m_menuItemEditWalkCycle = new wxMenuItem( m_menuShoe, ID_EDITWALKCYCLE, wxString( _("Define &Walkcycle Support") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuShoe->Append( m_menuItemEditWalkCycle );
	m_menuItemEditWalkCycle->Enable( false );
	
	m_menubar->Append( m_menuShoe, _("&Shoe") ); 
	
	m_menuPattern = new wxMenu();
	wxMenuItem* m_menuItemLoadPattern;
	m_menuItemLoadPattern = new wxMenuItem( m_menuPattern, ID_LOADPATTERN, wxString( _("&Load Pattern") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuPattern->Append( m_menuItemLoadPattern );
	m_menuItemLoadPattern->Enable( false );
	
	wxMenuItem* m_menuItemSavePattern;
	m_menuItemSavePattern = new wxMenuItem( m_menuPattern, ID_SAVEPATTERN, wxString( _("&Save Pattern") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuPattern->Append( m_menuItemSavePattern );
	m_menuItemSavePattern->Enable( false );
	
	wxMenuItem* m_menuItemShowFlattening;
	m_menuItemShowFlattening = new wxMenuItem( m_menuPattern, wxID_ANY, wxString( _("Show Flattening") ) , wxEmptyString, wxITEM_CHECK );
	m_menuPattern->Append( m_menuItemShowFlattening );
	m_menuItemShowFlattening->Enable( false );
	
	m_menubar->Append( m_menuPattern, _("&Pattern") ); 
	
	m_menuFabric = new wxMenu();
	wxMenuItem* m_menuItemEditFabricsLibrary;
	m_menuItemEditFabricsLibrary = new wxMenuItem( m_menuFabric, wxID_ANY, wxString( _("&Edit Fabrics Library") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFabric->Append( m_menuItemEditFabricsLibrary );
	m_menuItemEditFabricsLibrary->Enable( false );
	
	m_menuFabric->AppendSeparator();
	
	wxMenuItem* m_menuItemLoadFabricsLibrary;
	m_menuItemLoadFabricsLibrary = new wxMenuItem( m_menuFabric, wxID_ANY, wxString( _("&Load Fabrics Library") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFabric->Append( m_menuItemLoadFabricsLibrary );
	m_menuItemLoadFabricsLibrary->Enable( false );
	
	m_menubar->Append( m_menuFabric, _("F&abric") ); 
	
	m_menuGeometry = new wxMenu();
	wxMenuItem* m_menuItemSaveLast;
	m_menuItemSaveLast = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Save &Last") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveLast );
	
	wxMenuItem* m_menuItemSaveInsole;
	m_menuItemSaveInsole = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Save &Insole") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveInsole );
	m_menuItemSaveInsole->Enable( false );
	
	wxMenuItem* m_menuItemSaveSole;
	m_menuItemSaveSole = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Save &Sole Prototype") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveSole );
	m_menuItemSaveSole->Enable( false );
	
	wxMenuItem* m_menuItemCutaway;
	m_menuItemCutaway = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Save &Cutaway Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemCutaway );
	m_menuItemCutaway->Enable( false );
	
	m_menuGeometry->AppendSeparator();
	
	wxMenuItem* m_menuItemPackZip;
	m_menuItemPackZip = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Pack a Zip with &Everything") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemPackZip );
	m_menuItemPackZip->Enable( false );
	
	m_menubar->Append( m_menuGeometry, _("&Geometry") ); 
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemStereo3D;
	m_menuItemStereo3D = new wxMenuItem( m_menuView, ID_STEREO3D, wxString( _("Toggle Stereo &3D") ) + wxT('\t') + wxT("CTRL+3"), _("Toggle 3D view on/off."), wxITEM_CHECK );
	m_menuView->Append( m_menuItemStereo3D );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemShowLeft;
	m_menuItemShowLeft = new wxMenuItem( m_menuView, ID_SHOWLEFT, wxString( _("Show &Left") ) + wxT('\t') + wxT("Ctrl+E"), wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowLeft );
	
	wxMenuItem* m_menuItemShowRight;
	m_menuItemShowRight = new wxMenuItem( m_menuView, ID_SHOWRIGHT, wxString( _("Show &Right") ) + wxT('\t') + wxT("Ctrl+R"), wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowRight );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemShowBones;
	m_menuItemShowBones = new wxMenuItem( m_menuView, ID_SHOWBONES, wxString( _("Show &Bones") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowBones );
	
	wxMenuItem* m_menuItemShowLast;
	m_menuItemShowLast = new wxMenuItem( m_menuView, ID_SHOWLAST, wxString( _("Show &Last") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowLast );
	
	wxMenuItem* m_menuItemShowInsole;
	m_menuItemShowInsole = new wxMenuItem( m_menuView, ID_SHOWINSOLE, wxString( _("Show &Insole") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowInsole );
	
	wxMenuItem* m_menuIItemShowSole;
	m_menuIItemShowSole = new wxMenuItem( m_menuView, ID_SHOWSOLE, wxString( _("Show &Sole") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuIItemShowSole );
	
	wxMenuItem* m_menuItemShowUpper;
	m_menuItemShowUpper = new wxMenuItem( m_menuView, ID_SHOWUPPER, wxString( _("Show &Upper") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowUpper );
	
	wxMenuItem* m_menuItemShowCutaway;
	m_menuItemShowCutaway = new wxMenuItem( m_menuView, ID_SHOWCUTAWAY, wxString( _("Show &Cutaway Block") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowCutaway );
	
	wxMenuItem* m_menuItemShowFloor;
	m_menuItemShowFloor = new wxMenuItem( m_menuView, ID_SHOWFLOOR, wxString( _("Show &Floor") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowFloor );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemShowBackground;
	m_menuItemShowBackground = new wxMenuItem( m_menuView, ID_SHOWBACKGROUND, wxString( _("Show Back&ground") ) + wxT('\t') + wxT("CTRL+B"), wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowBackground );
	
	m_menubar->Append( m_menuView, _("&View") ); 
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItemSetupStereo3D;
	m_menuItemSetupStereo3D = new wxMenuItem( m_menuSettings, ID_SETUPSTEREO3D, wxString( _("Setup &Stereo3D") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItemSetupStereo3D );
	
	wxMenuItem* m_menuItemSetupUnits;
	m_menuItemSetupUnits = new wxMenuItem( m_menuSettings, ID_SETUPUNITS, wxString( _("Setup &Units") ) + wxT('\t') + wxT("CTRL+U"), wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItemSetupUnits );
	
	wxMenuItem* m_menuItemSelectLanguage;
	m_menuItemSelectLanguage = new wxMenuItem( m_menuSettings, wxID_ANY, wxString( _("Select &Language") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItemSelectLanguage );
	
	m_menubar->Append( m_menuSettings, _("S&ettings") ); 
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItemdebugParser;
	m_menuItemdebugParser = new wxMenuItem( m_menuHelp, wxID_ANY, wxString( _("Debug Mathparser") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItemdebugParser );
	
	m_menubar->Append( m_menuHelp, _("&Help") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( GUIFrameMain::m_splitterOnIdle ), NULL, this );
	m_splitter->SetMinimumPaneSize( 200 );
	
	m_panelConfig = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerConfig;
	bSizerConfig = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( m_panelConfig, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelPageFoot = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerFoot;
	bSizerFoot = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer281;
	bSizer281 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	m_buttonSetByShoeSize = new wxButton( m_panelPageFoot, wxID_ANY, _("Quick Setup"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_buttonSetByShoeSize, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 5, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText21 = new wxStaticText( m_panelPageFoot, wxID_ANY, _("Foot length (L):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer2->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlFootLength = new wxTextCtrl( m_panelPageFoot, ID_TEXTFOOTLENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlFootLength->SetToolTip( _("Length of the foot (not length of the last).") );
	
	fgSizer2->Add( m_textCtrlFootLength, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText23 = new wxStaticText( m_panelPageFoot, wxID_ANY, _("Ball width (W):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFootWidth = new wxTextCtrl( m_panelPageFoot, ID_TEXTFOOTWIDTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer2->Add( m_textCtrlFootWidth, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText25 = new wxStaticText( m_panelPageFoot, wxID_ANY, _("Heel width (H):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer2->Add( m_staticText25, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlHeelWidth = new wxTextCtrl( m_panelPageFoot, ID_TEXTHEELWIDTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlHeelWidth->SetToolTip( _("Widest part of the heel directly above the ground.") );
	
	fgSizer2->Add( m_textCtrlHeelWidth, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText27 = new wxStaticText( m_panelPageFoot, wxID_ANY, _("Ankle width (A):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer2->Add( m_staticText27, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlAnkleWidth = new wxTextCtrl( m_panelPageFoot, ID_TEXTANKLEWIDTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAnkleWidth->SetToolTip( _("Width of the ankle.") );
	
	fgSizer2->Add( m_textCtrlAnkleWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText22 = new wxStaticText( m_panelPageFoot, wxID_ANY, _("Leg length difference:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlLegLengthDifference = new wxTextCtrl( m_panelPageFoot, ID_TEXTLEGLENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlLegLengthDifference->Enable( false );
	m_textCtrlLegLengthDifference->SetToolTip( _("Distance the right leg is longer than the left (positive number). If the right leg is shorter than the left leg the number has to be negative.") );
	
	fgSizer2->Add( m_textCtrlLegLengthDifference, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer16->Add( fgSizer2, 0, 0, 5 );
	
	
	bSizer281->Add( bSizer16, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerShoeSizes;
	sbSizerShoeSizes = new wxStaticBoxSizer( new wxStaticBox( m_panelPageFoot, wxID_ANY, _("Shoesizes") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 6, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextShoeSizeEU = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("EU:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeEU->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeEU, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShoeSizeEU = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeEU->SetToolTip( _("Last length in Paris point") );
	
	fgSizer3->Add( m_textCtrlShoeSizeEU, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeUS = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("US:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeUS->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeUS, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeUS = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeUS->SetToolTip( _("Brannock-Scale") );
	
	fgSizer3->Add( m_textCtrlShoeSizeUS, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeUK = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("UK:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeUK->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeUK, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeUK = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeUK->SetToolTip( _("Last length in Barleycorns") );
	
	fgSizer3->Add( m_textCtrlShoeSizeUK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeCN = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("CN:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeCN->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeCN, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShoeSizeCN = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeCN->SetToolTip( _("Foot length in cm") );
	
	fgSizer3->Add( m_textCtrlShoeSizeCN, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeJP = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("JP:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeJP->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeJP, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeJP = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeJP->SetToolTip( _("Foot length in mm") );
	
	fgSizer3->Add( m_textCtrlShoeSizeJP, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextShoeSizeAU = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("AU:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeAU->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeAU, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeAU = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeAU->SetToolTip( _("Last length in Barleycorns") );
	
	fgSizer3->Add( m_textCtrlShoeSizeAU, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	sbSizerShoeSizes->Add( fgSizer3, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer281->Add( sbSizerShoeSizes, 0, 0, 5 );
	
	
	bSizerFoot->Add( bSizer281, 1, wxEXPAND, 5 );
	
	m_propertyGrid1 = new wxPropertyGrid(m_panelPageFoot, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizerFoot->Add( m_propertyGrid1, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( m_panelPageFoot, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_MULTILINE );
	m_panelBone = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	m_gridBoneLength = new wxGrid( m_panelBone, ID_GRIDLENGTH, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridBoneLength->CreateGrid( 0, 2 );
	m_gridBoneLength->EnableEditing( true );
	m_gridBoneLength->EnableGridLines( true );
	m_gridBoneLength->EnableDragGridSize( false );
	m_gridBoneLength->SetMargins( 0, 0 );
	
	// Columns
	m_gridBoneLength->SetColSize( 0, 130 );
	m_gridBoneLength->SetColSize( 1, 112 );
	m_gridBoneLength->EnableDragColMove( false );
	m_gridBoneLength->EnableDragColSize( true );
	m_gridBoneLength->SetColLabelSize( 30 );
	m_gridBoneLength->SetColLabelValue( 0, _("Length (Formula)") );
	m_gridBoneLength->SetColLabelValue( 1, _("Length (Value)") );
	m_gridBoneLength->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridBoneLength->AutoSizeRows();
	m_gridBoneLength->EnableDragRowSize( true );
	m_gridBoneLength->SetRowLabelSize( 100 );
	m_gridBoneLength->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridBoneLength->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer21->Add( m_gridBoneLength, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelBone->SetSizer( bSizer21 );
	m_panelBone->Layout();
	bSizer21->Fit( m_panelBone );
	m_notebook1->AddPage( m_panelBone, _("Bone Length"), true );
	m_panelBoneDiameter = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	m_gridBoneDiameter = new wxGrid( m_panelBoneDiameter, ID_GRIDDIAMETER, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridBoneDiameter->CreateGrid( 0, 4 );
	m_gridBoneDiameter->EnableEditing( true );
	m_gridBoneDiameter->EnableGridLines( true );
	m_gridBoneDiameter->EnableDragGridSize( false );
	m_gridBoneDiameter->SetMargins( 0, 0 );
	
	// Columns
	m_gridBoneDiameter->SetColSize( 0, 100 );
	m_gridBoneDiameter->SetColSize( 1, 100 );
	m_gridBoneDiameter->SetColSize( 2, 100 );
	m_gridBoneDiameter->SetColSize( 3, 100 );
	m_gridBoneDiameter->EnableDragColMove( false );
	m_gridBoneDiameter->EnableDragColSize( true );
	m_gridBoneDiameter->SetColLabelSize( 30 );
	m_gridBoneDiameter->SetColLabelValue( 0, _("r1 (Formula)") );
	m_gridBoneDiameter->SetColLabelValue( 1, _("r1 (Value)") );
	m_gridBoneDiameter->SetColLabelValue( 2, _("r2 (Formula)") );
	m_gridBoneDiameter->SetColLabelValue( 3, _("r2 (Value)") );
	m_gridBoneDiameter->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridBoneDiameter->EnableDragRowSize( true );
	m_gridBoneDiameter->SetRowLabelSize( 100 );
	m_gridBoneDiameter->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridBoneDiameter->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer28->Add( m_gridBoneDiameter, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelBoneDiameter->SetSizer( bSizer28 );
	m_panelBoneDiameter->Layout();
	bSizer28->Fit( m_panelBoneDiameter );
	m_notebook1->AddPage( m_panelBoneDiameter, _("Bone Diameter"), false );
	m_panelSkin = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	m_gridSkin = new wxGrid( m_panelSkin, ID_GRIDSKIN, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridSkin->CreateGrid( 0, 4 );
	m_gridSkin->EnableEditing( true );
	m_gridSkin->EnableGridLines( true );
	m_gridSkin->EnableDragGridSize( false );
	m_gridSkin->SetMargins( 0, 0 );
	
	// Columns
	m_gridSkin->SetColSize( 0, 100 );
	m_gridSkin->SetColSize( 1, 100 );
	m_gridSkin->SetColSize( 2, 100 );
	m_gridSkin->SetColSize( 3, 100 );
	m_gridSkin->EnableDragColMove( false );
	m_gridSkin->EnableDragColSize( true );
	m_gridSkin->SetColLabelSize( 30 );
	m_gridSkin->SetColLabelValue( 0, _("s1 (Formula)") );
	m_gridSkin->SetColLabelValue( 1, _("s1 (Value)") );
	m_gridSkin->SetColLabelValue( 2, _("s2 (Formula)") );
	m_gridSkin->SetColLabelValue( 3, _("s2 (Value)") );
	m_gridSkin->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridSkin->EnableDragRowSize( true );
	m_gridSkin->SetRowLabelSize( 100 );
	m_gridSkin->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridSkin->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer26->Add( m_gridSkin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	m_panelSkin->SetSizer( bSizer26 );
	m_panelSkin->Layout();
	bSizer26->Fit( m_panelSkin );
	m_notebook1->AddPage( m_panelSkin, _("Skin Thickness"), false );
	m_panelLeg = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );
	
	m_gridLeg = new wxGrid( m_panelLeg, ID_GRIDLEG, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridLeg->CreateGrid( 0, 4 );
	m_gridLeg->EnableEditing( true );
	m_gridLeg->EnableGridLines( true );
	m_gridLeg->EnableDragGridSize( false );
	m_gridLeg->SetMargins( 0, 0 );
	
	// Columns
	m_gridLeg->SetColSize( 0, 106 );
	m_gridLeg->SetColSize( 1, 69 );
	m_gridLeg->SetColSize( 2, 92 );
	m_gridLeg->SetColSize( 3, 124 );
	m_gridLeg->EnableDragColMove( false );
	m_gridLeg->EnableDragColSize( true );
	m_gridLeg->SetColLabelSize( 30 );
	m_gridLeg->SetColLabelValue( 0, _("Height (Formula)") );
	m_gridLeg->SetColLabelValue( 1, _("Height (Value)") );
	m_gridLeg->SetColLabelValue( 2, _("Circumfence (Formula)") );
	m_gridLeg->SetColLabelValue( 3, _("Circumfence (Value)") );
	m_gridLeg->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridLeg->EnableDragRowSize( true );
	m_gridLeg->SetRowLabelSize( 60 );
	m_gridLeg->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridLeg->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer27->Add( m_gridLeg, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText38 = new wxStaticText( m_panelLeg, wxID_ANY, _("(This table is only needed for boot designs.)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	bSizer27->Add( m_staticText38, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panelLeg->SetSizer( bSizer27 );
	m_panelLeg->Layout();
	bSizer27->Fit( m_panelLeg );
	m_notebook1->AddPage( m_panelLeg, _("Leg"), false );
	
	bSizer11->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizerFoot->Add( bSizer11, 1, wxEXPAND, 5 );
	
	
	m_panelPageFoot->SetSizer( bSizerFoot );
	m_panelPageFoot->Layout();
	bSizerFoot->Fit( m_panelPageFoot );
	m_notebook->AddPage( m_panelPageFoot, _("Foot"), true );
	m_panelPageLast = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer271;
	bSizer271 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 4, 3, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextHeelHeight = new wxStaticText( m_panelPageLast, wxID_ANY, _("Heel Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHeelHeight->Wrap( -1 );
	fgSizer1->Add( m_staticTextHeelHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlHeelHeight = new wxTextCtrl( m_panelPageLast, ID_TEXTHEELHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1->Add( m_textCtrlHeelHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_textCtrlResultHeelHeight = new wxTextCtrl( m_panelPageLast, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	fgSizer1->Add( m_textCtrlResultHeelHeight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBallHeight = new wxStaticText( m_panelPageLast, wxID_ANY, _("Ball Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBallHeight->Wrap( -1 );
	fgSizer1->Add( m_staticTextBallHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlBallHeight = new wxTextCtrl( m_panelPageLast, ID_TEXTBALLHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1->Add( m_textCtrlBallHeight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_textCtrlResultBallHeight = new wxTextCtrl( m_panelPageLast, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	fgSizer1->Add( m_textCtrlResultBallHeight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextToePitch = new wxStaticText( m_panelPageLast, wxID_ANY, _("Toe Pitch:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToePitch->Wrap( -1 );
	fgSizer1->Add( m_staticTextToePitch, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlToeAngle = new wxTextCtrl( m_panelPageLast, ID_TEXTTOEPITCH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1->Add( m_textCtrlToeAngle, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_textCtrlResultToeAngle = new wxTextCtrl( m_panelPageLast, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	fgSizer1->Add( m_textCtrlResultToeAngle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextMixing = new wxStaticText( m_panelPageLast, wxID_ANY, _("Angle Mixing:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextMixing->Wrap( -1 );
	fgSizer1->Add( m_staticTextMixing, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_sliderMixing = new wxSlider( m_panelPageLast, wxID_ANY, 10, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	m_sliderMixing->SetToolTip( _("Mixing determines how much of the needed bending of the foot is done by the heel and how much is spread on the forefoot. 0% is all heel, 100% is all forefoot. 100% is impractical unless some serious misalignment of the foot is to be compensated.") );
	
	fgSizer1->Add( m_sliderMixing, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_textCtrlResultMixing = new wxTextCtrl( m_panelPageLast, ID_TEXTMIXINGANGLE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	fgSizer1->Add( m_textCtrlResultMixing, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( fgSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	bSizer271->Add( bSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerPresets;
	sbSizerPresets = new wxStaticBoxSizer( new wxStaticBox( m_panelPageLast, wxID_ANY, _("Presets") ), wxVERTICAL );
	
	wxGridSizer* gSizerPreset;
	gSizerPreset = new wxGridSizer( 3, 3, 0, 0 );
	
	m_buttonFlats = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETFLATS, _("Flats"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonFlats, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonHHLow = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETHHLOW, _("High Heel (low)"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonHHLow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPlatform = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETPLATFORM, _("Platform Heel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonPlatform, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonClassic = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETCLASSIC, _("Classic"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonClassic, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_buttonHHMid = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETHHMID, _("High Heel (mid)"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonHHMid, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPony = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETPONY, _("Pony"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonPony, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPlateau = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETPLATEAU, _("Plateau"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonPlateau, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonHHHigh = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETHHHIGH, _("High Heel (high)"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonHHHigh, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_buttonBallet = new wxButton( sbSizerPresets->GetStaticBox(), ID_PRESETBALLET, _("Ballet"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerPreset->Add( m_buttonBallet, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	sbSizerPresets->Add( gSizerPreset, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer271->Add( sbSizerPresets, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer24->Add( bSizer271, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelPageLast->SetSizer( bSizer24 );
	m_panelPageLast->Layout();
	bSizer24->Fit( m_panelPageLast );
	m_notebook->AddPage( m_panelPageLast, _("Last"), false );
	m_panelPagePattern = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_treeListCtrl1 = new wxTreeListCtrl( m_panelPagePattern, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );
	
	bSizer22->Add( m_treeListCtrl1, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer23->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button14 = new wxButton( m_panelPagePattern, wxID_ANY, _("Add Line"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_button14, 0, wxALL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_button16 = new wxButton( m_panelPagePattern, wxID_ANY, _("Add Patch"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_button16, 0, wxALL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panelPagePattern, wxID_ANY, _("Fabric") ), wxVERTICAL );
	
	m_listBox1 = new wxListBox( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_listBox1->Append( _("Leather - black") );
	m_listBox1->Append( _("Leather - red") );
	m_listBox1->Append( _("Leather - white") );
	m_listBox1->Append( _("Patent - black") );
	m_listBox1->Append( _("Patent - white") );
	m_listBox1->Append( _("Cotton - black") );
	m_listBox1->Append( _("Cotton - yellow") );
	m_listBox1->Append( _("Cotton - red") );
	sbSizer5->Add( m_listBox1, 2, wxALL|wxEXPAND, 5 );
	
	
	bSizer23->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	
	bSizer22->Add( bSizer23, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	m_panelPagePattern->SetSizer( bSizer22 );
	m_panelPagePattern->Layout();
	bSizer22->Fit( m_panelPagePattern );
	m_notebook->AddPage( m_panelPagePattern, _("Pattern"), false );
	m_panelPageFlattening = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer241;
	bSizer241 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer241->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	m_button15 = new wxButton( m_panelPageFlattening, wxID_ANY, _("Export Flattening"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_button15, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_button17 = new wxButton( m_panelPageFlattening, wxID_ANY, _("Test Stitch"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_button17, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	bSizer241->Add( bSizer25, 0, 0, 5 );
	
	
	m_panelPageFlattening->SetSizer( bSizer241 );
	m_panelPageFlattening->Layout();
	bSizer241->Fit( m_panelPageFlattening );
	m_notebook->AddPage( m_panelPageFlattening, _("Flattening"), false );
	
	bSizerConfig->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panelConfig->SetSizer( bSizerConfig );
	m_panelConfig->Layout();
	bSizerConfig->Fit( m_panelConfig );
	m_panelCanvas = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerCanvas;
	bSizerCanvas = new wxBoxSizer( wxVERTICAL );
	
	m_canvas3D = new Canvas3D(m_panelCanvas);
	bSizerCanvas->Add( m_canvas3D, 1, wxALL|wxEXPAND, 5 );
	
	m_panelPattern = new PanelPattern(m_panelCanvas);
	m_panelPattern->Hide();
	
	bSizerCanvas->Add( m_panelPattern, 1, wxALL|wxEXPAND, 5 );
	
	m_panelCheck = new wxPanel( m_panelCanvas, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panelCheck->Hide();
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panelSupport = new PanelSupport(m_panelCheck);
	bSizer3->Add( m_panelSupport, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panelCheck, wxID_ANY, _("Walkcycle") ), wxVERTICAL );
	
	m_panelCycle = new PanelWalkcycle(m_panelCheck);
	sbSizer1->Add( m_panelCycle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_checkBoxLockAnkle = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Lock Ankle"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( m_checkBoxLockAnkle, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panelCheck, wxID_ANY, _("Forces, Moments") ), wxVERTICAL );
	
	wxString m_choiceDisplayChoices[] = { _("Kneeline"), _("Force"), _("Moment"), _("Crossforce") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 0 );
	sbSizer2->Add( m_choiceDisplay, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panelPlot = new PanelPlotSimple(m_panelCheck);
	sbSizer2->Add( m_panelPlot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer1, 1, wxEXPAND, 5 );
	
	
	m_panelCheck->SetSizer( bSizer3 );
	m_panelCheck->Layout();
	bSizer3->Fit( m_panelCheck );
	bSizerCanvas->Add( m_panelCheck, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panelCanvas->SetSizer( bSizerCanvas );
	m_panelCanvas->Layout();
	bSizerCanvas->Fit( m_panelCanvas );
	m_splitter->SplitVertically( m_panelConfig, m_panelCanvas, 400 );
	bSizer->Add( m_splitter, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameMain::OnClose ) );
	this->Connect( m_menuItemUndo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnUndo ) );
	this->Connect( m_menuItemRedo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnRedo ) );
	this->Connect( m_menuItemInitalizeFootModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetByShoeSize ) );
	this->Connect( m_menuItemFullSymmetry->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Connect( m_menuItemSymmetricModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Connect( m_menuItemIndividualModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Connect( m_menuItemFootCopyLeftToRight->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnCopyMeasurements ) );
	this->Connect( m_menuItemFootCopyRightToLeft->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnCopyMeasurements ) );
	this->Connect( m_menuItemLoadFootModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadFootModel ) );
	this->Connect( m_menuItemSaveFootModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveFootModel ) );
	this->Connect( m_menuItemFootModelLoadSTL->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadFootSTL ) );
	this->Connect( m_menuItemSetupFoot->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupFoot ) );
	this->Connect( m_menuItemSetupShoe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupShoe ) );
	this->Connect( m_menuItemTestGenerator->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionClassic->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionCemented->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionMolded->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionDutch->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemEditWalkCycle->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditWalkCycle ) );
	this->Connect( m_menuItemLoadPattern->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadPattern ) );
	this->Connect( m_menuItemSavePattern->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSavePattern ) );
	this->Connect( m_menuItemSaveLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveLast ) );
	this->Connect( m_menuItemSaveInsole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveInsole ) );
	this->Connect( m_menuItemSaveSole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveSole ) );
	this->Connect( m_menuItemCutaway->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveCutaway ) );
	this->Connect( m_menuItemPackZip->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnPackZip ) );
	this->Connect( m_menuItemStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Connect( m_menuItemShowLeft->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowRight->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowBones->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowInsole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuIItemShowSole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowUpper->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowCutaway->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowFloor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowBackground->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemSetupStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Connect( m_menuItemSetupUnits->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Connect( m_menuItemSelectLanguage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSelectLanguage ) );
	this->Connect( m_menuItemdebugParser->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnDebugParser ) );
	m_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( GUIFrameMain::OnPageChange ), NULL, this );
	m_buttonSetByShoeSize->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnSetByShoeSize ), NULL, this );
	m_textCtrlFootLength->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlFootWidth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlHeelWidth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlAnkleWidth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlLegLengthDifference->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_gridBoneLength->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameMain::OnCellChange ), NULL, this );
	m_gridBoneDiameter->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameMain::OnCellChange ), NULL, this );
	m_gridSkin->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameMain::OnCellChange ), NULL, this );
	m_gridLeg->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameMain::OnCellChange ), NULL, this );
	m_textCtrlHeelHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlBallHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlToeAngle->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScrollChange ), NULL, this );
	m_textCtrlResultMixing->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_buttonFlats->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonHHLow->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonPlatform->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonClassic->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonHHMid->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonPony->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonPlateau->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonHHHigh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonBallet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_checkBoxLockAnkle->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleAnkleLock ), NULL, this );
	m_choiceDisplay->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChoiceDisplay ), NULL, this );
}

GUIFrameMain::~GUIFrameMain()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameMain::OnClose ) );
	this->Disconnect( ID_UNDO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnUndo ) );
	this->Disconnect( ID_REDO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnRedo ) );
	this->Disconnect( ID_INITIALIZEFOOTMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetByShoeSize ) );
	this->Disconnect( ID_FULLSYMMETRY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Disconnect( ID_SYMMETRICMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Disconnect( ID_INDIVIDUALMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Disconnect( ID_COPYLEFTTORIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnCopyMeasurements ) );
	this->Disconnect( ID_COPYRIGHTTOLEFT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnCopyMeasurements ) );
	this->Disconnect( ID_LOADFOOTMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadFootModel ) );
	this->Disconnect( ID_SAVEFOOTMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveFootModel ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadFootSTL ) );
	this->Disconnect( ID_SETUPFOOT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupFoot ) );
	this->Disconnect( ID_SETUPSHOE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupShoe ) );
	this->Disconnect( ID_CONSTRUCTIONEXPERIMENTAL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONWELDED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONCEMENTED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONMOLDED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONDUTCH, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_EDITWALKCYCLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditWalkCycle ) );
	this->Disconnect( ID_LOADPATTERN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadPattern ) );
	this->Disconnect( ID_SAVEPATTERN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSavePattern ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveLast ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveInsole ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveSole ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveCutaway ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnPackZip ) );
	this->Disconnect( ID_STEREO3D, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Disconnect( ID_SHOWLEFT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWRIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWBONES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWLAST, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWINSOLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWSOLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWUPPER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWCUTAWAY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWFLOOR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWBACKGROUND, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SETUPSTEREO3D, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Disconnect( ID_SETUPUNITS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSelectLanguage ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnDebugParser ) );
	m_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( GUIFrameMain::OnPageChange ), NULL, this );
	m_buttonSetByShoeSize->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnSetByShoeSize ), NULL, this );
	m_textCtrlFootLength->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlFootWidth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlHeelWidth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlAnkleWidth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlLegLengthDifference->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_gridBoneLength->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameMain::OnCellChange ), NULL, this );
	m_gridBoneDiameter->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameMain::OnCellChange ), NULL, this );
	m_gridSkin->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameMain::OnCellChange ), NULL, this );
	m_gridLeg->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameMain::OnCellChange ), NULL, this );
	m_textCtrlHeelHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlBallHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_textCtrlToeAngle->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScrollChange ), NULL, this );
	m_textCtrlResultMixing->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnText ), NULL, this );
	m_buttonFlats->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonHHLow->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonPlatform->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonClassic->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonHHMid->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonPony->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonPlateau->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonHHHigh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_buttonBallet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnPreset ), NULL, this );
	m_checkBoxLockAnkle->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleAnkleLock ), NULL, this );
	m_choiceDisplay->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChoiceDisplay ), NULL, this );
	
}

GUIDialogQuickInitFoot::GUIDialogQuickInitFoot( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText37 = new wxStaticText( this, wxID_ANY, _("Shoesize:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	bSizer18->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSize = new wxTextCtrl( this, wxID_ANY, _("39"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	bSizer18->Add( m_textCtrlShoeSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceUnitChoices[] = { _("EU"), _("US"), _("CN"), _("UK"), _("JP"), _("AU"), _("mm"), _("cm"), _("in"), _("ft") };
	int m_choiceUnitNChoices = sizeof( m_choiceUnitChoices ) / sizeof( wxString );
	m_choiceUnit = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitNChoices, m_choiceUnitChoices, 0 );
	m_choiceUnit->SetSelection( 0 );
	bSizer18->Add( m_choiceUnit, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer17->Add( bSizer18, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_radioBtnSmall = new wxRadioButton( this, wxID_ANY, _("small"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	bSizer19->Add( m_radioBtnSmall, 0, wxALL, 5 );
	
	m_radioBtnMedium = new wxRadioButton( this, wxID_ANY, _("medium"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtnMedium->SetValue( true ); 
	bSizer19->Add( m_radioBtnMedium, 0, wxALL, 5 );
	
	m_radioBtnWide = new wxRadioButton( this, wxID_ANY, _("wide"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_radioBtnWide, 0, wxALL, 5 );
	
	
	bSizer17->Add( bSizer19, 0, 0, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonInit = new wxButton( this, wxID_OK, _("Init"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_buttonInit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonAbort = new wxButton( this, wxID_CANCEL, _("Abort"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_buttonAbort, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer17->Add( bSizer20, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer17 );
	this->Layout();
	bSizer17->Fit( this );
	
	// Connect Events
	m_textCtrlShoeSize->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIDialogQuickInitFoot::OnText ), NULL, this );
	m_buttonInit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialogQuickInitFoot::OnOK ), NULL, this );
}

GUIDialogQuickInitFoot::~GUIDialogQuickInitFoot()
{
	// Disconnect Events
	m_textCtrlShoeSize->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIDialogQuickInitFoot::OnText ), NULL, this );
	m_buttonInit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialogQuickInitFoot::OnOK ), NULL, this );
	
}

GUIFrameDebugParser::GUIFrameDebugParser( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Input (Number / Calculation / Formula / Unit):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer->Add( m_staticText10, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlExpression = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_textCtrlExpression, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Numeric Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer->Add( m_staticText11, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlNumber = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer->Add( m_textCtrlNumber, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Error:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer->Add( m_staticText12, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlError = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer->Add( m_textCtrlError, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Unit Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer->Add( m_staticText14, 0, wxALL, 5 );
	
	m_textCtrlUnit = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer->Add( m_textCtrlUnit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("SI Base Units:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_textCtrlSIBase = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlSIBase->Enable( false );
	
	bSizer->Add( m_textCtrlSIBase, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	bSizer->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameDebugParser::OnCloseX ) );
	m_textCtrlExpression->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameDebugParser::OnText ), NULL, this );
}

GUIFrameDebugParser::~GUIFrameDebugParser()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameDebugParser::OnCloseX ) );
	m_textCtrlExpression->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameDebugParser::OnText ), NULL, this );
	
}

GUIFrameSetupUnits::GUIFrameSetupUnits( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Units ") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText57 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, _("Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText57->Wrap( -1 );
	fgSizer6->Add( m_staticText57, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitLengthChoices;
	m_choiceUnitLength = new wxChoice( sbSizer6->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitLengthChoices, 0 );
	m_choiceUnitLength->SetSelection( 0 );
	fgSizer6->Add( m_choiceUnitLength, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText110 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, _("Small Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText110->Wrap( -1 );
	fgSizer6->Add( m_staticText110, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitSmallDistanceChoices;
	m_choiceUnitSmallDistance = new wxChoice( sbSizer6->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitSmallDistanceChoices, 0 );
	m_choiceUnitSmallDistance->SetSelection( 0 );
	fgSizer6->Add( m_choiceUnitSmallDistance, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText112 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, _("Angle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText112->Wrap( -1 );
	fgSizer6->Add( m_staticText112, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceUnitAngleChoices;
	m_choiceUnitAngle = new wxChoice( sbSizer6->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitAngleChoices, 0 );
	m_choiceUnitAngle->SetSelection( 0 );
	fgSizer6->Add( m_choiceUnitAngle, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	
	sbSizer6->Add( fgSizer6, 1, wxEXPAND, 5 );
	
	
	bSizer25->Add( sbSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer25->Add( m_buttonClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText64 = new wxStaticText( this, wxID_ANY, _("Unit conversion is only used for displaying.\nInternally everything is stored in SI base units."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	bSizer25->Add( m_staticText64, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer25 );
	this->Layout();
	bSizer25->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameSetupUnits::OnCloseX ) );
	m_choiceUnitLength->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameSetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitSmallDistance->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameSetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitAngle->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameSetupUnits::OnChangeUnit ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameSetupUnits::OnClose ), NULL, this );
}

GUIFrameSetupUnits::~GUIFrameSetupUnits()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameSetupUnits::OnCloseX ) );
	m_choiceUnitLength->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameSetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitSmallDistance->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameSetupUnits::OnChangeUnit ), NULL, this );
	m_choiceUnitAngle->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameSetupUnits::OnChangeUnit ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameSetupUnits::OnClose ), NULL, this );
	
}

GUIDialogAbout::GUIDialogAbout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer->Add( m_textCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_buttonClose = new wxButton( this, wxID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_buttonClose, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

GUIDialogAbout::~GUIDialogAbout()
{
}
