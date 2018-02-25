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

#include "../project/command/CommandFootModelSetValue.h"

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

//	m_menuEdit->Append(wxID_UNDO);
//	m_menuEdit->Append(wxID_REDO);
//	m_menuEdit->Append(
//			new wxMenuItem(m_menuEdit, wxID_UNDO,
//					wxString(_("&Undo")) + wxT('\t') + wxT("CTRL+Z"),
//					_("Undo last command"), wxITEM_NORMAL));
//	m_menuEdit->Append(
//			new wxMenuItem(m_menuEdit, wxID_REDO,
//					wxString(_("&Redo")) + wxT('\t') + wxT("CTRL+Y"),
//					_("Redo last undone command"), wxITEM_NORMAL));

	m_menuHelp->AppendSeparator();
	m_menuHelp->Append(wxID_HELP, _("&Help") + wxT("\tF1"));
	m_menuHelp->Append(wxID_ABOUT);

//	doc->GetCommandProcessor()->SetEditMenu(m_menuEdit);
	doc->GetCommandProcessor()->Initialize();

	this->config = config;
	settings.GetConfigFrom(config);

	m_canvas3D->SetProjectView(wxStaticCast(view, ProjectView));
	settings.WriteToCanvas(m_canvas3D);

	thread = NULL;
	updateVolume = false;

	dialogSetupStereo3D = new DialogSetupStereo3D(this, &settings);
	dialogSetupUnits = new DialogSetupUnits(this, &settings);

	TransferDataToWindow();

	this->Connect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshCanvas));
	this->Connect(ID_REFRESHVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshView));
	this->Connect(ID_THREADLASTDONE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::LastCalculationDone));

}

FrameMain::~FrameMain()
{
	printf("Destructing Frame\n");
	if(thread != NULL){
		thread->Wait();
		delete thread;
	}

	this->Disconnect(ID_THREADLASTDONE, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::LastCalculationDone));
	this->Disconnect(ID_REFRESHVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshView));
	this->Disconnect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshCanvas));

	settings.WriteConfigTo(config);
}

void FrameMain::OnClose(wxCloseEvent& event)
{
	wxDocument* doc = this->GetDocument();
	wxList tempDocs = doc->GetDocumentManager()->GetDocuments();
	wxList tempViews = doc->GetViews();

	printf("In frame: %u docs, %u views\n", tempDocs.GetCount(),
			tempViews.GetCount());

	printf("Closing Frame\n");

	if(tempDocs.GetCount() > 1){
		event.Skip(); // Only close this window, by passing the event to the default handler.
		return;
	}
	if(tempViews.GetCount() > 1){
		event.Skip(); // Only close this window, by passing the event to the default handler.
		return;
	}
	wxWindow* main = this->GetParent();
	printf("Closing Application from Frame\n");
	main->Close(); // Exit app by closing main window, this will close this window as well.
}

