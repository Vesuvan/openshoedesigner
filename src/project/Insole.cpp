///////////////////////////////////////////////////////////////////////////////
// Name               : Insole.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.09.2020
// Copyright          : (C) 2020 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Insole.h"

#include "foot/FootMeasurements.h"
#include "Shoe.h"

#include "../3D/OpenGL.h"

void Insole::Modify(bool modify)
{
	this->modified = modify;
}

bool Insole::IsModified(void) const
{
	return modified;
}

void Insole::Point::SetNormal(const Point& p0, const Point& p1)
{
	n = (p1.p - p0.p).Normal();
}
void Insole::Line::Setup(const Point& p0, const Point& p1, double f0, double f1)
{
	const double d = (p1.p - p0.p).Abs();
	x = Polynom::ByBezier(p0.p.x, p0.p.x + d * f0 * p0.n.x,
			p1.p.x - d * f1 * p1.n.x, p1.p.x);
	y = Polynom::ByBezier(p0.p.y, p0.p.y + d * f0 * p0.n.y,
			p1.p.y - d * f1 * p1.n.y, p1.p.y);
	z = Polynom::ByBezier(p0.p.z, p0.p.z + d * f0 * p0.n.z,
			p1.p.z - d * f1 * p1.n.z, p1.p.z);
}

void Insole::Line::Paint(void) const
{
	glBegin(GL_LINE_STRIP);
	for(double r = 0.0; r < 1.0001; r += 0.01){
		glVertex3d(x(r), y(r), z(r));
	}
	glEnd();
}

void Insole::Construct(const Shoe& shoe, const FootMeasurements& measurements)
{
	Point A, B, C, D, E, F, G, H, J, K, L, N, Z;

	J.p.Set(0, 0, 0);
	A.p = J.p - Vector3(measurements.footLength.value / 6.0, 0, 0);
	C.p = A.p + Vector3(measurements.footLength.value * 0.62, 0, 0);
	D.p = A.p + Vector3(measurements.footLength.value, 0, 0);
	B.p = A.p
			+ Vector3(measurements.footLength.value + shoe.extraLength.value, 0,
					0);
	{
		const double s = sin(shoe.ballMeasurementAngle.value);
		const double c = cos(shoe.ballMeasurementAngle.value);

		E.p = C.p
				+ Vector3(s * measurements.ballWidth.value / 2,
						c * measurements.ballWidth.value / 2, 0);
		F.p = C.p
				- Vector3(s * measurements.ballWidth.value / 2 * 1.24,
						c * measurements.ballWidth.value / 2 * 1.24, 0);
	}
	{
		const double s = sin(shoe.heelDirectionAngle.value);
		const double c = cos(shoe.heelDirectionAngle.value);
		K.p = J.p
				+ Vector3(s * measurements.heelWidth.value / 2,
						c * measurements.heelWidth.value / 2, 0);
		L.p = J.p
				- Vector3(s * measurements.heelWidth.value / 2,
						c * measurements.heelWidth.value / 2, 0);
		N.p.x = A.p.x * c;
		N.p.y = -A.p.x * s;
		N.p.z = A.p.z;
	}
	{
		const double s = sin(shoe.bigToeAngle.value);
		const double c = cos(shoe.bigToeAngle.value);
		const double r = (D.p.x - E.p.x) * c;
		G.p = E.p + Vector3(r, -s * r, 0);
	}
	{
		const double s = sin(shoe.littleToeAngle.value);
		const double c = cos(shoe.littleToeAngle.value);
		const double r = (D.p.x - F.p.x) * c;
		H.p = F.p + Vector3(r, s * r, 0);
	}
	Z.p = H.p - Vector3(measurements.footLength.value / 5, 0, 0);

	// Normals
	N.SetNormal(L, K);
	{
		const double s = sin(shoe.heelDirectionAngle.value);
		const double c = cos(shoe.heelDirectionAngle.value);
		K.n.Set(c, -s, 0);
		L.n.Set(c, -s, 0);
	}
	E.SetNormal(J, E);
	F.SetNormal(J, H);
	G.SetNormal(E, B);
	Z.SetNormal(L, C);
	B.SetNormal(G, H);

	inside.clear();
	Line temp;
	temp.Setup(N, K);
	inside.push_back(temp);
	temp.Setup(K, E, 0.7, 0.39);
	inside.push_back(temp);
	temp.Setup(E, G, 0.3, 0.2);
	inside.push_back(temp);
	temp.Setup(G, B, 0.39, 0.39);
	inside.push_back(temp);

	N.n *= -1;
	B.n *= -1;

	outside.clear();
	temp.Setup(N, L);
	outside.push_back(temp);
	temp.Setup(L, F, 0.3, 0.39);
	outside.push_back(temp);
	temp.Setup(F, Z, 0.39, 0.2);
	outside.push_back(temp);
	temp.Setup(Z, B, 0.4, 0.3);
	outside.push_back(temp);
}

void Insole::Paint(void) const
{
	for(auto & line : inside)
		line.Paint();
	for(auto & line : outside)
		line.Paint();
}

