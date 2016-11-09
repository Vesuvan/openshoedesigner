///////////////////////////////////////////////////////////////////////////////
// Name               : Project.bow
// Purpose            : 
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
 * - Dutch clog generator
 *
 * This process is started by calling UpdateFootPosition() followed by UpdateAndGenerate().
 * \todo Check if combineable into one command.
 *
 */

#include "Foot.h"
#include "Shoe.h"
#include "Pattern.h"

#include "../3D/Volume.h"
#include "../3D/Polygon3.h"

class Project {
public:

	enum Generator {
		Basic = 0, //!< Standard generator: Generates last, insole, sole, upper pattern and cutout
		Dutch //!< Generator for dutch wooden clogs: Generates last, insole and clog
	};

	Project();
	virtual ~Project();

	void Reset(void);
	bool UpdateFootPosition(void);
	void UpdateAndGenerate(void);

	// Get the parts of the model
	Foot* GetFoot(void);
	Shoe* GetShoe(void);

	// Setup model:
	void AddFootToGrid(wxGrid* gridLength, wxGrid* gridDiameter,
			wxGrid* gridSkin);
	void GetFootFromGrid(wxGrid* gridLength, wxGrid* gridDiameter,
			wxGrid* gridSkin);

	bool LoadModel(wxString fileName);
	bool SaveModel(wxString fileName);
	bool SaveLast(wxString fileName);

	// Painting:
	void PaintBones(void) const;
	void PaintLast(void) const;
	void PaintInsole(void) const;
	void PaintSole(void) const;
	void PaintUpper(void) const;
	void PaintCutaway(void) const;
	void PaintFloor(void) const;

public:
	Generator generator;

private:

	double floorLevel;

	Foot footmodel;
	Shoe shoe;

	Volume last;
	Volume sole;
	Pattern pattern;



	OrientedMatrix xray;
	OrientedMatrix heightfield;
	Polygon3 bow;

};

#endif /* PROJECT_H_ */