bool FrameMain::TransferDataToWindow()
{
	UpdateProject();

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
	const Foot *foot = &(project->footL);

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
	m_sliderMixing->SetValue(shoe->mixing * 100.0);
	m_textCtrlResultHeelHeight->SetValue(
			settings.Distance.TextFromSIWithUnit(shoe->heelHeight, 1));
	m_textCtrlResultBallHeight->SetValue(
			settings.Distance.TextFromSIWithUnit(shoe->ballHeight, 1));
	m_textCtrlResultToeAngle->SetValue(
			settings.Angle.TextFromSIWithUnit(shoe->toeAngle, 1));
	m_textCtrlResultMixing->SetValue(
			settings.Percent.TextFromSIWithUnit(shoe->mixing, 1));

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

	Foot *foot = project->activeFoot;

	for(size_t n = 0; n < foot->bones.size(); n++){
		wxString temp = m_gridBoneLength->GetCellValue(n, 0);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].lengthv.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetValue(
							_("Set ") + foot->bones[n].name
									+ _(" length to ") + temp, project, n,
							Bone::stringIdentifier::stringLength, temp));
			project->GetCommandProcessor()->SetMenuStrings();
		}
	}
	for(size_t n = 0; n < foot->bones.size(); n++){
		wxString temp = m_gridBoneDiameter->GetCellValue(n, 0);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].r1v.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetValue(
					_("Set ") + foot->bones[n].name + _(" r1 to ") + temp,
							project, n, Bone::stringIdentifier::stringR1,
							temp));
			project->GetCommandProcessor()->SetMenuStrings();
		}

		temp = m_gridBoneDiameter->GetCellValue(n, 2);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].r2v.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetValue(
					_("Set ") + foot->bones[n].name + _(" r2 to ") + temp,
							project, n, Bone::stringIdentifier::stringR2,
							temp));
			project->GetCommandProcessor()->SetMenuStrings();
		}
	}
	for(size_t n = 0; n < foot->bones.size(); n++){
		wxString temp = m_gridSkin->GetCellValue(n, 0);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].s1v.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetValue(
					_("Set ") + foot->bones[n].name + _(" s1 to ") + temp,
							project, n, Bone::stringIdentifier::stringS1,
							temp));
			project->GetCommandProcessor()->SetMenuStrings();
		}

		temp = m_gridSkin->GetCellValue(n, 2);
		temp = temp.Trim(false).Trim(true);
		if(foot->bones[n].s2v.Cmp(temp) != 0){
			project->GetCommandProcessor()->Submit(
					new CommandFootModelSetValue(
					_("Set ") + foot->bones[n].name + _(" s2 to ") + temp,
							project, n, Bone::stringIdentifier::stringS2,
							temp));
			project->GetCommandProcessor()->SetMenuStrings();
		}
	}
	UpdateProject();
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
	this->Refresh(); // FIXME: Recursive refresh not work with GTK1. Call Refresh on every child-dialog by hand.
}

void FrameMain::UpdateProject(void)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	if(project->updateState == 0) return;

	const bool multiThreading = true;
	if(multiThreading){
		if(thread == NULL){
			project->updateState = 1;
			project->Update(); // One update up in front to get all internal variables right for displaying.
			thread = new LastGenerationThread(this, project);
			thread->Create();
			thread->Run();
			updateVolume = false;
		}else{
			updateVolume = true;
		}
	}else{
		while(project->Update());
		updateVolume = false;
	}
	m_canvas3D->Refresh();
	Refresh();
}

void FrameMain::LastCalculationDone(wxCommandEvent& event)
{
	if(thread != NULL){
		thread->Wait();
		delete thread;
		thread = NULL;
	}
	if(updateVolume){
		Project* project = wxStaticCast(GetDocument(), Project);
		thread = new LastGenerationThread(this, project);
		thread->Create();
		thread->Run();
	}
	m_canvas3D->Refresh();
	Refresh();
}

void FrameMain::OnConstructionSelection(wxCommandEvent& event)
{
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

	switch(event.GetId()){
	case ID_SHOWLEFT:
		projectview->showLeft = event.IsChecked();

		if(event.IsChecked()){
			project->activeFoot = &(project->footL);
			project->active = Project::Left;
			projectview->foot = &(project->footL);
		}else{
			if(projectview->showRight){
				project->activeFoot = &(project->footR);
				project->active = Project::Right;
				projectview->foot = &(project->footR);
			}
		}
		break;
	case ID_SHOWRIGHT:
		projectview->showRight = event.IsChecked();

		if(event.IsChecked()){
			project->activeFoot = &(project->footR);
			project->active = Project::Right;
			projectview->foot = &(project->footR);
		}else{
			if(projectview->showLeft){
				project->activeFoot = &(project->footL);
				project->active = Project::Left;
				projectview->foot = &(project->footL);
			}
		}
		break;
	}

	TransferDataFromWindow();
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
		Foot *foot = project->activeFoot;
		foot->length = dialog.length;
		foot->ballwidth = dialog.width;
		foot->anklewidth = dialog.width;
		foot->heelwidth = dialog.width;
		project->FlagForUpdate();
		TransferDataToWindow();
	}

}
void FrameMain::OnText(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
//	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	Foot *foot = project->activeFoot;

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

	switch(event.GetId()){
	case ID_TEXTFOOTLENGTH:
		foot->length = parser.GetNumber(event.GetString());
		break;
	case ID_TEXTFOOTWIDTH:
		foot->ballwidth = parser.GetNumber(event.GetString());
		break;
	case ID_TEXTHEELWIDTH:
		foot->heelwidth = parser.GetNumber(event.GetString());
		break;
	case ID_TEXTANKLEWIDTH:
		foot->anklewidth = parser.GetNumber(event.GetString());
		break;
	case ID_TEXTLEGLENGTH:
		project->legLengthDifference = parser.GetNumber(event.GetString());
		break;
	case ID_TEXTHEELHEIGHT:
		project->shoe.exprHeelHeight = event.GetString();
		break;
	case ID_TEXTBALLHEIGHT:
		project->shoe.exprBallHeight = event.GetString();
		break;
	case ID_TEXTTOEPITCH:
		project->shoe.exprToeAngle = event.GetString();
		break;
	case ID_TEXTMIXINGANGLE:
		project->shoe.mixing = parser.GetNumber(event.GetString());
		break;
	}
	project->FlagForUpdate();
	TransferDataToWindow();
}

