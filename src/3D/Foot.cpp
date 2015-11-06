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
	Tibia->anchorD = 1.434929e-02;
	Tibia->anchorN.Set(2.409810e-03, 7.117950e-03, 0.000000e+00);
	Tibia->link.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	Tibia->normal.Set(-3.986688e-03, 9.469216e-02, 9.954986e-01);
	Tibia->length = 7.785660e-02;
	Tibia->r1 = 2.528573e-02;
	Tibia->r2 = 1.439082e-02;
	Fibula->anchorD = 1.000000e+00;
	Fibula->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	Fibula->link.Set(-3.586078e-01, 5.567514e-01, -2.923908e+00);
	Fibula->normal.Set(-7.400355e-02, 5.670335e-02, 9.956446e-01);
	Fibula->length = 1.126709e-01;
	Fibula->r1 = 1.390181e-02;
	Fibula->r2 = 6.540670e-03;
	Talus->anchorD = -1.758680e-02;
	Talus->anchorN.Set(-1.678539e-01, 1.447653e-01, -1.444233e-02);
	Talus->link.Set(1.025412e-01, -1.096320e-01, -5.254726e-01);
	Talus->normal.Set(-3.640681e-01, 3.718389e-01, -8.539264e-01);
	Talus->length = 2.907283e-02;
	Talus->r1 = 2.293168e-02;
	Talus->r2 = 2.921517e-02;
	Talus2->anchorD = 1.000000e+00;
	Talus2->anchorN.Set(-7.504960e-17, 0.000000e+00, 0.000000e+00);
	Talus2->link.Set(7.937163e-01, -3.313649e-01, 2.543787e-01);
	Talus2->normal.Set(-5.521587e-01, 3.929601e-01, -7.353252e-01);
	Talus2->length = 2.673818e-02;
	Talus2->r1 = 1.951300e-02;
	Talus2->r2 = 1.908296e-02;
	Calcaneus->anchorD = 1.000000e+00;
	Calcaneus->anchorN.Set(-7.504960e-17, 0.000000e+00, 0.000000e+00);
	Calcaneus->link.Set(-4.479561e-01, 1.775767e-01, -3.464426e-01);
	Calcaneus->normal.Set(5.235092e-02, -5.575949e-01, -8.284608e-01);
	Calcaneus->length = 1.757925e-02;
	Calcaneus->r1 = 2.719753e-02;
	Calcaneus->r2 = 1.655032e-02;
	Cuboideum->anchorD = 2.842214e-01;
	Cuboideum->anchorN.Set(6.900854e-01, 1.707813e-01, -2.198491e-01);
	Cuboideum->link.Set(7.479115e-01, 5.134296e-01, -2.010654e-01);
	Cuboideum->normal.Set(-9.162252e-01, -1.046218e-01, -3.867631e-01);
	Cuboideum->length = 2.587615e-02;
	Cuboideum->r1 = 1.832360e-02;
	Cuboideum->r2 = 1.044529e-02;
	Naviculare->anchorD = 2.197903e-02;
	Naviculare->anchorN.Set(1.517817e+00, -2.650324e-01, -7.625222e-01);
	Naviculare->link.Set(1.246512e-01, -2.158979e-02, -7.819413e-02);
	Naviculare->normal.Set(0.000000e+00, 0.000000e+00, 1.000000e+00);
	Naviculare->length = 1.000000e-06;
	Naviculare->r1 = 2.172060e-02;
	Naviculare->r2 = 2.172060e-02;
	Cuneiforme1->anchorD = 4.903230e+03;
	Cuneiforme1->anchorN.Set(-8.089786e-02, -3.518374e-01, 0.000000e+00);
	Cuneiforme1->link.Set(9.397911e-01, 1.633931e-01, -2.529293e-01);
	Cuneiforme1->normal.Set(0.000000e+00, 0.000000e+00, 1.000000e+00);
	Cuneiforme1->length = 1.000000e-06;
	Cuneiforme1->r1 = 1.671639e-02;
	Cuneiforme1->r2 = 1.671639e-02;
	Cuneiforme2->anchorD = 3.492370e+03;
	Cuneiforme2->anchorN.Set(1.107193e-01, 4.113975e-02, 0.000000e+00);
	Cuneiforme2->link.Set(5.791583e-01, 1.402033e-01, -1.504275e-01);
	Cuneiforme2->normal.Set(0.000000e+00, 0.000000e+00, 1.000000e+00);
	Cuneiforme2->length = 1.000000e-06;
	Cuneiforme2->r1 = 1.874400e-02;
	Cuneiforme2->r2 = 1.874400e-02;
	Cuneiforme3->anchorD = 1.093400e+03;
	Cuneiforme3->anchorN.Set(-1.594247e-02, 4.016395e-01, 0.000000e+00);
	Cuneiforme3->link.Set(5.758787e-01, 3.794734e-01, -2.820634e-02);
	Cuneiforme3->normal.Set(0.000000e+00, 0.000000e+00, 1.000000e+00);
	Cuneiforme3->length = 1.000000e-06;
	Cuneiforme3->r1 = 1.731531e-02;
	Cuneiforme3->r2 = 1.731531e-02;
	Metatarsalis1->anchorD = -2.214621e-02;
	Metatarsalis1->anchorN.Set(-1.502243e-01, 3.937761e-01, 2.493561e-01);
	Metatarsalis1->link.Set(3.801477e-01, 4.279980e-01, -8.520469e-02);
	Metatarsalis1->normal.Set(8.803889e-01, 4.365245e-02, -4.722392e-01);
	Metatarsalis1->length = 6.486395e-02;
	Metatarsalis1->r1 = 8.659070e-03;
	Metatarsalis1->r2 = 5.561170e-03;
	Metatarsalis2->anchorD = -2.934240e-01;
	Metatarsalis2->anchorN.Set(1.106238e-02, 1.119256e-01, -5.648288e-02);
	Metatarsalis2->link.Set(5.693937e-01, 1.377339e-01, -1.699605e-01);
	Metatarsalis2->normal.Set(9.042660e-01, 6.199103e-02, -4.224455e-01);
	Metatarsalis2->length = 6.548109e-02;
	Metatarsalis2->r1 = 6.980050e-03;
	Metatarsalis2->r2 = 6.134930e-03;
	Metatarsalis3->anchorD = -1.065960e+03;
	Metatarsalis3->anchorN.Set(2.638584e-01, 5.292542e-02, 0.000000e+00);
	Metatarsalis3->link.Set(4.692285e-01, 1.414510e-01, -1.955231e-01);
	Metatarsalis3->normal.Set(9.191955e-01, 6.531734e-02, -3.883468e-01);
	Metatarsalis3->length = 6.329055e-02;
	Metatarsalis3->r1 = 7.826470e-03;
	Metatarsalis3->r2 = 5.726150e-03;
	Metatarsalis4->anchorD = 2.940780e+03;
	Metatarsalis4->anchorN.Set(1.513743e-01, 2.843310e-02, 0.000000e+00);
	Metatarsalis4->link.Set(5.320468e-01, 1.386333e-01, -2.504484e-01);
	Metatarsalis4->normal.Set(9.132546e-01, 6.663408e-02, -4.019028e-01);
	Metatarsalis4->length = 6.031073e-02;
	Metatarsalis4->r1 = 9.360350e-03;
	Metatarsalis4->r2 = 6.546760e-03;
	Metatarsalis5->anchorD = 2.207580e+03;
	Metatarsalis5->anchorN.Set(-1.714611e-01, -1.605735e-01, 0.000000e+00);
	Metatarsalis5->link.Set(5.873472e-01, 5.145225e-03, -2.274363e-01);
	Metatarsalis5->normal.Set(8.890901e-01, -1.694282e-01, -4.252211e-01);
	Metatarsalis5->length = 5.183725e-02;
	Metatarsalis5->r1 = 1.259428e-02;
	Metatarsalis5->r2 = 1.347212e-02;
	PhalanxI1->anchorD = 1.000000e+00;
	PhalanxI1->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxI1->link.Set(6.398317e-01, 1.192218e-01, -1.881530e-01);
	PhalanxI1->normal.Set(9.972455e-01, 6.342086e-02, -3.846147e-02);
	PhalanxI1->length = 1.986066e-02;
	PhalanxI1->r1 = 3.898840e-03;
	PhalanxI1->r2 = 3.512770e-03;
	PhalanxI2->anchorD = 1.000000e+00;
	PhalanxI2->anchorN.Set(0.000000e+00, 0.000000e+00, -2.004096e-15);
	PhalanxI2->link.Set(7.108407e-01, 5.175706e-02, -3.466714e-01);
	PhalanxI2->normal.Set(9.933196e-01, -2.191169e-02, -1.132966e-01);
	PhalanxI2->length = 2.039505e-02;
	PhalanxI2->r1 = 3.867440e-03;
	PhalanxI2->r2 = 3.474690e-03;
	PhalanxI3->anchorD = 1.000000e+00;
	PhalanxI3->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxI3->link.Set(6.135314e-01, 6.334347e-02, -1.531557e-01);
	PhalanxI3->normal.Set(9.853794e-01, -9.107150e-02, -1.439909e-01);
	PhalanxI3->length = 2.373608e-02;
	PhalanxI3->r1 = 4.674270e-03;
	PhalanxI3->r2 = 3.601210e-03;
	PhalanxI4->anchorD = 1.000000e+00;
	PhalanxI4->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxI4->link.Set(5.895279e-01, 3.480107e-03, -6.988362e-02);
	PhalanxI4->normal.Set(9.996018e-01, 0.000000e+00, 2.821821e-02);
	PhalanxI4->length = 3.040661e-02;
	PhalanxI4->r1 = 6.156570e-03;
	PhalanxI4->r2 = 4.604840e-03;
	PhalanxI5->anchorD = 1.000000e+00;
	PhalanxI5->anchorN.Set(0.000000e+00, -1.372431e-16, 0.000000e+00);
	PhalanxI5->link.Set(5.031540e-01, -5.400108e-02, -8.480985e-02);
	PhalanxI5->normal.Set(9.937057e-01, 1.022509e-01, 4.575633e-02);
	PhalanxI5->length = 3.720709e-02;
	PhalanxI5->r1 = 1.141603e-02;
	PhalanxI5->r2 = 9.727550e-03;
	PhalanxII1->anchorD = 1.000000e+00;
	PhalanxII1->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxII1->link.Set(8.059903e-01, -7.327159e-02, -2.198148e-01);
	PhalanxII1->normal.Set(9.525231e-01, -9.217997e-02, -2.901767e-01);
	PhalanxII1->length = 4.188654e-03;
	PhalanxII1->r1 = 3.134880e-03;
	PhalanxII1->r2 = 3.001830e-03;
	PhalanxII2->anchorD = 1.000000e+00;
	PhalanxII2->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxII2->link.Set(7.246418e-01, -8.138721e-02, -7.616048e-02);
	PhalanxII2->normal.Set(9.902288e-01, -1.074341e-01, -8.890973e-02);
	PhalanxII2->length = 8.685326e-03;
	PhalanxII2->r1 = 2.978500e-03;
	PhalanxII2->r2 = 2.490330e-03;
	PhalanxII3->anchorD = 1.000000e+00;
	PhalanxII3->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxII3->link.Set(7.093165e-01, -2.263885e-02, -1.493714e-01);
	PhalanxII3->normal.Set(9.958559e-01, -4.807102e-02, -7.720283e-02);
	PhalanxII3->length = 1.157704e-02;
	PhalanxII3->r1 = 3.668320e-03;
	PhalanxII3->r2 = 3.399320e-03;
	PhalanxII4->anchorD = 1.000000e+00;
	PhalanxII4->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxII4->link.Set(6.481846e-01, -8.296824e-02, 2.150579e-02);
	PhalanxII4->normal.Set(9.651721e-01, -8.763234e-02, 2.465022e-01);
	PhalanxII4->length = 1.416486e-02;
	PhalanxII4->r1 = 3.864670e-03;
	PhalanxII4->r2 = 3.624720e-03;
	PhalanxII5->anchorD = 1.000000e+00;
	PhalanxII5->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxII5->link.Set(3.819062e-01, 8.130476e-02, 8.772219e-02);
	PhalanxII5->normal.Set(9.326873e-01, 1.839207e-01, 3.102702e-01);
	PhalanxII5->length = 2.294358e-02;
	PhalanxII5->r1 = 7.400430e-03;
	PhalanxII5->r2 = 5.206770e-03;
	PhalanxIII1->anchorD = 1.000000e+00;
	PhalanxIII1->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxIII1->link.Set(7.086128e-01, -1.503116e-01, 0.000000e+00);
	PhalanxIII1->normal.Set(9.855248e-01, -1.667943e-01, 3.033942e-02);
	PhalanxIII1->length = 8.484342e-03;
	PhalanxIII1->r1 = 2.859360e-03;
	PhalanxIII1->r2 = 1.989590e-03;
	PhalanxIII2->anchorD = 1.000000e+00;
	PhalanxIII2->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxIII2->link.Set(7.273183e-01, -2.331465e-02, -6.930379e-02);
	PhalanxIII2->normal.Set(9.767224e-01, -1.490837e-01, -1.542314e-01);
	PhalanxIII2->length = 7.521881e-03;
	PhalanxIII2->r1 = 2.571180e-03;
	PhalanxIII2->r2 = 1.910790e-03;
	PhalanxIII3->anchorD = 1.000000e+00;
	PhalanxIII3->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxIII3->link.Set(6.608749e-01, -7.998671e-02, -1.070490e-01);
	PhalanxIII3->normal.Set(9.788199e-01, -3.625032e-02, -2.014884e-01);
	PhalanxIII3->length = 9.303366e-03;
	PhalanxIII3->r1 = 3.292450e-03;
	PhalanxIII3->r2 = 2.230420e-03;
	PhalanxIII4->anchorD = 1.000000e+00;
	PhalanxIII4->anchorN.Set(0.000000e+00, 0.000000e+00, 0.000000e+00);
	PhalanxIII4->link.Set(6.280207e-01, -7.029133e-02, 1.393916e-01);
	PhalanxIII4->normal.Set(9.682211e-01, -5.254979e-02, 2.445125e-01);
	PhalanxIII4->length = 8.529054e-03;
	PhalanxIII4->r1 = 3.619310e-03;
	PhalanxIII4->r2 = 2.884480e-03;
}
