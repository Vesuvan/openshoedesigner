///////////////////////////////////////////////////////////////////////////////
// Name               : FrameMain.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.08.2015
// Copyright          : (C) 2015 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////

#include "FrameMain.h"

#include "IDs.h"
#include "DialogQuickInitFoot.h"
#include "FrameDebugParser.h"

#include "../3D/FileSTL.h"
#include "../languages.h"
#include <wx/cmdproc.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <math.h>
#include <cfloat>

#include "../project/command/CommandFootMeasurementSet.h"
#include "../project/command/CommandFootModelSetParameter.h"
#include "../project/command/CommandProjectSetLegLengthDifference.h"
#include "../project/command/CommandShoePreset.h"
#include "../project/command/CommandShoeSetParameter.h"

#include "../icons/FootMeasurements.xpm"
#include "../icons/FootMeasurements_small.xpm"
#include "../project/command/CommandFootMeasurementsCopy.h"
#include "../project/command/CommandProjectSetParameter.h"

#include "FrameParent.h"

FrameMain::FrameMain(wxDocument* doc, wxView* view, wxConfig* config,
		wxDocParentFrame* parent)
		: GUIFrameMain(doc, view, parent), bm0(FootMeasurements_small_xpm), bm1(
				FootMeasurements_xpm)
{
	loopGuard = false;
	this->config = config;

	presets.ReadFile(_T("data/Presets.ini"));

	m_menuFile->Append(wxID_NEW);
	m_menuFile->Append(wxID_OPEN);
	m_menuFile->Append(wxID_REVERT_TO_SAVED);
	wxMenu* m_menuRecent = new wxMenu();
	m_menuFile->Append(
			new wxMenuItem(m_menuFile, wxID_ANY, _("&Recently opened"),
					wxEmptyString, wxITEM_NORMAL, m_menuRecent));
	doc->GetDocumentManager()->FileHistoryAddFilesToMenu(m_menuRecent);
	m_menuFile->Append(wxID_SAVE);
	m_menuFile->Append(wxID_SAVEAS);
	m_menuFile->AppendSeparator();
	m_menuFile->Append(wxID_PRINT);
	m_menuFile->Append(wxID_PREVIEW);
	m_menuFile->Append(wxID_PRINT_SETUP, _("Print Setup..."));
	m_menuFile->AppendSeparator();
	m_menuFile->Append(wxID_CLOSE);
	m_menuFile->Append(wxID_EXIT);

	m_menuEdit->Append(wxID_UNDO);
	m_menuEdit->Append(wxID_REDO);

	m_menuPreferences->Append(ID_SETUPLANGUAGE, _T("Change Language"));
	m_menuPreferences->Append(ID_SETUPCONTROLLER, _("Setup 6DOF &Controller"));
	m_menuPreferences->Append(ID_SETUPSTEREO3D, _("Setup &Stereo 3D"));
	m_menuPreferences->Append(ID_SETUPMIDI, _("Setup &MIDI"));
	m_menuPreferences->Append(ID_SETUPUNITS,
	_("Setup &Units") + wxT("\tCtrl+U"));

	m_menuHelp->AppendSeparator();
	m_menuHelp->Append(wxID_HELP, _("&Help") + wxT("\tF1"));
	m_menuHelp->Append(wxID_ABOUT);

	doc->GetCommandProcessor()->SetEditMenu(m_menuEdit);
	doc->GetCommandProcessor()->Initialize();

	FrameParent* parentframe = wxStaticCast(parent, FrameParent);
	SettingsStereo3D* settings = &(parentframe->settingsStereo3D);

	m_canvas3D->SetProjectView(wxStaticCast(view, ProjectView));
	settings->WriteToCanvas(m_canvas3D);

	filepaths.Load(config);

	TransferDataToWindow();

	this->Connect(ID_3DSELECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::On3DSelect));
	this->Connect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshCanvas));
	this->Connect(ID_REFRESHVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshView));

//	timer.SetOwner(this);
//	this->Connect(wxEVT_TIMER, wxTimerEventHandler(FrameMain::OnTimer), NULL,
//			this);
//	timer.Start(100);
//	midi.Open(3);

	Project* project = wxStaticCast(doc, Project);
	project->Update();
}

FrameMain::~FrameMain()
{
	printf("FrameMain: Destructor called\n");
	this->Disconnect(ID_REFRESHVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshView));
	this->Disconnect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshCanvas));
	this->Disconnect(ID_3DSELECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::On3DSelect));

//	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(FrameMain::OnTimer), NULL,
//			this);

	filepaths.Save(config);
}

void FrameMain::OnClose(wxCloseEvent& event)
{
	wxDocument* doc = this->GetDocument();
	wxList tempDocs = doc->GetDocumentManager()->GetDocuments();
	wxList tempViews = doc->GetViews();
	Project* project = wxStaticCast(doc, Project);
	project->StopAllThreads();

	printf("FrameMain: %lu docs, %lu views\n", tempDocs.GetCount(),
			tempViews.GetCount());

	if(tempDocs.GetCount() > 1){
		event.Skip(); // Only close this window, by passing the event to the default handler.
		return;
	}
	if(tempViews.GetCount() > 1){
		event.Skip(); // Only close this window, by passing the event to the default handler.
		return;
	}
	wxWindow* main = this->GetParent();
	printf("FrameMain: parent->Close()\n");
	main->Close(); // Exit app by closing main window, this will close this window as well.
}