void FrameMain::OnCellChange(wxGridEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	TransferDataFromWindow();
	project->FlagForUpdate();
	TransferDataToWindow();
}

void FrameMain::OnPreset(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);

	Shoe * shoe = &(project->shoe);
	// 0.26 m is the average footlength (= size EU 39).
	switch(event.GetId()){
	case ID_PRESETFLATS:
		shoe->exprHeelHeight = _T("0 cm");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETCLASSIC:
		shoe->exprHeelHeight = _T("3 cm");
		shoe->exprBallHeight = _T("1.5 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETPLATEAU:
		shoe->exprHeelHeight = _T("11 cm");
		shoe->exprBallHeight = _T("9 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHLOW:
		shoe->exprHeelHeight = _T("7 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHMID:
		shoe->exprHeelHeight = _T("10 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETHHHIGH:
		shoe->exprHeelHeight = _T("13 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETPLATFORM:
		shoe->exprHeelHeight = _T("15 cm * (L/26cm)");
		shoe->exprBallHeight = _T("5 cm * (L/26cm)");
		shoe->exprToeAngle = _T("0 deg");
		break;
	case ID_PRESETPONY:
		shoe->exprHeelHeight = _T("16 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("45 deg");
		break;
	case ID_PRESETBALLET:
		shoe->exprHeelHeight = _T("20 cm * (L/26cm)");
		shoe->exprBallHeight = _T("0 cm");
		shoe->exprToeAngle = _T("90 deg");
		break;
	}
	project->FlagForUpdate();
	TransferDataToWindow();
}

void FrameMain::OnScroll(wxScrollEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);

	Shoe * shoe = &(project->shoe);
	shoe->mixing = ((double) event.GetPosition()) / 100.0;
	TransferDataToWindow();
}

void FrameMain::OnScrollChange(wxScrollEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);

	Shoe * shoe = &(project->shoe);
	shoe->mixing = ((double) event.GetPosition()) / 100.0;
	project->FlagForUpdate();
	TransferDataToWindow();
}

void FrameMain::OnToggleAnkleLock(wxCommandEvent& event)
{
}

void FrameMain::OnUndo(wxCommandEvent& event)
{
	printf("Undo\n");
	wxDocument *doc = GetDocument();
	doc->GetCommandProcessor()->Undo();
	TransferDataToWindow();
	Refresh();
}

void FrameMain::OnRedo(wxCommandEvent& event)
{
	printf("Redo\n");
	wxDocument *doc = GetDocument();
	doc->GetCommandProcessor()->Redo();
	TransferDataToWindow();
	Refresh();
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
}

void FrameMain::OnCopyMeasurements(wxCommandEvent& event)
{
}

void FrameMain::OnSetupBackgroundImages(wxCommandEvent& event)
{
}

void FrameMain::On3DSelect(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();
	OpenGLPick result;
	m_canvas3D->OnPick(result, x, y);
	if(result.HasHits()){
		result.SortByNear();
		if(result.Get(0, 1) == 1){
			const int boneNr = result.Get(0, 2);
			ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
			const Foot *foot = projectview->foot;
			if(boneNr < foot->bones.size()){
				m_statusBar->SetStatusText(foot->bones[boneNr].name);

				m_gridBoneLength->SelectRow(boneNr);
				m_gridBoneDiameter->SelectRow(boneNr);
				m_gridSkin->SelectRow(boneNr);
			}
		}else{
			m_statusBar->SetStatusText(wxString());
		}
	}else{
		m_statusBar->SetStatusText(wxString());
	}
}

void FrameMain::OnChoiceDisplay(wxCommandEvent& event)
{
}

