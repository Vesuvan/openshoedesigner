///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../StdInclude.h"

#include "gui.h"

#include "../icons/ButtonFootDefinition.xpm"
#include "../icons/ButtonL.xpm"
#include "../icons/ButtonLR.xpm"
#include "../icons/ButtonLastPosition.xpm"
#include "../icons/ButtonR.xpm"

///////////////////////////////////////////////////////////////////////////

GUIFrameMain::GUIFrameMain(wxDocument* doc, wxView* view, wxDocParentFrame* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDocChildFrame( doc, view, parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	m_menubar->Append( m_menuFile, _("&File") ); 
	
	m_menuEdit = new wxMenu();
	m_menubar->Append( m_menuEdit, _("&Edit") ); 
	
	m_menuFoot = new wxMenu();
	wxMenuItem* m_menuItemInitalizeFootModel;
	m_menuItemInitalizeFootModel = new wxMenuItem( m_menuFoot, ID_INITIALIZEFOOTMODEL, wxString( _("Quick &Initialization") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemInitalizeFootModel );
	
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
	
	wxMenuItem* m_menuItemSetupFoot;
	m_menuItemSetupFoot = new wxMenuItem( m_menuFoot, ID_SETUPFOOT, wxString( _("Setup &Footmodel") ) , wxEmptyString, wxITEM_CHECK );
	m_menuFoot->Append( m_menuItemSetupFoot );
	
	m_menubar->Append( m_menuFoot, _("F&oot") ); 
	
	m_menuLast = new wxMenu();
	wxMenuItem* m_menuItemLastLoadSTL;
	m_menuItemLastLoadSTL = new wxMenuItem( m_menuLast, wxID_ANY, wxString( _("Load Last from STL") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuLast->Append( m_menuItemLastLoadSTL );
	
	m_menubar->Append( m_menuLast, _("&Last") ); 
	
	m_menuShoe = new wxMenu();
	wxMenuItem* m_menuItemSetupShoe;
	m_menuItemSetupShoe = new wxMenuItem( m_menuShoe, ID_SETUPSHOE, wxString( _("Setup &Shoe") ) , wxEmptyString, wxITEM_CHECK );
	m_menuShoe->Append( m_menuItemSetupShoe );
	
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
	m_menuItemEditWalkCycle = new wxMenuItem( m_menuShoe, ID_EDITWALKCYCLE, wxString( _("Define &Walkcycle Support") ) , wxEmptyString, wxITEM_CHECK );
	m_menuShoe->Append( m_menuItemEditWalkCycle );
	
	wxMenuItem* m_menuItemLoadShoe;
	m_menuItemLoadShoe = new wxMenuItem( m_menuShoe, ID_LOADSHOE, wxString( _("Load Shoe") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuShoe->Append( m_menuItemLoadShoe );
	
	wxMenuItem* m_menuItemSaveShoe;
	m_menuItemSaveShoe = new wxMenuItem( m_menuShoe, ID_SAVESHOE, wxString( _("Save Shoe") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuShoe->Append( m_menuItemSaveShoe );
	
	m_menubar->Append( m_menuShoe, _("&Shoe") ); 
	
	m_menuPattern = new wxMenu();
	wxMenuItem* m_menuItemShowFlattening;
	m_menuItemShowFlattening = new wxMenuItem( m_menuPattern, wxID_ANY, wxString( _("Show Flattening") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuPattern->Append( m_menuItemShowFlattening );
	
	m_menubar->Append( m_menuPattern, _("&Pattern") ); 
	
	m_menuGeometry = new wxMenu();
	wxMenuItem* m_menuItemSaveLast;
	m_menuItemSaveLast = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Save &Last") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveLast );
	
	wxMenuItem* m_menuItemSaveInsole;
	m_menuItemSaveInsole = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Save &Insole") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveInsole );
	
	wxMenuItem* m_menuItemSaveSole;
	m_menuItemSaveSole = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Save &Sole Prototype") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemSaveSole );
	
	wxMenuItem* m_menuItemCutaway;
	m_menuItemCutaway = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Save &Cutaway Object") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemCutaway );
	
	m_menuGeometry->AppendSeparator();
	
	wxMenuItem* m_menuItemPackZip;
	m_menuItemPackZip = new wxMenuItem( m_menuGeometry, wxID_ANY, wxString( _("Pack a Zip with &Everything") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuGeometry->Append( m_menuItemPackZip );
	
	m_menubar->Append( m_menuGeometry, _("&Geometry") ); 
	
	m_menuView = new wxMenu();
	wxMenuItem* m_menuItemStereo3D;
	m_menuItemStereo3D = new wxMenuItem( m_menuView, ID_STEREO3D, wxString( _("Toggle Stereo &3D") ) + wxT('\t') + wxT("CTRL+3"), _("Toggle 3D view on/off."), wxITEM_CHECK );
	m_menuView->Append( m_menuItemStereo3D );
	
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
	m_menuItemdebugParser = new wxMenuItem( m_menuHelp, wxID_ANY, wxString( _("Debug Mathparser") ) , _("Opens a "), wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItemdebugParser );
	
	m_menubar->Append( m_menuHelp, _("&Help") ); 
	
	this->SetMenuBar( m_menubar );
	
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new Canvas3D(this);
	bSizer->Add( m_canvas, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	m_toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolFootDefinition = m_toolBar->AddTool( ID_TOOLSETUPFOOT, _("FootDefinition"), wxBitmap( ButtonFootDefinition_xpm ), wxNullBitmap, wxITEM_CHECK, _("Enter the measurements."), wxEmptyString, NULL ); 
	
	m_toolSetupShoe = m_toolBar->AddTool( ID_TOOLSETUPSHOE, _("Setup Shoe"), wxBitmap( ButtonLastPosition_xpm ), wxNullBitmap, wxITEM_CHECK, _("Setup the shoetype."), wxEmptyString, NULL ); 
	
	m_toolBar->AddSeparator(); 
	
	m_toolShowLeft = m_toolBar->AddTool( ID_SHOWLEFT, _("tool"), wxBitmap( ButtonL_xpm ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL ); 
	
	m_toolShowBoth = m_toolBar->AddTool( ID_SHOWBOTH, _("tool"), wxBitmap( ButtonLR_xpm ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL ); 
	
	m_toolShowRight = m_toolBar->AddTool( ID_SHOWRIGHT, _("tool"), wxBitmap( ButtonR_xpm ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL ); 
	
	m_toolBar->AddSeparator(); 
	
	m_toolBar->Realize(); 
	
	
	// Connect Events
	this->Connect( m_menuItemInitalizeFootModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnInitializeFootModel ) );
	this->Connect( m_menuItemLoadFootModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadFootModel ) );
	this->Connect( m_menuItemSaveFootModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveFootModel ) );
	this->Connect( m_menuItemSetupFoot->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupFoot ) );
	this->Connect( m_menuItemSetupShoe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupShoe ) );
	this->Connect( m_menuItemTestGenerator->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionClassic->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionCemented->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionMolded->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionDutch->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemEditWalkCycle->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditWalkCycle ) );
	this->Connect( m_menuItemLoadShoe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadShoe ) );
	this->Connect( m_menuItemSaveShoe->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveShoe ) );
	this->Connect( m_menuItemSaveLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveLast ) );
	this->Connect( m_menuItemSaveInsole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveInsole ) );
	this->Connect( m_menuItemSaveSole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveSole ) );
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
	this->Connect( m_menuItemSelectLanguage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSelectLanguage ) );
	this->Connect( m_menuItemdebugParser->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnDebugParser ) );
	this->Connect( m_toolFootDefinition->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Connect( m_toolSetupShoe->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Connect( m_toolShowLeft->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_toolShowBoth->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_toolShowRight->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
}

GUIFrameMain::~GUIFrameMain()
{
	// Disconnect Events
	this->Disconnect( ID_INITIALIZEFOOTMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnInitializeFootModel ) );
	this->Disconnect( ID_LOADFOOTMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadFootModel ) );
	this->Disconnect( ID_SAVEFOOTMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveFootModel ) );
	this->Disconnect( ID_SETUPFOOT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupFoot ) );
	this->Disconnect( ID_SETUPSHOE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupShoe ) );
	this->Disconnect( ID_CONSTRUCTIONEXPERIMENTAL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONWELDED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONCEMENTED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONMOLDED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONDUTCH, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_EDITWALKCYCLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditWalkCycle ) );
	this->Disconnect( ID_LOADSHOE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadShoe ) );
	this->Disconnect( ID_SAVESHOE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveShoe ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveLast ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveInsole ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveSole ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveCutaway ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnPackZip ) );
	this->Disconnect( ID_STEREO3D, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnToggleStereo3D ) );
	this->Disconnect( ID_SHOWBONES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWLAST, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWINSOLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWSOLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWUPPER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWCUTAWAY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWFLOOR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SETUPSTEREO3D, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupStereo3D ) );
	this->Disconnect( ID_SETUPUNITS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupUnits ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSelectLanguage ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnDebugParser ) );
	this->Disconnect( m_toolFootDefinition->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Disconnect( m_toolSetupShoe->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToolClicked ) );
	this->Disconnect( m_toolShowLeft->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( m_toolShowBoth->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( m_toolShowRight->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	
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
	
	m_textCtrlShoeSize = new wxTextCtrl( this, wxID_ANY, _("39"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT );
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
	m_textCtrlShoeSize->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIDialogQuickInitFoot::OnText ), NULL, this );
	m_choiceUnit->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIDialogQuickInitFoot::OnChoice ), NULL, this );
}

