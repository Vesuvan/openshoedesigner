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

#include "BoneSetup.h"

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
	Talus->AddChild(Talus2);
	Talus->AddChild(Calcaneus);

	Talus->AddChild(Cuboideum);
	Talus->AddChild(Naviculare);
	Naviculare->AddChild(Cuneiforme1);
	Naviculare->AddChild(Cuneiforme2);
	Naviculare->AddChild(Cuneiforme3);

	Cuboideum->AddChild(Metatarsalis1);
	Cuboideum->AddChild(Metatarsalis2);

	// Yes, this is correct: 3->3, 4->2, 5->1
	Cuneiforme3->AddChild(Metatarsalis3);
	Cuneiforme2->AddChild(Metatarsalis4);
	Cuneiforme1->AddChild(Metatarsalis5);

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

	InitBones();

}

Foot::~Foot()
{
	delete Tibia;
}

void Foot::Render(void) const
{
	Tibia->Paint();
}

void Foot::AddToVolume(Volume * vol)
{
	BoneToVolume b2v(vol);
	Tibia->Accept(b2v);
}

void Foot::Setup(FootParameters * param)
{

	Talus->roty = param->angle_1Y;
	Talus->rotx = param->angle_1X;
	Calcaneus->rotx = param->angle_2X;
	PhalanxI1->roty = param->angle_3Y;
	PhalanxI2->roty = param->angle_3Y;
	PhalanxI3->roty = param->angle_3Y;
	PhalanxI4->roty = param->angle_3Y;
	PhalanxI5->roty = param->angle_3Y;
	BoneSetup set;
	Tibia->Accept(set);
}

