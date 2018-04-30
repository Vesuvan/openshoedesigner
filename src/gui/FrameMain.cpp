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
//#include <wx/file.h>
#include <wx/cmdproc.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <math.h>
#include <cfloat>

#include "../project/command/CommandFootModelSetParameter.h"
#include "../project/command/CommandFootSetSize.h"
#include "../project/command/CommandProjectSetLegLengthDifference.h"
#include "../project/command/CommandShoePreset.h"
#include "../project/command/CommandShoeSetParameter.h"

FrameMain::FrameMain(wxDocument* doc, wxView* view, wxConfig* config,
		wxDocParentFrame* parent)
		: GUIFrameMain(doc, view, parent)
{
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

	m_menuHelp->AppendSeparator();
	m_menuHelp->Append(wxID_HELP, _("&Help") + wxT("\tF1"));
	m_menuHelp->Append(wxID_ABOUT);

	doc->GetCommandProcessor()->SetEditMenu(m_menuEdit);
	doc->GetCommandProcessor()->Initialize();

	this->config = config;
	settings.GetConfigFrom(config);

	m_canvas3D->SetProjectView(wxStaticCast(view, ProjectView));
	settings.WriteToCanvas(m_canvas3D);

	dialogSetupStereo3D = new DialogSetupStereo3D(this, &settings);
	dialogSetupUnits = new DialogSetupUnits(this, &settings);

	TransferDataToWindow();

	this->Connect(ID_3DSELECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::On3DSelect));
	this->Connect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshCanvas));
	this->Connect(ID_REFRESH, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshView));

//	timer.SetOwner(this);
//	this->Connect(wxEVT_TIMER, wxTimerEventHandler(FrameMain::OnTimer), NULL,
//			this);
//	timer.Start(100);
//	midi.Open(3);
}

FrameMain::~FrameMain()
{
	printf("FrameMain: Destructor called\n");

//	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(FrameMain::OnTimer), NULL,
//			this);

	this->Disconnect(ID_REFRESH, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshView));
	this->Disconnect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshCanvas));
	this->Disconnect(ID_3DSELECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::On3DSelect));
	settings.WriteConfigTo(config);
}

