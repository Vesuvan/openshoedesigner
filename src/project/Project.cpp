///////////////////////////////////////////////////////////////////////////////
// Name               : Project.cpp
// Purpose            : Project data
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 29.01.2016
// Copyright          : (C) 2016 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Project.h"

#include <wx/log.h>
#include <cstdio>

#include "../3D/FileSTL.h"
#include "../math/MathParser.h"
#include "IniFile.h"

#if wxUSE_STD_IOSTREAM
#include <wx/ioswrap.h>
#else
#include <wx/txtstrm.h>
#endif
#include <wx/wfstream.h>
#include <GL/gl.h>
#include <float.h>
#include "../gui/IDs.h"

static const int maxState = 10;



IMPLEMENT_DYNAMIC_CLASS(Project, wxDocument)

Project::Project()
		: wxDocument()
{



	IniFile presets("data/ShoePresets.ini");

//	vol.SetSize(4, 4, 4, 0.1);
//	vol.SetOrigin(Vector3(-0.15, -0.15, -0.15));

//	vol.SetSize(2, 2, 2, 0.1);
//	vol.SetOrigin(Vector3(-0.05, -0.05, -0.05));

//	for(size_t n = 0; n < vol.Numel(); n++)
//		vol[n] = 0.0;
//	vol.CalcSurface();

	thread0 = NULL;
	thread1 = NULL;
	this->Connect(ID_THREADDONE_0, ID_THREADDONE_1,
	wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(Project::OnCalculationDone));

	generator = Experimental;
	symmetry = Full;
	Reset();
}

Project::~Project()
{
	wxCriticalSectionLocker locker(CS);
//	if(thread0 != NULL){
//		thread0->Wait();
//		delete thread0;
//	}
//	if(thread1 != NULL){
//		thread1->Wait();
//		delete thread1;
//	}
	this->Disconnect(ID_THREADDONE_0, ID_THREADDONE_1,
	wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(Project::OnCalculationDone));

}

void Project::Reset(void)
{
	wxFileInputStream input(_T("data/FootModelDefault.txt"));
	wxTextInputStream text(input);
	footL.LoadModel(&text);
	footR.CopyModel(footL);
	footR.mirrored = true;
//	legLengthDifference = 0.0;
//
//	stateLeft = 0;
//	stateRight = 0;
}

void Project::OnRefreshViews(wxCommandEvent& event)
{
	UpdateAllViews();
}

void Project::OnCalculationDone(wxCommandEvent& event)
{
	CS.Enter();
//	if(event.GetId() == ID_THREADDONE_0 && thread0 != NULL){
//		thread0->Wait();
//		delete thread0;
//		thread0 = NULL;
//	}
//	if(event.GetId() == ID_THREADDONE_1 && thread1 != NULL){
//		thread1->Wait();
//		delete thread1;
//		thread1 = NULL;
//	}
	CS.Leave();
	UpdateAllViews();
}

void Project::Update(void)
{
//	if(side == Left || side == Both){
//		stateLeft = 0;
//	}
//	if(side == Right || side == Both){
//		stateRight = 0;
//	}
}

void Project::Recalculate(void)
{
	const bool multiThreading = true;

//	if(multiThreading){
//		wxCriticalSectionLocker locker(CS);
//		if(ThreadNeedsCalculations(0) && thread0 == NULL){
//			thread0 = new WorkerThread(this, 0);
//			thread0->Create();
//			thread0->Run();
//		}
//		if(ThreadNeedsCalculations(1) && thread1 == NULL){
//			thread1 = new WorkerThread(this, 1);
//			thread1->Create();
//			thread1->Run();
//		}
//	}else{
//		while(ThreadNeedsCalculations(0) || ThreadNeedsCalculations(1)){
//			ThreadCalculate(0);
//			ThreadCalculate(1);
//		}
//	}
}

bool Project::ThreadNeedsCalculations(size_t threadNr) const
{
//	switch(threadNr){
//	case 0:
//		return (stateLeft < maxState);
//	case 1:
//		return (stateRight < maxState);
//	}
	return false;
}

