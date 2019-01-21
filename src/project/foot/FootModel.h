///////////////////////////////////////////////////////////////////////////////
// Name               : FootModel.h
// Purpose            : Bone-based model of a foot
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

#ifndef FOOTMODEL_H_
#define FOOTMODEL_H_

/*!\class FootModel
 * \brief Bone-based model of a foot
 *
 * Stores the footbones and skin parameters.
 *
 * Upon calling Setup with a FootMeasurements object, the size and position of
 * the bones and the skin are calculated.
 *
 *\dot
 * digraph classes {
 *     rankdir = LR
 *
 *	 node [fontname=Helvetica, fontsize=10];
 *
 *   Tibia -> Talus
 *   Tibia -> Fibula
 *   Talus -> Cuboideum
 *   Talus -> Naviculare
 *   Talus -> Calcaneus
 *   Talus -> Talus2
 *   Naviculare -> Cuneiforme3
 *   Naviculare -> Cuneiforme2
 *   Naviculare -> Cuneiforme1
 *   Cuboideum -> Metatarsalis1
 *   Cuboideum -> Metatarsalis2
 *   Cuneiforme3 -> Metatarsalis3
 *   Cuneiforme2 -> Metatarsalis4
 *   Cuneiforme1 -> Metatarsalis5
 *   Metatarsalis1 -> PhalanxI1
 *   Metatarsalis2 -> PhalanxI2
 *   Metatarsalis3 -> PhalanxI3
 *   Metatarsalis4 -> PhalanxI4
 *   Metatarsalis5 -> PhalanxI5
 *   PhalanxI1 -> PhalanxII1
 *   PhalanxI2 -> PhalanxII2
 *   PhalanxI3 -> PhalanxII3
 *   PhalanxI4 -> PhalanxII4
 *   PhalanxI5 -> PhalanxII5
 *   PhalanxII1 -> PhalanxIII1
 *   PhalanxII2 -> PhalanxIII2
 *   PhalanxII3 -> PhalanxIII3
 *   PhalanxII4 -> PhalanxIII4
 * }
 * \enddot
 *
 * (Talus2 is an extra bone-element to get the form of the Talus right.)
 */

#include <wx/txtstrm.h>
#include "../../3D/Polygon3.h"
#include "../../3D/BoundingBox.h"
#include "../../3D/Volume.h"
#include "../../math/NelderMeadOptimizer.h"
#include "../foot/FootMeasurements.h"
#include "../foot/Skeleton.h"

class Shoe;

class FootModel:public Skeleton {
public:

	FootModel();
	virtual ~FootModel();

	bool IsModifiedForm(void) const;
	bool IsModifiedPosition(void) const;
	bool IsModifiedSkin(void) const;
	void ModifyForm(bool modified = true);
	void ModifyPosition(bool modified = true);
	void ModifySkin(bool modified = true);

	void PaintBones(void) const;
	void PaintSkin(void) const;

	bool LoadModel(wxTextInputStream* stream);
	bool SaveModel(wxTextOutputStream* stream);
	void CopyModel(const FootModel &other);

	void UpdateForm(const FootMeasurements &measurements);
	void UpdatePosition(const Shoe &shoe, double offset = 0.0, double mixing =
			0.05);

	void CalculateBones(void);
	void CalculateSkin(void);

	Polygon3 GetCenterline(void) const; //!< (Re-)move?

	AffineTransformMatrix origin; //!< Origin for drawing. The origin of the model is the ankle.

	BoundingBox bounds;
	Volume skin;

private:
	void InitBones(void);

	bool modifiedForm;
	bool modifiedPosition;
	bool modifiedSkin;

	// Model parameter, set by optimizer
	double L;
	double W;

	NelderMeadOptimizer optiForm;
	NelderMeadOptimizer optiPos;

private:
	static const unsigned int NBones;

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
};

#endif /* FOOTMODEL_H_ */
