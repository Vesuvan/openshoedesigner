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

FrameMain::FrameMain(wxWindow* parent) :
		GUIFrameMain(parent)
{
	foot.Setup();
	volume.SetSize(0.35, 0.2, 0.2, 0.005);
	volume.matrix.TranslateGlobal(-0.075, -0.075, -0.12);
	volume.Clear();

//	volume.AddHalfplane(Vector3(0, 0, 1), -0.10, 0.01);
//	volume.AddSphere(Vector3(0, 0.10, 0), 0.02, 0.1);
//	volume.AddSphere(Vector3(0.1, 0, 0.0), 0.04, 0.01);
//	volume.AddCylinder(Vector3(0.0, 0, 0.0), Vector3(0.05 * 1, 0, -0.00), 0.04,
//			0.04, 0.02,0.04);

	m_canvas->SetBones(&foot);

	foot.AddToVolume(&volume);

	volume.MarchingCubes(0.50);
	m_canvas->SetVolume(&volume);

//		m_canvas->stereoMode = stereoAnaglyph;
	m_canvas->eyeDistance = 0.005;
	m_canvas->leftEyeR = 0;
	m_canvas->leftEyeG = 109;
	m_canvas->leftEyeB = 0;
	m_canvas->rightEyeR = 106;
	m_canvas->rightEyeG = 0;
	m_canvas->rightEyeB = 0;


}

FrameMain::~FrameMain()
{
}

bool FrameMain::TransferDataFromWindow()
{
	return true;
}

bool FrameMain::TransferDataToWindow()
{
	return true;
}

void FrameMain::OnQuit(wxCommandEvent& event)
{
	Close();
}
