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
#include "WorkerThread.h"
#if wxUSE_STD_IOSTREAM
#include <wx/ioswrap.h>
#else
#include <wx/txtstrm.h>
#endif
#include <wx/wfstream.h>
#include <GL/gl.h>
#include <float.h>
#include "../gui/IDs.h"

IMPLEMENT_DYNAMIC_CLASS(Project, wxDocument)

Project::Project()
		: wxDocument(), legLengthDifference(_T("legLengthDifference"))
{

//	vol.SetSize(4, 4, 4, 0.1);
//	vol.SetOrigin(Vector3(-0.15, -0.15, -0.15));

//	vol.SetSize(2, 2, 2, 0.1);
//	vol.SetOrigin(Vector3(-0.05, -0.05, -0.05));

//	for(size_t n = 0; n < vol.Numel(); n++)
//		vol[n] = 0.0;
//	vol.CalcSurface();

	thread0 = NULL;
	thread1 = NULL;
	Reset();

	Bind(wxEVT_COMMAND_THREAD_COMPLETED, &Project::OnCalculationDone, this);
	Bind(wxEVT_COMMAND_THREAD_UPDATE, &Project::OnRefreshViews, this);
}

Project::~Project()
{
	Unbind(wxEVT_COMMAND_THREAD_UPDATE, &Project::OnRefreshViews, this);
	Unbind(wxEVT_COMMAND_THREAD_COMPLETED, &Project::OnCalculationDone, this);
	{
		wxCriticalSectionLocker locker(CSLeft);
		if(thread0 != NULL) thread0->Delete();
	}
	{
		wxCriticalSectionLocker locker(CSRight);
		if(thread1 != NULL) thread1->Delete();
	}
}

void Project::StopAllThreads(void)
{
	{
		wxCriticalSectionLocker enter(CS);
		if(thread0){
			if(thread0->Delete() != wxTHREAD_NO_ERROR)
			wxLogError
			("Can't delete thread0!");
		}
		if(thread1){
			if(thread1->Delete() != wxTHREAD_NO_ERROR)
			wxLogError
			("Can't delete thread1!");
		}
	}
	while(true){
		{
			wxCriticalSectionLocker enter(CS);
			if(thread0 == NULL && thread1 == NULL) break;
		}
		wxThread::This()->Sleep(1);
	}
}

void Project::Reset(void)
{

	measurementsSymmetric = true;
	measurementsource = fromMeasurements;
	modeltype = lastBased;

	generator = Experimental;
	legLengthDifference.formula = _T("0.0");

	wxFileInputStream input(_T("data/FootModelDefault.txt"));
	wxTextInputStream text(input);
	footL.LoadModel(&text);
	footR.CopyModel(footL);
	footR.mirrored = true;

	footScan.InitExample();

	lastModelR.LoadModel("data/Last_Default_Warped.stl");

//	lastModelR.hull.SaveObj("/tmp/hull_export.obj");

	lastModelL = lastModelR;
	lastModelL.mirrored = true;
}

void Project::Update(void)
{
	{
		// Update the left foot/shoe
		MathParser parser;
		parser.ignorecase = true;
		parser.AddAllowedUnit(_T("mm"), 1e-3);
		parser.AddAllowedUnit(_T("cm"), 1e-2);
		parser.AddAllowedUnit(_T("m"), 1);
		parser.AddAllowedUnit(_T("in"), 2.54e-2);
		parser.AddAllowedUnit(_T("ft"), 0.3048);
		parser.AddAllowedUnit(_T("rad"), 1);
		parser.AddAllowedUnit(_T("deg"), 0.017453);
		parser.AddAllowedUnit(_T("gon"), 0.015708);
		measL.Update(parser);
		legLengthDifference.Update(parser);
		if(legLengthDifference.IsModified()){
			measL.Modify(true);
			measR.Modify(true);
		}
		shoe.Update(parser);
		if(shoe.IsModified()){
			measL.Modify(true);
			measR.Modify(true);
			shoe.Modify(false);
		}
		if(measL.IsModified()){
			if(thread0 == NULL){
				thread0 = new WorkerThread(this, 0);
				if(thread0->Run() != wxTHREAD_NO_ERROR){
					wxLogError
					("Can't create the thread0!");
					delete thread0;
					thread0 = NULL;
				}
			}
		}
	}
	{
		// Update right foot/shoe
		MathParser parser;
		parser.ignorecase = true;
		parser.AddAllowedUnit(_T("mm"), 1e-3);
		parser.AddAllowedUnit(_T("cm"), 1e-2);
		parser.AddAllowedUnit(_T("m"), 1);
		parser.AddAllowedUnit(_T("in"), 2.54e-2);
		parser.AddAllowedUnit(_T("ft"), 0.3048);
		parser.AddAllowedUnit(_T("rad"), 1);
		parser.AddAllowedUnit(_T("deg"), 0.017453);
		parser.AddAllowedUnit(_T("gon"), 0.015708);
		measR.Update(parser);
		if(measR.IsModified()){
			if(thread1 == NULL){
				thread1 = new WorkerThread(this, 1);
				if(thread1->Run() != wxTHREAD_NO_ERROR){
					wxLogError
					("Can't create the thread1!");
					delete thread1;
					thread1 = NULL;
				}
			}
		}
	}
	UpdateAllViews();
}