bool FrameMain::TransferDataToWindow()
{
	const ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	const Project* project = wxStaticCast(GetDocument(), Project);
	const FootMeasurements * foot = projectview->GetActiveFootMeasurements();
	const Shoe * shoe = &(project->shoe);

	// Set checkboxes and selections in main menu
	loopGuard = true;
	if(project->measurementsource == Project::fromMeasurements) m_menuFoot->Check(
	ID_USEFOOTMEASUREMENTS,
			project->measurementsource == Project::fromMeasurements);
	if(project->measurementsource == Project::fromFootScan) m_menuFoot->Check(
	ID_USEFOOTSCAN, project->measurementsource == Project::fromFootScan);
	m_menuFoot->Check(ID_MEASUREMENTSYMMETRY, project->measurementsSymmetric);

	if(project->modeltype == Project::boneBased) m_menuFoot->Check(
	ID_USEBONEBASEDMODEL, project->modeltype == Project::boneBased);
	if(project->modeltype == Project::lastBased) m_menuFoot->Check(
	ID_USELASTBASEDMODEL, project->modeltype == Project::lastBased);

	if(project->generator == Project::Experimental) m_menuConstruction->Check(
	ID_CONSTRUCTIONEXPERIMENTAL, project->generator == Project::Experimental);
	if(project->generator == Project::Welted) m_menuConstruction->Check(
	ID_CONSTRUCTIONWELDED, project->generator == Project::Welted);
	if(project->generator == Project::Cemented) m_menuConstruction->Check(
	ID_CONSTRUCTIONCEMENTED, project->generator == Project::Cemented);
	if(project->generator == Project::Molded) m_menuConstruction->Check(
	ID_CONSTRUCTIONMOLDED, project->generator == Project::Molded);
	if(project->generator == Project::Dutch) m_menuConstruction->Check(
	ID_CONSTRUCTIONDUTCH, project->generator == Project::Dutch);
	if(project->generator == Project::Geta) m_menuConstruction->Check(
	ID_CONSTRUCTIONGETA, project->generator == Project::Geta);

	m_menuView->Check(ID_STEREO3D, m_canvas3D->stereoMode != stereoOff);
	m_menuView->Check(ID_SHOWLEFT, projectview->showLeft);
	m_menuView->Check(ID_SHOWRIGHT, projectview->showRight);
	m_menuView->Check(ID_SHOWBONES, projectview->showBones);
	m_menuView->Check(ID_SHOWSKIN, projectview->showSkin);
	m_menuView->Check(ID_SHOWLEG, projectview->showLeg);
	m_menuView->Check(ID_SHOWLAST, projectview->showLast);
	m_menuView->Check(ID_SHOWINSOLE, projectview->showInsole);
	m_menuView->Check(ID_SHOWSOLE, projectview->showSole);
	m_menuView->Check(ID_SHOWUPPER, projectview->showUpper);
	m_menuView->Check(ID_SHOWCUTAWAY, projectview->showCutaway);
	m_menuView->Check(ID_SHOWFLOOR, projectview->showFloor);
	m_menuView->Check(ID_SHOWCOORDINATESYSTEM,
			projectview->showCoordinateSystem);
	m_menuView->Check(ID_SHOWBACKGROUND, projectview->showBackground);

	// On Page Foot:
	if(projectview->active == ProjectView::Left
			|| projectview->active == ProjectView::Both){
		m_toggleBtnEditLeft->SetValue(true);
		m_toggleBtnEditLeft1->SetValue(true);
	}else{
		m_toggleBtnEditLeft->SetValue(false);
		m_toggleBtnEditLeft1->SetValue(false);
	}
	if(projectview->active == ProjectView::Right
			|| projectview->active == ProjectView::Both){
		m_toggleBtnEditRight->SetValue(true);
		m_toggleBtnEditRight1->SetValue(true);
	}else{
		m_toggleBtnEditRight->SetValue(false);
		m_toggleBtnEditRight1->SetValue(false);
	}

	if(project->measurementsource == Project::fromMeasurements){
		m_choicebookMeasurement->SetSelection(0);
	}else{
		m_choicebookMeasurement->SetSelection(1);
	}
	if(project->modeltype == Project::boneBased){
		m_choicebookFootModel->SetSelection(0);
	}else{
		m_choicebookFootModel->SetSelection(1);
	}

	TransferParameterToTextCtrl(foot->footLength, m_textCtrlFootLength,
			unitDistance);
	TransferParameterToTextCtrl(foot->ballGirth, m_textCtrlBallGirth,
			unitDistance);
	TransferParameterToTextCtrl(foot->waistGirth, m_textCtrlWaistGirth,
			unitDistance);
	TransferParameterToTextCtrl(foot->instepGirth, m_textCtrlInstepGirth,
			unitDistance);
	TransferParameterToTextCtrl(foot->longHeelGirth, m_textCtrlLongHeelGirth,
			unitDistance);
	TransferParameterToTextCtrl(foot->shortHeelGirth, m_textCtrlShortHeelGirth,
			unitDistance);
	TransferParameterToTextCtrl(foot->angleMixing, m_textCtrlAngleMixing,
			unitPercent);
	TransferParameterToTextCtrl(project->legLengthDifference,
			m_textCtrlLegLengthDifference, unitDistance);

	m_textCtrlShoeSizeEU->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::EU))));
	m_textCtrlShoeSizeUS->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::US))));
	m_textCtrlShoeSizeUK->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::UK))));
	m_textCtrlShoeSizeCN->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::CN))));
	m_textCtrlShoeSizeJP->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::JP))));
	m_textCtrlShoeSizeAU->SetValue(
			wxString::Format(_T("%g"),
					round(foot->GetSize(FootMeasurements::AU))));

	m_filePickerLastModel->SetFileName(
			wxFileName(project->lastModelL.filename));

	// On Page Leg:

	TransferParameterToTextCtrl(foot->belowCrutchGirth,
			m_textCtrlBelowCrutchGirth, unitDistance);
	TransferParameterToTextCtrl(foot->belowCrutchLevel,
			m_textCtrlBelowCrutchLevel, unitDistance);
	TransferParameterToTextCtrl(foot->middleOfCalfGirth,
			m_textCtrlMiddleOfCalfGirth, unitDistance);
	TransferParameterToTextCtrl(foot->middleOfCalfLevel,
			m_textCtrlMiddleOfCalfLevel, unitDistance);
	TransferParameterToTextCtrl(foot->aboveKneeGirth, m_textCtrlAboveKneeGirth,
			unitDistance);
	TransferParameterToTextCtrl(foot->aboveKneeLevel, m_textCtrlAboveKneeLevel,
			unitDistance);
	TransferParameterToTextCtrl(foot->overKneeCapGirth,
			m_textCtrlOverKneeCapGirth, unitDistance);
	TransferParameterToTextCtrl(foot->overKneeCapLevel,
			m_textCtrlOverKneeCapLevel, unitDistance);
	TransferParameterToTextCtrl(foot->belowKneeGirth, m_textCtrlBelowKneeGirth,
			unitDistance);
	TransferParameterToTextCtrl(foot->belowKneeLevel, m_textCtrlBelowKneeLevel,
			unitDistance);
	TransferParameterToTextCtrl(foot->middleOfShankGirth,
			m_textCtrlMiddleOfShankGirth, unitDistance);
	TransferParameterToTextCtrl(foot->middleOfShankLevel,
			m_textCtrlMiddleOfShankLevel, unitDistance);
	TransferParameterToTextCtrl(foot->aboveAnkleGirth,
			m_textCtrlAboveAnkleGirth, unitDistance);
	TransferParameterToTextCtrl(foot->aboveAnkleLevel,
			m_textCtrlAboveAnkleLevel, unitDistance);
	TransferParameterToTextCtrl(foot->overAnkleBoneGirth,
			m_textCtrlOverAnkleBoneGirth, unitDistance);
	TransferParameterToTextCtrl(foot->overAnkleBoneLevel,
			m_textCtrlOverAnkleBoneLevel, unitDistance);

	// On Page Shoe:

	{	// Add strings to shoe-type ChoiceCtrl
		wxArrayString newStrings;
		newStrings.Add(_("Custom"));
		IniFile::Section const * section = presets.FindSection(
				_T("PRESET_SHOETYPE"));
		while(section != NULL){
			newStrings.Add(section->GetParameter(_T("Name")));
			section = presets.NextSection(section);
		}
		wxArrayString temp = m_choiceShoeType->GetStrings();
		if(newStrings != temp){
			m_choiceShoeType->Set(newStrings);
			m_choiceShoeType->SetSelection(0);
		}
	}
	{	// Add strings to shoe-height ChoiceCtrl
		wxArrayString newStrings;
		newStrings.Add(_("Custom"));
		IniFile::Section const * section = presets.FindSection(
				_T("PRESET_HEIGHT"));
		while(section != NULL){
			newStrings.Add(section->GetParameter(_T("Name")));
			section = presets.NextSection(section);
		}
		wxArrayString temp = m_choiceShoeHeight->GetStrings();
		if(newStrings != temp){
			m_choiceShoeHeight->Set(newStrings);
			m_choiceShoeHeight->SetSelection(0);
		}
	}

	TransferParameterToTextCtrl(shoe->heelHeight, m_textCtrlHeelHeight,
			unitDistance);
	TransferParameterToTextCtrl(shoe->ballHeight, m_textCtrlBallHeight,
			unitDistance);
	TransferParameterToTextCtrl(shoe->heelPitch, m_textCtrlHeelPitch,
			unitAngle);
	TransferParameterToTextCtrl(shoe->toeSpring, m_textCtrlToeSpring,
			unitAngle);
	TransferParameterToTextCtrl(shoe->upperLevel, m_textCtrlUpperLevel,
			unitNone);
	TransferParameterToTextCtrl(shoe->extraLength, m_textCtrlExtraLength,
			unitDistance);
	TransferParameterToTextCtrl(shoe->footCompression,
			m_textCtrlFootCompression, unitPercent);

	// On Page Sole

	m_choiceConstruction->SetSelection((int) project->generator);

	loopGuard = false;

	return true;
}

