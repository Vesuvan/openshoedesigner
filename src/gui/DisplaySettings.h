///////////////////////////////////////////////////////////////////////////////
// Name               : DisplaySettings.h
// Purpose            : Settings for the GUI
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

#ifndef DISPLAYSETTINGS_H_
#define DISPLAYSETTINGS_H_

/*!\class DisplaySettings
 * \brief Settings for the GUI
 *
 * Collection of settings used in the GUI system.
 *   - Stereo 3D
 *   - Units
 */

#include <wx/config.h>

#include "../3D/OpenGLCanvas.h"

#include "../math/Unit.h"

class DisplaySettings {
	friend class DialogSetupUnits;

public:
	DisplaySettings();
	virtual ~DisplaySettings();

	Unit Time;
	Unit Distance;
	Unit SmallDistance;
	Unit Tolerance;
	Unit Angle;

	wxString lastFootDirectory;
	wxString lastShoeDirectory;
	wxString lastOutputDirectory;

	float eyeDistance;
	float focalDistance;
	unsigned char backgroundGrayLevel;
	unsigned char rightEyeR;
	unsigned char rightEyeG;
	unsigned char rightEyeB;
	unsigned char leftEyeR;
	unsigned char leftEyeG;
	unsigned char leftEyeB;

	bool GetConfigFrom(wxConfig * config);
	bool WriteConfigTo(wxConfig * config);

	void WriteToCanvas(OpenGLCanvas * canvas);

protected:
	// TODO: Put the unit lists into the Unit class, or at least the factors.
	wxArrayString unitsOfLength;
	wxArrayString unitsOfTime;
	wxArrayString unitsOfAngle;

	double * factorofLength;
	double * factorofTime;
	double * factorofAngle;
};

#endif /* DISPLAYSETTINGS_H_ */
