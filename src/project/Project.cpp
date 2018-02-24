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

	UpdateFootPosition();
	Update();
}

bool Project::UpdateFootPosition(void)
{
	if(!shoe.Evaluate(footL.length, footL.width, footL.H, footL.A)) return false;
	footL.SetPosition(shoe.heelHeight - shoe.ballHeight, shoe.toeAngle,
			shoe.mixing);
	return true;
}

void Project::Update(void)
{

	UpdateFootPosition();

	// Calculate the Footmodel
	lastvol.SetSize(0.40, 0.3, 0.4, 0.0075);
	lastvol.SetOrigin(Vector3(-0.15, -0.1, -0.3));
	//	lastvol.AddHalfplane(Vector3(0, 0, 1), -0.10, 0.01);
	//	lastvol.AddSphere(Vector3(0, 0.1, 0), 0.15, 0.1);
	//	lastvol.AddSphere(Vector3(0.13, 0, 0.0), 0.19, 0.01);
	//	lastvol.AddCylinder(Vector3(0.0, 0, 0.0), Vector3(0.05 * 1, 0, -0.00), 0.04,
	//			0.04, 0.02, 0.04);
	lastvol.Clear();

	for(size_t n = 0; n < footL.bones.size(); n++){
		lastvol.AddCylinder(footL.bones[n].p1, footL.bones[n].p2,
				footL.bones[n].r1 + footL.bones[n].s1,
				footL.bones[n].r2 + footL.bones[n].s2,
				(footL.bones[n].s1 + footL.bones[n].s2) / 2.0);
		//	volume->AddCylinder(footL.bones[n].p1,footL.bones[n].p2,footL.bones[n].r1,footL.bones[n].r2,footL.bones[n].s1,footL.bones[n].s2);
	}

//	footL.AddToVolume(&lastvol);
//	lastvol.Rotate(Volume::Z, 2);
//	lastvol.Rotate(Volume::Z, -1);
//	lastvol.Rotate(Volume::Z, -1);
	lastvol.CalcSurface();

	heightfield = lastvol.SurfaceField();
	OrientedMatrix temp = heightfield.XRay(Volume::MinValue);

	bow.Clear();
	for(unsigned int i = 0; i < temp.Numel(); i++){
		if(temp[i] < DBL_MAX){
			bow.InsertPoint(i * temp.dx + temp.origin.x, 0,
					temp[i] + temp.origin.z);
		}
	}

//	sole.origin.z -= 0.1;

	xray = lastvol.XRay(Volume::MeanValue);

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

bool Project::LoadModel(wxString fileName)
{
	wxFileInputStream input(fileName);
	wxTextInputStream text(input);

	if(footL.LoadModel(&text)){
		footL.SetPosition(shoe.heelHeight, shoe.toeAngle, shoe.mixing);
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

bool Project::SaveLast(wxString fileName)
{
	wxFFileOutputStream outStream(fileName);
	FileSTL temp;
	temp.WriteStream(outStream, lastvol.geometry);
	return true;
}