void Project::ThreadCalculate(size_t threadNr)
{
//	if(threadNr == 0){
//		if(stateLeft < maxState) stateLeft++;
//		switch(stateLeft){
//		case 1:
//			{
//				footL.UpdateModel();
//				footL.UpdatePosition(&shoe, fmax(0, legLengthDifference));
//			}
//			break;
//		case 2:
//			{
//				footL.CalculateSkin();
//			}
//			break;
//		case 3:
//			{
//				heightfield = footL.skin.SurfaceField();
//				OrientedMatrix temp = heightfield.XRay(Volume::MinValue);
//
//				bow.Clear();
//				for(unsigned int i = 0; i < temp.Numel(); i++){
//					if(temp[i] < DBL_MAX){
//						bow.InsertPoint(i * temp.dx + temp.origin.x, 0,
//								temp[i] + temp.origin.z);
//					}
//				}
//
//				//	sole.origin.z -= 0.1;
//
//				xray = footL.skin.XRay(Volume::MeanValue);
//				bow = footL.GetCenterline();
////	bow.elements[0] = lastvol.GetSurface(bow.elements[1],
////			(bow.elements[0] - bow.elements[1]) * 2);
////	size_t M = bow.elements.GetCount();
////	bow.elements[M - 1] = lastvol.GetSurface(bow.elements[M - 2],
////			(bow.elements[M - 1] - bow.elements[M - 2]) * 2);
////
//				bow.Resample(50);
////	bow.Filter(20);
//			}
//			break;
//		}
//	}
//	if(threadNr == 1){
//		if(stateRight < maxState) stateRight++;
//		switch(stateRight){
//		case 1:
//			{
//				footR.UpdateModel();
//				footR.UpdatePosition(&shoe, fmax(0, -legLengthDifference));
//			}
//			break;
//		case 2:
//			{
//				footR.CalculateSkin();
//			}
//			break;
//		}
//	}
}

bool Project::LoadModel(wxString fileName)
{
	wxFileInputStream input(fileName);
	wxTextInputStream text(input);

//	bool flag = false;
//	if(active == Left){
//		flag = footL.LoadModel(&text);
//		if(symmetry == Full) footR.CopyModel(footL);
//	}
//	if(active == Right){
//		flag = footR.LoadModel(&text);
//		if(symmetry == Full) footR.CopyModel(footL);
//	}
//	if(flag){
//		Update();
//		return true;
//	}
	return false;
}

bool Project::SaveModel(wxString fileName)
{
	wxFileOutputStream output(fileName);
	wxTextOutputStream text(output);
	return footL.SaveModel(&text);
}

DocumentOstream& Project::SaveObject(DocumentOstream& ostream)
{
#if wxUSE_STD_IOSTREAM
	DocumentOstream& stream = ostream;
#else
	wxTextOutputStream stream(ostream);
#endif
	wxDocument::SaveObject(ostream);

	// TODO: Add Project data

	return ostream;
}

DocumentIstream& Project::LoadObject(DocumentIstream& istream)
{
#if wxUSE_STD_IOSTREAM
	DocumentIstream& stream = istream;
#else
	wxTextInputStream stream(istream);
#endif

	wxDocument::LoadObject(istream);

	wxInt32 count = 0;
	stream >> count;

	if(false){
		wxLogWarning
		("File could not be read.");
#if wxUSE_STD_IOSTREAM
		istream.clear(std::ios::badbit);
#else
		istream.Reset(wxSTREAM_READ_ERROR);
#endif
		return istream;
	}

	// TODO: Add Project data

	return istream;
}

bool Project::SaveSkin(wxString fileName)
{
	wxFFileOutputStream outStream(fileName);
	FileSTL temp;
//	if(active == Left) temp.WriteStream(outStream, footL.skin.geometry);
//	if(active == Right) temp.WriteStream(outStream, footR.skin.geometry);
	return true;
}

