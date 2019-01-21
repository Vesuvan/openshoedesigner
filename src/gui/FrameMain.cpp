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

#include "../project/command/CommandFootMeasurementSet.h"
//#include "../project/command/CommandFootMeasurementSet.h"
#include "../project/command/CommandFootModelSetParameter.h"
#include "../project/command/CommandProjectSetLegLengthDifference.h"
#include "../project/command/CommandShoePreset.h"
#include "../project/command/CommandShoeSetParameter.h"
#include "FrameParent.h"

FrameMain::FrameMain(wxDocument* doc, wxView* view, wxConfig* config,
		wxDocParentFrame* parent)
		: GUIFrameMain(doc, view, parent)
{
	this->config = config;

	presets.ReadFile(_T("data/ShoePresets.ini"));

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
	DisplaySettings* settings = &(parentframe->settings);

	m_canvas3D->SetProjectView(wxStaticCast(view, ProjectView));
	m_panelFootMeasurements->SetDocView(doc, view);
	m_panelFootMeasurements->SetDisplaySettings(settings);
	m_panelLegMeasurements->SetDocView(doc, view);
	m_panelLegMeasurements->SetDisplaySettings(settings);
	settings->WriteToCanvas(m_canvas3D);

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

//	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(FrameMain::OnTimer), NULL,
//			this);

	this->Disconnect(ID_REFRESHVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshView));
	this->Disconnect(ID_REFRESH3DVIEW, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::RefreshCanvas));
	this->Disconnect(ID_3DSELECT, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(FrameMain::On3DSelect));
}

bool FrameMain::TransferDataToWindow()
{
	const ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	Project* project = wxStaticCast(GetDocument(), Project);
	const FootMeasurements * foot = projectview->GetActiveFootMeasurements();

	{
		wxArrayString newStrings;
		newStrings.Add(_("Custom"));
		for(size_t n = 0; n < presets.section.size(); ++n)
			newStrings.Add(presets.section[n].param[0].value);

		wxArrayString temp = m_choiceShoeType->GetStrings();
		if(newStrings != temp){
			m_choiceShoeType->Set(newStrings);
			m_choiceShoeType->SetSelection(0);
		}
	}

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

	Shoe * shoe = &(project->shoe);

	TransferParameterToTextCtrl(shoe->heelHeight, m_textCtrlHeelHeight);
	TransferParameterToTextCtrl(shoe->ballHeight, m_textCtrlBallHeight);
	TransferParameterToTextCtrl(shoe->heelPitch, m_textCtrlHeelPitch,false);
	TransferParameterToTextCtrl(shoe->toeSpring, m_textCtrlToeSpring,false);
	TransferParameterToTextCtrl(shoe->upperLevel, m_textCtrlUpperLevel,false);
	TransferParameterToTextCtrl(shoe->extraLength, m_textCtrlExtraLength);
	TransferParameterToTextCtrl(shoe->footCompression,
			m_textCtrlFootCompression,false);

//	m_textCtrlToeAngle->SetValue(shoe->exprToeAngle);
//
//	m_sliderMixing->SetValue(foot->mixing * 100.0);
//
//	m_textCtrlResultHeelHeight->SetValue(
//			settings.Distance.TextFromSIWithUnit(foot->heelHeight, 1));
//	m_textCtrlResultBallHeight->SetValue(
//			settings.Distance.TextFromSIWithUnit(foot->ballHeight, 1));
//	m_textCtrlResultToeAngle->SetValue(
//			settings.Angle.TextFromSIWithUnit(foot->toeAngle, 1));
//	m_textCtrlResultMixing->SetValue(
//			settings.Percent.TextFromSIWithUnit(foot->mixing, 1));

	m_panelFootMeasurements->TransferDataToWindow();
	m_panelLegMeasurements->TransferDataToWindow();
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

	const FootMeasurements *foot = projectview->GetActiveFootMeasurements();

	return true;
}

void FrameMain::RefreshCanvas(wxCommandEvent& event)
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

void FrameMain::OnLoadBoneModel(wxCommandEvent& event)
{
	FrameParent* parent = wxStaticCast(GetParent(), FrameParent);
	DisplaySettings* settings = &(parent->settings);

	wxFileDialog dialog(this, _("Open Foot Model..."), _T(""), _T(""),
			_("Foot Model (*.fmd; *.txt)|*.fmd;*.txt|All Files|*.*"),
			wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if(wxDir::Exists(settings->lastFootDirectory)){
		dialog.SetDirectory(settings->lastFootDirectory);
	}

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		Project* project = wxStaticCast(GetDocument(), Project);

		if(project->LoadModel(fileName.GetFullPath())){
			settings->lastFootDirectory = fileName.GetPath();
			TransferDataToWindow();
		}
	}
}

