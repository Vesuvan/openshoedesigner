///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../StdInclude.h"

#include "guipanels.h"

#include "../icons/FootMeasurements_small.xpm"
#include "../icons/LegMeasurements.xpm"

///////////////////////////////////////////////////////////////////////////

GUIPanelFootMeasurements::GUIPanelFootMeasurements( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizerHorizontal;
	bSizerHorizontal = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizerMeasurements;
	bSizerMeasurements = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizerMeasurements;
	fgSizerMeasurements = new wxFlexGridSizer( 8, 2, 0, 0 );
	fgSizerMeasurements->AddGrowableCol( 1 );
	fgSizerMeasurements->SetFlexibleDirection( wxHORIZONTAL );
	fgSizerMeasurements->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextFootLength = new wxStaticText( this, wxID_ANY, _("Foot length:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFootLength->Wrap( -1 );
	fgSizerMeasurements->Add( m_staticTextFootLength, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlFootLength = new wxTextCtrl( this, ID_MEASUREMENT_FOOTLENGTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlFootLength->SetToolTip( _("Length of the foot (not length of the last). Measured from the longest toe to the heel.") );
	
	fgSizerMeasurements->Add( m_textCtrlFootLength, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextBallGirth = new wxStaticText( this, wxID_ANY, _("Ball girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextBallGirth->Wrap( -1 );
	fgSizerMeasurements->Add( m_staticTextBallGirth, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlBallGirth = new wxTextCtrl( this, ID_MEASUREMENT_BALLGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBallGirth->SetToolTip( _("Grith around the widest part at the ball of the foot.") );
	
	fgSizerMeasurements->Add( m_textCtrlBallGirth, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextWaistGirth = new wxStaticText( this, wxID_ANY, _("Waist girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextWaistGirth->Wrap( -1 );
	fgSizerMeasurements->Add( m_staticTextWaistGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlWaistGirth = new wxTextCtrl( this, ID_MEASUREMENT_WAISTGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMeasurements->Add( m_textCtrlWaistGirth, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextInsteGirth = new wxStaticText( this, wxID_ANY, _("Instep girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextInsteGirth->Wrap( -1 );
	fgSizerMeasurements->Add( m_staticTextInsteGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlInstepGirth = new wxTextCtrl( this, ID_MEASUREMENT_INSTEPGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMeasurements->Add( m_textCtrlInstepGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextLongHeelGirth = new wxStaticText( this, wxID_ANY, _("Long heel girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLongHeelGirth->Wrap( -1 );
	fgSizerMeasurements->Add( m_staticTextLongHeelGirth, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlLongHeelGirth = new wxTextCtrl( this, ID_MEASUREMENT_LONGHEELGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMeasurements->Add( m_textCtrlLongHeelGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextShortHeelGirth = new wxStaticText( this, wxID_ANY, _("Short heel girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShortHeelGirth->Wrap( -1 );
	fgSizerMeasurements->Add( m_staticTextShortHeelGirth, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShortHeelGirth = new wxTextCtrl( this, ID_MEASUREMENT_SHORTHEELGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizerMeasurements->Add( m_textCtrlShortHeelGirth, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextAngleMixing = new wxStaticText( this, wxID_ANY, _("Angle Mixing:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextAngleMixing->Wrap( -1 );
	fgSizerMeasurements->Add( m_staticTextAngleMixing, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlAngleMixing = new wxTextCtrl( this, ID_MEASUREMENT_ANGLEMIXING, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAngleMixing->SetToolTip( _("Mixing determines how much of the needed bending of the foot is done by the heel and how much is spread on the forefoot. 0% is all heel, 100% is all forefoot. 100% is impractical unless some serious misalignment of the foot is to be compensated.") );
	
	fgSizerMeasurements->Add( m_textCtrlAngleMixing, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticTextLegLengthDifference = new wxStaticText( this, wxID_ANY, _("Leg length difference:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLegLengthDifference->Wrap( -1 );
	fgSizerMeasurements->Add( m_staticTextLegLengthDifference, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlLegLengthDifference = new wxTextCtrl( this, ID_MEASUREMENT_LEGLENGTHDIFFERENCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlLegLengthDifference->SetToolTip( _("Distance the right leg is longer than the left (positive number). If the right leg is shorter than the left leg the number has to be negative.") );
	
	fgSizerMeasurements->Add( m_textCtrlLegLengthDifference, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizerMeasurements->Add( fgSizerMeasurements, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerHorizontal->Add( bSizerMeasurements, 0, 0, 5 );
	
	
	bSizerHorizontal->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizerShoeSizes;
	bSizerShoeSizes = new wxBoxSizer( wxVERTICAL );
	
	m_buttonQuickSetup = new wxButton( this, ID_QUICKSETUP, _("Quick Setup"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerShoeSizes->Add( m_buttonQuickSetup, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizerShoeSizes;
	sbSizerShoeSizes = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Shoesizes") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizerShoeSizes;
	fgSizerShoeSizes = new wxFlexGridSizer( 6, 2, 0, 0 );
	fgSizerShoeSizes->AddGrowableCol( 1 );
	fgSizerShoeSizes->SetFlexibleDirection( wxHORIZONTAL );
	fgSizerShoeSizes->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextShoeSizeEU = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("EU:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeEU->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeEU, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShoeSizeEU = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeEU->SetToolTip( _("Last length in Paris point") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeEU, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeUS = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("US:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeUS->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeUS, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeUS = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeUS->SetToolTip( _("Brannock-Scale") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeUS, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeUK = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("UK:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeUK->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeUK, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeUK = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeUK->SetToolTip( _("Last length in Barleycorns") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeUK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeCN = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("CN:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeCN->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeCN, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textCtrlShoeSizeCN = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeCN->SetToolTip( _("Foot length in cm") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeCN, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_staticTextShoeSizeJP = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("JP:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeJP->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeJP, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeJP = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeJP->SetToolTip( _("Foot length in mm") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeJP, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticTextShoeSizeAU = new wxStaticText( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, _("AU:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextShoeSizeAU->Wrap( -1 );
	fgSizerShoeSizes->Add( m_staticTextShoeSizeAU, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlShoeSizeAU = new wxTextCtrl( sbSizerShoeSizes->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	m_textCtrlShoeSizeAU->SetToolTip( _("Last length in Barleycorns") );
	
	fgSizerShoeSizes->Add( m_textCtrlShoeSizeAU, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	sbSizerShoeSizes->Add( fgSizerShoeSizes, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizerShoeSizes->Add( sbSizerShoeSizes, 0, 0, 5 );
	
	
	bSizerHorizontal->Add( bSizerShoeSizes, 0, 0, 5 );
	
	
	bSizerHorizontal->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizerMain->Add( bSizerHorizontal, 1, wxEXPAND, 5 );
	
	m_bitmap = new wxStaticBitmap( this, wxID_ANY, wxBitmap( FootMeasurements_small_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMain->Add( m_bitmap, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	// Connect Events
	m_textCtrlFootLength->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlFootLength->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlFootLength->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlBallGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBallGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBallGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlWaistGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlWaistGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlWaistGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlInstepGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlInstepGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlInstepGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlLongHeelGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlLongHeelGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlLongHeelGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlShortHeelGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlShortHeelGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlShortHeelGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAngleMixing->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAngleMixing->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAngleMixing->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlLegLengthDifference->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlLegLengthDifference->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlLegLengthDifference->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_buttonQuickSetup->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPanelFootMeasurements::OnQuickSetup ), NULL, this );
	m_bitmap->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIPanelFootMeasurements::OnLeftDown ), NULL, this );
	m_bitmap->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIPanelFootMeasurements::OnSize ), NULL, this );
}

GUIPanelFootMeasurements::~GUIPanelFootMeasurements()
{
	// Disconnect Events
	m_textCtrlFootLength->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlFootLength->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlFootLength->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlBallGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBallGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBallGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlWaistGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlWaistGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlWaistGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlInstepGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlInstepGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlInstepGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlLongHeelGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlLongHeelGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlLongHeelGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlShortHeelGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlShortHeelGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlShortHeelGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAngleMixing->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAngleMixing->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAngleMixing->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlLegLengthDifference->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlLegLengthDifference->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelFootMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlLegLengthDifference->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelFootMeasurements::OnTextEnter ), NULL, this );
	m_buttonQuickSetup->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPanelFootMeasurements::OnQuickSetup ), NULL, this );
	m_bitmap->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIPanelFootMeasurements::OnLeftDown ), NULL, this );
	m_bitmap->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIPanelFootMeasurements::OnSize ), NULL, this );
	
}

GUIPanelLegMeasurements::GUIPanelLegMeasurements( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap = new wxStaticBitmap( this, wxID_ANY, wxBitmap( LegMeasurements_xpm ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerMain->Add( m_bitmap, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer;
	fgSizer = new wxFlexGridSizer( 9, 2, 0, 0 );
	fgSizer->SetFlexibleDirection( wxBOTH );
	fgSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticTextGirth = new wxStaticText( this, wxID_ANY, _("Girth:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextGirth->Wrap( -1 );
	fgSizer->Add( m_staticTextGirth, 0, wxALL, 5 );
	
	m_staticTextLevel = new wxStaticText( this, wxID_ANY, _("Level:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextLevel->Wrap( -1 );
	fgSizer->Add( m_staticTextLevel, 0, wxALL, 5 );
	
	m_textCtrlBelowCrutchGirth = new wxTextCtrl( this, ID_MEASUREMENT_BELOWCRUTCHGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBelowCrutchGirth->SetToolTip( _("Below crutch girth") );
	
	fgSizer->Add( m_textCtrlBelowCrutchGirth, 0, wxALL, 5 );
	
	m_textCtrlBelowCrutchLevel = new wxTextCtrl( this, ID_MEASUREMENT_BELOWCRUTCHLEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBelowCrutchLevel->SetToolTip( _("Below crutch level") );
	
	fgSizer->Add( m_textCtrlBelowCrutchLevel, 0, wxALL, 5 );
	
	m_textCtrlMiddleOfCalfGirth = new wxTextCtrl( this, ID_MEASUREMENT_MIDDLEOFCALFGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMiddleOfCalfGirth->SetToolTip( _("Middle of calf girth") );
	
	fgSizer->Add( m_textCtrlMiddleOfCalfGirth, 0, wxALL, 5 );
	
	m_textCtrlMiddleOfCalfLevel = new wxTextCtrl( this, ID_MEASUREMENT_MIDDLEOFCALFLEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMiddleOfCalfLevel->SetToolTip( _("Middle of calf level") );
	
	fgSizer->Add( m_textCtrlMiddleOfCalfLevel, 0, wxALL, 5 );
	
	m_textCtrlAboveKneeGirth = new wxTextCtrl( this, ID_MEASUREMENT_ABOVEKNEEGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAboveKneeGirth->SetToolTip( _("Above knee girth") );
	
	fgSizer->Add( m_textCtrlAboveKneeGirth, 0, wxALL, 5 );
	
	m_textCtrlAboveKneeLevel = new wxTextCtrl( this, ID_MEASUREMENT_ABOVEKNEELEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAboveKneeLevel->SetToolTip( _("Above knee level") );
	
	fgSizer->Add( m_textCtrlAboveKneeLevel, 0, wxALL, 5 );
	
	m_textCtrlOverKneeCapGirth = new wxTextCtrl( this, ID_MEASUREMENT_OVERKNEECAPGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOverKneeCapGirth->SetToolTip( _("Over knee cap girth") );
	
	fgSizer->Add( m_textCtrlOverKneeCapGirth, 0, wxALL, 5 );
	
	m_textCtrlOverKneeCapLevel = new wxTextCtrl( this, ID_MEASUREMENT_OVERKNEECAPLEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOverKneeCapLevel->SetToolTip( _("Over knee cap level") );
	
	fgSizer->Add( m_textCtrlOverKneeCapLevel, 0, wxALL, 5 );
	
	m_textCtrlBelowKneeGirth = new wxTextCtrl( this, ID_MEASUREMENT_BELOWKNEEGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBelowKneeGirth->SetToolTip( _("Below knee girth") );
	
	fgSizer->Add( m_textCtrlBelowKneeGirth, 0, wxALL, 5 );
	
	m_textCtrlBelowKneeLevel = new wxTextCtrl( this, ID_MEASUREMENT_BELOWKNEELEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlBelowKneeLevel->SetToolTip( _("Below knee level") );
	
	fgSizer->Add( m_textCtrlBelowKneeLevel, 0, wxALL, 5 );
	
	m_textCtrlMiddleOfShankGirth = new wxTextCtrl( this, ID_MEASUREMENT_MIDDLEOFSHANKGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMiddleOfShankGirth->SetToolTip( _("Middle of shank girth") );
	
	fgSizer->Add( m_textCtrlMiddleOfShankGirth, 0, wxALL, 5 );
	
	m_textCtrlMiddleOfShankLevel = new wxTextCtrl( this, ID_MEASUREMENT_MIDDLEOFSHANKLEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlMiddleOfShankLevel->SetToolTip( _("Middle of shank level") );
	
	fgSizer->Add( m_textCtrlMiddleOfShankLevel, 0, wxALL, 5 );
	
	m_textCtrlAboveAnkleGirth = new wxTextCtrl( this, ID_MEASUREMENT_ABOVEANKLEGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAboveAnkleGirth->SetToolTip( _("Above ankle girth") );
	
	fgSizer->Add( m_textCtrlAboveAnkleGirth, 0, wxALL, 5 );
	
	m_textCtrlAboveAnkleLevel = new wxTextCtrl( this, ID_MEASUREMENT_ABOVEANKLELEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlAboveAnkleLevel->SetToolTip( _("Above ankle level") );
	
	fgSizer->Add( m_textCtrlAboveAnkleLevel, 0, wxALL, 5 );
	
	m_textCtrlOverAnkleBoneGirth = new wxTextCtrl( this, ID_MEASUREMENT_OVERANKLEBONEGIRTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOverAnkleBoneGirth->SetToolTip( _("Over ankle bone girth") );
	
	fgSizer->Add( m_textCtrlOverAnkleBoneGirth, 0, wxALL, 5 );
	
	m_textCtrlOverAnkleBoneLevel = new wxTextCtrl( this, ID_MEASUREMENT_OVERANKLEBONELEVEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_textCtrlOverAnkleBoneLevel->SetToolTip( _("Over ankle bone level") );
	
	fgSizer->Add( m_textCtrlOverAnkleBoneLevel, 0, wxALL, 5 );
	
	
	bSizer->Add( fgSizer, 0, 0, 5 );
	
	
	bSizerMain->Add( bSizer, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	
	// Connect Events
	m_textCtrlBelowCrutchGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBelowCrutchGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBelowCrutchGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlBelowCrutchLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBelowCrutchLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBelowCrutchLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAboveKneeGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAboveKneeGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAboveKneeGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAboveKneeLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAboveKneeLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAboveKneeLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlOverKneeCapGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlOverKneeCapGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlOverKneeCapGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlOverKneeCapLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlOverKneeCapLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlOverKneeCapLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlBelowKneeGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBelowKneeGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBelowKneeGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlBelowKneeLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBelowKneeLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBelowKneeLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAboveAnkleGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAboveAnkleGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAboveAnkleGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAboveAnkleLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAboveAnkleLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAboveAnkleLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
}

GUIPanelLegMeasurements::~GUIPanelLegMeasurements()
{
	// Disconnect Events
	m_textCtrlBelowCrutchGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBelowCrutchGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBelowCrutchGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlBelowCrutchLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBelowCrutchLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBelowCrutchLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfCalfGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfCalfLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAboveKneeGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAboveKneeGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAboveKneeGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAboveKneeLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAboveKneeLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAboveKneeLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlOverKneeCapGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlOverKneeCapGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlOverKneeCapGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlOverKneeCapLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlOverKneeCapLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlOverKneeCapLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlBelowKneeGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBelowKneeGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBelowKneeGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlBelowKneeLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlBelowKneeLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlBelowKneeLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfShankGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlMiddleOfShankLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAboveAnkleGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAboveAnkleGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAboveAnkleGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlAboveAnkleLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlAboveAnkleLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlAboveAnkleLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlOverAnkleBoneGirth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnKillFocus ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( GUIPanelLegMeasurements::OnSetFocus ), NULL, this );
	m_textCtrlOverAnkleBoneLevel->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIPanelLegMeasurements::OnTextEnter ), NULL, this );
	
}
