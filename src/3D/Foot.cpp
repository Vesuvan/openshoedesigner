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

void Foot::AddToVolume(Volume* vol)
{
	BoneToVolume b2v(vol);
	Tibia->Accept(b2v);
}

void Foot::Setup(void)
{
	// Passe the parameters down to each bone.
//	Talus->roty = param->angle_1Y;
//	Talus->rotx = param->angle_1X;
//	Calcaneus->rotx = param->angle_2X;
//	PhalanxI1->roty = param->angle_3Y;
//	PhalanxI2->roty = param->angle_3Y;
//	PhalanxI3->roty = param->angle_3Y;
//	PhalanxI4->roty = param->angle_3Y;
//	PhalanxI5->roty = param->angle_3Y;

// Run the BoneSetup visitor to recalculate each single bone.
	BoneSetup set;
	set.parser.SetVariable(_T("L"), 28.67e-2);
	set.parser.SetVariable(_T("W"), 9.56e-2);
	Tibia->Accept(set);
}

bool Foot::LoadModel(wxTextInputStream* stream)
{
	if(!Tibia->Set(stream->ReadLine())) return false;
	if(!Fibula->Set(stream->ReadLine())) return false;
	if(!Talus->Set(stream->ReadLine())) return false;
	if(!Talus2->Set(stream->ReadLine())) return false;
	if(!Calcaneus->Set(stream->ReadLine())) return false;
	if(!Cuboideum->Set(stream->ReadLine())) return false;
	if(!Naviculare->Set(stream->ReadLine())) return false;
	if(!Cuneiforme1->Set(stream->ReadLine())) return false;
	if(!Cuneiforme2->Set(stream->ReadLine())) return false;
	if(!Cuneiforme3->Set(stream->ReadLine())) return false;
	if(!Metatarsalis1->Set(stream->ReadLine())) return false;
	if(!Metatarsalis2->Set(stream->ReadLine())) return false;
	if(!Metatarsalis3->Set(stream->ReadLine())) return false;
	if(!Metatarsalis4->Set(stream->ReadLine())) return false;
	if(!Metatarsalis5->Set(stream->ReadLine())) return false;
	if(!PhalanxI1->Set(stream->ReadLine())) return false;
	if(!PhalanxI2->Set(stream->ReadLine())) return false;
	if(!PhalanxI3->Set(stream->ReadLine())) return false;
	if(!PhalanxI4->Set(stream->ReadLine())) return false;
	if(!PhalanxI5->Set(stream->ReadLine())) return false;
	if(!PhalanxII1->Set(stream->ReadLine())) return false;
	if(!PhalanxII2->Set(stream->ReadLine())) return false;
	if(!PhalanxII3->Set(stream->ReadLine())) return false;
	if(!PhalanxII4->Set(stream->ReadLine())) return false;
	if(!PhalanxII5->Set(stream->ReadLine())) return false;
	if(!PhalanxIII1->Set(stream->ReadLine())) return false;
	if(!PhalanxIII2->Set(stream->ReadLine())) return false;
	if(!PhalanxIII3->Set(stream->ReadLine())) return false;
	if(!PhalanxIII4->Set(stream->ReadLine())) return false;

	return true;
}

