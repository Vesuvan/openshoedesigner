///////////////////////////////////////////////////////////////////////////////
// Name               : Foot.cpp
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

#include "Foot.h"

#include "BoneSetup.h"

#include "BoneToVolume.h"

Foot::Foot()
{
	Tibia = new Bone(_T("Tibia"));
	Fibula = new Bone(_T("Fibula"));
	Talus = new Bone(_T("Talus"));
	Talus2 = new Bone(_T("Talus2"));
	Calcaneus = new Bone(_T("Calcaneus"));
	Cuboideum = new Bone(_T("Cuboideum"));
	Naviculare = new Bone(_T("Naviculare"));
	Cuneiforme1 = new Bone(_T("Cuneiforme1"));
	Cuneiforme2 = new Bone(_T("Cuneiforme2"));
	Cuneiforme3 = new Bone(_T("Cuneiforme3"));
	Metatarsalis1 = new Bone(_T("Metatarsalis1"));
	Metatarsalis2 = new Bone(_T("Metatarsalis2"));
	Metatarsalis3 = new Bone(_T("Metatarsalis3"));
	Metatarsalis4 = new Bone(_T("Metatarsalis4"));
	Metatarsalis5 = new Bone(_T("Metatarsalis5"));

	PhalanxI1 = new Bone(_T("PhalanxI1"));
	PhalanxI2 = new Bone(_T("PhalanxI2"));
	PhalanxI3 = new Bone(_T("PhalanxI3"));
	PhalanxI4 = new Bone(_T("PhalanxI4"));
	PhalanxI5 = new Bone(_T("PhalanxI5"));

	PhalanxII1 = new Bone(_T("PhalanxII1"));
	PhalanxII2 = new Bone(_T("PhalanxII2"));
	PhalanxII3 = new Bone(_T("PhalanxII3"));
	PhalanxII4 = new Bone(_T("PhalanxII4"));
	PhalanxII5 = new Bone(_T("PhalanxII5"));

	PhalanxIII1 = new Bone(_T("PhalanxIII1"));
	PhalanxIII2 = new Bone(_T("PhalanxIII2"));
	PhalanxIII3 = new Bone(_T("PhalanxIII3"));
	PhalanxIII4 = new Bone(_T("PhalanxIII4"));

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
	// Passe the parameters down to each bone.
	Talus->roty = param->angle_1Y;
	Talus->rotx = param->angle_1X;
	Calcaneus->rotx = param->angle_2X;
	PhalanxI1->roty = param->angle_3Y;
	PhalanxI2->roty = param->angle_3Y;
	PhalanxI3->roty = param->angle_3Y;
	PhalanxI4->roty = param->angle_3Y;
	PhalanxI5->roty = param->angle_3Y;

	// Run the BoneSetup visitor to recalculate each single bone.
	BoneSetup set;
	Tibia->Accept(set);
}