bool FrameMain::TransferDataFromWindow()
{
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	projectview->showBones = m_menuView->IsChecked(ID_SHOWBONES);
	projectview->showSkin = m_menuView->IsChecked(ID_SHOWSKIN);
	projectview->showLeg = m_menuView->IsChecked(ID_SHOWLEG);
	projectview->showLast = m_menuView->IsChecked(ID_SHOWLAST);
	projectview->showInsole = m_menuView->IsChecked(ID_SHOWINSOLE);
	projectview->showUpper = m_menuView->IsChecked(ID_SHOWUPPER);
	projectview->showSole = m_menuView->IsChecked(ID_SHOWSOLE);
	projectview->showCutaway = m_menuView->IsChecked(ID_SHOWCUTAWAY);
	projectview->showFloor = m_menuView->IsChecked(ID_SHOWFLOOR);
	projectview->showCoordinateSystem = m_menuView->IsChecked(
	ID_SHOWCOORDINATESYSTEM);
	projectview->showBackground = m_menuView->IsChecked(ID_SHOWBACKGROUND);
	return true;
}

void FrameMain::RefreshCanvas(wxCommandEvent& WXUNUSED(event))
{
	m_canvas3D->Refresh();
	Refresh();
}

void FrameMain::RefreshView(wxCommandEvent& event)
{
	TransferDataToWindow();
	this->Refresh(); // FIXME: Recursive refresh does not work with GTK1. Call Refresh on every child-dialog by hand.
}

