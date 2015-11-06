///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../StdInclude.h"

#include "gui.h"

#include "../icons/ButtonFootDefinition.xpm"
#include "../icons/ButtonLastPosition.xpm"

///////////////////////////////////////////////////////////////////////////

GUIFrameMain::GUIFrameMain( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItemQuit;
	m_menuItemQuit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( wxT("&Quit") ) + wxT('\t') + wxT("CTRL+Q"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemQuit );
	
	m_menubar->Append( m_menuFile, wxT("&File") );
	
	m_menuFoot = new wxMenu();
	wxMenuItem* m_menuItemInitalizeFoot;
	m_menuItemInitalizeFoot = new wxMenuItem( m_menuFoot, ID_INITIALIZEFOOT, wxString( wxT("Quick &Initialization") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemInitalizeFoot );
	
	wxMenuItem* m_menuItemSetupFoot;
	m_menuItemSetupFoot = new wxMenuItem( m_menuFoot, ID_SETUPFOOT, wxString( wxT("Setup &Foot") ) , wxEmptyString, wxITEM_CHECK );
	m_menuFoot->Append( m_menuItemSetupFoot );
	
	m_menubar->Append( m_menuFoot, wxT("F&oot") );
	
	m_menuShoe = new wxMenu();
	wxMenuItem* m_menuItemSetupLast;
	m_menuItemSetupLast = new wxMenuItem( m_menuShoe, ID_SETUPLAST, wxString( wxT("Setup &Last") ) , wxEmptyString, wxITEM_CHECK );
	m_menuShoe->Append( m_menuItemSetupLast );
	
	wxMenuItem* m_menuItemEditPattern;
	m_menuItemEditPattern = new wxMenuItem( m_menuShoe, ID_EDITPATTERN, wxString( wxT("Edit &Pattern") ) , wxEmptyString, wxITEM_CHECK );
	m_menuShoe->Append( m_menuItemEditPattern );
	
	wxMenuItem* m_menuItemEditWalkCycle;
	m_menuItemEditWalkCycle = new wxMenuItem( m_menuShoe, ID_EDITWALKCYCLE, wxString( wxT("Define &Walkcycle Support") ) , wxEmptyString, wxITEM_CHECK );
	m_menuShoe->Append( m_menuItemEditWalkCycle );
	
	m_menubar->Append( m_menuShoe, wxT("&Shoe") );
	
	m_menuGeometry = new wxMenu();
	wxMenuItem* m_menuItemSaveLast;
	m_menuItemSaveLast = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( wxT("Save &Last") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveLast );
	
	wxMenuItem* m_menuItemSaveInsole;
	m_menuItemSaveInsole = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( wxT("Save &Insole") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveInsole );
	
	wxMenuItem* m_menuItemSaveShoe;
	m_menuItemSaveShoe = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( wxT("Save &Sole Prototype") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveShoe );
	
	wxMenuItem* m_menuItemCutaway;
	m_menuItemCutaway = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( wxT("Save &Cutaway Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemCutaway );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_menuGeometry->AppendSeparator();
	
	wxMenuItem* m_menuItemPackZip;
	m_menuItemPackZip = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( wxT("Pack a Zip with &Everything") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemPackZip );
	
	m_menubar->Append( m_menuGeometry, wxT("&Geometry") );
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemStereo3D;
	m_menuItemStereo3D = new wxMenuItem( m_menuView, ID_STEREO3D, wxString( wxT("Toggle Stereo &3D") ) + wxT('\t') + wxT("CTRL+3"), wxT("Toggle 3D view on/off."), wxITEM_CHECK );
	m_menuView->Append( m_menuItemStereo3D );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemShowBones;
	m_menuItemShowBones = new wxMenuItem( m_menuView, ID_SHOWBONES, wxString( wxT("Show &Bones") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowBones );
	
	wxMenuItem* m_menuItemShowLast;
	m_menuItemShowLast = new wxMenuItem( m_menuView, ID_SHOWLAST, wxString( wxT("Show &Last") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowLast );
	
	wxMenuItem* m_menuItemShowInsole;
	m_menuItemShowInsole = new wxMenuItem( m_menuView, ID_SHOWINSOLE, wxString( wxT("Show &Insole") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowInsole );
	
	wxMenuItem* m_menuIItemShowSole;
	m_menuIItemShowSole = new wxMenuItem( m_menuView, ID_SHOWSOLE, wxString( wxT("Show &Sole") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuIItemShowSole );
	
	wxMenuItem* m_menuItemShowUpper;
	m_menuItemShowUpper = new wxMenuItem( m_menuView, ID_SHOWUPPER, wxString( wxT("Show &Upper") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowUpper );
	
	wxMenuItem* m_menuItemShowCutaway;
	m_menuItemShowCutaway = new wxMenuItem( m_menuView, ID_SHOWCUTAWAY, wxString( wxT("Show &Cutaway Block") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowCutaway );
	
	wxMenuItem* m_menuItemShowFloor;
	m_menuItemShowFloor = new wxMenuItem( m_menuView, ID_SHOWFLOOR, wxString( wxT("Show &Floor") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowFloor );
	
	m_menubar->Append( m_menuView, wxT("&View") );
	
	m_menuSystem = new wxMenu();
	wxMenuItem* m_menuItemSetupStereo3D;
	m_menuItemSetupStereo3D = new wxMenuItem( m_menuSystem, ID_SETUPSTEREO3D, wxString( wxT("Setup &Stereo3D") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSystem->Append( m_menuItemSetupStereo3D );
	
	wxMenuItem* m_menuItemSetupUnits;
	m_menuItemSetupUnits = new wxMenuItem( m_menuSystem, ID_SETUPUNITS, wxString( wxT("Setup &Units") ) + wxT('\t') + wxT("CTRL+U"), wxEmptyString, wxITEM_NORMAL );
	m_menuSystem->Append( m_menuItemSetupUnits );
	
	m_menubar->Append( m_menuSystem, wxT("S&ystem") );
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItemAbout;
	m_menuItemAbout = new wxMenuItem( m_menuHelp, wxID_ABOUT, wxString( wxT("&About") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItemAbout );
	
	m_menubar->Append( m_menuHelp, wxT("&Help") );
	
	this->SetMenuBar( m_menubar );
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new Canvas3D(this);
	bSizer1->Add( m_canvas, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolBar->AddTool( ID_TOOLSETUPFOOT, wxT("FootDefinition"), wxBitmap( ButtonFootDefinition_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Enter the measurements."), wxEmptyString );
	m_toolBar->AddTool( ID_TOOLSETUPLAST, wxT("LastPosition"), wxBitmap( ButtonLastPosition_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Setup the last Position."), wxEmptyString );
	m_toolBar->Realize();
	
	
	// Connect Events
	this->Connect( m_menuItemQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnQuit ) );
	this->Connect( m_menuItemInitalizeFoot->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnInitializeFoot ) );
	this->Connect( m_menuItemSetupFoot->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupFoot ) );
	this->Connect( m_menuItemSetupLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupLast ) );
	this->Connect( m_menuItemEditPattern->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditPattern ) );
	this->Connect( m_menuItemEditWalkCycle->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditWalkCycle ) );
	this->Connect( m_menuItemSaveLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveLast ) );
	this->Connect( m_menuItemSaveInsole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveInsole ) );
	this->Connect( m_menuItemSaveShoe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveSole ) );
	this->Connect( m_menuItemCutaway->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveCutaway ) );
	this->Connect( m_menuItemPackZip->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnPackZip ) );
	this->Connect( m_menuItemStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Connect( m_menuItemShowBones->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowInsole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuIItemShowSole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowUpper->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowCutaway->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowFloor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemSetupStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Connect( m_menuItemSetupUnits->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Connect( m_menuItemAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnAbout ) );
	this->Connect( ID_TOOLSETUPFOOT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Connect( ID_TOOLSETUPLAST, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
}

GUIFrameMain::~GUIFrameMain()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnInitializeFoot ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupFoot ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupLast ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditPattern ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditWalkCycle ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveLast ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveInsole ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveSole ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveCutaway ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnPackZip ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnAbout ) );
	this->Disconnect( ID_TOOLSETUPFOOT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Disconnect( ID_TOOLSETUPLAST, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
}

GUIFrameFootParameter::GUIFrameFootParameter( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelMeasurements = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 5, 6, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->AddGrowableCol( 4 );
	fgSizer2->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText21 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("Foot length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer2->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrl5 = new wxTextCtrl( m_panelMeasurements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText22 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer2->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText23 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("Foot width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl6 = new wxTextCtrl( m_panelMeasurements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText24 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer2->Add( m_staticText24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText25 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("Heel width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer2->Add( m_staticText25, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrl7 = new wxTextCtrl( m_panelMeasurements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl7, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText26 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizer2->Add( m_staticText26, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText27 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("Ankle width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer2->Add( m_staticText27, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrl8 = new wxTextCtrl( m_panelMeasurements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl8, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText28 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer2->Add( m_staticText28, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText29 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer2->Add( m_staticText29, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl9 = new wxTextCtrl( m_panelMeasurements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl9, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText30 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer2->Add( m_staticText30, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText31 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer2->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrl10 = new wxTextCtrl( m_panelMeasurements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl10, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText32 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer2->Add( m_staticText32, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText33 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	fgSizer2->Add( m_staticText33, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl11 = new wxTextCtrl( m_panelMeasurements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl11, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText34 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer2->Add( m_staticText34, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText35 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer2->Add( m_staticText35, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl12 = new wxTextCtrl( m_panelMeasurements, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl12, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText36 = new wxStaticText( m_panelMeasurements, wxID_ANY, wxT("mm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer2->Add( m_staticText36, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer16->Add( fgSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonCalculate = new wxButton( m_panelMeasurements, wxID_ANY, wxT("Calculate Bones and Skin"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_buttonCalculate, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panelMeasurements->SetSizer( bSizer16 );
	m_panelMeasurements->Layout();
	bSizer16->Fit( m_panelMeasurements );
	m_notebook->AddPage( m_panelMeasurements, wxT("Measurements"), true );
	m_panelBone = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	m_gridBoneLength = new wxGrid( m_panelBone, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridBoneLength->CreateGrid( 1, 3 );
	m_gridBoneLength->EnableEditing( true );
	m_gridBoneLength->EnableGridLines( true );
	m_gridBoneLength->EnableDragGridSize( false );
	m_gridBoneLength->SetMargins( 0, 0 );
	
	// Columns
	m_gridBoneLength->EnableDragColMove( false );
	m_gridBoneLength->EnableDragColSize( true );
	m_gridBoneLength->SetColLabelSize( 30 );
	m_gridBoneLength->SetColLabelValue( 0, wxT("Formula") );
	m_gridBoneLength->SetColLabelValue( 1, wxT("Value") );
	m_gridBoneLength->SetColLabelValue( 2, wxT("Unit") );
	m_gridBoneLength->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridBoneLength->EnableDragRowSize( true );
	m_gridBoneLength->SetRowLabelSize( 80 );
	m_gridBoneLength->SetRowLabelValue( 0, wxT("Tibia") );
	m_gridBoneLength->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridBoneLength->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer21->Add( m_gridBoneLength, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panelBone->SetSizer( bSizer21 );
	m_panelBone->Layout();
	bSizer21->Fit( m_panelBone );
	m_notebook->AddPage( m_panelBone, wxT("Bone Length"), false );
	m_panel10 = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	m_gridBoneDiameter = new wxGrid( m_panel10, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridBoneDiameter->CreateGrid( 5, 5 );
	m_gridBoneDiameter->EnableEditing( true );
	m_gridBoneDiameter->EnableGridLines( true );
	m_gridBoneDiameter->EnableDragGridSize( false );
	m_gridBoneDiameter->SetMargins( 0, 0 );
	
	// Columns
	m_gridBoneDiameter->EnableDragColMove( false );
	m_gridBoneDiameter->EnableDragColSize( true );
	m_gridBoneDiameter->SetColLabelSize( 30 );
	m_gridBoneDiameter->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridBoneDiameter->EnableDragRowSize( true );
	m_gridBoneDiameter->SetRowLabelSize( 80 );
	m_gridBoneDiameter->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridBoneDiameter->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer28->Add( m_gridBoneDiameter, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panel10->SetSizer( bSizer28 );
	m_panel10->Layout();
	bSizer28->Fit( m_panel10 );
	m_notebook->AddPage( m_panel10, wxT("Bone Diameter"), false );
	m_panelSkin = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	m_gridSkin = new wxGrid( m_panelSkin, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridSkin->CreateGrid( 5, 5 );
	m_gridSkin->EnableEditing( true );
	m_gridSkin->EnableGridLines( true );
	m_gridSkin->EnableDragGridSize( false );
	m_gridSkin->SetMargins( 0, 0 );
	
	// Columns
	m_gridSkin->EnableDragColMove( false );
	m_gridSkin->EnableDragColSize( true );
	m_gridSkin->SetColLabelSize( 30 );
	m_gridSkin->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridSkin->EnableDragRowSize( true );
	m_gridSkin->SetRowLabelSize( 80 );
	m_gridSkin->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridSkin->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer26->Add( m_gridSkin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_panelSkin->SetSizer( bSizer26 );
	m_panelSkin->Layout();
	bSizer26->Fit( m_panelSkin );
	m_notebook->AddPage( m_panelSkin, wxT("Skin Density"), false );
	m_panelLeg = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );
	
	m_gridLeg = new wxGrid( m_panelLeg, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridLeg->CreateGrid( 5, 5 );
	m_gridLeg->EnableEditing( true );
	m_gridLeg->EnableGridLines( true );
	m_gridLeg->EnableDragGridSize( false );
	m_gridLeg->SetMargins( 0, 0 );
	
	// Columns
	m_gridLeg->EnableDragColMove( false );
	m_gridLeg->EnableDragColSize( true );
	m_gridLeg->SetColLabelSize( 30 );
	m_gridLeg->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridLeg->EnableDragRowSize( true );
	m_gridLeg->SetRowLabelSize( 80 );
	m_gridLeg->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridLeg->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer27->Add( m_gridLeg, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panelLeg->SetSizer( bSizer27 );
	m_panelLeg->Layout();
	bSizer27->Fit( m_panelLeg );
	m_notebook->AddPage( m_panelLeg, wxT("Leg"), false );
	
	bSizer11->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer11 );
	this->Layout();
	m_menubar = new wxMenuBar( 0 );
	m_menuFoot = new wxMenu();
	wxMenuItem* m_menuItemInitialize;
	m_menuItemInitialize = new wxMenuItem( m_menuFoot, ID_INITIALIZEFOOT, wxString( wxT("&Initialize") ) , wxT("Initialize measurements from shoe-size."), wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemInitialize );
	
	wxMenuItem* m_separator;
	m_separator = m_menuFoot->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuFoot, wxID_ANY, wxString( wxT("&Close") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuFoot, wxT("&Foot Setup") );
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItem23;
	m_menuItem23 = new wxMenuItem( m_menuSettings, ID_SETUPUNITS, wxString( wxT("Setup &Units") ) + wxT('\t') + wxT("CTRL+U"), wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItem23 );
	
	m_menubar->Append( m_menuSettings, wxT("&Settings") );
	
	this->SetMenuBar( m_menubar );
	
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameFootParameter::OnCloseX ) );
	m_buttonCalculate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameFootParameter::OnCalculate ), NULL, this );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameFootParameter::OnClose ) );
}

GUIFrameFootParameter::~GUIFrameFootParameter()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameFootParameter::OnCloseX ) );
	m_buttonCalculate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameFootParameter::OnCalculate ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameFootParameter::OnClose ) );
}

GUIDialogInitSettings::GUIDialogInitSettings( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText37 = new wxStaticText( this, wxID_ANY, wxT("Shoesize:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	bSizer18->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSize = new wxTextCtrl( this, wxID_ANY, wxT("39"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
	bSizer18->Add( m_textCtrlShoeSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceUnitChoices[] = { wxT("EU"), wxT("US"), wxT("CN"), wxT("UK"), wxT("JP"), wxT("AU"), wxT("mm"), wxT("cm"), wxT("in"), wxT("ft") };
	int m_choiceUnitNChoices = sizeof( m_choiceUnitChoices ) / sizeof( wxString );
	m_choiceUnit = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitNChoices, m_choiceUnitChoices, 0 );
	m_choiceUnit->SetSelection( 0 );
	bSizer18->Add( m_choiceUnit, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer17->Add( bSizer18, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_radioBtnWide = new wxRadioButton( this, wxID_ANY, wxT("wide"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	bSizer19->Add( m_radioBtnWide, 0, wxALL, 5 );
	
	m_radioBtnMedium = new wxRadioButton( this, wxID_ANY, wxT("medium"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtnMedium->SetValue( true ); 
	bSizer19->Add( m_radioBtnMedium, 0, wxALL, 5 );
	
	m_radioBtnSmall = new wxRadioButton( this, wxID_ANY, wxT("small"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_radioBtnSmall, 0, wxALL, 5 );
	
	bSizer17->Add( bSizer19, 0, 0, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button2 = new wxButton( this, wxID_OK, wxT("Init"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_button2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_button3 = new wxButton( this, wxID_CANCEL, wxT("Abort"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( m_button3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer17->Add( bSizer20, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer17 );
	this->Layout();
	bSizer17->Fit( this );
	
	// Connect Events
	m_textCtrlShoeSize->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIDialogInitSettings::OnText ), NULL, this );
	m_choiceUnit->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIDialogInitSettings::OnChoice ), NULL, this );
}

GUIDialogInitSettings::~GUIDialogInitSettings()
{
	// Disconnect Events
	m_textCtrlShoeSize->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIDialogInitSettings::OnText ), NULL, this );
	m_choiceUnit->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIDialogInitSettings::OnChoice ), NULL, this );
}

GUIFrameLastParameter::GUIFrameLastParameter( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 3, 1, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Articulatio Talocruralis") ), wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Plantar"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer3->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Neutral"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer3->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Dorsal"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer3->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	m_slider1Y = new wxSlider( this, ID_SLIDER1Y, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer1->Add( m_slider1Y, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer4->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer4->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl1Y = new wxTextCtrl( this, ID_TEXT1Y, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_textCtrl1Y, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText111 = new wxStaticText( this, wxID_ANY, wxT("Pronation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	bSizer311->Add( m_staticText111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer311->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText211 = new wxStaticText( this, wxID_ANY, wxT("Neutral"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	bSizer311->Add( m_staticText211, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer311->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText311 = new wxStaticText( this, wxID_ANY, wxT("Suspination"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText311->Wrap( -1 );
	bSizer311->Add( m_staticText311, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer311, 1, wxEXPAND, 5 );
	
	m_slider1X = new wxSlider( this, ID_SLIDER1X, 0, -30, 30, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer1->Add( m_slider1X, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer42->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText42 = new wxStaticText( this, wxID_ANY, wxT("Angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer42->Add( m_staticText42, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl1X = new wxTextCtrl( this, ID_TEXT1X, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer42->Add( m_textCtrl1X, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer42, 1, wxEXPAND, 5 );
	
	fgSizer1->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Articulatio Talotarsalis") ), wxVERTICAL );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Eversion"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer31->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer31->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Neutral"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer31->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer31->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText31 = new wxStaticText( this, wxID_ANY, wxT("Inversion"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer31->Add( m_staticText31, 0, wxALL, 5 );
	
	sbSizer11->Add( bSizer31, 0, wxEXPAND, 5 );
	
	m_slider2X = new wxSlider( this, ID_SLIDER2X, 0, -60, 60, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer11->Add( m_slider2X, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer41->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("Angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer41->Add( m_staticText41, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl2X = new wxTextCtrl( this, ID_TEXT2X, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( m_textCtrl2X, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer11->Add( bSizer41, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	fgSizer1->Add( sbSizer11, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer111;
	sbSizer111 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Articulationes Metatarsophalangeae") ), wxVERTICAL );
	
	wxBoxSizer* bSizer312;
	bSizer312 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText112 = new wxStaticText( this, wxID_ANY, wxT("Plantar"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText112->Wrap( -1 );
	bSizer312->Add( m_staticText112, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer312->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText212 = new wxStaticText( this, wxID_ANY, wxT("Neutral"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText212->Wrap( -1 );
	bSizer312->Add( m_staticText212, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer312->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText312 = new wxStaticText( this, wxID_ANY, wxT("Dorsal"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText312->Wrap( -1 );
	bSizer312->Add( m_staticText312, 0, wxALL, 5 );
	
	sbSizer111->Add( bSizer312, 0, wxEXPAND, 5 );
	
	m_slider3Y = new wxSlider( this, ID_SLIDER3Y, 0, -50, 50, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer111->Add( m_slider3Y, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer411;
	bSizer411 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer411->Add( 0, 0, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText411 = new wxStaticText( this, wxID_ANY, wxT("Angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	bSizer411->Add( m_staticText411, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl3Y = new wxTextCtrl( this, ID_TEXT3Y, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer411->Add( m_textCtrl3Y, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer111->Add( bSizer411, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	fgSizer1->Add( sbSizer111, 1, wxEXPAND, 5 );
	
	bSizer2->Add( fgSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameLastParameter::OnClose ) );
	m_slider1Y->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_textCtrl1Y->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastParameter::OnText ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_textCtrl1X->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastParameter::OnText ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_textCtrl2X->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastParameter::OnText ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_textCtrl3Y->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastParameter::OnText ), NULL, this );
}

GUIFrameLastParameter::~GUIFrameLastParameter()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameLastParameter::OnClose ) );
	m_slider1Y->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_textCtrl1Y->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastParameter::OnText ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_textCtrl1X->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastParameter::OnText ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_textCtrl2X->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastParameter::OnText ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastParameter::OnScroll ), NULL, this );
	m_textCtrl3Y->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastParameter::OnText ), NULL, this );
}

GUIFrameWalkcycleSupport::GUIFrameWalkcycleSupport( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panelSupport = new PanelSupport(this);
	bSizer12->Add( m_panelSupport, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Walkcycle") ), wxVERTICAL );
	
	m_panelCycle = new PanelWalkcycle(this);
	sbSizer4->Add( m_panelCycle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_checkBoxLockAnkle = new wxCheckBox( this, wxID_ANY, wxT("Lock Ankle"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_checkBoxLockAnkle, 0, wxALL|wxEXPAND, 5 );
	
	bSizer15->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Forces, Moments") ), wxVERTICAL );
	
	m_panelPlot = new PanelPlotSimple(this);
	sbSizer5->Add( m_panelPlot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxString m_choiceChoices[] = { wxT("Kneeline"), wxT("Force"), wxT("Moment"), wxT("Crossforce") };
	int m_choiceNChoices = sizeof( m_choiceChoices ) / sizeof( wxString );
	m_choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceNChoices, m_choiceChoices, 0 );
	m_choice->SetSelection( 0 );
	sbSizer5->Add( m_choice, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer15->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	bSizer12->Add( bSizer15, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer12 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameWalkcycleSupport::OnClose ) );
}

GUIFrameWalkcycleSupport::~GUIFrameWalkcycleSupport()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameWalkcycleSupport::OnClose ) );
}

GUIFramePattern::GUIFramePattern( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel = new PanelPattern(this);
	bSizer14->Add( m_panel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("Preset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	bSizer15->Add( m_staticText17, 0, wxALL, 5 );
	
	wxString m_choice2Choices[] = { wxT("Custom Design") };
	int m_choice2NChoices = sizeof( m_choice2Choices ) / sizeof( wxString );
	m_choice2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2NChoices, m_choice2Choices, 0 );
	m_choice2->SetSelection( 0 );
	bSizer15->Add( m_choice2, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Style:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	bSizer15->Add( m_staticText18, 0, wxALL, 5 );
	
	wxString m_choice3Choices[] = { wxT("Standard") };
	int m_choice3NChoices = sizeof( m_choice3Choices ) / sizeof( wxString );
	m_choice3 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice3NChoices, m_choice3Choices, 0 );
	m_choice3->SetSelection( 0 );
	bSizer15->Add( m_choice3, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText19 = new wxStaticText( this, wxID_ANY, wxT("Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	bSizer15->Add( m_staticText19, 0, wxALL, 5 );
	
	m_slider5 = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer15->Add( m_slider5, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("Factor:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	bSizer15->Add( m_staticText20, 0, wxALL, 5 );
	
	m_slider6 = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer15->Add( m_slider6, 0, wxALL|wxEXPAND, 5 );
	
	bSizer14->Add( bSizer15, 0, 0, 5 );
	
	this->SetSizer( bSizer14 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFramePattern::OnClose ) );
}

GUIFramePattern::~GUIFramePattern()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFramePattern::OnClose ) );
}
