///////////////////////////////////////////////////////////////////////////////
// Name               : Foot.cpp
// Purpose            : 
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

#include "Foot.h"

#include "BoneToVolume.h"

Foot::Foot()
{
	Tibia = new Bone;
	Fibula = new Bone;
	Talus = new Bone;
	Talus2 = new Bone;
	Calcaneus = new Bone;
	Cuboideum = new Bone;
	Naviculare = new Bone;
	Cuneiforme1 = new Bone;
	Cuneiforme2 = new Bone;
	Cuneiforme3 = new Bone;
	Metatarsalis1 = new Bone;
	Metatarsalis2 = new Bone;
	Metatarsalis3 = new Bone;
	Metatarsalis4 = new Bone;
	Metatarsalis5 = new Bone;

	PhalanxI1 = new Bone;
	PhalanxI2 = new Bone;
	PhalanxI3 = new Bone;
	PhalanxI4 = new Bone;
	PhalanxI5 = new Bone;

	PhalanxII1 = new Bone;
	PhalanxII2 = new Bone;
	PhalanxII3 = new Bone;
	PhalanxII4 = new Bone;
	PhalanxII5 = new Bone;

	PhalanxIII1 = new Bone;
	PhalanxIII2 = new Bone;
	PhalanxIII3 = new Bone;
	PhalanxIII4 = new Bone;

	Tibia->AddChild(Fibula);

	Tibia->AddChild(Talus);
	Tibia->AddChild(Talus2);
	Talus->AddChild(Calcaneus);

	Talus->AddChild(Cuboideum);
	Talus->AddChild(Naviculare);
	Naviculare->AddChild(Cuneiforme1);
	Naviculare->AddChild(Cuneiforme2);
	Naviculare->AddChild(Cuneiforme3);

	Cuboideum->AddChild(Metatarsalis1);
	Cuboideum->AddChild(Metatarsalis2);

	// Yes, this is correct: 3->3, 4->2, 5->1
	Cuneiforme1->AddChild(Metatarsalis3);
	Cuneiforme2->AddChild(Metatarsalis4);
	Cuneiforme3->AddChild(Metatarsalis5);

	Metatarsalis1->AddChild(PhalanxI1);
	Metatarsalis2->AddChild(PhalanxI2);
	Metatarsalis3->AddChild(PhalanxI3);
	Metatarsalis4->AddChild(PhalanxI4);
	Metatarsalis5->AddChild(PhalanxI5);

	PhalanxI1->AddChild(PhalanxII1);
	PhalanxI2->AddChild(PhalanxII2);
	PhalanxI3->AddChild(PhalanxII3);
	PhalanxI4->AddChild(PhalanxII4);
	PhalanxI5->AddChild(PhalanxII5);
	
	PhalanxII1->AddChild(PhalanxIII1);
	PhalanxII2->AddChild(PhalanxIII2);
	PhalanxII3->AddChild(PhalanxIII3);
	PhalanxII4->AddChild(PhalanxIII4);
}

Foot::~Foot()
{
	delete Tibia;
}

void Foot::Render(void) const
{
	Tibia->Paint();
}

void Foot::AddToVolume(Volume* vol)
{
	BoneToVolume b2v;
	b2v.SetVolume(vol);
	Tibia->Accept(b2v);
}