void Foot::InitBones(void)
{
	Tibia->linkD = 0.014349;
	Tibia->linkN.Set(-0.002410, -0.007118, 0.000000);
	Tibia->anchor.Set(0.000000, 0.000000, 0.000000);
	Tibia->normal.Set(-0.003987, 0.094692, 0.995499);
	Tibia->length = 0.077857;
	Tibia->r1 = 0.025286;
	Tibia->r2 = 0.014391;
	Fibula->linkD = 1.000000;
	Fibula->linkN.Set(0.000000, 0.000000, 0.000000);
	Fibula->anchor.Set(-0.358608, 0.556751, -2.923908);
	Fibula->normal.Set(-0.074004, 0.056703, 0.995645);
	Fibula->length = 0.112671;
	Fibula->r1 = 0.013902;
	Fibula->r2 = 0.006541;
	Talus->linkD = -0.017587;
	Talus->linkN.Set(0.167854, -0.144765, 0.014442);
	Talus->anchor.Set(0.102541, -0.109632, -0.525473);
	Talus->normal.Set(-0.364068, 0.371839, -0.853926);
	Talus->length = 0.029073;
	Talus->r1 = 0.022932;
	Talus->r2 = 0.029215;
	Talus2->linkD = 1.000000;
	Talus2->linkN.Set(0.000000, 0.000000, 0.000000);
	Talus2->anchor.Set(0.793716, -0.331365, 0.254379);
	Talus2->normal.Set(-0.552159, 0.392960, -0.735325);
	Talus2->length = 0.026738;
	Talus2->r1 = 0.019513;
	Talus2->r2 = 0.019083;
	Calcaneus->linkD = 1.000000;
	Calcaneus->linkN.Set(0.000000, 0.000000, 0.000000);
	Calcaneus->anchor.Set(-0.447956, 0.177577, -0.346443);
	Calcaneus->normal.Set(0.052351, -0.557595, -0.828461);
	Calcaneus->length = 0.017579;
	Calcaneus->r1 = 0.027198;
	Calcaneus->r2 = 0.016550;
	Cuboideum->linkD = 0.284221;
	Cuboideum->linkN.Set(-0.690085, -0.170781, 0.219849);
	Cuboideum->anchor.Set(0.747911, 0.513430, -0.201065);
	Cuboideum->normal.Set(-0.916225, -0.104622, -0.386763);
	Cuboideum->length = 0.025876;
	Cuboideum->r1 = 0.018324;
	Cuboideum->r2 = 0.010445;
	Naviculare->linkD = 0.021979;
	Naviculare->linkN.Set(-1.517817, 0.265032, 0.762522);
	Naviculare->anchor.Set(0.124651, -0.021590, -0.078194);
	Naviculare->normal.Set(0.000000, 0.000000, 1.000000);
	Naviculare->length = 0.000000;
	Naviculare->r1 = 0.021721;
	Naviculare->r2 = 0.021721;
	Cuneiforme1->linkD = 0.004903;
	Cuneiforme1->linkN.Set(0.080898, 0.351837, 0.000000);
	Cuneiforme1->anchor.Set(0.939791, 0.163393, -0.252929);
	Cuneiforme1->normal.Set(0.000000, 0.000000, 1.000000);
	Cuneiforme1->length = 0.000000;
	Cuneiforme1->r1 = 0.016716;
	Cuneiforme1->r2 = 0.016716;
	Cuneiforme2->linkD = 0.003492;
	Cuneiforme2->linkN.Set(-0.110719, -0.041140, 0.000000);
	Cuneiforme2->anchor.Set(0.579158, 0.140203, -0.150428);
	Cuneiforme2->normal.Set(0.000000, 0.000000, 1.000000);
	Cuneiforme2->length = 0.000000;
	Cuneiforme2->r1 = 0.018744;
	Cuneiforme2->r2 = 0.018744;
	Cuneiforme3->linkD = 0.001093;
	Cuneiforme3->linkN.Set(0.015942, -0.401639, 0.000000);
	Cuneiforme3->anchor.Set(0.575879, 0.379473, -0.028206);
	Cuneiforme3->normal.Set(0.000000, 0.000000, 1.000000);
	Cuneiforme3->length = 0.000000;
	Cuneiforme3->r1 = 0.017315;
	Cuneiforme3->r2 = 0.017315;
	Metatarsalis1->linkD = -0.022146;
	Metatarsalis1->linkN.Set(0.150224, -0.393776, -0.249356);
	Metatarsalis1->anchor.Set(0.380148, 0.427998, -0.085205);
	Metatarsalis1->normal.Set(0.880389, 0.043652, -0.472239);
	Metatarsalis1->length = 0.064864;
	Metatarsalis1->r1 = 0.008659;
	Metatarsalis1->r2 = 0.005561;
	Metatarsalis2->linkD = -0.293424;
	Metatarsalis2->linkN.Set(-0.011062, -0.111926, 0.056483);
	Metatarsalis2->anchor.Set(0.569394, 0.137734, -0.169960);
	Metatarsalis2->normal.Set(0.904266, 0.061991, -0.422445);
	Metatarsalis2->length = 0.065481;
	Metatarsalis2->r1 = 0.006980;
	Metatarsalis2->r2 = 0.006135;
	Metatarsalis3->linkD = -0.001066;
	Metatarsalis3->linkN.Set(-0.263858, -0.052925, 0.000000);
	Metatarsalis3->anchor.Set(0.469229, 0.141451, -0.195523);
	Metatarsalis3->normal.Set(0.919196, 0.065317, -0.388347);
	Metatarsalis3->length = 0.063291;
	Metatarsalis3->r1 = 0.007826;
	Metatarsalis3->r2 = 0.005726;
	Metatarsalis4->linkD = 0.002941;
	Metatarsalis4->linkN.Set(-0.151374, -0.028433, 0.000000);
	Metatarsalis4->anchor.Set(0.532047, 0.138633, -0.250448);
	Metatarsalis4->normal.Set(0.913255, 0.066634, -0.401903);
	Metatarsalis4->length = 0.060311;
	Metatarsalis4->r1 = 0.009360;
	Metatarsalis4->r2 = 0.006547;
	Metatarsalis5->linkD = 0.002208;
	Metatarsalis5->linkN.Set(0.171461, 0.160574, 0.000000);
	Metatarsalis5->anchor.Set(0.587347, 0.005145, -0.227436);
	Metatarsalis5->normal.Set(0.889090, -0.169428, -0.425221);
	Metatarsalis5->length = 0.051837;
	Metatarsalis5->r1 = 0.012594;
	Metatarsalis5->r2 = 0.013472;
	PhalanxI1->linkD = 1.000000;
	PhalanxI1->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxI1->anchor.Set(0.639832, 0.119222, -0.188153);
	PhalanxI1->normal.Set(0.997245, 0.063421, -0.038461);
	PhalanxI1->length = 0.019861;
	PhalanxI1->r1 = 0.003899;
	PhalanxI1->r2 = 0.003513;
	PhalanxI2->linkD = 1.000000;
	PhalanxI2->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxI2->anchor.Set(0.710841, 0.051757, -0.346671);
	PhalanxI2->normal.Set(0.993320, -0.021912, -0.113297);
	PhalanxI2->length = 0.020395;
	PhalanxI2->r1 = 0.003867;
	PhalanxI2->r2 = 0.003475;
	PhalanxI3->linkD = 1.000000;
	PhalanxI3->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxI3->anchor.Set(0.613531, 0.063343, -0.153156);
	PhalanxI3->normal.Set(0.985379, -0.091072, -0.143991);
	PhalanxI3->length = 0.023736;
	PhalanxI3->r1 = 0.004674;
	PhalanxI3->r2 = 0.003601;
	PhalanxI4->linkD = 1.000000;
	PhalanxI4->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxI4->anchor.Set(0.589528, 0.003480, -0.069884);
	PhalanxI4->normal.Set(0.999602, 0.000000, 0.028218);
	PhalanxI4->length = 0.030407;
	PhalanxI4->r1 = 0.006157;
	PhalanxI4->r2 = 0.004605;
	PhalanxI5->linkD = 1.000000;
	PhalanxI5->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxI5->anchor.Set(0.503154, -0.054001, -0.084810);
	PhalanxI5->normal.Set(0.993706, 0.102251, 0.045756);
	PhalanxI5->length = 0.037207;
	PhalanxI5->r1 = 0.011416;
	PhalanxI5->r2 = 0.009728;
	PhalanxII1->linkD = 1.000000;
	PhalanxII1->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxII1->anchor.Set(0.805990, -0.073272, -0.219815);
	PhalanxII1->normal.Set(0.952523, -0.092180, -0.290177);
	PhalanxII1->length = 0.004189;
	PhalanxII1->r1 = 0.003135;
	PhalanxII1->r2 = 0.003002;
	PhalanxII2->linkD = 1.000000;
	PhalanxII2->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxII2->anchor.Set(0.724642, -0.081387, -0.076160);
	PhalanxII2->normal.Set(0.990229, -0.107434, -0.088910);
	PhalanxII2->length = 0.008685;
	PhalanxII2->r1 = 0.002979;
	PhalanxII2->r2 = 0.002490;
	PhalanxII3->linkD = 1.000000;
	PhalanxII3->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxII3->anchor.Set(0.709316, -0.022639, -0.149371);
	PhalanxII3->normal.Set(0.995856, -0.048071, -0.077203);
	PhalanxII3->length = 0.011577;
	PhalanxII3->r1 = 0.003668;
	PhalanxII3->r2 = 0.003399;
	PhalanxII4->linkD = 1.000000;
	PhalanxII4->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxII4->anchor.Set(0.648185, -0.082968, 0.021506);
	PhalanxII4->normal.Set(0.965172, -0.087632, 0.246502);
	PhalanxII4->length = 0.014165;
	PhalanxII4->r1 = 0.003865;
	PhalanxII4->r2 = 0.003625;
	PhalanxII5->linkD = 1.000000;
	PhalanxII5->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxII5->anchor.Set(0.381906, 0.081305, 0.087722);
	PhalanxII5->normal.Set(0.932687, 0.183921, 0.310270);
	PhalanxII5->length = 0.022944;
	PhalanxII5->r1 = 0.007400;
	PhalanxII5->r2 = 0.005207;
	PhalanxIII1->linkD = 1.000000;
	PhalanxIII1->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxIII1->anchor.Set(0.708613, -0.150312, 0.000000);
	PhalanxIII1->normal.Set(0.985525, -0.166794, 0.030339);
	PhalanxIII1->length = 0.008484;
	PhalanxIII1->r1 = 0.002859;
	PhalanxIII1->r2 = 0.001990;
	PhalanxIII2->linkD = 1.000000;
	PhalanxIII2->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxIII2->anchor.Set(0.727318, -0.023315, -0.069304);
	PhalanxIII2->normal.Set(0.976722, -0.149084, -0.154231);
	PhalanxIII2->length = 0.007522;
	PhalanxIII2->r1 = 0.002571;
	PhalanxIII2->r2 = 0.001911;
	PhalanxIII3->linkD = 1.000000;
	PhalanxIII3->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxIII3->anchor.Set(0.660875, -0.079987, -0.107049);
	PhalanxIII3->normal.Set(0.978820, -0.036250, -0.201488);
	PhalanxIII3->length = 0.009303;
	PhalanxIII3->r1 = 0.003292;
	PhalanxIII3->r2 = 0.002230;
	PhalanxIII4->linkD = 1.000000;
	PhalanxIII4->linkN.Set(0.000000, 0.000000, 0.000000);
	PhalanxIII4->anchor.Set(0.628021, -0.070291, 0.139392);
	PhalanxIII4->normal.Set(0.968221, -0.052550, 0.244512);
	PhalanxIII4->length = 0.008529;
	PhalanxIII4->r1 = 0.003619;
	PhalanxIII4->r2 = 0.002884;
}
