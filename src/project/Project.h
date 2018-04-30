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
 * This process is started by calling UpdateFootPosition() followed by UpdateAndGenerate().
 * \todo Check if combineable into one command.
 *
 */

#include "foot/Foot.h"
#include "Shoe.h"
#include "last/Last.h"

#include "pattern/Pattern.h"

#include "../3D/Volume.h"
#include "../3D/Polygon3.h"
#include "last/PolyHull.h"
#include "WorkerThread.h"

#include <wx/docview.h>

#if wxUSE_STD_IOSTREAM
typedef wxSTD istream DocumentIstream;
typedef wxSTD ostream DocumentOstream;
#else // !wxUSE_STD_IOSTREAM
typedef wxInputStream DocumentIstream;
typedef wxOutputStream DocumentOstream;
#endif // wxUSE_STD_IOSTREAM/!wxUSE_STD_IOSTREAM

class Project:public wxDocument {
public:
	enum Symmetry {
		No, OnlyModel, Full
	};

	enum Side {
		Left, Right, Both
	};
	enum PartToUpdate {
		UpdateFoot, UpdateLast, UpdateSole, UpdatePattern, UpdateFlattening
	};

	enum Generator {
		Experimental, //!< Default generator for development of algorithms
		Welted, //!< Welt sewn shoes: Generates last, insole, sole, upper pattern and cutout
		Cemented, //!< for cemented soles (simple, glued-together shoes)
		Molded, //!< for industrial shoes, where the sole is injection-molded to the upper
		Dutch //!< Generator for dutch wooden clogs: Generates last, insole and clog
	};

	Project();
	virtual ~Project();

	void Reset(void);

	DocumentOstream& SaveObject(DocumentOstream& ostream);
	DocumentIstream& LoadObject(DocumentIstream& istream);

	bool LoadModel(wxString fileName);
	bool SaveModel(wxString fileName);
	bool SaveSkin(wxString fileName);

	void Update(PartToUpdate part = UpdateFoot, Side side = Both);
	void Recalculate(void);
	bool ThreadNeedsCalculations(size_t threadNr) const;
	void ThreadCalculate(size_t threadNr);
	void OnCalculationDone(wxCommandEvent& event);
	void OnRefreshViews(wxCommandEvent& event);

	const Foot * GetActiveFoot(void) const;

public:
	Side active;

	double legLengthDifference;
	Symmetry symmetry;
	Foot footL;
	Foot footR;
	Last lastL;
	Last lastR;

	Shoe shoe;

	Pattern pattern;
	Generator generator;

	PolyHull test;
//	Volume vol;
	OrientedMatrix xray;
	OrientedMatrix heightfield;
	Polygon3 bow;
private:
	int stateLeft;
	int stateRight;
	WorkerThread* thread0;
	WorkerThread* thread1;
	wxCriticalSection CS;

DECLARE_DYNAMIC_CLASS(Project)
	;
};

#endif /* PROJECT_H_ */