//void FrameMain::OnTimer(wxTimerEvent& event)
//{
//	Project* project = wxStaticCast(GetDocument(), Project);
//
//
//	midi.Poll();
//	if(project->vol.Numel() == 8){
//		for(size_t n = 0; n < 8; n++)
//			project->vol[n] = ((double) midi.cc[n + 1] - 64.0) / 64.0;
//	}else{
//		project->vol.At(1, 1, 1) = ((double) midi.cc[1] - 64.0) / 64.0;
//		project->vol.At(2, 1, 1) = ((double) midi.cc[2] - 64.0) / 64.0;
//		project->vol.At(1, 2, 1) = ((double) midi.cc[3] - 64.0) / 64.0;
//		project->vol.At(2, 2, 1) = ((double) midi.cc[4] - 64.0) / 64.0;
//		project->vol.At(1, 1, 2) = ((double) midi.cc[5] - 64.0) / 64.0;
//		project->vol.At(2, 1, 2) = ((double) midi.cc[6] - 64.0) / 64.0;
//		project->vol.At(1, 2, 2) = ((double) midi.cc[7] - 64.0) / 64.0;
//		project->vol.At(2, 2, 2) = ((double) midi.cc[8] - 64.0) / 64.0;
//	}
//	project->vol.CalcSurface();
//
//	this->Refresh();
//}

void FrameMain::On3DSelect(wxCommandEvent& event)
{
//	int x = event.GetX();
//	int y = event.GetY();
//	OpenGLPick result;
//	m_canvas3D->OnPick(result, x, y);
//	if(result.HasHits()){
//		result.SortByNear();
//		switch(result.Get(1)){
//		case 1:
//			{
//				const int boneNr = result.Get(2);
//				ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
//				const Foot *foot = projectview->foot;
//				if(boneNr < foot->bones.size()){
//					m_statusBar->SetStatusText(foot->bones[boneNr].name);
//
//					m_gridBoneLength->SelectRow(boneNr);
//					m_gridBoneDiameter->SelectRow(boneNr);
//					m_gridSkin->SelectRow(boneNr);
//				}
//				break;
//			}
//		case 3:
//			{
//				wxString temp;
//				temp = wxString::Format(_T("U: %i, V: %i"), result.Get(2),
//						result.Get(3));
//				m_statusBar->SetStatusText(temp);
//				break;
//			}
//		default:
//			{
//				m_statusBar->SetStatusText(wxString());
//				break;
//			}
//		}
//	}else{
//		m_statusBar->SetStatusText(wxString());
//	}
}

void FrameMain::OnSize(wxSizeEvent& event)
{
//	if(event.GetId() == ID_IMAGEFOOT){
	wxSize s = m_panelPageFoot->GetSize();
	if(s.GetWidth() > 460)
		m_bitmapFoot->SetBitmap(bm1);
	else
		m_bitmapFoot->SetBitmap(bm0);
//	this->Layout();
//	}
	event.Skip();
}

void FrameMain::OnPageChange(wxNotebookEvent& event)
{
	if(loopGuard) return;
	std::cout << "OnPageChange( " << event.GetId() << " )\n";

	Project* project = wxStaticCast(GetDocument(), Project);
	switch(event.GetId()){
	case ID_MEASUREMENTSOURCE:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Set source."), project,
						event.GetId(),
						m_choicebookMeasurement->GetSelection()));
		break;
	case ID_FOOTMODEL:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Set footmodel."), project,
						event.GetId(), m_choicebookFootModel->GetSelection()));
		break;
	default:
		return;
	}
	TransferDataToWindow();
}

void FrameMain::OnToggleButton(wxCommandEvent& event)
{
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	Project* project = wxStaticCast(GetDocument(), Project);
	if(project->measurementsSymmetric){
		projectview->active = ProjectView::Both;
		TransferDataToWindow();
		return;
	}
	switch(event.GetId()){
	case ID_EDITLEFT:
		if(projectview->active == ProjectView::Right){
			projectview->active = ProjectView::Both;
		}else{
			projectview->active = ProjectView::Right;
		}
		break;
	case ID_EDITRIGHT:
		if(projectview->active == ProjectView::Left){
			projectview->active = ProjectView::Both;
		}else{
			projectview->active = ProjectView::Left;
		}
		break;
	default:
		printf("ToggleButton %u pressed.\n", event.GetId());
		break;
	}
	TransferDataToWindow();
}