void Foot::Setup(void)
{
	PhalanxIII1->p1.Set(0.153609, 0.056155, -0.067119);
	PhalanxIII1->r1 = 0.002859;
	PhalanxIII1->p2.Set(0.162876, 0.054611, -0.066861);
	PhalanxIII1->r2 = 0.001629;
	PhalanxII1->p1.Set(0.145372, 0.057442, -0.065903);
	PhalanxII1->r1 = 0.003135;
	PhalanxII1->p2.Set(0.149362, 0.057056, -0.067119);
	PhalanxII1->r2 = 0.003002;
	PhalanxI1->p1.Set(0.120146, 0.057442, -0.061785);
	PhalanxI1->r1 = 0.003899;
	PhalanxI1->p2.Set(0.139709, 0.057957, -0.064359);
	PhalanxI1->r2 = 0.003513;
	Metatarsalis1->p1.Set(0.056567, 0.053324, -0.030639);
	Metatarsalis1->r1 = 0.006408;
	Metatarsalis1->p2.Set(0.110880, 0.056155, -0.061270);
	Metatarsalis1->r2 = 0.004751;
	PhalanxIII2->p1.Set(0.172255, 0.042580, -0.071309);
	PhalanxIII2->r1 = 0.002314;
	PhalanxIII2->p2.Set(0.180895, 0.040942, -0.072081);
	PhalanxIII2->r2 = 0.001654;
	PhalanxII2->p1.Set(0.160785, 0.043772, -0.069764);
	PhalanxII2->r1 = 0.002979;
	PhalanxII2->p2.Set(0.169127, 0.042580, -0.070537);
	PhalanxII2->r2 = 0.002490;
	PhalanxI2->p1.Set(0.135313, 0.044517, -0.066933);
	PhalanxI2->r1 = 0.003867;
	PhalanxI2->p2.Set(0.155571, 0.044070, -0.070537);
	PhalanxI2->r2 = 0.003475;
	Metatarsalis2->p1.Set(0.068429, 0.039899, -0.035529);
	Metatarsalis2->r1 = 0.005367;
	Metatarsalis2->p2.Set(0.128013, 0.044517, -0.065131);
	Metatarsalis2->r2 = 0.004684;
	PhalanxIII3->p1.Set(0.192812, 0.028280, -0.073003);
	PhalanxIII3->r1 = 0.002329;
	PhalanxIII3->p2.Set(0.202047, 0.027684, -0.076430);
	PhalanxIII3->r2 = 0.002230;
	PhalanxII3->p1.Set(0.176426, 0.028876, -0.071365);
	PhalanxII3->r1 = 0.003044;
	PhalanxII3->p2.Set(0.188343, 0.028578, -0.072259);
	PhalanxII3->r2 = 0.003057;
	PhalanxI3->p1.Set(0.147974, 0.031110, -0.068386);
	PhalanxI3->r1 = 0.004674;
	PhalanxI3->p2.Set(0.170914, 0.029323, -0.070769);
	PhalanxI3->r2 = 0.003601;
	Metatarsalis3->p1.Set(0.083623, 0.027684, -0.040232);
	Metatarsalis3->r1 = 0.006497;
	Metatarsalis3->p2.Set(0.139186, 0.030812, -0.064810);
	Metatarsalis3->r2 = 0.005760;
	PhalanxIII4->p1.Set(0.206247, 0.011031, -0.060640);
	PhalanxIII4->r1 = 0.003619;
	PhalanxIII4->p2.Set(0.214505, 0.010583, -0.058554);
	PhalanxIII4->r2 = 0.002884;
	PhalanxII4->p1.Set(0.187878, 0.012798, -0.065174);
	PhalanxII4->r1 = 0.003865;
	PhalanxII4->p2.Set(0.201032, 0.011686, -0.061682);
	PhalanxII4->r2 = 0.003075;
	PhalanxI4->p1.Set(0.151018, 0.013626, -0.066246);
	PhalanxI4->r1 = 0.006157;
	PhalanxI4->p2.Set(0.181413, 0.013626, -0.065388);
	PhalanxI4->r2 = 0.004605;
	Metatarsalis4->p1.Set(0.087264, 0.008436, -0.040935);
	Metatarsalis4->r1 = 0.008458;
	Metatarsalis4->p2.Set(0.142157, 0.013945, -0.065174);
	Metatarsalis4->r2 = 0.006086;
	Cuneiforme1->p1.Set(0.077627, -0.001572, -0.039061);
	Cuneiforme1->r1 = 0.016716;
	Cuneiforme1->p2.Set(0.077627, -0.001572, -0.039061);
	Cuneiforme1->r2 = 0.000000;
	Cuneiforme2->p1.Set(0.069102, 0.003618, -0.036837);
	Cuneiforme2->r1 = 0.018744;
	Cuneiforme2->p2.Set(0.069102, 0.003618, -0.036837);
	Cuneiforme2->r2 = 0.000000;
	Cuneiforme3->p1.Set(0.065395, 0.021410, -0.031648);
	Cuneiforme3->r1 = 0.014287;
	Cuneiforme3->p2.Set(0.065395, 0.021410, -0.031648);
	Cuneiforme3->r2 = 0.000000;
	Cuboideum->p1.Set(0.046862, 0.031788, -0.033130);
	Cuboideum->r1 = 0.018324;
	Cuboideum->p2.Set(0.046862, 0.031788, -0.033130);
	Cuboideum->r2 = 0.000000;
	Talus->p1.Set(0.002117, 0.005363, -0.015709);
	Talus->r1 = 0.022932;
	Talus->p2.Set(-0.003906, 0.016173, -0.038967);
	Talus->r2 = 0.026124;
	Calcaneus->p1.Set(-0.030007, 0.022094, -0.054972);
	Calcaneus->r1 = 0.027198;
	Calcaneus->p2.Set(-0.024430, 0.021879, -0.078568);
	Calcaneus->r2 = 0.010560;
	PhalanxII5->p1.Set(0.194303, -0.008409, -0.058953);
	PhalanxII5->r1 = 0.005225;
	PhalanxII5->p2.Set(0.218030, -0.004965, -0.054938);
	PhalanxII5->r2 = 0.003389;
	PhalanxI5->p1.Set(0.143279, -0.015047, -0.067602);
	PhalanxI5->r1 = 0.014166;
	PhalanxI5->p2.Set(0.187141, -0.011615, -0.066676);
	PhalanxI5->r2 = 0.009728;
	Metatarsalis5->p1.Set(0.091231, -0.004965, -0.041192);
	Metatarsalis5->r1 = 0.010804;
	Metatarsalis5->p2.Set(0.129070, -0.012259, -0.061424);
	Metatarsalis5->r2 = 0.008016;
	Naviculare->p1.Set(0.043261, -0.001443, -0.034242);
	Naviculare->r1 = -0.021721;
	Naviculare->p2.Set(0.043261, -0.001443, -0.034242);
	Naviculare->r2 = 0.000000;
	Talus2->p1.Set(0.024512, 0.002048, -0.026984);
	Talus2->r1 = 0.018522;
	Talus2->p2.Set(0.010603, 0.012555, -0.043509);
	Talus2->r2 = 0.019083;
}