bool FrameMain::TransferDataToWindow()
{
	const ProjectView* projectview = wxStaticCast(GetView(), ProjectView);

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

	Project* project = wxStaticCast(GetDocument(), Project);
	const Foot *foot = project->GetActiveFoot();

	m_textCtrlFootLength->SetValue(
			settings.Distance.TextFromSIWithUnit(foot->length, 1));
	m_textCtrlFootWidth->SetValue(
			settings.Distance.TextFromSIWithUnit(foot->ballwidth, 1));
	m_textCtrlHeelWidth->SetValue(
			settings.Distance.TextFromSIWithUnit(foot->heelwidth, 1));
	m_textCtrlAnkleWidth->SetValue(
			settings.Distance.TextFromSIWithUnit(foot->anklewidth, 1));
	m_textCtrlLegLengthDifference->SetValue(
			settings.Distance.TextFromSIWithUnit(project->legLengthDifference,
					1));

	m_textCtrlShoeSizeEU->SetValue(
			wxString::Format(_T("%g"), round(foot->GetSize(Foot::EU))));
	m_textCtrlShoeSizeUS->SetValue(
			wxString::Format(_T("%g"), round(foot->GetSize(Foot::US))));
	m_textCtrlShoeSizeUK->SetValue(
			wxString::Format(_T("%g"), round(foot->GetSize(Foot::UK))));
	m_textCtrlShoeSizeCN->SetValue(
			wxString::Format(_T("%g"), round(foot->GetSize(Foot::CN))));
	m_textCtrlShoeSizeJP->SetValue(
			wxString::Format(_T("%g"), round(foot->GetSize(Foot::JP))));
	m_textCtrlShoeSizeAU->SetValue(
			wxString::Format(_T("%g"), round(foot->GetSize(Foot::AU))));

	const unsigned int N = foot->GetBoneCount();
	if(m_gridBoneLength->GetNumberRows() == 0) m_gridBoneLength->AppendRows(N);
	for(size_t n = 0; n < foot->bones.size(); n++){
		m_gridBoneLength->SetRowLabelValue(n, foot->bones[n].name);
		m_gridBoneLength->SetCellValue(n, 0, foot->bones[n].lengthv);
		m_gridBoneLength->SetCellValue(n, 1,
				settings.SmallDistance.TextFromSIWithUnit(foot->bones[n].length,
						1));
		m_gridBoneLength->SetReadOnly(n, 1);
		m_gridBoneLength->SetCellAlignment(n, 1, wxALIGN_RIGHT, wxALIGN_TOP);
	}

	if(m_gridBoneDiameter->GetNumberRows() == 0) m_gridBoneDiameter->AppendRows(
			N);
	for(size_t n = 0; n < foot->bones.size(); n++){
		m_gridBoneDiameter->SetRowLabelValue(n, foot->bones[n].name);
		m_gridBoneDiameter->SetCellValue(n, 0, foot->bones[n].r1v);
		m_gridBoneDiameter->SetCellValue(n, 1,
				settings.SmallDistance.TextFromSIWithUnit(foot->bones[n].r1,
						1));
		m_gridBoneDiameter->SetCellValue(n, 2, foot->bones[n].r2v);
		m_gridBoneDiameter->SetCellValue(n, 3,
				settings.SmallDistance.TextFromSIWithUnit(foot->bones[n].r2,
						1));
		m_gridBoneDiameter->SetReadOnly(n, 1);
		m_gridBoneDiameter->SetReadOnly(n, 3);
		m_gridBoneDiameter->SetCellAlignment(n, 1, wxALIGN_RIGHT, wxALIGN_TOP);
		m_gridBoneDiameter->SetCellAlignment(n, 3, wxALIGN_RIGHT, wxALIGN_TOP);
	}

	if(m_gridSkin->GetNumberRows() == 0) m_gridSkin->AppendRows(N);
	for(size_t n = 0; n < foot->bones.size(); n++){
		m_gridSkin->SetRowLabelValue(n, foot->bones[n].name);
		m_gridSkin->SetCellValue(n, 0, foot->bones[n].s1v);
		m_gridSkin->SetCellValue(n, 1,
				settings.SmallDistance.TextFromSIWithUnit(foot->bones[n].s1,
						1));
		m_gridSkin->SetCellValue(n, 2, foot->bones[n].s2v);
		m_gridSkin->SetCellValue(n, 3,
				settings.SmallDistance.TextFromSIWithUnit(foot->bones[n].s2,
						1));
		m_gridSkin->SetReadOnly(n, 1);
		m_gridSkin->SetReadOnly(n, 3);
		m_gridSkin->SetCellAlignment(n, 1, wxALIGN_RIGHT, wxALIGN_TOP);
		m_gridSkin->SetCellAlignment(n, 3, wxALIGN_RIGHT, wxALIGN_TOP);
	}

	Shoe * shoe = &(project->shoe);
	m_textCtrlHeelHeight->SetValue(shoe->exprHeelHeight);
	m_textCtrlBallHeight->SetValue(shoe->exprBallHeight);
	m_textCtrlToeAngle->SetValue(shoe->exprToeAngle);

	m_sliderMixing->SetValue(foot->mixing * 100.0);

	m_textCtrlResultHeelHeight->SetValue(
			settings.Distance.TextFromSIWithUnit(foot->heelHeight, 1));
	m_textCtrlResultBallHeight->SetValue(
			settings.Distance.TextFromSIWithUnit(foot->ballHeight, 1));
	m_textCtrlResultToeAngle->SetValue(
			settings.Angle.TextFromSIWithUnit(foot->toeAngle, 1));
	m_textCtrlResultMixing->SetValue(
			settings.Percent.TextFromSIWithUnit(foot->mixing, 1));

	if(dialogSetupStereo3D->IsShown()) dialogSetupStereo3D->TransferDataToWindow();

	return true;
}