void FrameMain::OnChoice(wxCommandEvent& event)
{
	std::cout << "OnChoice( " << event.GetId() << " )\n";

	switch(event.GetId()){
	case ID_PRESETSHOETYPE:
		break;
	case ID_PRESETSHOEHEIGHT:
		break;
	default:
		event.Skip();
	}

	//void FrameMain::OnPreset(wxCommandEvent& event)
	//{
	//	Project* project = wxStaticCast(GetDocument(), Project);
	//	project->GetCommandProcessor()->Submit(
	//			new CommandShoePreset(
	//					wxString::Format(_("Set preset to %i"), event.GetId()),
	//					project, event.GetId()));
	//	TransferDataToWindow();
	//}

}

void FrameMain::OnCheckBox(wxCommandEvent& event)
{
	std::cout << "OnCheckBox( " << event.GetId() << " )\n";
}

void FrameMain::OnScroll(wxScrollEvent& event)
{
	std::cout << "OnScroll( " << event.GetId() << " )\n";
}

void FrameMain::OnSetFocus(wxFocusEvent& event)
{
	switch(event.GetId()){
	case ID_MEASUREMENT_FOOTLENGTH:
	case ID_MEASUREMENT_BALLGIRTH:
	case ID_MEASUREMENT_WAISTGIRTH:
	case ID_MEASUREMENT_INSTEPGIRTH:
	case ID_MEASUREMENT_LONGHEELGIRTH:
	case ID_MEASUREMENT_SHORTHEELGIRTH:
	case ID_MEASUREMENT_ANGLEMIXING:
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
	case ID_MEASUREMENT_BELOWKNEELEVEL:
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
	case ID_HEELHEIGHT:
	case ID_BALLHEIGHT:
	case ID_HEELPITCH:
	case ID_TOESPRING:
	case ID_UPPERLEVEL:
	case ID_EXTRALENGTH:
	case ID_FOOTCOMPRESSION:
		TransferDataToWindow();
	}
}

void FrameMain::OnKillFocus(wxFocusEvent& event)
{
	switch(event.GetId()){
	case ID_MEASUREMENT_FOOTLENGTH:
	case ID_MEASUREMENT_BALLGIRTH:
	case ID_MEASUREMENT_WAISTGIRTH:
	case ID_MEASUREMENT_INSTEPGIRTH:
	case ID_MEASUREMENT_LONGHEELGIRTH:
	case ID_MEASUREMENT_SHORTHEELGIRTH:
	case ID_MEASUREMENT_ANGLEMIXING:
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
	case ID_MEASUREMENT_BELOWKNEELEVEL:
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
	case ID_HEELHEIGHT:
	case ID_BALLHEIGHT:
	case ID_HEELPITCH:
	case ID_TOESPRING:
	case ID_UPPERLEVEL:
	case ID_EXTRALENGTH:
	case ID_FOOTCOMPRESSION:
		TransferDataToWindow();
	}
}

void FrameMain::OnTextEnter(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	const wxString newFormula = event.GetString();

	switch(event.GetId()){
	case ID_MEASUREMENT_FOOTLENGTH:
	case ID_MEASUREMENT_BALLGIRTH:
	case ID_MEASUREMENT_WAISTGIRTH:
	case ID_MEASUREMENT_INSTEPGIRTH:
	case ID_MEASUREMENT_LONGHEELGIRTH:
	case ID_MEASUREMENT_SHORTHEELGIRTH:
	case ID_MEASUREMENT_ANGLEMIXING:
		project->GetCommandProcessor()->Submit(
				new CommandFootMeasurementSet(
						wxString::Format(_("Set %s to %s"),
								GetNameByID(event.GetId()), newFormula),
						project, projectview->active, event.GetId(),
						newFormula));
		m_panelPageFoot->Navigate();
		break;
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetLegLengthDifference(
						wxString::Format(_("Set leg length difference to %s"),
								newFormula), project, newFormula));
		m_panelPageFoot->Navigate();
		break;
	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
	case ID_MEASUREMENT_BELOWKNEELEVEL:
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		project->GetCommandProcessor()->Submit(
				new CommandFootMeasurementSet(
						wxString::Format(_("Set %s to %s"),
								GetNameByID(event.GetId()), newFormula),
						project, projectview->active, event.GetId(),
						newFormula));
		m_panelPageLeg->Navigate();
		break;
	case ID_HEELHEIGHT:
	case ID_BALLHEIGHT:
	case ID_HEELPITCH:
	case ID_TOESPRING:
	case ID_UPPERLEVEL:
	case ID_EXTRALENGTH:
	case ID_FOOTCOMPRESSION:
		project->GetCommandProcessor()->Submit(
				new CommandShoeSetParameter(
						wxString::Format(_("Set %s to %s"),
								GetNameByID(event.GetId()), newFormula),
						project, event.GetId(), newFormula));
		m_panelPageShoe->Navigate();
		break;
	}

}

void FrameMain::OnMouseWheel(wxMouseEvent& event)
{
	std::cout << "OnMouseWheel( " << event.GetId() << " )\n";

}