void FrameMain::OnSaveBoneModel(wxCommandEvent& event)
{
	FrameParent* parent = wxStaticCast(GetParent(), FrameParent);
	DisplaySettings* settings = &(parent->settings);

	wxFileDialog dialog(this, _("Save Foot Model As..."), _T(""), _T(""),
			_("Foot Model (*.fmd; *.txt)|*.fmd;*.txt|All Files|*.*"),
			wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(wxDir::Exists(settings->lastFootDirectory)){
		dialog.SetDirectory(settings->lastFootDirectory);
	}

//	if(project.fileName.IsOk()) dialog.SetFilename(
//			project.fileName.GetFullPath());

	if(dialog.ShowModal() == wxID_OK){
		wxFileName fileName(dialog.GetPath());
		Project* project = wxStaticCast(GetDocument(), Project);
		if(project->SaveModel(fileName.GetFullPath())){
			settings->lastFootDirectory = fileName.GetPath();
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

void FrameMain::OnDebugParser(wxCommandEvent& event)
{
	(new FrameDebugParser(this))->Show();
}

void FrameMain::OnPageChange(wxNotebookEvent& event)
{
}

void FrameMain::OnQuickSetupMeasurements(wxCommandEvent& event)
{
	DialogQuickInitFoot dialog(this);
	if(dialog.ShowModal() == wxID_OK){
		Project* project = wxStaticCast(GetDocument(), Project);
		ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
		FrameParent* parent = wxStaticCast(GetParent(), FrameParent);
		DisplaySettings* settings = &(parent->settings);

		wxString lengthStr = settings->Distance.TextFromSIWithUnit(
				dialog.length);

		project->GetCommandProcessor()->Submit(
				new CommandFootMeasurementSet(
				_("Set footlength to ") + lengthStr, project,
						projectview->active, ID_MEASUREMENT_FOOTLENGTH,
						lengthStr));

//		ballGirth.formula = _T("footLength*0.93");

//		const FootMeasurements *foot = projectview->GetActiveFootMeasurements();

//		if(fabs(foot->footLength - dialog.length) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set footlength to %g"),
//								dialog.length), project, FootModel::Length,
//						dialog.length));
//		if(fabs(foot->ballwidth - dialog.width) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set ballwidth to %g"),
//								dialog.width), project, FootModel::BallWidth,
//						dialog.width));

//		if(fabs(foot->anklewidth - dialog.width) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set anklewidth to %g"),
//								dialog.width), project, FootModel::AnkleWidth,
//						dialog.width));
//		if(fabs(foot->heelwidth - dialog.width) > FLT_EPSILON) project->GetCommandProcessor()->Submit(
//				new CommandFootSetSize(
//						wxString::Format(_("Set heelwidth to %g"),
//								dialog.width), project, FootModel::HeelWidth,
//						dialog.width));
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

void FrameMain::OnChoiceDisplay(wxCommandEvent& event)
{
}

void FrameMain::OnFileChangedLastFile(wxFileDirPickerEvent& event)
{
}

void FrameMain::OnFileChangedScanFile(wxFileDirPickerEvent& event)
{
}

void FrameMain::OnChoice(wxCommandEvent& event)
{
	printf("Preset selected %u\n", event.GetId());
	switch(event.GetId()){
	case ID_PRESETSHOEHEIGHT:
		break;
	case ID_PRESETSHOETYPE:
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

void FrameMain::OnTextEnter(wxCommandEvent& event)
{
	Project* project = wxStaticCast(GetDocument(), Project);
	ProjectView* projectview = wxStaticCast(GetView(), ProjectView);
	const wxString newFormula = event.GetString();

	project->GetCommandProcessor()->Submit(
			new CommandShoeSetParameter(
					wxString::Format(_("Set %s to %s"),
							GetNameByID(event.GetId()), newFormula), project,
					event.GetId(), newFormula));

	Navigate();
}

void FrameMain::OnKillFocus(wxFocusEvent& event)
{
	switch(event.GetId()){
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

void FrameMain::OnSetFocus(wxFocusEvent& event)
{
	switch(event.GetId()){
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

wxString FrameMain::GetNameByID(int id)
{
	switch(id){
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
		wxTextCtrl* ctrl, bool isDistance)
{
	FrameParent* parent = wxStaticCast(GetParent(), FrameParent);
	DisplaySettings* settings = &(parent->settings);

	if(ctrl->HasFocus()){
		ctrl->SetValue(parameter.formula);
	}else{
		if(parameter.errorFlag){
			ctrl->SetBackgroundColour(*wxRED);
			ctrl->SetValue(parameter.errorStr);
		} else{
			ctrl->SetBackgroundColour(wxNullColour);
			if(isDistance){
				ctrl->SetValue(
						settings->Distance.TextFromSIWithUnit(parameter.value,
								1));
			} else{
				ctrl->SetValue(wxString::Format(_T("%g %%"), parameter.value*100));
			}
		}
	}
}

void FrameMain::OnCheckBox(wxCommandEvent& event)
{
	printf("CheckBox %u pressed.\n", event.GetId());
}

void FrameMain::OnChangeModel(wxCommandEvent& event)
{
}

void FrameMain::OnEditBoneModel(wxCommandEvent& event)
{
}

void FrameMain::OnToggleButton(wxCommandEvent& event)
{
	printf("ToggleButton %u pressed.\n", event.GetId());
}