GUIDialogQuickInitFoot::~GUIDialogQuickInitFoot()
{
	// Disconnect Events
	m_textCtrlShoeSize->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIDialogQuickInitFoot::OnText ), NULL, this );
	m_choiceUnit->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIDialogQuickInitFoot::OnChoice ), NULL, this );
	
}

GUIFrameFoot::GUIFrameFoot( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelMeasurements = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->AddGrowableCol( 3 );
	fgSizer2->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText21 = new wxStaticText( m_panelMeasurements, wxID_ANY, _("Foot length (L):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer2->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlFootLength = new wxTextCtrl( m_panelMeasurements, ID_TEXTFOOTLENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlFootLength, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText23 = new wxStaticText( m_panelMeasurements, wxID_ANY, _("Ball width (W):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer2->Add( m_staticText23, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlFootWidth = new wxTextCtrl( m_panelMeasurements, ID_TEXTFOOTWIDTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlFootWidth, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText25 = new wxStaticText( m_panelMeasurements, wxID_ANY, _("Heel width (H):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer2->Add( m_staticText25, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlHeelWidth = new wxTextCtrl( m_panelMeasurements, ID_TEXTHEELWIDTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlHeelWidth, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText27 = new wxStaticText( m_panelMeasurements, wxID_ANY, _("Ankle width (A):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer2->Add( m_staticText27, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlAnkleWidth = new wxTextCtrl( m_panelMeasurements, ID_ANKLEWIDTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlAnkleWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer16->Add( fgSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_buttonSetByShoeSize = new wxButton( m_panelMeasurements, wxID_ANY, _("Set by shoesize"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( m_buttonSetByShoeSize, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizerShoeSizes;
	sbSizerShoeSizes = new wxStaticBoxSizer( new wxStaticBox( m_panelMeasurements, wxID_ANY, _("Shoesizes") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 3, 6, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableCol( 3 );
	fgSizer3->AddGrowableCol( 5 );
	fgSizer3->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextShoeSizeEU = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("EU:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeEU->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeEU, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShoeSizeEU = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlShoeSizeEU, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeUS = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("US:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeUS->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeUS, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeUS = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlShoeSizeUS, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeUK = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("UK:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeUK->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeUK, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeUK = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlShoeSizeUK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeCN = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("CN:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeCN->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeCN, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShoeSizeCN = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlShoeSizeCN, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeJP = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("JP:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeJP->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeJP, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeJP = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlShoeSizeJP, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextShoeSizeAU = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("AU:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeAU->Wrap( -1 );
	fgSizer3->Add( m_staticTextShoeSizeAU, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeAU = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer3->Add( m_textCtrlShoeSizeAU, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	sbSizerShoeSizes->Add( fgSizer3, 0, wxEXPAND, 5 );
	
	
	bSizer16->Add( sbSizerShoeSizes, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	m_panelMeasurements->SetSizer( bSizer16 );
	m_panelMeasurements->Layout();
	bSizer16->Fit( m_panelMeasurements );
	m_notebook->AddPage( m_panelMeasurements, _("Measurements"), true );
	m_panelBone = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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
	m_gridBoneLength->SetColSize( 0, 250 );
	m_gridBoneLength->SetColSize( 1, 150 );
	m_gridBoneLength->EnableDragColMove( false );
	m_gridBoneLength->EnableDragColSize( true );
	m_gridBoneLength->SetColLabelSize( 30 );
	m_gridBoneLength->SetColLabelValue( 0, _("Length (Formula)") );
	m_gridBoneLength->SetColLabelValue( 1, _("Length (Value)") );
	m_gridBoneLength->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridBoneLength->AutoSizeRows();
	m_gridBoneLength->EnableDragRowSize( true );
	m_gridBoneLength->SetRowLabelSize( 150 );
	m_gridBoneLength->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridBoneLength->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer21->Add( m_gridBoneLength, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelBone->SetSizer( bSizer21 );
	m_panelBone->Layout();
	bSizer21->Fit( m_panelBone );
	m_notebook->AddPage( m_panelBone, _("Bone Length"), false );
	m_panelBoneDiameter = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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
	m_gridBoneDiameter->SetColSize( 0, 150 );
	m_gridBoneDiameter->SetColSize( 1, 100 );
	m_gridBoneDiameter->SetColSize( 2, 150 );
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
	m_gridBoneDiameter->SetRowLabelSize( 150 );
	m_gridBoneDiameter->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridBoneDiameter->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer28->Add( m_gridBoneDiameter, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelBoneDiameter->SetSizer( bSizer28 );
	m_panelBoneDiameter->Layout();
	bSizer28->Fit( m_panelBoneDiameter );
	m_notebook->AddPage( m_panelBoneDiameter, _("Bone Diameter"), false );
	m_panelSkin = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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
	m_gridSkin->SetColSize( 0, 150 );
	m_gridSkin->SetColSize( 1, 100 );
	m_gridSkin->SetColSize( 2, 150 );
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
	m_gridSkin->SetRowLabelSize( 150 );
	m_gridSkin->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridSkin->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer26->Add( m_gridSkin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	m_panelSkin->SetSizer( bSizer26 );
	m_panelSkin->Layout();
	bSizer26->Fit( m_panelSkin );
	m_notebook->AddPage( m_panelSkin, _("Skin Thickness"), false );
	m_panelLeg = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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
	m_gridLeg->SetColSize( 0, 140 );
	m_gridLeg->SetColSize( 1, 130 );
	m_gridLeg->SetColSize( 2, 180 );
	m_gridLeg->SetColSize( 3, 160 );
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
	m_notebook->AddPage( m_panelLeg, _("Leg"), false );
	
	bSizer11->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer11 );
	this->Layout();
	m_menubar = new wxMenuBar( 0 );
	m_menuFoot = new wxMenu();
	wxMenuItem* m_menuItemInitialize;
	m_menuItemInitialize = new wxMenuItem( m_menuFoot, ID_INITIALIZEFOOTMODEL, wxString( _("&Initialize") ) , _("Initialize measurements from shoe-size."), wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemInitialize );
	
	wxMenuItem* m_menuItemLoadModel;
	m_menuItemLoadModel = new wxMenuItem( m_menuFoot, ID_LOADFOOTMODEL, wxString( _("&Load Model") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemLoadModel );
	
	wxMenuItem* m_menuItemSaveModel;
	m_menuItemSaveModel = new wxMenuItem( m_menuFoot, ID_SAVEFOOTMODEL, wxString( _("&Save Model") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemSaveModel );
	
	m_menuFoot->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuFoot, wxID_ANY, wxString( _("&Close") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuFoot, _("&Foot Setup") ); 
	
	m_menuSettings = new wxMenu();
	wxMenuItem* m_menuItemSetupUnits;
	m_menuItemSetupUnits = new wxMenuItem( m_menuSettings, ID_SETUPUNITS, wxString( _("Setup &Units") ) + wxT('\t') + wxT("CTRL+U"), wxEmptyString, wxITEM_NORMAL );
	m_menuSettings->Append( m_menuItemSetupUnits );
	
	m_menubar->Append( m_menuSettings, _("&Settings") ); 
	
	this->SetMenuBar( m_menubar );
	
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameFoot::OnCloseX ) );
	m_textCtrlFootLength->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameFoot::OnText ), NULL, this );
	m_textCtrlFootWidth->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameFoot::OnText ), NULL, this );
	m_textCtrlHeelWidth->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameFoot::OnText ), NULL, this );
	m_textCtrlAnkleWidth->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameFoot::OnText ), NULL, this );
	m_buttonSetByShoeSize->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameFoot::OnSetByShoeSize ), NULL, this );
	m_gridBoneLength->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameFoot::OnCellChange ), NULL, this );
	m_gridBoneDiameter->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameFoot::OnCellChange ), NULL, this );
	m_gridSkin->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameFoot::OnCellChange ), NULL, this );
	m_gridLeg->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameFoot::OnCellChange ), NULL, this );
	this->Connect( m_menuItemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameFoot::OnClose ) );
}

GUIFrameFoot::~GUIFrameFoot()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameFoot::OnCloseX ) );
	m_textCtrlFootLength->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameFoot::OnText ), NULL, this );
	m_textCtrlFootWidth->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameFoot::OnText ), NULL, this );
	m_textCtrlHeelWidth->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameFoot::OnText ), NULL, this );
	m_textCtrlAnkleWidth->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUIFrameFoot::OnText ), NULL, this );
	m_buttonSetByShoeSize->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameFoot::OnSetByShoeSize ), NULL, this );
	m_gridBoneLength->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameFoot::OnCellChange ), NULL, this );
	m_gridBoneDiameter->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameFoot::OnCellChange ), NULL, this );
	m_gridSkin->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameFoot::OnCellChange ), NULL, this );
	m_gridLeg->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameFoot::OnCellChange ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameFoot::OnClose ) );
	
}