wxString FrameMain::GetNameByID(int id)
{
	switch(id){

	case ID_MEASUREMENT_FOOTLENGTH:
		return _T("FootLength");
	case ID_MEASUREMENT_BALLGIRTH:
		return _T("BallGirth");
	case ID_MEASUREMENT_WAISTGIRTH:
		return _T("WaistGirth");
	case ID_MEASUREMENT_INSTEPGIRTH:
		return _T("InstepGirth");
	case ID_MEASUREMENT_LONGHEELGIRTH:
		return _T("LongHeelGirth");
	case ID_MEASUREMENT_SHORTHEELGIRTH:
		return _T("ShortHeelGirth");
	case ID_MEASUREMENT_ANGLEMIXING:
		return _T("AngleMixing");
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
		return _T("LegLengthDifference");

	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		return _T("BelowCrutchGirth");
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		return _T("BelowCrutchLevel");
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		return _T("MiddleOfCalfGirth");
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		return _T("MiddleOfCalfLevel");
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		return _T("AboveKneeGirth");
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		return _T("AboveKneeLevel");
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		return _T("OverKneeCapGirth");
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		return _T("OverKneeCapLevel");
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		return _T("BelowKneeGirth");
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		return _T("BelowKneeLevel");
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		return _T("MiddleOfShankGirth");
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		return _T("MiddleOfShankLevel");
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		return _T("AboveAnkleGirth");
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		return _T("AboveAnkleLevel");
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		return _T("OverAnkleBoneGirth");
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return _T("OverAnkleBoneLevel");

	case ID_HEELHEIGHT:
		return _T("HeelHeight");
	case ID_BALLHEIGHT:
		return _T("BallHeight");
	case ID_HEELPITCH:
		return _T("HeelPitch");
	case ID_TOESPRING:
		return _T("ToeSpring");
	case ID_UPPERLEVEL:
		return _T("UpperLevel");
	case ID_EXTRALENGTH:
		return _T("ExtraLenght");
	case ID_FOOTCOMPRESSION:
		return _T("FootCompression");
	}
	return _T("");
}

wxTextCtrl* FrameMain::GetTextCtrlByID(int id)
{
	switch(id){
	case ID_MEASUREMENT_FOOTLENGTH:
		return m_textCtrlFootLength;
	case ID_MEASUREMENT_BALLGIRTH:
		return m_textCtrlBallGirth;
	case ID_MEASUREMENT_WAISTGIRTH:
		return m_textCtrlWaistGirth;
	case ID_MEASUREMENT_INSTEPGIRTH:
		return m_textCtrlInstepGirth;
	case ID_MEASUREMENT_LONGHEELGIRTH:
		return m_textCtrlLongHeelGirth;
	case ID_MEASUREMENT_SHORTHEELGIRTH:
		return m_textCtrlShortHeelGirth;
	case ID_MEASUREMENT_ANGLEMIXING:
		return m_textCtrlAngleMixing;
	case ID_MEASUREMENT_LEGLENGTHDIFFERENCE:
		return m_textCtrlLegLengthDifference;

	case ID_MEASUREMENT_BELOWCRUTCHGIRTH:
		return m_textCtrlBelowCrutchGirth;
	case ID_MEASUREMENT_BELOWCRUTCHLEVEL:
		return m_textCtrlBelowCrutchLevel;
	case ID_MEASUREMENT_MIDDLEOFCALFGIRTH:
		return m_textCtrlMiddleOfCalfGirth;
	case ID_MEASUREMENT_MIDDLEOFCALFLEVEL:
		return m_textCtrlMiddleOfCalfLevel;
	case ID_MEASUREMENT_ABOVEKNEEGIRTH:
		return m_textCtrlAboveKneeGirth;
	case ID_MEASUREMENT_ABOVEKNEELEVEL:
		return m_textCtrlAboveKneeLevel;
	case ID_MEASUREMENT_OVERKNEECAPGIRTH:
		return m_textCtrlOverKneeCapGirth;
	case ID_MEASUREMENT_OVERKNEECAPLEVEL:
		return m_textCtrlOverKneeCapLevel;
	case ID_MEASUREMENT_BELOWKNEEGIRTH:
		return m_textCtrlBelowKneeGirth;
	case ID_MEASUREMENT_BELOWKNEELEVEL:
		return m_textCtrlBelowKneeLevel;
	case ID_MEASUREMENT_MIDDLEOFSHANKGIRTH:
		return m_textCtrlMiddleOfShankGirth;
	case ID_MEASUREMENT_MIDDLEOFSHANKLEVEL:
		return m_textCtrlMiddleOfShankLevel;
	case ID_MEASUREMENT_ABOVEANKLEGIRTH:
		return m_textCtrlAboveAnkleGirth;
	case ID_MEASUREMENT_ABOVEANKLELEVEL:
		return m_textCtrlAboveAnkleLevel;
	case ID_MEASUREMENT_OVERANKLEBONEGIRTH:
		return m_textCtrlOverAnkleBoneGirth;
	case ID_MEASUREMENT_OVERANKLEBONELEVEL:
		return m_textCtrlOverAnkleBoneLevel;

	case ID_HEELHEIGHT:
		return m_textCtrlHeelHeight;
	case ID_BALLHEIGHT:
		return m_textCtrlBallHeight;
	case ID_HEELPITCH:
		return m_textCtrlHeelPitch;
	case ID_TOESPRING:
		return m_textCtrlToeSpring;
	case ID_UPPERLEVEL:
		return m_textCtrlUpperLevel;
	case ID_EXTRALENGTH:
		return m_textCtrlExtraLength;
	case ID_FOOTCOMPRESSION:
		return m_textCtrlFootCompression;
	}
	return NULL;
}

