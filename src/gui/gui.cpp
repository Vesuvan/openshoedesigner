///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

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
	
	m_menuSetup = new wxMenu();
	wxMenuItem* m_menuItemStereo3D;
	m_menuItemStereo3D = new wxMenuItem( m_menuSetup, ID_STEREO3D, wxString( wxT("Toggle Stereo &3D") ) + wxT('\t') + wxT("CTRL+3"), wxT("Toggle 3D view on/off."), wxITEM_CHECK );
	m_menuSetup->Append( m_menuItemStereo3D );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_menuSetup->AppendSeparator();
	
	wxMenuItem* m_menuItemSetupStereo3D;
	m_menuItemSetupStereo3D = new wxMenuItem( m_menuSetup, ID_SETUPSTEREO3D, wxString( wxT("Setup &Stereo3D") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSetup->Append( m_menuItemSetupStereo3D );
	
	wxMenuItem* m_menuItemSetupUnits;
	m_menuItemSetupUnits = new wxMenuItem( m_menuSetup, ID_SETUPUNITS, wxString( wxT("Setup &Units") ) + wxT('\t') + wxT("CTRL+U"), wxEmptyString, wxITEM_NORMAL );
	m_menuSetup->Append( m_menuItemSetupUnits );
	
	m_menubar->Append( m_menuSetup, wxT("&Setup") );
	
	this->SetMenuBar( m_menubar );
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new Canvas3D(this);
	bSizer1->Add( m_canvas, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolBar->AddTool( ID_FOOTDEFINITION, wxT("FootDefinition"), wxBitmap( ButtonFootDefinition_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Enter the measurements."), wxEmptyString );
	m_toolBar->AddTool( ID_LASTPOSITION, wxT("LastPosition"), wxBitmap( ButtonLastPosition_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Setup the last Position."), wxEmptyString );
	m_toolBar->Realize();
	
	
	// Connect Events
	this->Connect( m_menuItemQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnQuit ) );
	this->Connect( m_menuItemStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Connect( m_menuItemSetupStereo3D->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Connect( m_menuItemSetupUnits->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Connect( ID_FOOTDEFINITION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Connect( ID_LASTPOSITION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
}

GUIFrameMain::~GUIFrameMain()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Disconnect( ID_FOOTDEFINITION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Disconnect( ID_LASTPOSITION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
}

GUIFrameLastPosition::GUIFrameLastPosition( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
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
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameLastPosition::OnClose ) );
	m_slider1Y->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_textCtrl1Y->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastPosition::OnText ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_textCtrl1X->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastPosition::OnText ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_textCtrl2X->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastPosition::OnText ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_textCtrl3Y->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastPosition::OnText ), NULL, this );
}

GUIFrameLastPosition::~GUIFrameLastPosition()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameLastPosition::OnClose ) );
	m_slider1Y->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1Y->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_textCtrl1Y->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastPosition::OnText ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider1X->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_textCtrl1X->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastPosition::OnText ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider2X->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_textCtrl2X->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastPosition::OnText ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_slider3Y->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameLastPosition::OnScroll ), NULL, this );
	m_textCtrl3Y->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameLastPosition::OnText ), NULL, this );
}
