///////////////////////////////////////////////////////////////////////////////
// Name               : Foot.h
// Purpose            : Footbones and skin parameters
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 13.08.2015
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

#ifndef FOOT_H_
#define FOOT_H_

/*!\class Foot
 * \brief Footbones and skin parameters
 *
 * Stores the footbones and skin parameters.
 *
 * Upon calling Setup with a FootParameters object, the parameters of bones and skin are recalculated.
 *
 * Tibia
 * Fibula
 * Talus
 * Talus2
 * Calcaneus
 * Cuboideum
 * Naviculare
 * Cuneiforme1
 * Cuneiforme2
 * Cuneiforme3
 * Metatarsalis1
 * Metatarsalis2
 * Metatarsalis3
 * Metatarsalis4
 * Metatarsalis5
 * PhalanxI1
 * PhalanxI2
 * PhalanxI3
 * PhalanxI4
 * PhalanxI5
 * PhalanxII1
 * PhalanxII2
 * PhalanxII3
 * PhalanxII4
 * PhalanxII5
 * PhalanxIII1
 * PhalanxIII2
 * PhalanxIII3
 * PhalanxIII4
 *
 */

#include "Bone.h"

#include "../3D/Volume.h"

#include <wx/txtstrm.h>
#include <wx/grid.h>

class Foot {

public:
	Foot();
	virtual ~Foot();
	void Render(void) const;

	unsigned int GetBoneCount(void) const;
	bool LoadModel(wxTextInputStream* stream);
	bool SaveModel(wxTextOutputStream* stream);

	void AddToGrid(wxGrid* gridLength, wxGrid* gridDiameter, wxGrid* gridSkin);
	void GetFromGrid(wxGrid* gridLength, wxGrid* gridDiameter,
			wxGrid* gridSkin);

	void SetPosition(double heelheight, double toeAngle, double mixing = 0.5);
	void SetSize(double L, double W, double H, double A);

	double GetHeelHeight(void) const;
	double GetToeHeight(void) const;

	void AddToVolume(Volume* vol);

private:
	void InitBones(void);
	void Update(void);

public:
	double L, W, H, A;

private:
	Bone* Tibia; /// Schienbein
	Bone* Fibula; /// Wadenbein
	Bone* Talus; /// Sprungbein
	Bone* Talus2; /// Sprungbein (Extrabone)
	Bone* Calcaneus; /// Fersenbein
	Bone* Cuboideum; /// Wuerfelbein
	Bone* Naviculare; /// Kahnbein
	Bone* Cuneiforme1; /// Keilbein 1
	Bone* Cuneiforme2; /// Keilbein 2
	Bone* Cuneiforme3; /// Keilbein 3
	Bone* Metatarsalis1; /// Mittelfussknochen 1
	Bone* Metatarsalis2; /// Mittelfussknochen 2
	Bone* Metatarsalis3; /// Mittelfussknochen 3
	Bone* Metatarsalis4; /// Mittelfussknochen 4
	Bone* Metatarsalis5; /// Mittelfussknochen 5
	Bone* PhalanxI1;
	Bone* PhalanxI2;
	Bone* PhalanxI3;
	Bone* PhalanxI4;
	Bone* PhalanxI5;
	Bone* PhalanxII1;
	Bone* PhalanxII2;
	Bone* PhalanxII3;
	Bone* PhalanxII4;
	Bone* PhalanxII5;
	Bone* PhalanxIII1;
	Bone* PhalanxIII2;
	Bone* PhalanxIII3;
	Bone* PhalanxIII4;

private:
	static const unsigned int NBones;
};

#endif /* FOOT_H_ */