bool FrameMain::TransferDataFromWindow()
{
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	Project* project = wxStaticCast(GetDocument(), Project);

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

	const Foot *foot = project->GetActiveFoot();

	for(size_t n = 0; n < foot->bones.size(); n++){
		wxString temp = m_gridBoneLength->GetCellValue(n, 0);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].lengthv.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetParameter(
							_("Set ") + foot->bones[n].name
									+ _(" length to ") + temp, project, n,
							Bone::stringIdentifier::stringLength, temp));
		}
	}
	for(size_t n = 0; n < foot->bones.size(); n++){
		wxString temp = m_gridBoneDiameter->GetCellValue(n, 0);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].r1v.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetParameter(
					_("Set ") + foot->bones[n].name + _(" r1 to ") + temp,
							project, n, Bone::stringIdentifier::stringR1,
							temp));
		}

		temp = m_gridBoneDiameter->GetCellValue(n, 2);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].r2v.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetParameter(
					_("Set ") + foot->bones[n].name + _(" r2 to ") + temp,
							project, n, Bone::stringIdentifier::stringR2,
							temp));
		}
	}
	for(size_t n = 0; n < foot->bones.size(); n++){
		wxString temp = m_gridSkin->GetCellValue(n, 0);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].s1v.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetParameter(
					_("Set ") + foot->bones[n].name + _(" s1 to ") + temp,
							project, n, Bone::stringIdentifier::stringS1,
							temp));
		}

		temp = m_gridSkin->GetCellValue(n, 2);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].s2v.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetParameter(
					_("Set ") + foot->bones[n].name + _(" s2 to ") + temp,
							project, n, Bone::stringIdentifier::stringS2,
							temp));
		}
	}
	return true;
}

