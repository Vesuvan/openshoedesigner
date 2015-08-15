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

void Foot::Setup(void)
{
	Fibula->p1.Set(0.019474, -0.015216, 0.032985);
	Fibula->r1 = 0.013990;
	Fibula->p2.Set(0.007124, 0.039971, 0.029622);
	Fibula->r2 = 0.010907;
	Tibia->p1.Set(-0.002434, 0.005787, 0.007300);
	Tibia->r1 = 0.023388;
	Tibia->p2.Set(-0.001540, 0.033268, 0.007300);
	Tibia->r2 = 0.017677;
	Cuneiforme1->p1.Set(-0.081290, -0.039061, -0.005463);
	Cuneiforme1->r1 = 0.011979;
	Cuneiforme1->p2.Set(-0.073042, -0.050051, -0.005578);
	Cuneiforme1->r2 = 0.008856;
	Cuneiforme2->p1.Set(-0.069102, -0.036837, 0.003618);
	Cuneiforme2->r1 = 0.014685;
	Cuneiforme2->p2.Set(-0.065392, -0.047698, 0.003389);
	Cuneiforme2->r2 = 0.011649;
	Cuneiforme3->p1.Set(-0.065395, -0.031648, 0.021410);
	Cuneiforme3->r1 = 0.014287;
	Cuneiforme3->p2.Set(-0.058696, -0.049879, 0.020173);
	Cuneiforme3->r2 = 0.010362;
	PhalanxIII1->p1.Set(-0.153609, -0.067119, 0.056155);
	PhalanxIII1->r1 = 0.003187;
	PhalanxIII1->p2.Set(-0.161853, -0.066861, 0.054731);
	PhalanxIII1->r2 = 0.002342;
	PhalanxII1->p1.Set(-0.144560, -0.065903, 0.057532);
	PhalanxII1->r1 = 0.003135;
	PhalanxII1->p2.Set(-0.149362, -0.066903, 0.057056);
	PhalanxII1->r2 = 0.003002;
	PhalanxI1->p1.Set(-0.119787, -0.059630, 0.056813);
	PhalanxI1->r1 = 0.004569;
	PhalanxI1->p2.Set(-0.139709, -0.064359, 0.057957);
	PhalanxI1->r2 = 0.003513;
	Metatarsalis1->p1.Set(-0.056567, -0.034194, 0.053324);
	Metatarsalis1->r1 = 0.010552;
	Metatarsalis1->p2.Set(-0.112496, -0.057211, 0.055167);
	Metatarsalis1->r2 = 0.005472;
	PhalanxIII2->p1.Set(-0.172255, -0.071309, 0.042580);
	PhalanxIII2->r1 = 0.002793;
	PhalanxIII2->p2.Set(-0.180083, -0.072081, 0.041273);
	PhalanxIII2->r2 = 0.002274;
	PhalanxII2->p1.Set(-0.160009, -0.069980, 0.043772);
	PhalanxII2->r1 = 0.003109;
	PhalanxII2->p2.Set(-0.169127, -0.071183, 0.042580);
	PhalanxII2->r2 = 0.003246;
	PhalanxI2->p1.Set(-0.134407, -0.066933, 0.044129);
	PhalanxI2->r1 = 0.004459;
	PhalanxI2->p2.Set(-0.155571, -0.069782, 0.044070);
	PhalanxI2->r2 = 0.003475;
	Metatarsalis2->p1.Set(-0.069334, -0.034236, 0.039253);
	Metatarsalis2->r1 = 0.007522;
	Metatarsalis2->p2.Set(-0.126591, -0.064700, 0.043870);
	Metatarsalis2->r2 = 0.005974;
	PhalanxIII3->p1.Set(-0.192812, -0.073434, 0.028280);
	PhalanxIII3->r1 = 0.002329;
	PhalanxIII3->p2.Set(-0.202047, -0.076106, 0.027684);
	PhalanxIII3->r2 = 0.002230;
	PhalanxII3->p1.Set(-0.176426, -0.071365, 0.028876);
	PhalanxII3->r1 = 0.003044;
	PhalanxII3->p2.Set(-0.188343, -0.072582, 0.028578);
	PhalanxII3->r2 = 0.003057;
	PhalanxI3->p1.Set(-0.147974, -0.068386, 0.031110);
	PhalanxI3->r1 = 0.004674;
	PhalanxI3->p2.Set(-0.170914, -0.070769, 0.029323);
	PhalanxI3->r2 = 0.003601;
	Metatarsalis3->p1.Set(-0.082201, -0.038400, 0.026779);
	Metatarsalis3->r1 = 0.009293;
	Metatarsalis3->p2.Set(-0.139186, -0.064810, 0.030812);
	Metatarsalis3->r2 = 0.005760;
	PhalanxIII4->p1.Set(-0.206799, -0.059921, 0.011269);
	PhalanxIII4->r1 = 0.003619;
	PhalanxIII4->p2.Set(-0.214383, -0.058644, 0.010583);
	PhalanxIII4->r2 = 0.003159;
	PhalanxII4->p1.Set(-0.187878, -0.065174, 0.012798);
	PhalanxII4->r1 = 0.004476;
	PhalanxII4->p2.Set(-0.201854, -0.061952, 0.011607);
	PhalanxII4->r2 = 0.004170;
	PhalanxI4->p1.Set(-0.151018, -0.066246, 0.013626);
	PhalanxI4->r1 = 0.006157;
	PhalanxI4->p2.Set(-0.181413, -0.065819, 0.013626);
	PhalanxI4->r2 = 0.004605;
	Metatarsalis4->p1.Set(-0.087781, -0.040935, 0.009341);
	Metatarsalis4->r1 = 0.009685;
	Metatarsalis4->p2.Set(-0.142157, -0.067006, 0.013945);
	Metatarsalis4->r2 = 0.006086;
	Cuboideum->p1.Set(-0.046862, -0.033130, 0.031788);
	Cuboideum->r1 = 0.018324;
	Cuboideum->p2.Set(-0.026337, -0.043138, 0.030861);
	Cuboideum->r2 = 0.010445;
	Talus->p1.Set(-0.002117, -0.015709, 0.005363);
	Talus->r1 = 0.022932;
	Talus->p2.Set(0.003906, -0.038967, 0.016173);
	Talus->r2 = 0.026124;
	Calcaneus->p1.Set(0.030007, -0.054972, 0.022094);
	Calcaneus->r1 = 0.027198;
	Calcaneus->p2.Set(0.024430, -0.078568, 0.021879);
	Calcaneus->r2 = 0.010560;
	PhalanxII5->p1.Set(-0.194303, -0.064790, -0.008409);
	PhalanxII5->r1 = 0.007658;
	PhalanxII5->p2.Set(-0.217106, -0.055948, -0.005612);
	PhalanxII5->r2 = 0.004365;
	PhalanxI5->p1.Set(-0.148846, -0.067063, -0.015047);
	PhalanxI5->r1 = 0.012214;
	PhalanxI5->p2.Set(-0.187141, -0.066676, -0.011615);
	PhalanxI5->r2 = 0.009728;
	Metatarsalis5->p1.Set(-0.089885, -0.043994, -0.004965);
	Metatarsalis5->r1 = 0.013598;
	Metatarsalis5->p2.Set(-0.137334, -0.065824, -0.013681);
	Metatarsalis5->r2 = 0.012239;
	Naviculare->p1.Set(-0.043261, -0.034242, -0.001443);
	Naviculare->r1 = 0.021721;
	Naviculare->p2.Set(-0.043261, -0.034242, -0.001443);
	Naviculare->r2 = 0.000000;
	Talus2->p1.Set(-0.024512, -0.026984, 0.002048);
	Talus2->r1 = 0.018522;
	Talus2->p2.Set(-0.010603, -0.043509, 0.012555);
	Talus2->r2 = 0.019083;
}
