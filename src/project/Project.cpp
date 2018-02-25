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

#if wxUSE_STD_IOSTREAM
#include <wx/ioswrap.h>
#else
#include <wx/txtstrm.h>
#endif
#include <wx/wfstream.h>
#include <GL/gl.h>
#include <float.h>

IMPLEMENT_DYNAMIC_CLASS(Project, wxDocument)

Project::Project()
		: wxDocument()
{
	generator = Experimental;
	symmetry = Full;
	activeFoot = &footL;
	active = Left;
	Reset();
}

Project::~Project()
{
}

void Project::Reset(void)
{
	wxFileInputStream input(_T("data/FootModelDefault.txt"));
	wxTextInputStream text(input);
	footL.LoadModel(&text);
	footR.CopyModel(footL);
	footR.mirrored = true;
	legLengthDifference = 0.0;

	FlagForUpdate();
	Update();
}

bool Project::UpdateFootPosition(void)
{
	const double L = (footL.length + footR.length) / 2.0;
	const double W = (footL.ballwidth + footR.ballwidth) / 2.0;
	const double H = (footL.heelwidth + footR.heelwidth) / 2.0;
	const double A = (footL.anklewidth + footR.anklewidth) / 2.0;

	if(!shoe.Evaluate(L, W, H, A)) return false;

	const double heelHeightL = shoe.heelHeight + fmax(0, legLengthDifference);
	const double heelHeightR = shoe.heelHeight + fmax(0, -legLengthDifference);

	footL.UpdateModel();
	footL.SetPosition(heelHeightL, shoe.ballHeight, shoe.toeAngle, shoe.mixing);

	footR.UpdateModel();
	footR.SetPosition(heelHeightR, shoe.ballHeight, shoe.toeAngle, shoe.mixing);

	return true;
}

void Project::FlagForUpdate(void)
{
	if(updateState < 1) updateState = 1;
}

bool Project::Update(void)
{
	if(updateState == 0) return false;

	switch(updateState){
	case 1:
		if(symmetry == Full || symmetry == OnlyModel){
			if(active == Left) footR.CopyModel(footL);
			if(active == Right) footL.CopyModel(footR);
		}
		if(symmetry == Full){
			if(active == Left) footR.CopyModelParameter(footL);
			if(active == Right) footL.CopyModelParameter(footR);
		}
		UpdateFootPosition();
		if(active == Left) updateState = 2;
		if(active == Right) updateState = 3;
		break;
	case 2:
		footL.CalculateSkin();
		if(active == Left) updateState = 3;
		if(active == Right) updateState = 0;
		break;
	case 3:
		footR.CalculateSkin();
		if(active == Left) updateState = 0;
		if(active == Right) updateState = 2;
		break;
	}

	if(updateState == 0){

		heightfield = footL.skin.SurfaceField();
		OrientedMatrix temp = heightfield.XRay(Volume::MinValue);

		bow.Clear();
		for(unsigned int i = 0; i < temp.Numel(); i++){
			if(temp[i] < DBL_MAX){
				bow.InsertPoint(i * temp.dx + temp.origin.x, 0,
						temp[i] + temp.origin.z);
			}
		}

//	sole.origin.z -= 0.1;

		xray = footL.skin.XRay(Volume::MeanValue);

//	bow = foot.GetCenterline();
//	bow.elements[0] = lastvol.GetSurface(bow.elements[1],
//			(bow.elements[0] - bow.elements[1]) * 2);
//	size_t M = bow.elements.GetCount();
//	bow.elements[M - 1] = lastvol.GetSurface(bow.elements[M - 2],
//			(bow.elements[M - 1] - bow.elements[M - 2]) * 2);
//
//	bow.Resample(50);
//	bow.Filter(20);
	}
	return (updateState == 0)? false : true;
}

bool Project::LoadModel(wxString fileName)
{
	wxFileInputStream input(fileName);
	wxTextInputStream text(input);

	bool flag = false;
	if(active == Left){
		flag = footL.LoadModel(&text);
		if(symmetry == Full) footR.CopyModel(footL);
	}
	if(active == Right){
		flag = footR.LoadModel(&text);
		if(symmetry == Full) footR.CopyModel(footL);
	}
	if(flag){
		UpdateFootPosition();
		return true;
	}
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
	if(active == Left) temp.WriteStream(outStream, footL.skin.geometry);
	if(active == Right) temp.WriteStream(outStream, footR.skin.geometry);
	return true;
}

