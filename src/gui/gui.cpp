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
	m_menuItemQuit = new wxMenuItem( m_menuFile, wxID_QUIT, wxString( wxT("&Quit") ) + wxT('\t') + wxT("CTRL+Q"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemQuit );
	
	m_menubar->Append( m_menuFile, wxT("&File") );
	
	m_menuFoot = new wxMenu();
	wxMenuItem* m_menuItemSetupFoot;
	m_menuItemSetupFoot = new wxMenuItem( m_menuFoot, ID_SETUPFOOT, wxString( wxT("Setup &Foot") ) , wxEmptyString, wxITEM_CHECK );
	m_menuFoot->Append( m_menuItemSetupFoot );
	
	m_menubar->Append( m_menuFoot, wxT("F&oot") );
	
	m_menuShoe = new wxMenu();
	wxMenuItem* m_menuItemSetupLast;
	m_menuItemSetupLast = new wxMenuItem( m_menuShoe, ID_SETUPLAST, wxString( wxT("Setup &Last") ) , wxEmptyString, wxITEM_CHECK );
	m_menuShoe->Append( m_menuItemSetupLast );
	
	wxMenuItem* m_menuItemDefineWalkCycle;
	m_menuItemDefineWalkCycle = new wxMenuItem( m_menuShoe, wxID_ANY, wxString( wxT("Define &Walkcycle Support") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuShoe->Append( m_menuItemDefineWalkCycle );
	
	m_menubar->Append( m_menuShoe, wxT("&Shoe") );
	
	m_menuGeometry = new wxMenu();
	wxMenuItem* m_menuItemSaveLast;
	m_menuItemSaveLast = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( wxT("Save &Last") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveLast );
	
	wxMenuItem* m_menuItemSaveInsole;
	m_menuItemSaveInsole = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( wxT("Save &Insole") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveInsole );
	
	wxMenuItem* m_menuItemSaveShoe;
	m_menuItemSaveShoe = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( wxT("Save &Shoe Prototype") ) , wxEmptyString, wxITEM_NORMAL );
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
	
	wxMenuItem* m_menuItemShowShoe;
	m_menuItemShowShoe = new wxMenuItem( m_menuView, ID_SHOWSHOE, wxString( wxT("Show &Shoe") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowShoe );
	
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
	this->Connect( m_menuItemSetupFoot->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupFoot ) );
	this->Connect( m_menuItemSetupLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupLast ) );
	this->Connect( m_menuItemDefineWalkCycle->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnDefineWalkCycle ) );
	this->Connect( m_menuItemSaveLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveLast ) );
	this->Connect( m_menuItemSaveInsole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveInsole ) );
	this->Connect( m_menuItemSaveShoe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveShoe ) );
	this->Connect( m_menuItemCutaway->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveCutaway ) );
	this->Connect( m_menuItemPackZip->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnPackZip ) );
	this->Connect( m_menuItemStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Connect( m_menuItemShowBones->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowInsole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowShoe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowCutaway->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowFloor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemSetupStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Connect( m_menuItemSetupUnits->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Connect( ID_TOOLSETUPFOOT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Connect( ID_TOOLSETUPLAST, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
}

GUIFrameMain::~GUIFrameMain()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupFoot ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupLast ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnDefineWalkCycle ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveLast ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveInsole ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveShoe ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveCutaway ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnPackZip ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Disconnect( ID_TOOLSETUPFOOT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Disconnect( ID_TOOLSETUPLAST, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
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

GUIFrameFootParameter::GUIFrameFootParameter( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel1, wxT("a page"), false );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel2, wxT("a page"), false );
	
	bSizer11->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer11 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameFootParameter::OnClose ) );
}

GUIFrameFootParameter::~GUIFrameFootParameter()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameFootParameter::OnClose ) );
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
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("label") ), wxVERTICAL );
	
	m_panelCycle = new PanelSupport(this);
	sbSizer4->Add( m_panelCycle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_checkBoxLockAnkle = new wxCheckBox( this, wxID_ANY, wxT("Lock Ankle"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_checkBoxLockAnkle, 0, wxALL|wxEXPAND, 5 );
	
	bSizer15->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("label") ), wxVERTICAL );
	
	m_panelData = new PanelSupport(this);
	sbSizer5->Add( m_panelData, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
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