void FrameMain::TransferParameterToTextCtrl(const ParameterFormula parameter,
		wxTextCtrl* ctrl, typeUnit type)
{
	FrameParent* parent = wxStaticCast(GetParent(), FrameParent);
	CollectionUnits * units = &(parent->units);

	if(ctrl->HasFocus()){
		ctrl->SetValue(parameter.formula);
	}else{
		if(parameter.errorFlag){
			ctrl->SetBackgroundColour(*wxRED);
			ctrl->SetValue(parameter.errorStr);
		} else{
			ctrl->SetBackgroundColour(wxNullColour);
			switch(type){
				case unitNone:
				ctrl->SetValue(wxString::Format(_T("%g"), parameter.value));
				break;
				case unitTime:
				ctrl->SetValue(
						units->Time.TextFromSIWithUnit(parameter.value));
				break;
				case unitDistance:
				ctrl->SetValue(
						units->Distance.TextFromSIWithUnit(parameter.value,
								1));
				break;
				case unitSmallDistance:
				ctrl->SetValue(
						units->SmallDistance.TextFromSIWithUnit(parameter.value
								,1));
				break;
				case unitTolerance:
				ctrl->SetValue(
						units->Tolerance.TextFromSIWithUnit(parameter.value
								,1));
				break;
				case unitAngle:
				ctrl->SetValue(
						units->Angle.TextFromSIWithUnit(parameter.value
								,1));
				break;
				case unitPercent:
				ctrl->SetValue(wxString::Format(_T("%g %%"), parameter.value*100));
				break;
				default:
				throw(std::logic_error(__FILE__ "TransferParameterToTextCtrl(): Unhandeled Type of unit."));
			}
		}
	}
}

void FrameMain::OnChoiceDisplay(wxCommandEvent& event)
{
	std::cout << "OnChoiceDisplay( " << event.GetId() << " )\n";

}

void FrameMain::OnToggleAnkleLock(wxCommandEvent& event)
{
	std::cout << "OnToggleAnkleLock( " << event.GetId() << " )\n";

}

void FrameMain::OnFileChangedScanFile(wxFileDirPickerEvent& event)
{
	std::cout << "OnFileChangedScanFile( " << event.GetId() << " )\n";
}

void FrameMain::OnFileChangedLastFile(wxFileDirPickerEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	project->LoadLastModel(event.GetPath());
	Refresh();
}

void FrameMain::OnQuickSetupMeasurements(wxCommandEvent& WXUNUSED(event))
{
	DialogQuickInitFoot dialog(this);
	if(dialog.ShowModal() == wxID_OK){
		Project* project = wxStaticCast(GetDocument(), Project);
		ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
		FrameParent* parent = wxStaticCast(GetParent(), FrameParent);
		CollectionUnits * units = &(parent->units);

		wxString lengthStr = units->Distance.TextFromSIWithUnit(dialog.length);

		project->GetCommandProcessor()->Submit(
				new CommandFootMeasurementSet(
				_("Set footlength to ") + lengthStr, project,
						projectview->active, ID_MEASUREMENT_FOOTLENGTH,
						lengthStr));

		wxString girthStr = wxString::Format(_T("footLength*%g"), dialog.width);
		project->GetCommandProcessor()->Submit(
				new CommandFootMeasurementSet(
				_("Set ballgirth to ") + girthStr, project,
						projectview->active, ID_MEASUREMENT_BALLGIRTH,
						girthStr));
	}
}

void FrameMain::OnChangeModel(wxCommandEvent& event)
{
	if(loopGuard) return;
	std::cout << "OnChangeModel( " << event.GetId() << " )\n";
	Project* project = wxStaticCast(GetDocument(), Project);
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	switch(event.GetId()){
	case ID_MEASUREMENTSYMMETRY:
		projectview->active = ProjectView::Both;
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Change symmetry"), project,
				ID_MEASUREMENTSYMMETRY, (int) !project->measurementsSymmetric));
		break;
	case ID_USEFOOTMEASUREMENTS:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Use foot measurements"),
						project,
						ID_MEASUREMENTSOURCE,
						(int) Project::fromMeasurements));
		break;
	case ID_USEFOOTSCAN:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Use foot scan"), project,
				ID_MEASUREMENTSOURCE,
						(int) Project::fromFootScan));
		break;
	case ID_USEBONEBASEDMODEL:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Use bone-based model"),
						project,
						ID_FOOTMODEL, (int) Project::boneBased));
		break;
	case ID_USELASTBASEDMODEL:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Use last-based model"),
						project,
						ID_FOOTMODEL, (int) Project::lastBased));
		break;
	}
}

void FrameMain::OnCopyMeasurements(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	switch(event.GetId()){
	case ID_COPYACTIVETOINACTIVE:
		project->GetCommandProcessor()->Submit(
				new CommandFootMeasurementsCopy(
						_("Copy active to inactive measurements"), project,
						projectview->active != ProjectView::Right));
		break;
	case ID_COPYLEFTTORIGHT:
		project->GetCommandProcessor()->Submit(
				new CommandFootMeasurementsCopy(
						_("Copy left to right measurements"), project, true));
		break;
	case ID_COPYRIGHTTOLEFT:
		project->GetCommandProcessor()->Submit(
				new CommandFootMeasurementsCopy(
						_("Copy right to left measurements"), project, false));
		break;
	}
}

void FrameMain::OnLoadFootSTL(wxCommandEvent& event)
{
	std::cout << "OnLoadFootSTL( " << event.GetId() << " )\n";
}

void FrameMain::OnEditBoneModel(wxCommandEvent& event)
{
	std::cout << "OnEditBoneModel( " << event.GetId() << " )\n";
}