bool Project::UpdateLeft(void)
{
	wxCriticalSectionLocker locker(CSLeft);
	if(measL.IsModified()){
		measL.Modify(false);
		lastModelL.Modify(true);
		footL.UpdateForm(measL);
		return true;
	}
	if(footL.IsModifiedForm()){
		footL.ModifyForm(false);
		footL.UpdatePosition(shoe, fmax(legLengthDifference.value, 0),
				measL.angleMixing.value);
		return true;
	}
	if(footL.IsModifiedPosition()){
		footL.ModifyPosition(false);
		footL.CalculateSkin();
		return true;
	}
	if(lastModelL.IsModified()){
		lastModelL.Modify(false);
		lastModelL.UpdateForm(measL);
//		lastModelL.UpdateGeometry();
		return true;
	}

	if(footL.IsModifiedSkin()){
		footL.ModifySkin(false);
		heightfield = footL.skin.SurfaceField();
		OrientedMatrix temp = heightfield.XRay(Volume::MinValue);
		bow.Clear();
		for(unsigned int i = 0; i < temp.Numel(); i++){
			if(temp[i] < DBL_MAX){
				bow.InsertPoint(i * temp.dx + temp.origin.x, 0,
						temp[i] + temp.origin.z);
			}
		}
		xray = footL.skin.XRay(Volume::MeanValue);
		bow = footL.GetCenterline();
		//	bow.elements[0] = lastvol.GetSurface(bow.elements[1],
		//			(bow.elements[0] - bow.elements[1]) * 2);
		//	size_t M = bow.elements.GetCount();
		//	bow.elements[M - 1] = lastvol.GetSurface(bow.elements[M - 2],
		//			(bow.elements[M - 1] - bow.elements[M - 2]) * 2);
		//
		bow.Resample(50);
		bow.Filter(20);

		return true;
	}

	printf("Update L - done\n");
	return false;
}

bool Project::UpdateRight(void)
{
	wxCriticalSectionLocker locker(CSRight);
	if(measR.IsModified()){
		measR.Modify(false);
		lastModelR.Modify(true);
		footR.UpdateForm(measR);
		return true;
	}
	if(footR.IsModifiedForm()){
		footR.ModifyForm(false);
		footR.UpdatePosition(shoe, fmax(-legLengthDifference.value, 0),
				measR.angleMixing.value);
		return true;
	}
	if(footR.IsModifiedPosition()){
		footR.ModifyPosition(false);
		footR.CalculateSkin();
		return true;
	}

	if(lastModelR.IsModified()){
		lastModelR.Modify(false);
		lastModelR.UpdateForm(measR);
//		lastModelR.UpdateGeometry();
		return true;
	}

	printf("Update R - done\n");
	return false;
}

void Project::OnRefreshViews(wxThreadEvent& event)
{
	UpdateAllViews();
}

void Project::OnCalculationDone(wxThreadEvent& event)
{
	CS.Enter();

	CS.Leave();
	UpdateAllViews(); // This has been done by OnRefreshViews.
}

DocumentIstream& Project::LoadObject(DocumentIstream& istream)
{
	wxDocument::LoadObject(istream);
#if wxUSE_STD_IOSTREAM
	DocumentIstream& stream = istream;
#else
	wxTextInputStream stream(istream);
#endif

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

DocumentOstream& Project::SaveObject(DocumentOstream& ostream)
{
	wxDocument::SaveObject(ostream);
#if wxUSE_STD_IOSTREAM
	DocumentOstream& stream = ostream;
#else
	wxTextOutputStream stream(ostream);
#endif

// TODO: Add Project data

	return ostream;
}

bool Project::LoadFootModel(wxString fileName)
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
	return false;
}

bool Project::SaveFootModel(wxString fileName)
{
	wxFileOutputStream output(fileName);
	wxTextOutputStream text(output);
	return footL.SaveModel(&text);
}

bool Project::LoadLastModel(wxString fileName)
{
	try{
		if(!lastModelR.LoadModel(fileName.ToStdString())) return false;
	}
	catch(std::exception &exeption){
		std::cout << "Exeption caught: " << exeption.what() << "\n";
	}
	lastModelL = lastModelR;
	lastModelL.mirrored = true;
	return true;
}

bool Project::SaveLast(wxString fileName, bool left, bool right)
{
	wxFFileOutputStream outStream(fileName);
	FileSTL temp;
//	if(left) temp.WriteStream(outStream, lastModelL.geometry);
//	if(right) temp.WriteStream(outStream, lastModelR.geometry);
	return true;

}

bool Project::SaveSkin(wxString fileName, bool left, bool right)
{
	wxFFileOutputStream outStream(fileName);
	FileSTL temp;
	if(left) temp.WriteStream(outStream, footL.skin.geometry);
	if(right) temp.WriteStream(outStream, footR.skin.geometry);
	return true;
}