void FrameMain::RefreshCanvas(wxCommandEvent& event)
{
	settings.WriteToCanvas(m_canvas3D);
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

void FrameMain::OnClose(wxCloseEvent& event)
{
	wxDocument* doc = this->GetDocument();
	wxList tempDocs = doc->GetDocumentManager()->GetDocuments();
	wxList tempViews = doc->GetViews();

	printf("FrameMain: %u docs, %u views\n", tempDocs.GetCount(),
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

void FrameMain::OnConstructionSelection(wxCommandEvent& event)
{
	event.Skip();
}

void FrameMain::OnLoadFootModel(wxCommandEvent& event)
{
	wxFileDialog dialog(this, _("Open Foot Model..."), _T(""), _T(""),
			_("Foot Model (*.fmd; *.txt)|*.fmd;*.txt|All Files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(settings.lastFootDirectory)){
		dialog.SetDirectory(settings.lastFootDirectory);
	}

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		Project* project = wxStaticCast(GetDocument(), Project);

		if(project->LoadModel(fileName.GetFullPath())){
			settings.lastFootDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnSaveFootModel(wxCommandEvent& event)
{

	wxFileDialog dialog(this, _("Save Foot Model As..."), _T(""), _T(""),
			_("Foot Model (*.fmd; *.txt)|*.fmd;*.txt|All Files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(wxDir::Exists(settings.lastFootDirectory)){
		dialog.SetDirectory(settings.lastFootDirectory);
	}

//	if(project.fileName.IsOk()) dialog.SetFilename(
//			project.fileName.GetFullPath());

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		Project* project = wxStaticCast(GetDocument(), Project);
		if(project->SaveModel(fileName.GetFullPath())){
			settings.lastFootDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnLoadPattern(wxCommandEvent& event)
{
}

void FrameMain::OnSavePattern(wxCommandEvent& event)
{
}

void FrameMain::OnSetupFoot(wxCommandEvent& event)
{

}

void FrameMain::OnSetupShoe(wxCommandEvent& event)
{

}

void FrameMain::OnEditWalkCycle(wxCommandEvent& event)
{

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
		project->SaveSkin(fileName.GetFullPath());
	}
}

void FrameMain::OnSaveInsole(wxCommandEvent& event)
{
}

void FrameMain::OnSaveSole(wxCommandEvent& event)
{
}

void FrameMain::OnSaveCutaway(wxCommandEvent& event)
{
}

void FrameMain::OnPackZip(wxCommandEvent& event)
{
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
	Project* project = wxStaticCast(GetDocument(), Project);
	TransferDataFromWindow();

	switch(event.GetId()){
	case ID_SHOWLEFT:
		projectview->showLeft = event.IsChecked();

		if(event.IsChecked()){
			project->active = Project::Left;
		}else{
			if(projectview->showRight){
				project->active = Project::Right;
			}
		}
		break;
	case ID_SHOWRIGHT:
		projectview->showRight = event.IsChecked();

		if(event.IsChecked()){
			project->active = Project::Right;
		}else{
			if(projectview->showLeft){
				project->active = Project::Left;
			}
		}
		break;
	}
	TransferDataToWindow();
	Refresh();
}

void FrameMain::OnSetupStereo3D(wxCommandEvent& event)
{
	dialogSetupStereo3D->Show();
	dialogSetupStereo3D->Raise();
}

void FrameMain::OnSetupUnits(wxCommandEvent& event)
{
	dialogSetupUnits->Show();
	dialogSetupUnits->Raise();
}

void FrameMain::OnSelectLanguage(wxCommandEvent& event)
{
	long lng =
			wxGetSingleChoiceIndex(
					_T(
							"Please choose language:\nChanges will take place after restart!"),
					_T("Language"), WXSIZEOF(langNames), langNames);
	if(lng >= 0) config->Write(_T("Language"), langNames[lng]);
}

void FrameMain::OnDebugParser(wxCommandEvent& event)
{
	(new FrameDebugParser(this))->Show();
}

void FrameMain::OnPageChange(wxNotebookEvent& event)
{
}

void FrameMain::OnSetByShoeSize(wxCommandEvent& event)
{
	DialogQuickInitFoot dialog(this);
	if(dialog.ShowModal() == wxID_OK){
		Project* project = wxStaticCast(GetDocument(), Project);
		const Foot *foot = project->GetActiveFoot();
		if(fabs(foot->length - dialog.length) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set footlength to %g"),
								dialog.length), project, Foot::Length,
						dialog.length));
		if(fabs(foot->ballwidth - dialog.width) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set ballwidth to %g"),
								dialog.width), project, Foot::BallWidth,
						dialog.width));

		if(fabs(foot->anklewidth - dialog.width) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set anklewidth to %g"),
								dialog.width), project, Foot::AnkleWidth,
						dialog.width));
		if(fabs(foot->heelwidth - dialog.width) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set heelwidth to %g"),
								dialog.width), project, Foot::HeelWidth,
						dialog.width));
	}
}
void FrameMain::OnText(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
//	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	const Foot *foot = project->GetActiveFoot();

	MathParser parser(false);
	parser.AddAllowedUnit(_T("mm"), 1e-3);
	parser.AddAllowedUnit(_T("cm"), 1e-2);
	parser.AddAllowedUnit(_T("m"), 1);
	parser.AddAllowedUnit(_T("in"), 2.54e-2);
	parser.AddAllowedUnit(_T("ft"), 0.3048);
	parser.AddAllowedUnit(_T("%"), 1e-2);
	parser.AddAllowedUnit(_T("rad"), 1);
	parser.AddAllowedUnit(_T("deg"), 0.017453);
	parser.AddAllowedUnit(_T("gon"), 0.015708);

	const double temp = parser.GetNumber(event.GetString());

	switch(event.GetId()){
	case ID_TEXTFOOTLENGTH:
		project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set footlength to %g"), temp),
						project, Foot::Length, temp));

		break;
	case ID_TEXTFOOTWIDTH:
		project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set ballwidth to %g"), temp),
						project, Foot::BallWidth, temp));
		break;
	case ID_TEXTHEELWIDTH:
		project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set heelwidth to %g"), temp),
						project, Foot::HeelWidth, temp));
		break;
	case ID_TEXTANKLEWIDTH:
		project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set anklewidth to %g"), temp),
						project, Foot::AnkleWidth, temp));
		break;
	case ID_TEXTLEGLENGTH:
		project->GetCommandProcessor()->Submit(
				new CommandProjectSetLegLengthDifference(
						wxString::Format(_("Set leglengthdifference to %g"),
								temp), project, temp));
		break;
	case ID_TEXTHEELHEIGHT:
		project->GetCommandProcessor()->Submit(
				new CommandShoeSetParameter(
				_("Set heelheight to ") + event.GetString(), project, 0,
						event.GetString()));
		break;
	case ID_TEXTBALLHEIGHT:
		project->GetCommandProcessor()->Submit(
				new CommandShoeSetParameter(
				_("Set ballheight to ") + event.GetString(), project, 1,
						event.GetString()));
		break;
	case ID_TEXTTOEPITCH:
		project->GetCommandProcessor()->Submit(
				new CommandShoeSetParameter(
				_("Set toe pitch to ") + event.GetString(), project, 2,
						event.GetString()));
		break;
	case ID_TEXTMIXINGANGLE:
		project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set mixing to %g"), temp), project,
						Foot::Mixing, temp));
		break;
	}

}