void Foot::InitBones(void)
{
	Tibia->anchorD = 0.0143493;
	Tibia->anchorN.Set(0.00240981, 0.00711795, 0);
	Tibia->link.Set(0, 0, 0);
	Tibia->normal.Set(-0.00398669, 0.0946922, 0.995499);
	Tibia->length = 0.0778566;
	Tibia->r1 = 0.0252857;
	Tibia->r2 = 0.0143908;
	Tibia->s1 = 0.01;
	Tibia->s2 = 0.01;
	Fibula->anchorD = 1;
	Fibula->anchorN.Set(0, 0, 0);
	Fibula->link.Set(-0.358608, 0.556751, -2.92391);
	Fibula->normal.Set(-0.0740036, 0.0567033, 0.995645);
	Fibula->length = 0.112671;
	Fibula->r1 = 0.0139018;
	Fibula->r2 = 0.00654067;
	Fibula->s1 = 0.01;
	Fibula->s2 = 0.01;
	Talus->anchorD = -0.0175868;
	Talus->anchorN.Set(-0.167854, 0.144765, -0.0144423);
	Talus->link.Set(0.102541, -0.109632, -0.525473);
	Talus->normal.Set(-0.364068, 0.371839, -0.853926);
	Talus->length = 0.0290728;
	Talus->r1 = 0.0229317;
	Talus->r2 = 0.0292152;
	Talus->s1 = 0.01;
	Talus->s2 = 0.01;
	Talus2->anchorD = 1;
	Talus2->anchorN.Set(-7.50496e-17, 0, 0);
	Talus2->link.Set(0.793716, -0.331365, 0.254379);
	Talus2->normal.Set(-0.552159, 0.39296, -0.735325);
	Talus2->length = 0.0267382;
	Talus2->r1 = 0.019513;
	Talus2->r2 = 0.019083;
	Talus2->s1 = 0.01;
	Talus2->s2 = 0.01;
	Calcaneus->anchorD = 1;
	Calcaneus->anchorN.Set(-7.50496e-17, 0, 0);
	Calcaneus->link.Set(-0.447956, 0.177577, -0.346443);
	Calcaneus->normal.Set(0.0523509, -0.557595, -0.828461);
	Calcaneus->length = 0.0175793;
	Calcaneus->r1 = 0.0271975;
	Calcaneus->r2 = 0.0165503;
	Calcaneus->s1 = 0.01;
	Calcaneus->s2 = 0.01;
	Cuboideum->anchorD = 0.284221;
	Cuboideum->anchorN.Set(0.690085, 0.170781, -0.219849);
	Cuboideum->link.Set(0.747911, 0.51343, -0.201065);
	Cuboideum->normal.Set(-0.916225, -0.104622, -0.386763);
	Cuboideum->length = 0.0258761;
	Cuboideum->r1 = 0.0183236;
	Cuboideum->r2 = 0.0104453;
	Cuboideum->s1 = 0.01;
	Cuboideum->s2 = 0.01;
	Naviculare->anchorD = 0.021979;
	Naviculare->anchorN.Set(1.51782, -0.265032, -0.762522);
	Naviculare->link.Set(0.124651, -0.0215898, -0.0781941);
	Naviculare->normal.Set(0, 0, 1);
	Naviculare->length = 1e-06;
	Naviculare->r1 = 0.0217206;
	Naviculare->r2 = 0.0217206;
	Naviculare->s1 = 0.01;
	Naviculare->s2 = 0.01;
	Cuneiforme1->anchorD = 4903.23;
	Cuneiforme1->anchorN.Set(-0.0808979, -0.351837, 0);
	Cuneiforme1->link.Set(0.939791, 0.163393, -0.252929);
	Cuneiforme1->normal.Set(0, 0, 1);
	Cuneiforme1->length = 1e-06;
	Cuneiforme1->r1 = 0.0167164;
	Cuneiforme1->r2 = 0.0167164;
	Cuneiforme1->s1 = 0.01;
	Cuneiforme1->s2 = 0.01;
	Cuneiforme2->anchorD = 3492.37;
	Cuneiforme2->anchorN.Set(0.110719, 0.0411397, 0);
	Cuneiforme2->link.Set(0.579158, 0.140203, -0.150428);
	Cuneiforme2->normal.Set(0, 0, 1);
	Cuneiforme2->length = 1e-06;
	Cuneiforme2->r1 = 0.018744;
	Cuneiforme2->r2 = 0.018744;
	Cuneiforme2->s1 = 0.01;
	Cuneiforme2->s2 = 0.01;
	Cuneiforme3->anchorD = 1093.4;
	Cuneiforme3->anchorN.Set(-0.0159425, 0.401639, 0);
	Cuneiforme3->link.Set(0.575879, 0.379473, -0.0282063);
	Cuneiforme3->normal.Set(0, 0, 1);
	Cuneiforme3->length = 1e-06;
	Cuneiforme3->r1 = 0.0173153;
	Cuneiforme3->r2 = 0.0173153;
	Cuneiforme3->s1 = 0.01;
	Cuneiforme3->s2 = 0.01;
	Metatarsalis1->anchorD = -0.0221462;
	Metatarsalis1->anchorN.Set(-0.150224, 0.393776, 0.249356);
	Metatarsalis1->link.Set(0.380148, 0.427998, -0.0852047);
	Metatarsalis1->normal.Set(0.880389, 0.0436524, -0.472239);
	Metatarsalis1->length = 0.0648639;
	Metatarsalis1->r1 = 0.00865907;
	Metatarsalis1->r2 = 0.00556117;
	Metatarsalis1->s1 = 0.01;
	Metatarsalis1->s2 = 0.01;
	Metatarsalis2->anchorD = -0.293424;
	Metatarsalis2->anchorN.Set(0.0110624, 0.111926, -0.0564829);
	Metatarsalis2->link.Set(0.569394, 0.137734, -0.16996);
	Metatarsalis2->normal.Set(0.904266, 0.061991, -0.422445);
	Metatarsalis2->length = 0.0654811;
	Metatarsalis2->r1 = 0.00698005;
	Metatarsalis2->r2 = 0.00613493;
	Metatarsalis2->s1 = 0.01;
	Metatarsalis2->s2 = 0.01;
	Metatarsalis3->anchorD = -1065.96;
	Metatarsalis3->anchorN.Set(0.263858, 0.0529254, 0);
	Metatarsalis3->link.Set(0.469229, 0.141451, -0.195523);
	Metatarsalis3->normal.Set(0.919196, 0.0653173, -0.388347);
	Metatarsalis3->length = 0.0632905;
	Metatarsalis3->r1 = 0.00782647;
	Metatarsalis3->r2 = 0.00572615;
	Metatarsalis3->s1 = 0.01;
	Metatarsalis3->s2 = 0.01;
	Metatarsalis4->anchorD = 2940.78;
	Metatarsalis4->anchorN.Set(0.151374, 0.0284331, 0);
	Metatarsalis4->link.Set(0.532047, 0.138633, -0.250448);
	Metatarsalis4->normal.Set(0.913255, 0.0666341, -0.401903);
	Metatarsalis4->length = 0.0603107;
	Metatarsalis4->r1 = 0.00936035;
	Metatarsalis4->r2 = 0.00654676;
	Metatarsalis4->s1 = 0.01;
	Metatarsalis4->s2 = 0.01;
	Metatarsalis5->anchorD = 2207.58;
	Metatarsalis5->anchorN.Set(-0.171461, -0.160574, 0);
	Metatarsalis5->link.Set(0.587347, 0.00514523, -0.227436);
	Metatarsalis5->normal.Set(0.88909, -0.169428, -0.425221);
	Metatarsalis5->length = 0.0518372;
	Metatarsalis5->r1 = 0.0125943;
	Metatarsalis5->r2 = 0.0134721;
	Metatarsalis5->s1 = 0.01;
	Metatarsalis5->s2 = 0.01;
	PhalanxI1->anchorD = 1;
	PhalanxI1->anchorN.Set(0, 0, 0);
	PhalanxI1->link.Set(0.639832, 0.119222, -0.188153);
	PhalanxI1->normal.Set(0.997245, 0.0634209, -0.0384615);
	PhalanxI1->length = 0.0198607;
	PhalanxI1->r1 = 0.00389884;
	PhalanxI1->r2 = 0.00351277;
	PhalanxI1->s1 = 0.01;
	PhalanxI1->s2 = 0.01;
	PhalanxI2->anchorD = 1;
	PhalanxI2->anchorN.Set(0, 0, -2.0041e-15);
	PhalanxI2->link.Set(0.710841, 0.0517571, -0.346671);
	PhalanxI2->normal.Set(0.99332, -0.0219117, -0.113297);
	PhalanxI2->length = 0.020395;
	PhalanxI2->r1 = 0.00386744;
	PhalanxI2->r2 = 0.00347469;
	PhalanxI2->s1 = 0.01;
	PhalanxI2->s2 = 0.01;
	PhalanxI3->anchorD = 1;
	PhalanxI3->anchorN.Set(0, 0, 0);
	PhalanxI3->link.Set(0.613531, 0.0633435, -0.153156);
	PhalanxI3->normal.Set(0.985379, -0.0910715, -0.143991);
	PhalanxI3->length = 0.0237361;
	PhalanxI3->r1 = 0.00467427;
	PhalanxI3->r2 = 0.00360121;
	PhalanxI3->s1 = 0.01;
	PhalanxI3->s2 = 0.01;
	PhalanxI4->anchorD = 1;
	PhalanxI4->anchorN.Set(0, 0, 0);
	PhalanxI4->link.Set(0.589528, 0.00348011, -0.0698836);
	PhalanxI4->normal.Set(0.999602, 0, 0.0282182);
	PhalanxI4->length = 0.0304066;
	PhalanxI4->r1 = 0.00615657;
	PhalanxI4->r2 = 0.00460484;
	PhalanxI4->s1 = 0.01;
	PhalanxI4->s2 = 0.01;
	PhalanxI5->anchorD = 1;
	PhalanxI5->anchorN.Set(0, -1.37243e-16, 0);
	PhalanxI5->link.Set(0.503154, -0.0540011, -0.0848098);
	PhalanxI5->normal.Set(0.993706, 0.102251, 0.0457563);
	PhalanxI5->length = 0.0372071;
	PhalanxI5->r1 = 0.011416;
	PhalanxI5->r2 = 0.00972755;
	PhalanxI5->s1 = 0.01;
	PhalanxI5->s2 = 0.01;
	PhalanxII1->anchorD = 1;
	PhalanxII1->anchorN.Set(0, 0, 0);
	PhalanxII1->link.Set(0.80599, -0.0732716, -0.219815);
	PhalanxII1->normal.Set(0.952523, -0.09218, -0.290177);
	PhalanxII1->length = 0.00418865;
	PhalanxII1->r1 = 0.00313488;
	PhalanxII1->r2 = 0.00300183;
	PhalanxII1->s1 = 0.01;
	PhalanxII1->s2 = 0.01;
	PhalanxII2->anchorD = 1;
	PhalanxII2->anchorN.Set(0, 0, 0);
	PhalanxII2->link.Set(0.724642, -0.0813872, -0.0761605);
	PhalanxII2->normal.Set(0.990229, -0.107434, -0.0889097);
	PhalanxII2->length = 0.00868533;
	PhalanxII2->r1 = 0.0029785;
	PhalanxII2->r2 = 0.00249033;
	PhalanxII2->s1 = 0.01;
	PhalanxII2->s2 = 0.01;
	PhalanxII3->anchorD = 1;
	PhalanxII3->anchorN.Set(0, 0, 0);
	PhalanxII3->link.Set(0.709316, -0.0226388, -0.149371);
	PhalanxII3->normal.Set(0.995856, -0.048071, -0.0772028);
	PhalanxII3->length = 0.011577;
	PhalanxII3->r1 = 0.00366832;
	PhalanxII3->r2 = 0.00339932;
	PhalanxII3->s1 = 0.01;
	PhalanxII3->s2 = 0.01;
	PhalanxII4->anchorD = 1;
	PhalanxII4->anchorN.Set(0, 0, 0);
	PhalanxII4->link.Set(0.648185, -0.0829682, 0.0215058);
	PhalanxII4->normal.Set(0.965172, -0.0876323, 0.246502);
	PhalanxII4->length = 0.0141649;
	PhalanxII4->r1 = 0.00386467;
	PhalanxII4->r2 = 0.00362472;
	PhalanxII4->s1 = 0.01;
	PhalanxII4->s2 = 0.01;
	PhalanxII5->anchorD = 1;
	PhalanxII5->anchorN.Set(0, 0, 0);
	PhalanxII5->link.Set(0.381906, 0.0813048, 0.0877222);
	PhalanxII5->normal.Set(0.932687, 0.183921, 0.31027);
	PhalanxII5->length = 0.0229436;
	PhalanxII5->r1 = 0.00740043;
	PhalanxII5->r2 = 0.00520677;
	PhalanxII5->s1 = 0.01;
	PhalanxII5->s2 = 0.01;
	PhalanxIII1->anchorD = 1;
	PhalanxIII1->anchorN.Set(0, 0, 0);
	PhalanxIII1->link.Set(0.708613, -0.150312, 0);
	PhalanxIII1->normal.Set(0.985525, -0.166794, 0.0303394);
	PhalanxIII1->length = 0.00848434;
	PhalanxIII1->r1 = 0.00285936;
	PhalanxIII1->r2 = 0.00198959;
	PhalanxIII1->s1 = 0.01;
	PhalanxIII1->s2 = 0.01;
	PhalanxIII2->anchorD = 1;
	PhalanxIII2->anchorN.Set(0, 0, 0);
	PhalanxIII2->link.Set(0.727318, -0.0233147, -0.0693038);
	PhalanxIII2->normal.Set(0.976722, -0.149084, -0.154231);
	PhalanxIII2->length = 0.00752188;
	PhalanxIII2->r1 = 0.00257118;
	PhalanxIII2->r2 = 0.00191079;
	PhalanxIII2->s1 = 0.01;
	PhalanxIII2->s2 = 0.01;
	PhalanxIII3->anchorD = 1;
	PhalanxIII3->anchorN.Set(0, 0, 0);
	PhalanxIII3->link.Set(0.660875, -0.0799867, -0.107049);
	PhalanxIII3->normal.Set(0.97882, -0.0362503, -0.201488);
	PhalanxIII3->length = 0.00930337;
	PhalanxIII3->r1 = 0.00329245;
	PhalanxIII3->r2 = 0.00223042;
	PhalanxIII3->s1 = 0.01;
	PhalanxIII3->s2 = 0.01;
	PhalanxIII4->anchorD = 1;
	PhalanxIII4->anchorN.Set(0, 0, 0);
	PhalanxIII4->link.Set(0.628021, -0.0702913, 0.139392);
	PhalanxIII4->normal.Set(0.968221, -0.0525498, 0.244512);
	PhalanxIII4->length = 0.00852905;
	PhalanxIII4->r1 = 0.00361931;
	PhalanxIII4->r2 = 0.00288448;
	PhalanxIII4->s1 = 0.01;
	PhalanxIII4->s2 = 0.01;
}
