///////////////////////////////////////////////////////////////////////////////
// Name               : DisplaySettings.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 07.01.2015
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

#include "DisplaySettings.h"

#include <wx/filename.h>

DisplaySettings::DisplaySettings()
{
	Distance.Setup(_T("m"), _T("cm"), (double) 10e-3);
	Time.Setup(_T("s"), _T("min"), (double) 60);
	SmallDistance.Setup(_T("m"), _T("mm"), (double) 1e-3);
	Tolerance.Setup(_T("m"), _T("um"), (double) 1e-6);
	Angle.Setup(_T("rad"), _T("deg"), (double) M_PI / 180.0);

	// Setup available units
	factorofLength = new double[7];
	unitsOfLength.Add(_T("um"));
	factorofLength[0] = 1e-6; // m
	unitsOfLength.Add(_T("mil"));
	factorofLength[1] = 25.4e-6; // m
	unitsOfLength.Add(_T("mm"));
	factorofLength[2] = 1e-3; // m
	unitsOfLength.Add(_T("cm"));
	factorofLength[3] = 10e-3; // m
	unitsOfLength.Add(_T("in"));
	factorofLength[4] = 25.4e-3; // m
	unitsOfLength.Add(_T("ft"));
	factorofLength[5] = 12 * 25.4e-3; // m
	unitsOfLength.Add(_T("m"));
	factorofLength[6] = 1; // m

	factorofTime = new double[4];
	unitsOfTime.Add(_T("s"));
	factorofTime[0] = 1; // s
	unitsOfTime.Add(_T("min"));
	factorofTime[1] = 60; // s
	unitsOfTime.Add(_T("h"));
	factorofTime[2] = 3600; // s
	unitsOfTime.Add(_T("d"));
	factorofTime[3] = 86400; // s

	factorofAngle = new double[3];
	unitsOfAngle.Add(_T("rad"));
	factorofAngle[0] = 1.0; // rad
	unitsOfAngle.Add(_T("deg"));
	factorofAngle[1] = M_PI / 180.0; // rad
	unitsOfAngle.Add(_T("gon"));
	factorofAngle[2] = M_PI / 200.0; // rad

	eyeDistance = 0.1;
	focalDistance = 1.0;
	backgroundGrayLevel = 90;
	rightEyeR = 0;
	rightEyeG = 77;
	rightEyeB = 102;
	leftEyeR = 179;
	leftEyeG = 0;
	leftEyeB = 0;
}

DisplaySettings::~DisplaySettings()
{
	delete[] factorofTime;
	delete[] factorofLength;
	delete[] factorofAngle;

}

bool DisplaySettings::GetConfigFrom(wxConfig * config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	wxString cwd = wxFileName::GetCwd();
	config->Read(_T("LastFootDirectory"), &lastFootDirectory, cwd);
	config->Read(_T("LastShoeDirectory"), &lastShoeDirectory, cwd);
	config->Read(_T("LastOutputDirectory"), &lastOutputDirectory, cwd);

	wxString temp;
	int i;

	config->Read(_T("UnitTime"), &temp, _T("min"));
	i = unitsOfTime.Index(temp);
	if(i != wxNOT_FOUND) Time.Setup(_T("s"), unitsOfTime[i], factorofTime[i]);

	config->Read(_T("UnitDistance"), &temp, _T("cm"));
	i = unitsOfLength.Index(temp);
	if(i != wxNOT_FOUND) Distance.Setup(_T("m"), unitsOfLength[i],
			factorofLength[i]);

	config->Read(_T("UnitSmallDistance"), &temp, _T("cm"));
	i = unitsOfLength.Index(temp);
	if(i != wxNOT_FOUND) SmallDistance.Setup(_T("m"), unitsOfLength[i],
			factorofLength[i]);

	config->Read(_T("UnitTolerance"), &temp, _T("um"));
	i = unitsOfLength.Index(temp);
	if(i != wxNOT_FOUND) Tolerance.Setup(_T("m"), unitsOfLength[i],
			factorofLength[i]);

	config->Read(_T("UnitAngle"), &temp, _T("deg"));
	i = unitsOfAngle.Index(temp);
	if(i != wxNOT_FOUND) Angle.Setup(_T("rad"), unitsOfAngle[i],
			factorofAngle[i]);

	long lval;
	config->Read(_T("Stereo3DColorLeftEyeRed"), &lval, 140l);
	leftEyeR = lval;
	config->Read(_T("Stereo3DColorLeftEyeGreen"), &lval, 0l);
	leftEyeG = lval;
	config->Read(_T("Stereo3DColorLeftEyeBlue"), &lval, 0l);
	leftEyeB = lval;
	config->Read(_T("Stereo3DColorRightEyeRed"), &lval, 0l);
	rightEyeR = lval;
	config->Read(_T("Stereo3DColorRightEyeGreen"), &lval, 70l);
	rightEyeG = lval;
	config->Read(_T("Stereo3DColorRightEyeBlue"), &lval, 90l);
	rightEyeB = lval;

	double dval;
	config->Read(_T("Stereo3DEyeDistance"), &dval, 0.1);
	eyeDistance = dval;
	config->Read(_T("Stereo3DFocalDistance"), &dval, 1.0);
	focalDistance = dval;

	return true;
}

bool DisplaySettings::WriteConfigTo(wxConfig * config)
{
	wxASSERT(config!=NULL);
	if(config == NULL) return false;

	config->Write(_T("UnitTime"), Time.GetOtherName());
	config->Write(_T("UnitDistance"), Distance.GetOtherName());
	config->Write(_T("UnitSmallDistance"), SmallDistance.GetOtherName());
	config->Write(_T("UnitTolerance"), Tolerance.GetOtherName());
	config->Write(_T("UnitAngle"), Angle.GetOtherName());

	config->Write(_T("LastFootDirectory"), lastFootDirectory);
	config->Write(_T("LastShoeDirectory"), lastShoeDirectory);
	config->Write(_T("LastOutputDirectory"), lastOutputDirectory);

	config->Write(_T("Stereo3DColorLeftEyeRed"), (long) leftEyeR);
	config->Write(_T("Stereo3DColorLeftEyeGreen"), (long) leftEyeG);
	config->Write(_T("Stereo3DColorLeftEyeBlue"), (long) leftEyeB);
	config->Write(_T("Stereo3DColorRightEyeRed"), (long) rightEyeR);
	config->Write(_T("Stereo3DColorRightEyeGreen"), (long) rightEyeG);
	config->Write(_T("Stereo3DColorRightEyeBlue"), (long) rightEyeB);
	config->Write(_T("Stereo3DEyeDistance"), (double) eyeDistance);
	config->Write(_T("Stereo3DFocalDistance"), (double) focalDistance);

	return true;
}

void DisplaySettings::WriteToCanvas(OpenGLCanvas* canvas)
{
	canvas->leftEyeR = this->leftEyeR;
	canvas->leftEyeG = this->leftEyeG;
	canvas->leftEyeB = this->leftEyeB;
	canvas->rightEyeR = this->rightEyeR;
	canvas->rightEyeG = this->rightEyeG;
	canvas->rightEyeB = this->rightEyeB;
	canvas->focalDistance = this->focalDistance;
	canvas->eyeDistance = this->eyeDistance;
	canvas->backgroundGrayLevel = this->backgroundGrayLevel;
}