void FrameMain::OnCellChange(wxGridEvent& event)
{
	TransferDataFromWindow();
}

void FrameMain::OnPreset(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	project->GetCommandProcessor()->Submit(
			new CommandShoePreset(
					wxString::Format(_("Set preset to %i"), event.GetId()),
					project, event.GetId()));
	TransferDataToWindow();
}

void FrameMain::OnScroll(wxScrollEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	const Foot * foot = project->GetActiveFoot();
	const double mixing = ((double) event.GetPosition()) / 100.0;

	if(fabs(mixing - foot->mixing) > FLT_EPSILON){
		project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set mixing to %g"), mixing),
						project, Foot::Mixing, mixing));
		TransferDataToWindow();
		//TODO: Adapt for gapfree scrolling
	}
}

void FrameMain::OnScrollChange(wxScrollEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	const Foot * foot = project->GetActiveFoot();
	const double mixing = ((double) event.GetPosition()) / 100.0;

	if(fabs(mixing - foot->mixing) > FLT_EPSILON){
		project->GetCommandProcessor()->Submit(
				new CommandFootSetSize(
						wxString::Format(_("Set mixing to %g"), mixing),
						project, Foot::Mixing, mixing));
		TransferDataToWindow();
	}
}

void FrameMain::OnToggleAnkleLock(wxCommandEvent& event)
{
}

void FrameMain::OnLoadFootSTL(wxCommandEvent& event)
{
}

void FrameMain::OnSetSymmetry(wxCommandEvent& event)
{
	switch(event.GetId()){
	case ID_FULLSYMMETRY:
		break;
	case ID_SYMMETRICMODEL:
		break;
	case ID_INDIVIDUALMODEL:
		break;
	default:
		break;
	}
	event.Skip();
}

void FrameMain::OnCopyMeasurements(wxCommandEvent& event)
{
}

void FrameMain::OnSetupBackgroundImages(wxCommandEvent& event)
{
}

void FrameMain::OnIdle(wxIdleEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	project->Recalculate();
}

void FrameMain::OnChoiceDisplay(wxCommandEvent& event)
{
}

