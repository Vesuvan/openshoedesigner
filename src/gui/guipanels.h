///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIPANELS_H__
#define __GUIPANELS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

#define ID_MEASUREMENT_FOOTLENGTH 3000
#define ID_MEASUREMENT_BALLGIRTH 3001
#define ID_MEASUREMENT_WAISTGIRTH 3002
#define ID_MEASUREMENT_INSTEPGIRTH 3003
#define ID_MEASUREMENT_LONGHEELGIRTH 3004
#define ID_MEASUREMENT_SHORTHEELGIRTH 3005
#define ID_MEASUREMENT_ANGLEMIXING 3006
#define ID_MEASUREMENT_LEGLENGTHDIFFERENCE 3007
#define ID_QUICKSETUP 3008
#define ID_MEASUREMENT_BELOWCRUTCHGIRTH 3009
#define ID_MEASUREMENT_BELOWCRUTCHLEVEL 3010
#define ID_MEASUREMENT_MIDDLEOFCALFGIRTH 3011
#define ID_MEASUREMENT_MIDDLEOFCALFLEVEL 3012
#define ID_MEASUREMENT_ABOVEKNEEGIRTH 3013
#define ID_MEASUREMENT_ABOVEKNEELEVEL 3014
#define ID_MEASUREMENT_OVERKNEECAPGIRTH 3015
#define ID_MEASUREMENT_OVERKNEECAPLEVEL 3016
#define ID_MEASUREMENT_BELOWKNEEGIRTH 3017
#define ID_MEASUREMENT_BELOWKNEELEVEL 3018
#define ID_MEASUREMENT_MIDDLEOFSHANKGIRTH 3019
#define ID_MEASUREMENT_MIDDLEOFSHANKLEVEL 3020
#define ID_MEASUREMENT_ABOVEANKLEGIRTH 3021
#define ID_MEASUREMENT_ABOVEANKLELEVEL 3022
#define ID_MEASUREMENT_OVERANKLEBONEGIRTH 3023
#define ID_MEASUREMENT_OVERANKLEBONELEVEL 3024

///////////////////////////////////////////////////////////////////////////////
/// Class GUIPanelFootMeasurements
///////////////////////////////////////////////////////////////////////////////
class GUIPanelFootMeasurements : public wxPanel 
{
	private:
	
	protected:
		wxStaticText* m_staticTextFootLength;
		wxTextCtrl* m_textCtrlFootLength;
		wxStaticText* m_staticTextBallGirth;
		wxTextCtrl* m_textCtrlBallGirth;
		wxStaticText* m_staticTextWaistGirth;
		wxTextCtrl* m_textCtrlWaistGirth;
		wxStaticText* m_staticTextInsteGirth;
		wxTextCtrl* m_textCtrlInstepGirth;
		wxStaticText* m_staticTextLongHeelGirth;
		wxTextCtrl* m_textCtrlLongHeelGirth;
		wxStaticText* m_staticTextShortHeelGirth;
		wxTextCtrl* m_textCtrlShortHeelGirth;
		wxStaticText* m_staticTextAngleMixing;
		wxTextCtrl* m_textCtrlAngleMixing;
		wxStaticText* m_staticTextLegLengthDifference;
		wxTextCtrl* m_textCtrlLegLengthDifference;
		wxButton* m_buttonQuickSetup;
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
		wxStaticBitmap* m_bitmap;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnSetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnTextEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuickSetup( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIPanelFootMeasurements( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~GUIPanelFootMeasurements();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIPanelLegMeasurements
///////////////////////////////////////////////////////////////////////////////
class GUIPanelLegMeasurements : public wxPanel 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmap;
		wxStaticText* m_staticTextGirth;
		wxStaticText* m_staticTextLevel;
		wxTextCtrl* m_textCtrlBelowCrutchGirth;
		wxTextCtrl* m_textCtrlBelowCrutchLevel;
		wxTextCtrl* m_textCtrlMiddleOfCalfGirth;
		wxTextCtrl* m_textCtrlMiddleOfCalfLevel;
		wxTextCtrl* m_textCtrlAboveKneeGirth;
		wxTextCtrl* m_textCtrlAboveKneeLevel;
		wxTextCtrl* m_textCtrlOverKneeCapGirth;
		wxTextCtrl* m_textCtrlOverKneeCapLevel;
		wxTextCtrl* m_textCtrlBelowKneeGirth;
		wxTextCtrl* m_textCtrlBelowKneeLevel;
		wxTextCtrl* m_textCtrlMiddleOfShankGirth;
		wxTextCtrl* m_textCtrlMiddleOfShankLevel;
		wxTextCtrl* m_textCtrlAboveAnkleGirth;
		wxTextCtrl* m_textCtrlAboveAnkleLevel;
		wxTextCtrl* m_textCtrlOverAnkleBoneGirth;
		wxTextCtrl* m_textCtrlOverAnkleBoneLevel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnSetFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnTextEnter( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIPanelLegMeasurements( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~GUIPanelLegMeasurements();
	
};

#endif //__GUIPANELS_H__
