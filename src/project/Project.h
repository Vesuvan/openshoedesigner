///////////////////////////////////////////////////////////////////////////////
// Name               : Project.h
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
 */

#include "../3D/Volume.h"
#include "Foot.h"
#include "Shoe.h"
#include "Pattern.h"

class Project {
public:
	Project();
	virtual ~Project();

	void Reset(void);
	void Update(void);
	void UpdateVolume(void);

	const Foot* GetFoot(void) const;
	Shoe* GetShoe(void);
	void AddFootToGrid(wxGrid* gridLength, wxGrid* gridDiameter,
			wxGrid* gridSkin);
	void GetFootFromGrid(wxGrid* gridLength, wxGrid* gridDiameter,
			wxGrid* gridSkin);

	bool LoadModel(wxString fileName);
	bool SaveModel(wxString fileName);
	bool SaveLast(wxString fileName);

	void PaintBones(void) const;
	void PaintLast(void) const;
	void PaintInsole(void) const;
	void PaintSole(void) const;
	void PaintUpper(void) const;
	void PaintCutaway(void) const;
	void PaintFloor(void) const;
	bool Evaluate(void);

public:

	wxString HeelHeight;
	wxString HeelAngle;
	wxString PlateauHeight;
	wxString ToeAngle;

private:

	double floorLevel;

	Foot foot;
	Shoe shoe;
	Pattern pattern;

	Volume volume;
};

#endif /* PROJECT_H_ */
