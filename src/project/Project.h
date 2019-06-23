///////////////////////////////////////////////////////////////////////////////
// Name               : Project.h
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

#ifndef PROJECT_H_
#define PROJECT_H_

/*!\class Project
 * \brief Project container
 *
 * Data part of the Data View Model.
 *
 * Dataflow upon update:
 *
 * - The Shoe gets parameters about the Foot (size, width, form, ...).
 * - The Shoe updates its parameters (angles, heights)
 * - The data of the Shoe is passed back to the Foot to update the position of the Bone%s.
 * - The form of the Foot is calculated, this is not the form of the Last. Albeit it is quite close.
 *
 * Here it runs off into various generators.
 *
 * - Basic generator
 * - Generator for classic construction
 * - Generator for cemented shoes
 * - Generator for injection molded shoes
 * - Dutch clog generator
 *
 */

#include <stddef.h>
#include <wx/docview.h>

#include <wx/object.h>
#include <wx/platform.h>
#include <wx/setup.h>
#include <wx/string.h>
#include <wx/thread.h>
#include <iostream>

#include "../3D/OrientedMatrix.h"
#include "../3D/PointCloud.h"
#include "../3D/Polygon3.h"
//#include "../3D/Volume.h"

#include "foot/FootMeasurements.h"
#include "foot/FootModel.h"
#include "last/Last.h"
#include "last/LastModel.h"
#include "Shoe.h"
#include "pattern/Pattern.h"

class WorkerThread;

#if wxUSE_STD_IOSTREAM
typedef wxSTD istream DocumentIstream;
typedef wxSTD ostream DocumentOstream;
#else // !wxUSE_STD_IOSTREAM
typedef wxInputStream DocumentIstream;
typedef wxOutputStream DocumentOstream;
#endif // wxUSE_STD_IOSTREAM/!wxUSE_STD_IOSTREAM

class Project:public wxDocument {
	friend class WorkerThread;
public:

	// +++ Measurements +++
	bool measurementsSymmetric;

	enum MeasurementSource {
		fromMeasurements = 0, fromFootScan
	} measurementsource;
	FootMeasurements measL;
	FootMeasurements measR;
	ParameterFormula legLengthDifference; // Distance the right leg is shorter than the left.

	PointCloud footScan;

	enum ModelType {
		boneBased = 0, lastBased
	} modeltype;
	FootModel footL;
	FootModel footR;

	LastModel lastModelL;
	LastModel lastModelR;

	// +++ Shoe +++
	Shoe shoe;

	// Last to generate
	Last lastL;
	Last lastR;

	// Pattern for the upper of the shoe
	Pattern pattern;

	// +++ Generator +++
	enum Generator {
		Experimental = 0, //!< Default generator for development of algorithms
		Welted, //!< Welt sewn shoes: Generates last, insole, sole, upper pattern and cutout
		Cemented, //!< for cemented soles (simple, glued-together shoes)
		Molded, //!< for industrial shoes, where the sole is injection-molded to the upper
		Dutch, //!< Generator for dutch wooden clogs: Generates last, insole and clog
		Geta   //!< Japanese Geta generator
	} generator;

	// Generated products / debugging structures

	//	Volume vol;
	OrientedMatrix xray;
	OrientedMatrix heightfield;
	Polygon3 bow;

public:
	Project();
	virtual ~Project();
	void StopAllThreads(void); //!< Call from OnClose; the event loop has to be running.

	void Reset(void);

	DocumentOstream& SaveObject(DocumentOstream& ostream);
	DocumentIstream& LoadObject(DocumentIstream& istream);

	bool LoadFootModel(wxString fileName);
	bool SaveFootModel(wxString fileName);
	bool LoadLastModel(wxString fileName);
	bool SaveLast(wxString fileName, bool left, bool right);
	bool SaveSkin(wxString fileName, bool left, bool right);

	void Update(void);

protected:
	bool UpdateLeft(void);
	bool UpdateRight(void);

private:
	void OnCalculationDone(wxThreadEvent& event);
	void OnRefreshViews(wxThreadEvent& event);

private:
	WorkerThread* thread0;
	WorkerThread* thread1;

	wxCriticalSection CS;
	wxCriticalSection CSLeft;
	wxCriticalSection CSRight;

DECLARE_DYNAMIC_CLASS(Project)

};

#endif /* PROJECT_H_ */