GUIFrameShoe::GUIFrameShoe( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 4, 3, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextHeelHeight = new wxStaticText( this, wxID_ANY, _("Heel Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHeelHeight->Wrap( -1 );
	fgSizer1->Add( m_staticTextHeelHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlHeelHeight = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1->Add( m_textCtrlHeelHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_textCtrlResultHeelHeight = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	fgSizer1->Add( m_textCtrlResultHeelHeight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBallHeight = new wxStaticText( this, wxID_ANY, _("Ball Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBallHeight->Wrap( -1 );
	fgSizer1->Add( m_staticTextBallHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlBallHeight = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1->Add( m_textCtrlBallHeight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_textCtrlResultBallHeight = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	fgSizer1->Add( m_textCtrlResultBallHeight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextToeAngle = new wxStaticText( this, wxID_ANY, _("Toe Angle:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToeAngle->Wrap( -1 );
	fgSizer1->Add( m_staticTextToeAngle, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlToeAngle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer1->Add( m_textCtrlToeAngle, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_textCtrlResultToeAngle = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	fgSizer1->Add( m_textCtrlResultToeAngle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextMixing = new wxStaticText( this, wxID_ANY, _("Angle Mixing:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextMixing->Wrap( -1 );
	fgSizer1->Add( m_staticTextMixing, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_sliderMixing = new wxSlider( this, wxID_ANY, 10, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	m_sliderMixing->SetToolTip( _("Mixing determines how much of the needed bending of the foot is done by the heel and how much is spread on the forefoot. 0% is all heel, 100% is all forefoot. 100% is impractical unless some serious misalignment of the foot is to be compensated.") );
	
	fgSizer1->Add( m_sliderMixing, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_textCtrlResultMixing = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_RIGHT );
	fgSizer1->Add( m_textCtrlResultMixing, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( fgSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 3, 3, 0, 0 );
	
	m_buttonFlats = new wxButton( this, ID_PRESETFLATS, _("Flats"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonFlats, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonHHLow = new wxButton( this, ID_PRESETHHLOW, _("High Heel (low)"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonHHLow, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPlatform = new wxButton( this, ID_PRESETPLATFORM, _("Platform Heel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonPlatform, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonClassic = new wxButton( this, ID_PRESETCLASSIC, _("Classic"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonClassic, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_buttonHHMid = new wxButton( this, ID_PRESETHHMID, _("High Heel (mid)"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonHHMid, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPony = new wxButton( this, ID_PRESETPONY, _("Pony"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonPony, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonPlateau = new wxButton( this, ID_PRESETPLATEAU, _("Plateau"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonPlateau, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_buttonHHHigh = new wxButton( this, ID_PRESETHHHIGH, _("High Heel (high)"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonHHHigh, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_buttonBallet = new wxButton( this, ID_PRESETBALLET, _("Ballet"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_buttonBallet, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	bSizer2->Add( gSizer1, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameShoe::OnCloseX ) );
	m_textCtrlHeelHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameShoe::OnTextEnter ), NULL, this );
	m_textCtrlBallHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameShoe::OnTextEnter ), NULL, this );
	m_textCtrlToeAngle->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameShoe::OnTextEnter ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameShoe::OnScrollChange ), NULL, this );
	m_buttonFlats->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonHHLow->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonPlatform->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonClassic->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonHHMid->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonPony->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonPlateau->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonHHHigh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonBallet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
}

GUIFrameShoe::~GUIFrameShoe()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameShoe::OnCloseX ) );
	m_textCtrlHeelHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameShoe::OnTextEnter ), NULL, this );
	m_textCtrlBallHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameShoe::OnTextEnter ), NULL, this );
	m_textCtrlToeAngle->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameShoe::OnTextEnter ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameShoe::OnScroll ), NULL, this );
	m_sliderMixing->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameShoe::OnScrollChange ), NULL, this );
	m_buttonFlats->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonHHLow->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonPlatform->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonClassic->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonHHMid->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonPony->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonPlateau->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonHHHigh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	m_buttonBallet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameShoe::OnPreset ), NULL, this );
	
}

GUIFrameWalkcycleSupport::GUIFrameWalkcycleSupport( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_panelSupport = new PanelSupport(this);
	bSizer->Add( m_panelSupport, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Walkcycle") ), wxVERTICAL );
	
	m_panelCycle = new PanelWalkcycle(this);
	sbSizer1->Add( m_panelCycle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_checkBoxLockAnkle = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Lock Ankle"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer1->Add( m_checkBoxLockAnkle, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer1->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Forces, Moments") ), wxVERTICAL );
	
	m_panelPlot = new PanelPlotSimple(this);
	sbSizer2->Add( m_panelPlot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxString m_choiceDisplayChoices[] = { _("Kneeline"), _("Force"), _("Moment"), _("Crossforce") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 0 );
	sbSizer2->Add( m_choiceDisplay, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer1->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	
	bSizer->Add( bSizer1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameWalkcycleSupport::OnCloseX ) );
	m_checkBoxLockAnkle->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrameWalkcycleSupport::OnToggleAnkleLock ), NULL, this );
	m_choiceDisplay->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameWalkcycleSupport::OnChoiceDisplay ), NULL, this );
}

GUIFrameWalkcycleSupport::~GUIFrameWalkcycleSupport()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameWalkcycleSupport::OnCloseX ) );
	m_checkBoxLockAnkle->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrameWalkcycleSupport::OnToggleAnkleLock ), NULL, this );
	m_choiceDisplay->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameWalkcycleSupport::OnChoiceDisplay ), NULL, this );
	
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