void FrameMain::OnLoadBoneModel(wxCommandEvent& event)
{
	FrameParent* parent = wxStaticCast(GetParent(), FrameParent);

	wxFileDialog dialog(this, _("Open Foot Model..."), _T(""), _T(""),
			_("Foot Model (*.fmd; *.txt)|*.fmd;*.txt|All Files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(filepaths.lastFootDirectory)){
		dialog.SetDirectory(filepaths.lastFootDirectory);
	}

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		Project* project = wxStaticCast(GetDocument(), Project);

		if(project->LoadFootModel(fileName.GetFullPath())){
			filepaths.lastFootDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnSaveBoneModel(wxCommandEvent& event)
{
	FrameParent* parent = wxStaticCast(GetParent(), FrameParent);

	wxFileDialog dialog(this, _("Save Foot Model As..."), _T(""), _T(""),
			_("Foot Model (*.fmd; *.txt)|*.fmd;*.txt|All Files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(wxDir::Exists(filepaths.lastFootDirectory)){
		dialog.SetDirectory(filepaths.lastFootDirectory);
	}

//	if(project.fileName.IsOk()) dialog.SetFilename(
//			project.fileName.GetFullPath());

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		Project* project = wxStaticCast(GetDocument(), Project);
		if(project->SaveFootModel(fileName.GetFullPath())){
			filepaths.lastFootDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnConstructionSelection(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);

	switch(event.GetId()){
	case ID_SELECTCONSTRUCTION:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Set construction method"),
						project,
						ID_SELECTCONSTRUCTION, event.GetSelection()));
		break;
	case ID_CONSTRUCTIONEXPERIMENTAL:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(
						_("Select experimental generator"), project,
						ID_SELECTCONSTRUCTION, (int) Project::Experimental));
		break;
	case ID_CONSTRUCTIONWELDED:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(_("Select welted construction"),
						project,
						ID_SELECTCONSTRUCTION, (int) Project::Welted));
		break;
	case ID_CONSTRUCTIONCEMENTED:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(
						_("Select cemented construction"), project,
						ID_SELECTCONSTRUCTION, (int) Project::Cemented));
		break;
	case ID_CONSTRUCTIONMOLDED:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(
						_("Select molded sole construction"), project,
						ID_SELECTCONSTRUCTION, (int) Project::Molded));
		break;
	case ID_CONSTRUCTIONDUTCH:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(
						_("Select generator for Dutch clogs"), project,
						ID_SELECTCONSTRUCTION, (int) Project::Dutch));
		break;
	case ID_CONSTRUCTIONGETA:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetParameter(
						_("Select generator for Japanese getas"), project,
						ID_SELECTCONSTRUCTION, (int) Project::Geta));
		break;
	}
	TransferDataToWindow();
}

void FrameMain::OnLoadPattern(wxCommandEvent& event)
{
	std::cout << "OnLoadPattern( " << event.GetId() << " )\n";
}

void FrameMain::OnSavePattern(wxCommandEvent& event)
{
	std::cout << "OnSavePattern( " << event.GetId() << " )\n";
}

void FrameMain::OnSaveLast(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Save last..."), _T(""), _T(""),
			_("STL file (*.stl)|*.stl|All files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName;
		fileName = dialog.GetPath();
		Project* project = wxStaticCast(GetDocument(), Project);
		ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
		if(project->modeltype == Project::boneBased){
			project->SaveSkin(fileName.GetFullPath(),
					projectview->active != ProjectView::Right,
					projectview->active == ProjectView::Right);
		}else{
			project->SaveLast(fileName.GetFullPath(),
					projectview->active != ProjectView::Right,
					projectview->active == ProjectView::Right);
		}
	}
}

void FrameMain::OnSaveInsole(wxCommandEvent& event)
{
	std::cout << "OnSaveInsole( " << event.GetId() << " )\n";

}

void FrameMain::OnSaveSole(wxCommandEvent& event)
{
	std::cout << "OnSaveSole( " << event.GetId() << " )\n";

}

void FrameMain::OnSaveCutaway(wxCommandEvent& event)
{
	std::cout << "OnSaveCutaway( " << event.GetId() << " )\n";

}

void FrameMain::OnPackZip(wxCommandEvent& event)
{
	std::cout << "OnPackZip( " << event.GetId() << " )\n";

}

void FrameMain::OnToggleStereo3D(wxCommandEvent& event)
{
	if(m_canvas3D->stereoMode == stereoOff){
		m_canvas3D->stereoMode = stereoAnaglyph;
	}else{
		m_canvas3D->stereoMode = stereoOff;
	}
	m_menuView->Check(ID_STEREO3D, m_canvas3D->stereoMode != stereoOff);
	Refresh();
}

void FrameMain::OnViewChange(wxCommandEvent& event)
{
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	TransferDataFromWindow();

	switch(event.GetId()){
	case ID_SHOWLEFT:
		projectview->showLeft = event.IsChecked();
		break;
	case ID_SHOWRIGHT:
		projectview->showRight = event.IsChecked();
		break;
	}
	TransferDataToWindow();
	Refresh();
}

void FrameMain::OnSetupBackgroundImages(wxCommandEvent& event)
{
	std::cout << "OnSetupBackgroundImages( " << event.GetId() << " )\n";
}

void FrameMain::OnDebugParser(wxCommandEvent& event)
{
	(new FrameDebugParser(this))->Show();
}

