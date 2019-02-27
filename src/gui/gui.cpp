///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../StdInclude.h"

#include "gui.h"

#include "../icons/FootMeasurements_small.xpm"
#include "../icons/LegMeasurements.xpm"

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
	wxMenuItem* m_menuItemQuickSetup;
	m_menuItemQuickSetup = new wxMenuItem( m_menuFoot, ID_QUICKSETUPMEASUREMENTS, wxString( _("Quick &Setup") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemQuickSetup );
	
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
	
	m_menuFootParameters = new wxMenu();
	wxMenuItem* m_menuFootParametersItem = new wxMenuItem( m_menuFoot, wxID_ANY, _("Foot &parameters"), wxEmptyString, wxITEM_NORMAL, m_menuFootParameters );
	wxMenuItem* m_menuItemFootModelBone;
	m_menuItemFootModelBone = new wxMenuItem( m_menuFootParameters, ID_USEFOOTMEASUREMENTS, wxString( _("from &measurements") ) , wxEmptyString, wxITEM_RADIO );
	m_menuFootParameters->Append( m_menuItemFootModelBone );
	m_menuItemFootModelBone->Check( true );
	
	wxMenuItem* m_menuItemFootModelScan;
	m_menuItemFootModelScan = new wxMenuItem( m_menuFootParameters, ID_USEFOOTSCAN, wxString( _("from &scan") ) , wxEmptyString, wxITEM_RADIO );
	m_menuFootParameters->Append( m_menuItemFootModelScan );
	
	m_menuFoot->Append( m_menuFootParametersItem );
	
	m_menuFootModel = new wxMenu();
	wxMenuItem* m_menuFootModelItem = new wxMenuItem( m_menuFoot, wxID_ANY, _("Foot &model"), wxEmptyString, wxITEM_NORMAL, m_menuFootModel );
	wxMenuItem* m_menuItemBoneBasedModel;
	m_menuItemBoneBasedModel = new wxMenuItem( m_menuFootModel, ID_USEBONEBASEDMODEL, wxString( _("Bone-based model") ) , wxEmptyString, wxITEM_RADIO );
	m_menuFootModel->Append( m_menuItemBoneBasedModel );
	m_menuItemBoneBasedModel->Check( true );
	
	wxMenuItem* m_menuItemUseLastBasedModel;
	m_menuItemUseLastBasedModel = new wxMenuItem( m_menuFootModel, ID_USELASTBASEDMODEL, wxString( _("Last-based model") ) , wxEmptyString, wxITEM_RADIO );
	m_menuFootModel->Append( m_menuItemUseLastBasedModel );
	
	m_menuFoot->Append( m_menuFootModelItem );
	
	m_menuFoot->AppendSeparator();
	
	wxMenuItem* m_menuItemFootModelLoadSTL;
	m_menuItemFootModelLoadSTL = new wxMenuItem( m_menuFoot, wxID_ANY, wxString( _("Load foot scan") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFoot->Append( m_menuItemFootModelLoadSTL );
	m_menuItemFootModelLoadSTL->Enable( false );
	
	m_menuBoneModel = new wxMenu();
	wxMenuItem* m_menuBoneModelItem = new wxMenuItem( m_menuFoot, wxID_ANY, _("&Foot bone model"), wxEmptyString, wxITEM_NORMAL, m_menuBoneModel );
	wxMenuItem* m_menuItemEditBoneModel;
	m_menuItemEditBoneModel = new wxMenuItem( m_menuBoneModel, ID_EDITBONEMODEL, wxString( _("&Edit bone model") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuBoneModel->Append( m_menuItemEditBoneModel );
	m_menuItemEditBoneModel->Enable( false );
	
	wxMenuItem* m_menuItemLoadBoneModel;
	m_menuItemLoadBoneModel = new wxMenuItem( m_menuBoneModel, ID_LOADFOOTMODEL, wxString( _("&Load bone model") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuBoneModel->Append( m_menuItemLoadBoneModel );
	
	wxMenuItem* m_menuItemSaveBoneModel;
	m_menuItemSaveBoneModel = new wxMenuItem( m_menuBoneModel, ID_SAVEFOOTMODEL, wxString( _("&Save bone model") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuBoneModel->Append( m_menuItemSaveBoneModel );
	
	m_menuFoot->Append( m_menuBoneModelItem );
	
	m_menubar->Append( m_menuFoot, _("F&oot") ); 
	
	m_menuLast = new wxMenu();
	wxMenuItem* m_menuItemLastLoadSTL;
	m_menuItemLastLoadSTL = new wxMenuItem( m_menuLast, wxID_ANY, wxString( _("Load Last from STL") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuLast->Append( m_menuItemLastLoadSTL );
	m_menuItemLastLoadSTL->Enable( false );
	
	m_menubar->Append( m_menuLast, _("&Last") ); 
	
	m_menuShoe = new wxMenu();
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
	
	wxMenuItem* m_menuItemShowSkin;
	m_menuItemShowSkin = new wxMenuItem( m_menuView, ID_SHOWSKIN, wxString( _("Show &Skin") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowSkin );
	
	wxMenuItem* m_menuItemShowLeg;
	m_menuItemShowLeg = new wxMenuItem( m_menuView, ID_SHOWLEG, wxString( _("Show L&eg") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowLeg );
	m_menuItemShowLeg->Enable( false );
	
	wxMenuItem* m_menuItemShowLast;
	m_menuItemShowLast = new wxMenuItem( m_menuView, ID_SHOWLAST, wxString( _("Show L&ast") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowLast );
	
	wxMenuItem* m_menuItemShowInsole;
	m_menuItemShowInsole = new wxMenuItem( m_menuView, ID_SHOWINSOLE, wxString( _("Show &Insole") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowInsole );
	
	wxMenuItem* m_menuIItemShowSole;
	m_menuIItemShowSole = new wxMenuItem( m_menuView, ID_SHOWSOLE, wxString( _("Show S&ole") ) , wxEmptyString, wxITEM_CHECK );
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
	
	wxMenuItem* m_menuItemShowCoordinateSystem;
	m_menuItemShowCoordinateSystem = new wxMenuItem( m_menuView, ID_SHOWCOORDINATESYSTEM, wxString( _("Show Coor&dinate System") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowCoordinateSystem );
	
	wxMenuItem* m_menuItemShowBackground;
	m_menuItemShowBackground = new wxMenuItem( m_menuView, ID_SHOWBACKGROUND, wxString( _("Show Back&ground") ) + wxT('\t') + wxT("CTRL+B"), wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_menuItemShowBackground );
	
	m_menuView->AppendSeparator();
	
	wxMenuItem* m_menuItemSetupBackground;
	m_menuItemSetupBackground = new wxMenuItem( m_menuView, wxID_ANY, wxString( _("Setup Background Images") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_menuItemSetupBackground );
	
	m_menubar->Append( m_menuView, _("&View") ); 
	
	m_menuPreferences = new wxMenu();
	m_menubar->Append( m_menuPreferences, _("P&references") ); 
	
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
	m_splitter->SetMinimumPaneSize( 300 );
	
	m_panelConfig = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerConfig;
	bSizerConfig = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( m_panelConfig, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelPageFoot = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerFoot;
	bSizerFoot = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerEditLeftRight;
	bSizerEditLeftRight = new wxBoxSizer( wxHORIZONTAL );
	
	m_toggleBtnEditLeft = new wxToggleButton( m_panelPageFoot, ID_EDITLEFT, _("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toggleBtnEditLeft->SetValue( true ); 
	bSizerEditLeftRight->Add( m_toggleBtnEditLeft, 1, wxALL, 5 );
	
	m_toggleBtnEditRight = new wxToggleButton( m_panelPageFoot, ID_EDITRIGHT, _("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toggleBtnEditRight->SetValue( true ); 
	bSizerEditLeftRight->Add( m_toggleBtnEditRight, 1, wxALL, 5 );
	
	
	bSizerFoot->Add( bSizerEditLeftRight, 0, wxEXPAND, 5 );
	
	m_choicebookMeasurement = new wxChoicebook( m_panelPageFoot, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_DEFAULT );
	m_panelMeasurementBased = new wxPanel( m_choicebookMeasurement, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerFootMeasurements;
	bSizerFootMeasurements = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerFootMeasurementsHorizontal;
	bSizerFootMeasurementsHorizontal = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerFootMeasurementsVertical;
	bSizerFootMeasurementsVertical = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizerFootMeasurements;
	fgSizerFootMeasurements = new wxFlexGridSizer( 8, 2, 0, 0 );
	fgSizerFootMeasurements->AddGrowableCol( 1 );
	fgSizerFootMeasurements->SetFlexibleDirection( wxHORIZONTAL );
	fgSizerFootMeasurements->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextFootLength = new wxStaticText( m_panelMeasurementBased, wxID_ANY, _("Foot length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFootLength->Wrap( -1 );
	fgSizerFootMeasurements->Add( m_staticTextFootLength, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlFootLength = new ExtendedTextCtrl( m_panelMeasurementBased, ID_MEASUREMENT_FOOTLENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlFootLength->SetToolTip( _("Length of the foot (not length of the last). Measured from the longest toe to the heel.") );
	
	fgSizerFootMeasurements->Add( m_textCtrlFootLength, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBallGirth = new wxStaticText( m_panelMeasurementBased, wxID_ANY, _("Ball girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBallGirth->Wrap( -1 );
	fgSizerFootMeasurements->Add( m_staticTextBallGirth, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlBallGirth = new ExtendedTextCtrl( m_panelMeasurementBased, ID_MEASUREMENT_BALLGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBallGirth->SetToolTip( _("Grith around the widest part at the ball of the foot.") );
	
	fgSizerFootMeasurements->Add( m_textCtrlBallGirth, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextWaistGirth = new wxStaticText( m_panelMeasurementBased, wxID_ANY, _("Waist girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextWaistGirth->Wrap( -1 );
	fgSizerFootMeasurements->Add( m_staticTextWaistGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlWaistGirth = new ExtendedTextCtrl( m_panelMeasurementBased, ID_MEASUREMENT_WAISTGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerFootMeasurements->Add( m_textCtrlWaistGirth, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextInsteGirth = new wxStaticText( m_panelMeasurementBased, wxID_ANY, _("Instep girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextInsteGirth->Wrap( -1 );
	fgSizerFootMeasurements->Add( m_staticTextInsteGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlInstepGirth = new ExtendedTextCtrl( m_panelMeasurementBased, ID_MEASUREMENT_INSTEPGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerFootMeasurements->Add( m_textCtrlInstepGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextLongHeelGirth = new wxStaticText( m_panelMeasurementBased, wxID_ANY, _("Long heel girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLongHeelGirth->Wrap( -1 );
	fgSizerFootMeasurements->Add( m_staticTextLongHeelGirth, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlLongHeelGirth = new ExtendedTextCtrl( m_panelMeasurementBased, ID_MEASUREMENT_LONGHEELGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerFootMeasurements->Add( m_textCtrlLongHeelGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextShortHeelGirth = new wxStaticText( m_panelMeasurementBased, wxID_ANY, _("Short heel girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShortHeelGirth->Wrap( -1 );
	fgSizerFootMeasurements->Add( m_staticTextShortHeelGirth, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShortHeelGirth = new ExtendedTextCtrl( m_panelMeasurementBased, ID_MEASUREMENT_SHORTHEELGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerFootMeasurements->Add( m_textCtrlShortHeelGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextAngleMixing = new wxStaticText( m_panelMeasurementBased, wxID_ANY, _("Angle Mixing:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextAngleMixing->Wrap( -1 );
	fgSizerFootMeasurements->Add( m_staticTextAngleMixing, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlAngleMixing = new ExtendedTextCtrl( m_panelMeasurementBased, ID_MEASUREMENT_ANGLEMIXING, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAngleMixing->SetToolTip( _("Mixing determines how much of the needed bending of the foot is done by the heel and how much is spread on the forefoot. 0% is all heel, 100% is all forefoot. 100% is impractical unless some serious misalignment of the foot is to be compensated.") );
	
	fgSizerFootMeasurements->Add( m_textCtrlAngleMixing, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextLegLengthDifference = new wxStaticText( m_panelMeasurementBased, wxID_ANY, _("Leg length difference:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLegLengthDifference->Wrap( -1 );
	fgSizerFootMeasurements->Add( m_staticTextLegLengthDifference, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlLegLengthDifference = new ExtendedTextCtrl( m_panelMeasurementBased, ID_MEASUREMENT_LEGLENGTHDIFFERENCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlLegLengthDifference->SetToolTip( _("Distance the right leg is longer than the left (positive number). If the right leg is shorter than the left leg the number has to be negative.") );
	
	fgSizerFootMeasurements->Add( m_textCtrlLegLengthDifference, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerFootMeasurementsVertical->Add( fgSizerFootMeasurements, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerFootMeasurementsHorizontal->Add( bSizerFootMeasurementsVertical, 0, 0, 5 );
	
	
	bSizerFootMeasurementsHorizontal->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerShoeSizes;
	bSizerShoeSizes = new wxBoxSizer( wxVERTICAL );
	
	m_buttonQuickSetup = new wxButton( m_panelMeasurementBased, ID_QUICKSETUPMEASUREMENTS, _("Quick Setup"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerShoeSizes->Add( m_buttonQuickSetup, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerShoeSizes;
	sbSizerShoeSizes = new wxStaticBoxSizer( new wxStaticBox( m_panelMeasurementBased, wxID_ANY, _("Shoesizes") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerShoeSizes;
	fgSizerShoeSizes = new wxFlexGridSizer( 6, 2, 0, 0 );
	fgSizerShoeSizes->AddGrowableCol( 1 );
	fgSizerShoeSizes->SetFlexibleDirection( wxHORIZONTAL );
	fgSizerShoeSizes->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextShoeSizeEU = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("EU:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeEU->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeEU, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShoeSizeEU = new ExtendedTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeEU->SetToolTip( _("Last length in Paris point") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeEU, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeUS = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("US:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeUS->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeUS, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeUS = new ExtendedTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeUS->SetToolTip( _("Brannock-Scale") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeUS, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeUK = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("UK:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeUK->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeUK, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeUK = new ExtendedTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeUK->SetToolTip( _("Last length in Barleycorns") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeUK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeCN = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("CN:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeCN->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeCN, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShoeSizeCN = new ExtendedTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeCN->SetToolTip( _("Foot length in cm") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeCN, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeJP = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("JP:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeJP->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeJP, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeJP = new ExtendedTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeJP->SetToolTip( _("Foot length in mm") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeJP, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextShoeSizeAU = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("AU:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeAU->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeAU, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeAU = new ExtendedTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeAU->SetToolTip( _("Last length in Barleycorns") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeAU, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	sbSizerShoeSizes->Add( fgSizerShoeSizes, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerShoeSizes->Add( sbSizerShoeSizes, 0, 0, 5 );
	
	
	bSizerFootMeasurementsHorizontal->Add( bSizerShoeSizes, 0, 0, 5 );
	
	
	bSizerFootMeasurementsHorizontal->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizerFootMeasurements->Add( bSizerFootMeasurementsHorizontal, 0, wxEXPAND, 5 );
	
	m_bitmapFoot = new wxStaticBitmap( m_panelMeasurementBased, ID_IMAGEFOOT, wxBitmap( FootMeasurements_small_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerFootMeasurements->Add( m_bitmapFoot, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelMeasurementBased->SetSizer( bSizerFootMeasurements );
	m_panelMeasurementBased->Layout();
	bSizerFootMeasurements->Fit( m_panelMeasurementBased );
	m_choicebookMeasurement->AddPage( m_panelMeasurementBased, _("Measurement based"), true );
	m_panelScanBased = new wxPanel( m_choicebookMeasurement, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerScanBasedModel;
	bSizerScanBasedModel = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextScanFile = new wxStaticText( m_panelScanBased, wxID_ANY, _("Scan file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextScanFile->Wrap( -1 );
	bSizerScanBasedModel->Add( m_staticTextScanFile, 0, wxALL, 5 );
	
	m_filePickerScanFile = new wxFilePickerCtrl( m_panelScanBased, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerScanBasedModel->Add( m_filePickerScanFile, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panelScanBased->SetSizer( bSizerScanBasedModel );
	m_panelScanBased->Layout();
	bSizerScanBasedModel->Fit( m_panelScanBased );
	m_choicebookMeasurement->AddPage( m_panelScanBased, _("Scan based"), false );
	bSizerFoot->Add( m_choicebookMeasurement, 1, wxEXPAND | wxALL, 5 );
	
	m_choicebookFootModel = new wxChoicebook( m_panelPageFoot, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCHB_DEFAULT );
	m_panelBoneBasedModel = new wxPanel( m_choicebookFootModel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerBoneBasedModel;
	bSizerBoneBasedModel = new wxBoxSizer( wxVERTICAL );
	
	m_buttonEditBoneModel = new wxButton( m_panelBoneBasedModel, ID_EDITBONEMODEL, _("Edit model"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerBoneBasedModel->Add( m_buttonEditBoneModel, 0, wxALL, 5 );
	
	
	m_panelBoneBasedModel->SetSizer( bSizerBoneBasedModel );
	m_panelBoneBasedModel->Layout();
	bSizerBoneBasedModel->Fit( m_panelBoneBasedModel );
	m_choicebookFootModel->AddPage( m_panelBoneBasedModel, _("Bone based model"), true );
	m_panelLastBasedModel = new wxPanel( m_choicebookFootModel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerLastBasedModel;
	bSizerLastBasedModel = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextLastModel = new wxStaticText( m_panelLastBasedModel, wxID_ANY, _("Last Model:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLastModel->Wrap( -1 );
	bSizerLastBasedModel->Add( m_staticTextLastModel, 0, wxALL, 5 );
	
	m_filePickerLastModel = new wxFilePickerCtrl( m_panelLastBasedModel, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerLastBasedModel->Add( m_filePickerLastModel, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panelLastBasedModel->SetSizer( bSizerLastBasedModel );
	m_panelLastBasedModel->Layout();
	bSizerLastBasedModel->Fit( m_panelLastBasedModel );
	m_choicebookFootModel->AddPage( m_panelLastBasedModel, _("Last based model"), false );
	bSizerFoot->Add( m_choicebookFootModel, 0, wxEXPAND | wxALL, 5 );
	
	
	m_panelPageFoot->SetSizer( bSizerFoot );
	m_panelPageFoot->Layout();
	bSizerFoot->Fit( m_panelPageFoot );
	m_notebook->AddPage( m_panelPageFoot, _("Foot"), true );
	m_panelPageLeg = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerLeg;
	bSizerLeg = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerLeftRight1;
	bSizerLeftRight1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_toggleBtnEditLeft1 = new wxToggleButton( m_panelPageLeg, ID_EDITLEFT, _("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toggleBtnEditLeft1->SetValue( true ); 
	bSizerLeftRight1->Add( m_toggleBtnEditLeft1, 1, wxALL, 5 );
	
	m_toggleBtnEditRight1 = new wxToggleButton( m_panelPageLeg, ID_EDITRIGHT, _("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toggleBtnEditRight1->SetValue( true ); 
	bSizerLeftRight1->Add( m_toggleBtnEditRight1, 1, wxALL, 5 );
	
	
	bSizerLeg->Add( bSizerLeftRight1, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerLegMeasurements;
	bSizerLegMeasurements = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmapLeg = new wxStaticBitmap( m_panelPageLeg, wxID_ANY, wxBitmap( LegMeasurements_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerLegMeasurements->Add( m_bitmapLeg, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerLegMeasurementsVertical;
	bSizerLegMeasurementsVertical = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizerLegMeasurements;
	fgSizerLegMeasurements = new wxFlexGridSizer( 9, 2, 0, 0 );
	fgSizerLegMeasurements->SetFlexibleDirection( wxBOTH );
	fgSizerLegMeasurements->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextGirth = new wxStaticText( m_panelPageLeg, wxID_ANY, _("Girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextGirth->Wrap( -1 );
	fgSizerLegMeasurements->Add( m_staticTextGirth, 0, wxALL, 5 );
	
	m_staticTextLevel = new wxStaticText( m_panelPageLeg, wxID_ANY, _("Level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLevel->Wrap( -1 );
	fgSizerLegMeasurements->Add( m_staticTextLevel, 0, wxALL, 5 );
	
	m_textCtrlBelowCrutchGirth = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_BELOWCRUTCHGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBelowCrutchGirth->SetToolTip( _("Below crutch girth") );
	
	fgSizerLegMeasurements->Add( m_textCtrlBelowCrutchGirth, 0, wxALL, 5 );
	
	m_textCtrlBelowCrutchLevel = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_BELOWCRUTCHLEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBelowCrutchLevel->SetToolTip( _("Below crutch level") );
	
	fgSizerLegMeasurements->Add( m_textCtrlBelowCrutchLevel, 0, wxALL, 5 );
	
	m_textCtrlMiddleOfCalfGirth = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_MIDDLEOFCALFGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMiddleOfCalfGirth->SetToolTip( _("Middle of calf girth") );
	
	fgSizerLegMeasurements->Add( m_textCtrlMiddleOfCalfGirth, 0, wxALL, 5 );
	
	m_textCtrlMiddleOfCalfLevel = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_MIDDLEOFCALFLEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMiddleOfCalfLevel->SetToolTip( _("Middle of calf level") );
	
	fgSizerLegMeasurements->Add( m_textCtrlMiddleOfCalfLevel, 0, wxALL, 5 );
	
	m_textCtrlAboveKneeGirth = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_ABOVEKNEEGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAboveKneeGirth->SetToolTip( _("Above knee girth") );
	
	fgSizerLegMeasurements->Add( m_textCtrlAboveKneeGirth, 0, wxALL, 5 );
	
	m_textCtrlAboveKneeLevel = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_ABOVEKNEELEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAboveKneeLevel->SetToolTip( _("Above knee level") );
	
	fgSizerLegMeasurements->Add( m_textCtrlAboveKneeLevel, 0, wxALL, 5 );
	
	m_textCtrlOverKneeCapGirth = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_OVERKNEECAPGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOverKneeCapGirth->SetToolTip( _("Over knee cap girth") );
	
	fgSizerLegMeasurements->Add( m_textCtrlOverKneeCapGirth, 0, wxALL, 5 );
	
	m_textCtrlOverKneeCapLevel = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_OVERKNEECAPLEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOverKneeCapLevel->SetToolTip( _("Over knee cap level") );
	
	fgSizerLegMeasurements->Add( m_textCtrlOverKneeCapLevel, 0, wxALL, 5 );
	
	m_textCtrlBelowKneeGirth = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_BELOWKNEEGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBelowKneeGirth->SetToolTip( _("Below knee girth") );
	
	fgSizerLegMeasurements->Add( m_textCtrlBelowKneeGirth, 0, wxALL, 5 );
	
	m_textCtrlBelowKneeLevel = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_BELOWKNEELEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBelowKneeLevel->SetToolTip( _("Below knee level") );
	
	fgSizerLegMeasurements->Add( m_textCtrlBelowKneeLevel, 0, wxALL, 5 );
	
	m_textCtrlMiddleOfShankGirth = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_MIDDLEOFSHANKGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMiddleOfShankGirth->SetToolTip( _("Middle of shank girth") );
	
	fgSizerLegMeasurements->Add( m_textCtrlMiddleOfShankGirth, 0, wxALL, 5 );
	
	m_textCtrlMiddleOfShankLevel = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_MIDDLEOFSHANKLEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMiddleOfShankLevel->SetToolTip( _("Middle of shank level") );
	
	fgSizerLegMeasurements->Add( m_textCtrlMiddleOfShankLevel, 0, wxALL, 5 );
	
	m_textCtrlAboveAnkleGirth = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_ABOVEANKLEGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAboveAnkleGirth->SetToolTip( _("Above ankle girth") );
	
	fgSizerLegMeasurements->Add( m_textCtrlAboveAnkleGirth, 0, wxALL, 5 );
	
	m_textCtrlAboveAnkleLevel = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_ABOVEANKLELEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAboveAnkleLevel->SetToolTip( _("Above ankle level") );
	
	fgSizerLegMeasurements->Add( m_textCtrlAboveAnkleLevel, 0, wxALL, 5 );
	
	m_textCtrlOverAnkleBoneGirth = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_OVERANKLEBONEGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOverAnkleBoneGirth->SetToolTip( _("Over ankle bone girth") );
	
	fgSizerLegMeasurements->Add( m_textCtrlOverAnkleBoneGirth, 0, wxALL, 5 );
	
	m_textCtrlOverAnkleBoneLevel = new ExtendedTextCtrl( m_panelPageLeg, ID_MEASUREMENT_OVERANKLEBONELEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOverAnkleBoneLevel->SetToolTip( _("Over ankle bone level") );
	
	fgSizerLegMeasurements->Add( m_textCtrlOverAnkleBoneLevel, 0, wxALL, 5 );
	
	
	bSizerLegMeasurementsVertical->Add( fgSizerLegMeasurements, 0, 0, 5 );
	
	
	bSizerLegMeasurements->Add( bSizerLegMeasurementsVertical, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerLeg->Add( bSizerLegMeasurements, 0, wxEXPAND, 5 );
	
	
	m_panelPageLeg->SetSizer( bSizerLeg );
	m_panelPageLeg->Layout();
	bSizerLeg->Fit( m_panelPageLeg );
	m_notebook->AddPage( m_panelPageLeg, _("Leg"), false );
	m_panelPageShoe = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerShoe;
	bSizerShoe = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerPresetType;
	sbSizerPresetType = new wxStaticBoxSizer( new wxStaticBox( m_panelPageShoe, wxID_ANY, _("Preset") ), wxVERTICAL );
	
	wxArrayString m_choiceShoeTypeChoices;
	m_choiceShoeType = new wxChoice( sbSizerPresetType->GetStaticBox(), ID_PRESETSHOETYPE, wxDefaultPosition, wxDefaultSize, m_choiceShoeTypeChoices, 0 );
	m_choiceShoeType->SetSelection( 0 );
	sbSizerPresetType->Add( m_choiceShoeType, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizerShoe->Add( sbSizerPresetType, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizerShoeBaseMeasurements;
	fgSizerShoeBaseMeasurements = new wxFlexGridSizer( 4, 2, 0, 0 );
	fgSizerShoeBaseMeasurements->AddGrowableCol( 1 );
	fgSizerShoeBaseMeasurements->SetFlexibleDirection( wxBOTH );
	fgSizerShoeBaseMeasurements->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextHeelHeight = new wxStaticText( m_panelPageShoe, wxID_ANY, _("Heel Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHeelHeight->Wrap( -1 );
	fgSizerShoeBaseMeasurements->Add( m_staticTextHeelHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlHeelHeight = new ExtendedTextCtrl( m_panelPageShoe, ID_HEELHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerShoeBaseMeasurements->Add( m_textCtrlHeelHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticTextBallHeight = new wxStaticText( m_panelPageShoe, wxID_ANY, _("Ball Height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBallHeight->Wrap( -1 );
	fgSizerShoeBaseMeasurements->Add( m_staticTextBallHeight, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlBallHeight = new ExtendedTextCtrl( m_panelPageShoe, ID_BALLHEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerShoeBaseMeasurements->Add( m_textCtrlBallHeight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextHeelPitch = new wxStaticText( m_panelPageShoe, wxID_ANY, _("Heel Pitch:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextHeelPitch->Wrap( -1 );
	fgSizerShoeBaseMeasurements->Add( m_staticTextHeelPitch, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlHeelPitch = new ExtendedTextCtrl( m_panelPageShoe, ID_HEELPITCH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerShoeBaseMeasurements->Add( m_textCtrlHeelPitch, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticTextToeSpring = new wxStaticText( m_panelPageShoe, wxID_ANY, _("Toe Spring:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextToeSpring->Wrap( -1 );
	fgSizerShoeBaseMeasurements->Add( m_staticTextToeSpring, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlToeSpring = new ExtendedTextCtrl( m_panelPageShoe, ID_TOESPRING, _("10 deg"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerShoeBaseMeasurements->Add( m_textCtrlToeSpring, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	bSizerShoe->Add( fgSizerShoeBaseMeasurements, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerShoeHeight;
	sbSizerShoeHeight = new wxStaticBoxSizer( new wxStaticBox( m_panelPageShoe, wxID_ANY, _("Preset") ), wxVERTICAL );
	
	wxArrayString m_choiceShoeHeightChoices;
	m_choiceShoeHeight = new wxChoice( sbSizerShoeHeight->GetStaticBox(), ID_PRESETSHOEHEIGHT, wxDefaultPosition, wxDefaultSize, m_choiceShoeHeightChoices, 0 );
	m_choiceShoeHeight->SetSelection( 1 );
	sbSizerShoeHeight->Add( m_choiceShoeHeight, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizerShoe->Add( sbSizerShoeHeight, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizerUpperLevel;
	fgSizerUpperLevel = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizerUpperLevel->SetFlexibleDirection( wxBOTH );
	fgSizerUpperLevel->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextUpperLevel = new wxStaticText( m_panelPageShoe, wxID_ANY, _("Upper level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextUpperLevel->Wrap( -1 );
	fgSizerUpperLevel->Add( m_staticTextUpperLevel, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlUpperLevel = new ExtendedTextCtrl( m_panelPageShoe, ID_UPPERLEVEL, _("0.8"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerUpperLevel->Add( m_textCtrlUpperLevel, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerShoe->Add( fgSizerUpperLevel, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerLastForm;
	sbSizerLastForm = new wxStaticBoxSizer( new wxStaticBox( m_panelPageShoe, wxID_ANY, _("Lastform") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer6->AddGrowableCol( 1 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextTipSymmetry = new wxStaticText( sbSizerLastForm->GetStaticBox(), wxID_ANY, _("Tip symetry:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTipSymmetry->Wrap( -1 );
	fgSizer6->Add( m_staticTextTipSymmetry, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_sliderSymmetry = new wxSlider( sbSizerLastForm->GetStaticBox(), ID_TIPSYMMETRY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	fgSizer6->Add( m_sliderSymmetry, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextTipPointedness = new wxStaticText( sbSizerLastForm->GetStaticBox(), wxID_ANY, _("Tip pointedness:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTipPointedness->Wrap( -1 );
	fgSizer6->Add( m_staticTextTipPointedness, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_sliderTipPointedness = new wxSlider( sbSizerLastForm->GetStaticBox(), ID_TIPPOINTEDNESS, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	fgSizer6->Add( m_sliderTipPointedness, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextTipSharpness = new wxStaticText( sbSizerLastForm->GetStaticBox(), wxID_ANY, _("Tip sharpness:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextTipSharpness->Wrap( -1 );
	fgSizer6->Add( m_staticTextTipSharpness, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_sliderTipSharpness = new wxSlider( sbSizerLastForm->GetStaticBox(), ID_TIPSHARPNESS, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	fgSizer6->Add( m_sliderTipSharpness, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextExtraLength = new wxStaticText( sbSizerLastForm->GetStaticBox(), wxID_ANY, _("Extra length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextExtraLength->Wrap( -1 );
	fgSizer6->Add( m_staticTextExtraLength, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlExtraLength = new ExtendedTextCtrl( sbSizerLastForm->GetStaticBox(), ID_EXTRALENGTH, _("2 cm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlExtraLength->SetToolTip( _("Difference between foot-length and last-length. To make a shoe walkable, this should be at least 2 cm  (Standard value used in the shoe industry).") );
	
	fgSizer6->Add( m_textCtrlExtraLength, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextFootCompression = new wxStaticText( sbSizerLastForm->GetStaticBox(), wxID_ANY, _("Foot compression:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFootCompression->Wrap( -1 );
	fgSizer6->Add( m_staticTextFootCompression, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlFootCompression = new ExtendedTextCtrl( sbSizerLastForm->GetStaticBox(), ID_FOOTCOMPRESSION, _("5 %"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlFootCompression->SetToolTip( _("Pressure from the sides of the shoe onto the foot. Higher values give a tighter fit of the shoe. This is needed for example with high heels to prevent the foot from slipping around in the shoe. Set to 0 % for diabetic footwear.") );
	
	fgSizer6->Add( m_textCtrlFootCompression, 0, wxALL|wxEXPAND, 5 );
	
	
	sbSizerLastForm->Add( fgSizer6, 1, wxEXPAND, 5 );
	
	
	bSizerShoe->Add( sbSizerLastForm, 0, wxEXPAND, 5 );
	
	
	m_panelPageShoe->SetSizer( bSizerShoe );
	m_panelPageShoe->Layout();
	bSizerShoe->Fit( m_panelPageShoe );
	m_notebook->AddPage( m_panelPageShoe, _("Shoe"), false );
	m_panelPageSole = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	m_checkBoxSeparatedHeel = new wxCheckBox( m_panelPageSole, ID_CHECKSEPARATEDHEEL, _("Separated heel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( m_checkBoxSeparatedHeel, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerFormHeel;
	sbSizerFormHeel = new wxStaticBoxSizer( new wxStaticBox( m_panelPageSole, wxID_ANY, _("Heel") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerFormHeel;
	fgSizerFormHeel = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerFormHeel->AddGrowableCol( 1 );
	fgSizerFormHeel->SetFlexibleDirection( wxBOTH );
	fgSizerFormHeel->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText29 = new wxStaticText( sbSizerFormHeel->GetStaticBox(), wxID_ANY, _("Level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizerFormHeel->Add( m_staticText29, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrl29 = new ExtendedTextCtrl( sbSizerFormHeel->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerFormHeel->Add( m_textCtrl29, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText30 = new wxStaticText( sbSizerFormHeel->GetStaticBox(), wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizerFormHeel->Add( m_staticText30, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl31 = new ExtendedTextCtrl( sbSizerFormHeel->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerFormHeel->Add( m_textCtrl31, 0, wxALL|wxEXPAND, 5 );
	
	
	sbSizerFormHeel->Add( fgSizerFormHeel, 0, wxEXPAND, 5 );
	
	
	bSizer28->Add( sbSizerFormHeel, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerFormPlateau;
	sbSizerFormPlateau = new wxStaticBoxSizer( new wxStaticBox( m_panelPageSole, wxID_ANY, _("Platform") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerFormPlateau;
	fgSizerFormPlateau = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizerFormPlateau->AddGrowableCol( 1 );
	fgSizerFormPlateau->SetFlexibleDirection( wxBOTH );
	fgSizerFormPlateau->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText31 = new wxStaticText( sbSizerFormPlateau->GetStaticBox(), wxID_ANY, _("Level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizerFormPlateau->Add( m_staticText31, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl35 = new ExtendedTextCtrl( sbSizerFormPlateau->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerFormPlateau->Add( m_textCtrl35, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText32 = new wxStaticText( sbSizerFormPlateau->GetStaticBox(), wxID_ANY, _("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizerFormPlateau->Add( m_staticText32, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrl33 = new ExtendedTextCtrl( sbSizerFormPlateau->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerFormPlateau->Add( m_textCtrl33, 0, wxALL|wxEXPAND, 5 );
	
	
	sbSizerFormPlateau->Add( fgSizerFormPlateau, 0, wxEXPAND, 5 );
	
	
	bSizer28->Add( sbSizerFormPlateau, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panelPageSole, wxID_ANY, _("Walkcycle Support Heel") ), wxVERTICAL );
	
	m_sliderSupportHeelRadius = new wxSlider( sbSizer8->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer8->Add( m_sliderSupportHeelRadius, 0, wxALL|wxEXPAND, 5 );
	
	m_sliderSupportHeelOffset = new wxSlider( sbSizer8->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer8->Add( m_sliderSupportHeelOffset, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer28->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( m_panelPageSole, wxID_ANY, _("Walkcycle Support Toe") ), wxVERTICAL );
	
	m_sliderSupportToeRadius = new wxSlider( sbSizer9->GetStaticBox(), ID_SLIDERTOESUPPORTRADIUS, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer9->Add( m_sliderSupportToeRadius, 0, wxALL|wxEXPAND, 5 );
	
	m_sliderSupportToeOffset = new wxSlider( sbSizer9->GetStaticBox(), ID_SLIDERTOESUPPORTOFFSET, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer9->Add( m_sliderSupportToeOffset, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer28->Add( sbSizer9, 0, wxEXPAND, 5 );
	
	
	m_panelPageSole->SetSizer( bSizer28 );
	m_panelPageSole->Layout();
	bSizer28->Fit( m_panelPageSole );
	m_notebook->AddPage( m_panelPageSole, _("Sole"), false );
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
	
	m_button11 = new wxButton( m_panelPagePattern, wxID_ANY, _("Add Stitching"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_button11, 0, wxALL|wxEXPAND, 5 );
	
	m_button141 = new wxButton( m_panelPagePattern, wxID_ANY, _("Add Padding"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_button141, 0, wxALL|wxEXPAND, 5 );
	
	m_button10 = new wxButton( m_panelPagePattern, wxID_ANY, _("Add Coordinate System"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_button10, 0, wxALL|wxEXPAND, 5 );
	
	m_button12 = new wxButton( m_panelPagePattern, wxID_ANY, _("Add Laces"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_button12, 0, wxALL|wxEXPAND, 5 );
	
	m_button13 = new wxButton( m_panelPagePattern, wxID_ANY, _("Add Accessory"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer23->Add( m_button13, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panelPagePattern, wxID_ANY, _("Fabrics") ), wxVERTICAL );
	
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
	
	wxBoxSizer* bSizerCheckRounding;
	bSizerCheckRounding = new wxBoxSizer( wxHORIZONTAL );
	
	m_panelSupport = new PanelSupport(m_panelCheck);
	bSizerCheckRounding->Add( m_panelSupport, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerSupport;
	bSizerSupport = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizerCycle;
	sbSizerCycle = new wxStaticBoxSizer( new wxStaticBox( m_panelCheck, wxID_ANY, _("Walkcycle") ), wxVERTICAL );
	
	m_panelCycle = new PanelWalkcycle(m_panelCheck);
	sbSizerCycle->Add( m_panelCycle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_checkBoxLockAnkle = new wxCheckBox( sbSizerCycle->GetStaticBox(), wxID_ANY, _("Lock Ankle"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerCycle->Add( m_checkBoxLockAnkle, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizerSupport->Add( sbSizerCycle, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerPlot;
	sbSizerPlot = new wxStaticBoxSizer( new wxStaticBox( m_panelCheck, wxID_ANY, _("Forces, Moments") ), wxVERTICAL );
	
	wxString m_choiceDisplayChoices[] = { _("Kneeline"), _("Force"), _("Moment"), _("Crossforce") };
	int m_choiceDisplayNChoices = sizeof( m_choiceDisplayChoices ) / sizeof( wxString );
	m_choiceDisplay = new wxChoice( sbSizerPlot->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceDisplayNChoices, m_choiceDisplayChoices, 0 );
	m_choiceDisplay->SetSelection( 0 );
	sbSizerPlot->Add( m_choiceDisplay, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_panelPlot = new PanelPlotSimple(m_panelCheck);
	sbSizerPlot->Add( m_panelPlot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	bSizerSupport->Add( sbSizerPlot, 1, wxEXPAND, 5 );
	
	
	bSizerCheckRounding->Add( bSizerSupport, 0, wxEXPAND, 5 );
	
	
	m_panelCheck->SetSizer( bSizerCheckRounding );
	m_panelCheck->Layout();
	bSizerCheckRounding->Fit( m_panelCheck );
	bSizerCanvas->Add( m_panelCheck, 1, wxEXPAND | wxALL, 5 );
	
	
	m_panelCanvas->SetSizer( bSizerCanvas );
	m_panelCanvas->Layout();
	bSizerCanvas->Fit( m_panelCanvas );
	m_splitter->SplitVertically( m_panelConfig, m_panelCanvas, 500 );
	bSizer->Add( m_splitter, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameMain::OnClose ) );
	this->Connect( m_menuItemQuickSetup->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnQuickSetupMeasurements ) );
	this->Connect( m_menuItemFullSymmetry->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Connect( m_menuItemSymmetricModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Connect( m_menuItemIndividualModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Connect( m_menuItemFootCopyLeftToRight->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnCopyMeasurements ) );
	this->Connect( m_menuItemFootCopyRightToLeft->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnCopyMeasurements ) );
	this->Connect( m_menuItemFootModelBone->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChangeModel ) );
	this->Connect( m_menuItemFootModelScan->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChangeModel ) );
	this->Connect( m_menuItemBoneBasedModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChangeModel ) );
	this->Connect( m_menuItemUseLastBasedModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChangeModel ) );
	this->Connect( m_menuItemFootModelLoadSTL->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadFootSTL ) );
	this->Connect( m_menuItemEditBoneModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditBoneModel ) );
	this->Connect( m_menuItemLoadBoneModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadBoneModel ) );
	this->Connect( m_menuItemSaveBoneModel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveBoneModel ) );
	this->Connect( m_menuItemTestGenerator->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionClassic->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionCemented->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionMolded->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Connect( m_menuItemConstructionDutch->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
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
	this->Connect( m_menuItemShowSkin->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowLeg->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowLast->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowInsole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuIItemShowSole->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowUpper->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowCutaway->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowFloor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowCoordinateSystem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemShowBackground->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Connect( m_menuItemSetupBackground->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupBackgroundImages ) );
	this->Connect( m_menuItemdebugParser->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnDebugParser ) );
	m_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( GUIFrameMain::OnPageChange ), NULL, this );
	m_panelPageFoot->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_toggleBtnEditLeft->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleButton ), NULL, this );
	m_toggleBtnEditRight->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleButton ), NULL, this );
	m_textCtrlFootLength->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlFootLength->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlFootLength->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlFootLength->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBallGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBallGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBallGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBallGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlWaistGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlWaistGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlWaistGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlWaistGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlInstepGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlInstepGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlInstepGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlInstepGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlLongHeelGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlLongHeelGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlLongHeelGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlLongHeelGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlShortHeelGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlShortHeelGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlShortHeelGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlShortHeelGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAngleMixing->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAngleMixing->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAngleMixing->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAngleMixing->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlLegLengthDifference->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlLegLengthDifference->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlLegLengthDifference->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlLegLengthDifference->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_buttonQuickSetup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnQuickSetupMeasurements ), NULL, this );
	m_bitmapFoot->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIFrameMain::OnSize ), NULL, this );
	m_filePickerScanFile->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( GUIFrameMain::OnFileChangedScanFile ), NULL, this );
	m_buttonEditBoneModel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnEditBoneModel ), NULL, this );
	m_filePickerLastModel->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( GUIFrameMain::OnFileChangedLastFile ), NULL, this );
	m_toggleBtnEditLeft1->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleButton ), NULL, this );
	m_toggleBtnEditRight1->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleButton ), NULL, this );
	m_textCtrlBelowCrutchGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBelowCrutchGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBelowCrutchGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBelowCrutchGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBelowCrutchLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBelowCrutchLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBelowCrutchLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBelowCrutchLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAboveKneeGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAboveKneeGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAboveKneeGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAboveKneeGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAboveKneeLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAboveKneeLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAboveKneeLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAboveKneeLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlOverKneeCapGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlOverKneeCapGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlOverKneeCapGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlOverKneeCapGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlOverKneeCapLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlOverKneeCapLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlOverKneeCapLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlOverKneeCapLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBelowKneeGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBelowKneeGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBelowKneeGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBelowKneeGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBelowKneeLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBelowKneeLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBelowKneeLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBelowKneeLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAboveAnkleGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAboveAnkleGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAboveAnkleGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAboveAnkleGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAboveAnkleLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAboveAnkleLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAboveAnkleLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAboveAnkleLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_choiceShoeType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChoice ), NULL, this );
	m_textCtrlHeelHeight->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlHeelHeight->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlHeelHeight->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlHeelHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBallHeight->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBallHeight->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBallHeight->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBallHeight->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlHeelPitch->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlHeelPitch->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlHeelPitch->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlHeelPitch->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlToeSpring->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlToeSpring->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlToeSpring->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlToeSpring->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_choiceShoeHeight->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChoice ), NULL, this );
	m_textCtrlUpperLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlUpperLevel->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlUpperLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlUpperLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlExtraLength->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlExtraLength->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlExtraLength->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlExtraLength->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlFootCompression->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlFootCompression->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlFootCompression->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlFootCompression->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_checkBoxSeparatedHeel->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrameMain::OnCheckBox ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_checkBoxLockAnkle->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleAnkleLock ), NULL, this );
	m_choiceDisplay->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChoiceDisplay ), NULL, this );
}

GUIFrameMain::~GUIFrameMain()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrameMain::OnClose ) );
	this->Disconnect( ID_QUICKSETUPMEASUREMENTS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnQuickSetupMeasurements ) );
	this->Disconnect( ID_FULLSYMMETRY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Disconnect( ID_SYMMETRICMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Disconnect( ID_INDIVIDUALMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetSymmetry ) );
	this->Disconnect( ID_COPYLEFTTORIGHT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnCopyMeasurements ) );
	this->Disconnect( ID_COPYRIGHTTOLEFT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnCopyMeasurements ) );
	this->Disconnect( ID_USEFOOTMEASUREMENTS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChangeModel ) );
	this->Disconnect( ID_USEFOOTSCAN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChangeModel ) );
	this->Disconnect( ID_USEBONEBASEDMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChangeModel ) );
	this->Disconnect( ID_USELASTBASEDMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChangeModel ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadFootSTL ) );
	this->Disconnect( ID_EDITBONEMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnEditBoneModel ) );
	this->Disconnect( ID_LOADFOOTMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnLoadBoneModel ) );
	this->Disconnect( ID_SAVEFOOTMODEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSaveBoneModel ) );
	this->Disconnect( ID_CONSTRUCTIONEXPERIMENTAL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONWELDED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONCEMENTED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONMOLDED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
	this->Disconnect( ID_CONSTRUCTIONDUTCH, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnConstructionSelection ) );
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
	this->Disconnect( ID_SHOWSKIN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWLEG, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWLAST, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWINSOLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWSOLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWUPPER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWCUTAWAY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWFLOOR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWCOORDINATESYSTEM, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( ID_SHOWBACKGROUND, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnViewChange ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnSetupBackgroundImages ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrameMain::OnDebugParser ) );
	m_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( GUIFrameMain::OnPageChange ), NULL, this );
	m_panelPageFoot->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_toggleBtnEditLeft->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleButton ), NULL, this );
	m_toggleBtnEditRight->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleButton ), NULL, this );
	m_textCtrlFootLength->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlFootLength->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlFootLength->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlFootLength->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBallGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBallGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBallGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBallGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlWaistGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlWaistGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlWaistGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlWaistGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlInstepGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlInstepGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlInstepGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlInstepGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlLongHeelGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlLongHeelGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlLongHeelGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlLongHeelGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlShortHeelGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlShortHeelGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlShortHeelGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlShortHeelGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAngleMixing->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAngleMixing->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAngleMixing->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAngleMixing->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlLegLengthDifference->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlLegLengthDifference->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlLegLengthDifference->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlLegLengthDifference->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_buttonQuickSetup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnQuickSetupMeasurements ), NULL, this );
	m_bitmapFoot->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrameMain::OnSize ), NULL, this );
	m_filePickerScanFile->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( GUIFrameMain::OnFileChangedScanFile ), NULL, this );
	m_buttonEditBoneModel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnEditBoneModel ), NULL, this );
	m_filePickerLastModel->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( GUIFrameMain::OnFileChangedLastFile ), NULL, this );
	m_toggleBtnEditLeft1->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleButton ), NULL, this );
	m_toggleBtnEditRight1->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleButton ), NULL, this );
	m_textCtrlBelowCrutchGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBelowCrutchGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBelowCrutchGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBelowCrutchGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBelowCrutchLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBelowCrutchLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBelowCrutchLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBelowCrutchLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAboveKneeGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAboveKneeGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAboveKneeGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAboveKneeGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAboveKneeLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAboveKneeLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAboveKneeLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAboveKneeLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlOverKneeCapGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlOverKneeCapGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlOverKneeCapGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlOverKneeCapGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlOverKneeCapLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlOverKneeCapLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlOverKneeCapLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlOverKneeCapLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBelowKneeGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBelowKneeGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBelowKneeGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBelowKneeGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBelowKneeLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBelowKneeLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBelowKneeLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBelowKneeLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAboveAnkleGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAboveAnkleGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAboveAnkleGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAboveAnkleGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlAboveAnkleLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlAboveAnkleLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlAboveAnkleLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlAboveAnkleLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_choiceShoeType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChoice ), NULL, this );
	m_textCtrlHeelHeight->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlHeelHeight->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlHeelHeight->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlHeelHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlBallHeight->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlBallHeight->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlBallHeight->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlBallHeight->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlHeelPitch->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlHeelPitch->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlHeelPitch->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlHeelPitch->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlToeSpring->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlToeSpring->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlToeSpring->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlToeSpring->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_choiceShoeHeight->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChoice ), NULL, this );
	m_textCtrlUpperLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlUpperLevel->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlUpperLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlUpperLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlExtraLength->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlExtraLength->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlExtraLength->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlExtraLength->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_textCtrlFootCompression->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIFrameMain::OnKillFocus ), NULL, this );
	m_textCtrlFootCompression->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( GUIFrameMain::OnMouseWheel ), NULL, this );
	m_textCtrlFootCompression->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIFrameMain::OnSetFocus ), NULL, this );
	m_textCtrlFootCompression->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameMain::OnTextEnter ), NULL, this );
	m_checkBoxSeparatedHeel->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrameMain::OnCheckBox ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelRadius->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportHeelOffset->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeRadius->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_sliderSupportToeOffset->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameMain::OnScroll ), NULL, this );
	m_checkBoxLockAnkle->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrameMain::OnToggleAnkleLock ), NULL, this );
	m_choiceDisplay->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrameMain::OnChoiceDisplay ), NULL, this );
	
}

GUIFrameBoneModel::GUIFrameBoneModel( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_MULTILINE );
	m_panelBone = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerLength;
	bSizerLength = new wxBoxSizer( wxVERTICAL );
	
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
	bSizerLength->Add( m_gridBoneLength, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelBone->SetSizer( bSizerLength );
	m_panelBone->Layout();
	bSizerLength->Fit( m_panelBone );
	m_notebook->AddPage( m_panelBone, _("Bone Length"), true );
	m_panelBoneDiameter = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerDiameter;
	bSizerDiameter = new wxBoxSizer( wxVERTICAL );
	
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
	bSizerDiameter->Add( m_gridBoneDiameter, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panelBoneDiameter->SetSizer( bSizerDiameter );
	m_panelBoneDiameter->Layout();
	bSizerDiameter->Fit( m_panelBoneDiameter );
	m_notebook->AddPage( m_panelBoneDiameter, _("Bone Diameter"), false );
	m_panelSkinThickness = new wxPanel( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerSkinThickness;
	bSizerSkinThickness = new wxBoxSizer( wxVERTICAL );
	
	m_gridSkinThickness = new wxGrid( m_panelSkinThickness, ID_GRIDSKIN, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridSkinThickness->CreateGrid( 0, 4 );
	m_gridSkinThickness->EnableEditing( true );
	m_gridSkinThickness->EnableGridLines( true );
	m_gridSkinThickness->EnableDragGridSize( false );
	m_gridSkinThickness->SetMargins( 0, 0 );
	
	// Columns
	m_gridSkinThickness->SetColSize( 0, 100 );
	m_gridSkinThickness->SetColSize( 1, 100 );
	m_gridSkinThickness->SetColSize( 2, 100 );
	m_gridSkinThickness->SetColSize( 3, 100 );
	m_gridSkinThickness->EnableDragColMove( false );
	m_gridSkinThickness->EnableDragColSize( true );
	m_gridSkinThickness->SetColLabelSize( 30 );
	m_gridSkinThickness->SetColLabelValue( 0, _("s1 (Formula)") );
	m_gridSkinThickness->SetColLabelValue( 1, _("s1 (Value)") );
	m_gridSkinThickness->SetColLabelValue( 2, _("s2 (Formula)") );
	m_gridSkinThickness->SetColLabelValue( 3, _("s2 (Value)") );
	m_gridSkinThickness->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridSkinThickness->EnableDragRowSize( true );
	m_gridSkinThickness->SetRowLabelSize( 100 );
	m_gridSkinThickness->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridSkinThickness->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizerSkinThickness->Add( m_gridSkinThickness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	m_panelSkinThickness->SetSizer( bSizerSkinThickness );
	m_panelSkinThickness->Layout();
	bSizerSkinThickness->Fit( m_panelSkinThickness );
	m_notebook->AddPage( m_panelSkinThickness, _("Skin Thickness"), false );
	
	bSizer->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer );
	this->Layout();
	m_menubar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItemReset;
	m_menuItemReset = new wxMenuItem( m_menuFile, wxID_NEW, wxString( _("&Reset") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemReset );
	
	wxMenuItem* m_menuItemLoad;
	m_menuItemLoad = new wxMenuItem( m_menuFile, wxID_OPEN, wxString( _("&Load ...") ) + wxT('\t') + wxT("Ctrl+L"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemLoad );
	
	wxMenuItem* m_menuItemSave;
	m_menuItemSave = new wxMenuItem( m_menuFile, wxID_SAVE, wxString( _("&Save") ) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemSave );
	
	wxMenuItem* m_menuItemSaveAs;
	m_menuItemSaveAs = new wxMenuItem( m_menuFile, wxID_SAVEAS, wxString( _("Save &as ...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemSaveAs );
	
	m_menuFile->AppendSeparator();
	
	wxMenuItem* m_menuItemClose;
	m_menuItemClose = new wxMenuItem( m_menuFile, wxID_CLOSE, wxString( _("&Close Window") ) + wxT('\t') + wxT("Ctrl+W"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemClose );
	
	m_menubar->Append( m_menuFile, _("&File") ); 
	
	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItemHelp;
	m_menuItemHelp = new wxMenuItem( m_menuHelp, wxID_HELP, wxString( _("&Help") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItemHelp );
	
	m_menubar->Append( m_menuHelp, _("&Help") ); 
	
	this->SetMenuBar( m_menubar );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_gridBoneLength->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameBoneModel::OnCellChange ), NULL, this );
	m_gridBoneDiameter->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameBoneModel::OnCellChange ), NULL, this );
	m_gridSkinThickness->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameBoneModel::OnCellChange ), NULL, this );
}

GUIFrameBoneModel::~GUIFrameBoneModel()
{
	// Disconnect Events
	m_gridBoneLength->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameBoneModel::OnCellChange ), NULL, this );
	m_gridBoneDiameter->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameBoneModel::OnCellChange ), NULL, this );
	m_gridSkinThickness->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( GUIFrameBoneModel::OnCellChange ), NULL, this );
	
}

GUIDialogQuickInitFoot::GUIDialogQuickInitFoot( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerSize;
	bSizerSize = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextShoeSize = new wxStaticText( this, wxID_ANY, _("Shoesize:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSize->Wrap( -1 );
	bSizerSize->Add( m_staticTextShoeSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSize = new ExtendedTextCtrl( this, wxID_ANY, _("39"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RIGHT );
	bSizerSize->Add( m_textCtrlShoeSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString m_choiceUnitChoices[] = { _("EU"), _("US"), _("CN"), _("UK"), _("JP"), _("AU"), _("mm"), _("cm"), _("in"), _("ft") };
	int m_choiceUnitNChoices = sizeof( m_choiceUnitChoices ) / sizeof( wxString );
	m_choiceUnit = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceUnitNChoices, m_choiceUnitChoices, 0 );
	m_choiceUnit->SetSelection( 0 );
	bSizerSize->Add( m_choiceUnit, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerMain->Add( bSizerSize, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizerWidth;
	bSizerWidth = new wxBoxSizer( wxHORIZONTAL );
	
	m_radioBtnSmall = new wxRadioButton( this, wxID_ANY, _("small"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	bSizerWidth->Add( m_radioBtnSmall, 0, wxALL, 5 );
	
	m_radioBtnMedium = new wxRadioButton( this, wxID_ANY, _("medium"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtnMedium->SetValue( true ); 
	bSizerWidth->Add( m_radioBtnMedium, 0, wxALL, 5 );
	
	m_radioBtnWide = new wxRadioButton( this, wxID_ANY, _("wide"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerWidth->Add( m_radioBtnWide, 0, wxALL, 5 );
	
	
	bSizerMain->Add( bSizerWidth, 0, 0, 5 );
	
	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonInit = new wxButton( this, wxID_OK, _("Init"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonInit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonAbort = new wxButton( this, wxID_CANCEL, _("Abort"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonAbort, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerMain->Add( bSizerButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	// Connect Events
	m_textCtrlShoeSize->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIDialogQuickInitFoot::OnTextEnter ), NULL, this );
}

GUIDialogQuickInitFoot::~GUIDialogQuickInitFoot()
{
	// Disconnect Events
	m_textCtrlShoeSize->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIDialogQuickInitFoot::OnTextEnter ), NULL, this );
	
}

GUIFrameDebugParser::GUIFrameDebugParser( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Input (Number / Calculation / Formula / Unit):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer->Add( m_staticText10, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlExpression = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer->Add( m_textCtrlExpression, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Numeric Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer->Add( m_staticText11, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrlNumber = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer->Add( m_textCtrlNumber, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Error:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer->Add( m_staticText12, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlError = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer->Add( m_textCtrlError, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Unit Text:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer->Add( m_staticText14, 0, wxALL, 5 );
	
	m_textCtrlUnit = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer->Add( m_textCtrlUnit, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("SI Base Units:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_textCtrlSIBase = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
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
	
	m_textCtrl = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
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

GUIDialogFormulaEditor::GUIDialogFormulaEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	m_dataViewListCtrl = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_HORIZ_RULES|wxDV_SINGLE|wxDV_VERT_RULES );
	m_dataViewListCtrl->SetToolTip( _("Available variables for formula.\nDouble-click to copy to cursor position.") );
	
	m_dataViewListColumnVariable = m_dataViewListCtrl->AppendTextColumn( _("Variable") );
	m_dataViewListColumnFormula = m_dataViewListCtrl->AppendTextColumn( _("Formula") );
	m_dataViewListColumnValue = m_dataViewListCtrl->AppendTextColumn( _("Value") );
	bSizerMain->Add( m_dataViewListCtrl, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerVariableName;
	bSizerVariableName = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextVariableName = new wxStaticText( this, wxID_ANY, _("<>"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextVariableName->Wrap( -1 );
	bSizerVariableName->Add( m_staticTextVariableName, 0, wxALL, 5 );
	
	
	bSizerMain->Add( bSizerVariableName, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerFormulaAndUnit;
	bSizerFormulaAndUnit = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlFormula = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlFormula->SetToolTip( _("Enter formula or value. \nAllowed operations are: +, -, *, /, ^, cos, sin, tan, acos, asin, atan, exp, log, sqrt, cbrt, ceil, floor, round, abs") );
	
	bSizerFormulaAndUnit->Add( m_textCtrlFormula, 1, wxALL, 5 );
	
	m_textCtrlUnit = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlUnit->SetToolTip( _("Unit") );
	
	bSizerFormulaAndUnit->Add( m_textCtrlUnit, 0, wxALL, 5 );
	
	
	bSizerMain->Add( bSizerFormulaAndUnit, 0, wxEXPAND, 5 );
	
	m_textCtrlResult = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_textCtrlResult->SetToolTip( _("Result") );
	
	bSizerMain->Add( m_textCtrlResult, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonClear = new wxButton( this, wxID_ANY, _("Clear formula"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonClear, 0, wxALL, 5 );
	
	m_buttonCopyResultFormula = new wxButton( this, wxID_ANY, _("Copy result to formula"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonCopyResultFormula, 0, wxALL, 5 );
	
	
	bSizerButtons->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonCancel, 0, wxALL, 5 );
	
	m_buttonOK = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonOK, 0, wxALL, 5 );
	
	
	bSizerMain->Add( bSizerButtons, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_dataViewListCtrl->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( GUIDialogFormulaEditor::OnItemActivated ), NULL, this );
	m_buttonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialogFormulaEditor::OnClearFormula ), NULL, this );
	m_buttonCopyResultFormula->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialogFormulaEditor::OnCopyResultToFormula ), NULL, this );
}

GUIDialogFormulaEditor::~GUIDialogFormulaEditor()
{
	// Disconnect Events
	m_dataViewListCtrl->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler( GUIDialogFormulaEditor::OnItemActivated ), NULL, this );
	m_buttonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialogFormulaEditor::OnClearFormula ), NULL, this );
	m_buttonCopyResultFormula->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialogFormulaEditor::OnCopyResultToFormula ), NULL, this );
	
}

GUIFrameSetupBackgroundImages::GUIFrameSetupBackgroundImages( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerLeftColumn;
	bSizerLeftColumn = new wxBoxSizer( wxVERTICAL );
	
	m_listCtrl = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_ICON );
	bSizerLeftColumn->Add( m_listCtrl, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAdd = new wxButton( this, wxID_ANY, _("Add/Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonAdd, 1, wxALL, 5 );
	
	m_buttonRemove = new wxButton( this, wxID_ANY, _("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_buttonRemove, 1, wxALL, 5 );
	
	
	bSizerLeftColumn->Add( bSizerButtons, 0, wxEXPAND, 5 );
	
	
	bSizerMain->Add( bSizerLeftColumn, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerRightColumn;
	bSizerRightColumn = new wxBoxSizer( wxVERTICAL );
	
	m_staticTextFilename = new wxStaticText( this, wxID_ANY, _("Filename:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFilename->Wrap( -1 );
	bSizerRightColumn->Add( m_staticTextFilename, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_filePicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizerRightColumn->Add( m_filePicker, 0, wxALL|wxEXPAND, 5 );
	
	m_staticTextDirection = new wxStaticText( this, wxID_ANY, _("Direction:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDirection->Wrap( -1 );
	bSizerRightColumn->Add( m_staticTextDirection, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxGridSizer* gSizerDirection;
	gSizerDirection = new wxGridSizer( 0, 2, 0, 0 );
	
	m_checkBoxFront = new wxCheckBox( this, wxID_ANY, _("Front"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerDirection->Add( m_checkBoxFront, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_checkBoxBack = new wxCheckBox( this, wxID_ANY, _("Back"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerDirection->Add( m_checkBoxBack, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_checkBoxLeft = new wxCheckBox( this, wxID_ANY, _("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerDirection->Add( m_checkBoxLeft, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_checkBoxRight = new wxCheckBox( this, wxID_ANY, _("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerDirection->Add( m_checkBoxRight, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_checkBoxTop = new wxCheckBox( this, wxID_ANY, _("Top"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerDirection->Add( m_checkBoxTop, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_checkBoxBottom = new wxCheckBox( this, wxID_ANY, _("Bottom"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizerDirection->Add( m_checkBoxBottom, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	
	bSizerRightColumn->Add( gSizerDirection, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_staticText46 = new wxStaticText( this, wxID_ANY, _("Scale:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	bSizerRightColumn->Add( m_staticText46, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizerScale;
	bSizerScale = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlScale = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerScale->Add( m_textCtrlScale, 1, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_spinBtnScale = new wxSpinButton( this, ID_SPINSCALE, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerScale->Add( m_spinBtnScale, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizerRightColumn->Add( bSizerScale, 0, wxEXPAND, 5 );
	
	m_staticTextOffsHor = new wxStaticText( this, wxID_ANY, _("Horizontal offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOffsHor->Wrap( -1 );
	bSizerRightColumn->Add( m_staticTextOffsHor, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizerHorizontalOffset;
	bSizerHorizontalOffset = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlOffsHor = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerHorizontalOffset->Add( m_textCtrlOffsHor, 1, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_spinBtnOffsHor = new wxSpinButton( this, ID_SPINOFFSHOR, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerHorizontalOffset->Add( m_spinBtnOffsHor, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizerRightColumn->Add( bSizerHorizontalOffset, 0, wxEXPAND, 5 );
	
	m_staticTextOffsVert = new wxStaticText( this, wxID_ANY, _("Vertical Offset:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextOffsVert->Wrap( -1 );
	bSizerRightColumn->Add( m_staticTextOffsVert, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizerVerticalOffset;
	bSizerVerticalOffset = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlOffsVert = new ExtendedTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerVerticalOffset->Add( m_textCtrlOffsVert, 1, wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_spinBtnOffsVert = new wxSpinButton( this, ID_SPINOFFSVERT, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerVerticalOffset->Add( m_spinBtnOffsVert, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	bSizerRightColumn->Add( bSizerVerticalOffset, 0, wxEXPAND, 5 );
	
	m_staticTextRotation = new wxStaticText( this, wxID_ANY, _("Rotation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextRotation->Wrap( -1 );
	bSizerRightColumn->Add( m_staticTextRotation, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_sliderRotation = new wxSlider( this, wxID_ANY, 0, -180, 180, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_HORIZONTAL|wxSL_LABELS );
	bSizerRightColumn->Add( m_sliderRotation, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizerRightColumn->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonClose = new wxButton( this, ID_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerRightColumn->Add( m_buttonClose, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	bSizerMain->Add( bSizerRightColumn, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnAddUpdate ), NULL, this );
	m_buttonRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnRemove ), NULL, this );
	m_textCtrlScale->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnTextEnter ), NULL, this );
	m_spinBtnScale->Connect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( GUIFrameSetupBackgroundImages::OnSpin ), NULL, this );
	m_textCtrlOffsHor->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnTextEnter ), NULL, this );
	m_spinBtnOffsHor->Connect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( GUIFrameSetupBackgroundImages::OnSpin ), NULL, this );
	m_textCtrlOffsVert->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnTextEnter ), NULL, this );
	m_spinBtnOffsVert->Connect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( GUIFrameSetupBackgroundImages::OnSpin ), NULL, this );
	m_sliderRotation->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIFrameSetupBackgroundImages::OnRightDown ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
}

GUIFrameSetupBackgroundImages::~GUIFrameSetupBackgroundImages()
{
	// Disconnect Events
	m_buttonAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnAddUpdate ), NULL, this );
	m_buttonRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnRemove ), NULL, this );
	m_textCtrlScale->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnTextEnter ), NULL, this );
	m_spinBtnScale->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( GUIFrameSetupBackgroundImages::OnSpin ), NULL, this );
	m_textCtrlOffsHor->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnTextEnter ), NULL, this );
	m_spinBtnOffsHor->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( GUIFrameSetupBackgroundImages::OnSpin ), NULL, this );
	m_textCtrlOffsVert->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrameSetupBackgroundImages::OnTextEnter ), NULL, this );
	m_spinBtnOffsVert->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( GUIFrameSetupBackgroundImages::OnSpin ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( GUIFrameSetupBackgroundImages::OnRightDown ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	m_sliderRotation->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrameSetupBackgroundImages::OnScroll ), NULL, this );
	
}