void Foot::InitBones(void)
{
	Tibia->r1 = 0.025286;
	Tibia->r2 = 0.014391;
	Tibia->link.Set(0.000000, 0.000000, 0.000000);
	Tibia->bone.Set(-0.000310, 0.007372, 0.077506);
	Tibia->anchor.Set(0.000000, 0.000000, 0.000000);
	Fibula->r1 = 0.013902;
	Fibula->r2 = 0.006541;
	Fibula->link.Set(-0.013749, 0.021345, -0.112101);
	Fibula->bone.Set(-0.008338, 0.006389, 0.112180);
	Fibula->anchor.Set(-0.000310, 0.007372, 0.077506);
	Talus->r1 = 0.022932;
	Talus->r2 = 0.029215;
	Talus->link.Set(0.004944, -0.005286, -0.025337);
	Talus->bone.Set(-0.010584, 0.010810, -0.024826);
	Talus->anchor.Set(-0.004239, 0.003531, -0.001728);
	Talus2->r1 = 0.019513;
	Talus2->r2 = 0.019083;
	Talus2->link.Set(0.033834, -0.014125, 0.010843);
	Talus2->bone.Set(-0.014764, 0.010507, -0.019661);
	Talus2->anchor.Set(-0.010584, 0.010810, -0.024826);
	Calcaneus->r1 = 0.027198;
	Calcaneus->r2 = 0.016550;
	Calcaneus->link.Set(-0.022538, 0.008934, -0.017430);
	Calcaneus->bone.Set(0.000920, -0.009802, -0.014564);
	Calcaneus->anchor.Set(-0.010584, 0.010810, -0.024826);
	Cuboideum->r1 = 0.018324;
	Cuboideum->r2 = 0.010445;
	Cuboideum->link.Set(0.030894, 0.021208, -0.008305);
	Cuboideum->bone.Set(-0.023708, -0.002707, -0.010008);
	Cuboideum->anchor.Set(0.012852, 0.006998, -0.012109);
	Naviculare->r1 = 0.021721;
	Naviculare->r2 = 0.021721;
	Naviculare->link.Set(0.005566, -0.000964, -0.003492);
	Naviculare->bone.Set(0.000000, 0.000000, 0.000000);
	Naviculare->anchor.Set(0.034580, -0.005841, -0.018035);
	Cuneiforme1->r1 = 0.016716;
	Cuneiforme1->r2 = 0.016716;
	Cuneiforme1->link.Set(0.036123, 0.006280, -0.009722);
	Cuneiforme1->bone.Set(0.000000, 0.000000, 0.000000);
	Cuneiforme1->anchor.Set(-0.001757, -0.007642, 0.004903);
	Cuneiforme2->r1 = 0.018744;
	Cuneiforme2->r2 = 0.018744;
	Cuneiforme2->link.Set(0.023435, 0.005673, -0.006087);
	Cuneiforme2->bone.Set(0.000000, 0.000000, 0.000000);
	Cuneiforme2->anchor.Set(0.002405, 0.000894, 0.003492);
	Cuneiforme3->r1 = 0.017315;
	Cuneiforme3->r2 = 0.017315;
	Cuneiforme3->link.Set(0.022480, 0.014813, -0.001101);
	Cuneiforme3->bone.Set(0.000000, 0.000000, 0.000000);
	Cuneiforme3->anchor.Set(-0.000346, 0.008724, 0.001093);
	Metatarsalis1->r1 = 0.008659;
	Metatarsalis1->r2 = 0.005561;
	Metatarsalis1->link.Set(0.010257, 0.011549, -0.002299);
	Metatarsalis1->bone.Set(0.057106, 0.002831, -0.030631);
	Metatarsalis1->anchor.Set(-0.002228, 0.007275, 0.004791);
	Metatarsalis2->r1 = 0.006980;
	Metatarsalis2->r2 = 0.006135;
	Metatarsalis2->link.Set(0.014408, 0.003485, -0.004301);
	Metatarsalis2->bone.Set(0.059212, 0.004059, -0.027662);
	Metatarsalis2->anchor.Set(0.007159, 0.002845, 0.001902);
	Metatarsalis3->r1 = 0.007826;
	Metatarsalis3->r2 = 0.005726;
	Metatarsalis3->link.Set(0.011797, 0.003556, -0.004916);
	Metatarsalis3->bone.Set(0.058176, 0.004134, -0.024579);
	Metatarsalis3->anchor.Set(0.004569, 0.000916, -0.001066);
	Metatarsalis4->r1 = 0.009360;
	Metatarsalis4->r2 = 0.006547;
	Metatarsalis4->link.Set(0.014953, 0.003896, -0.007039);
	Metatarsalis4->bone.Set(0.055079, 0.004019, -0.024239);
	Metatarsalis4->anchor.Set(0.002837, 0.000533, 0.002941);
	Metatarsalis5->r1 = 0.012594;
	Metatarsalis5->r2 = 0.013472;
	Metatarsalis5->link.Set(0.017216, 0.000151, -0.006666);
	Metatarsalis5->bone.Set(0.046088, -0.008783, -0.022042);
	Metatarsalis5->anchor.Set(-0.002866, -0.002684, 0.002208);
	PhalanxI1->r1 = 0.003899;
	PhalanxI1->r2 = 0.003513;
	PhalanxI1->link.Set(0.007906, 0.001473, -0.002325);
	PhalanxI1->bone.Set(0.019806, 0.001260, -0.000764);
	PhalanxI1->anchor.Set(0.057106, 0.002831, -0.030631);
	PhalanxI2->r1 = 0.003867;
	PhalanxI2->r2 = 0.003475;
	PhalanxI2->link.Set(0.007672, 0.000559, -0.003741);
	PhalanxI2->bone.Set(0.020259, -0.000447, -0.002311);
	PhalanxI2->anchor.Set(0.059212, 0.004059, -0.027662);
	PhalanxI3->r1 = 0.004674;
	PhalanxI3->r2 = 0.003601;
	PhalanxI3->link.Set(0.007588, 0.000783, -0.001894);
	PhalanxI3->bone.Set(0.023389, -0.002162, -0.003418);
	PhalanxI3->anchor.Set(0.058176, 0.004134, -0.024579);
	PhalanxI4->r1 = 0.006157;
	PhalanxI4->r2 = 0.004605;
	PhalanxI4->link.Set(0.009048, 0.000053, -0.001073);
	PhalanxI4->bone.Set(0.030394, 0.000000, 0.000858);
	PhalanxI4->anchor.Set(0.055079, 0.004019, -0.024239);
	PhalanxI5->r1 = 0.011416;
	PhalanxI5->r2 = 0.009728;
	PhalanxI5->link.Set(0.012104, -0.001299, -0.002040);
	PhalanxI5->bone.Set(0.036973, 0.003804, 0.001702);
	PhalanxI5->anchor.Set(0.046088, -0.008783, -0.022042);
	PhalanxII1->r1 = 0.003135;
	PhalanxII1->r2 = 0.003002;
	PhalanxII1->link.Set(0.005663, -0.000515, -0.001544);
	PhalanxII1->bone.Set(0.003990, -0.000386, -0.001215);
	PhalanxII1->anchor.Set(0.019806, 0.001260, -0.000764);
	PhalanxII2->r1 = 0.002979;
	PhalanxII2->r2 = 0.002490;
	PhalanxII2->link.Set(0.004955, -0.000557, -0.000521);
	PhalanxII2->bone.Set(0.008600, -0.000933, -0.000772);
	PhalanxII2->anchor.Set(0.020259, -0.000447, -0.002311);
	PhalanxII3->r1 = 0.003668;
	PhalanxII3->r2 = 0.003399;
	PhalanxII3->link.Set(0.005899, -0.000188, -0.001242);
	PhalanxII3->bone.Set(0.011529, -0.000557, -0.000894);
	PhalanxII3->anchor.Set(0.023389, -0.002162, -0.003418);
	PhalanxII4->r1 = 0.003865;
	PhalanxII4->r2 = 0.003625;
	PhalanxII4->link.Set(0.006465, -0.000828, 0.000214);
	PhalanxII4->bone.Set(0.013672, -0.001241, 0.003492);
	PhalanxII4->anchor.Set(0.030394, 0.000000, 0.000858);
	PhalanxII5->r1 = 0.007400;
	PhalanxII5->r2 = 0.005207;
	PhalanxII5->link.Set(0.007162, 0.001525, 0.001645);
	PhalanxII5->bone.Set(0.021399, 0.004220, 0.007119);
	PhalanxII5->anchor.Set(0.036973, 0.003804, 0.001702);
	PhalanxIII1->r1 = 0.002859;
	PhalanxIII1->r2 = 0.001990;
	PhalanxIII1->link.Set(0.004247, -0.000901, 0.000000);
	PhalanxIII1->bone.Set(0.008362, -0.001415, 0.000257);
	PhalanxIII1->anchor.Set(0.003990, -0.000386, -0.001215);
	PhalanxIII2->r1 = 0.002571;
	PhalanxIII2->r2 = 0.001911;
	PhalanxIII2->link.Set(0.004033, -0.000129, -0.000384);
	PhalanxIII2->bone.Set(0.007347, -0.001121, -0.001160);
	PhalanxIII2->anchor.Set(0.008600, -0.000933, -0.000772);
	PhalanxIII3->r1 = 0.003292;
	PhalanxIII3->r2 = 0.002230;
	PhalanxIII3->link.Set(0.004598, -0.000557, -0.000745);
	PhalanxIII3->bone.Set(0.009106, -0.000337, -0.001875);
	PhalanxIII3->anchor.Set(0.011529, -0.000557, -0.000894);
	PhalanxIII4->r1 = 0.003619;
	PhalanxIII4->r2 = 0.002884;
	PhalanxIII4->link.Set(0.004698, -0.000526, 0.001043);
	PhalanxIII4->bone.Set(0.008258, -0.000448, 0.002085);
	PhalanxIII4->anchor.Set(0.013672, -0.001241, 0.003492);


}
