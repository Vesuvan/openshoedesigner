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

#include <cfloat>
#include <iostream>
#include "foot/FootMeasurements.h"
#include "Shoe.h"
#include "../3D/Bender.h"

#include "../3D/OpenGL.h"

void Insole::Modify(bool modify)
{
	this->modified = modify;
}

bool Insole::IsModified(void) const
{
	return modified;
}

void Insole::Transform(std::function <Vector3(Vector3)> func)
{
	inside.ApplyTransformation(func);
	inside.CalculateNormals();
	outside.ApplyTransformation(func);
	outside.CalculateNormals();
	A.Transform(func);
	B.Transform(func);
	C.Transform(func);
	D.Transform(func);
	E.Transform(func);
	F.Transform(func);
	G.Transform(func);
	H.Transform(func);
	J.Transform(func);
	K.Transform(func);
	L.Transform(func);
	N.Transform(func);
	Z.Transform(func);
}

void Insole::Mirror(bool isleft)
{
	if(leftside == isleft) return;
	AffineTransformMatrix m;
	m.ScaleGlobal(1, -1, 1);
	Transform(m);
	leftside = isleft;
}
void Insole::Point::SetNormal(const Point& p0, const Point& p1)
{
	n = (p1.p - p0.p).Normal();
}

void Insole::Point::Transform(std::function <Vector3(Vector3)> func)
{
	Vector3 h = p + n;
	p = func(p);
	h = func(h);
	n = (h - p).Normal();
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
	for(double r = -0.0; r < 1.0001; r += 0.01){
		glVertex3d(x(r), y(r), z(r));
	}
	glEnd();
}

void Insole::Paint(void) const
{
//	for(auto & line : lines)
//		line.Paint();

	size_t N = inside.Size();
	if(outside.Size() < N) N = outside.Size();

	glBegin(GL_QUAD_STRIP);
	for(size_t n = 0; n < N; ++n){
		if(leftside){
			glNormal3f(inside.Normal(n).x, inside.Normal(n).y,
					inside.Normal(n).z);
			glVertex3f(inside[n].x, inside[n].y, inside[n].z);
			glNormal3f(outside.Normal(n).x, outside.Normal(n).y,
					outside.Normal(n).z);
			glVertex3f(outside[n].x, outside[n].y, outside[n].z);
		}else{
			glNormal3f(outside.Normal(n).x, outside.Normal(n).y,
					outside.Normal(n).z);
			glVertex3f(outside[n].x, outside[n].y, outside[n].z);
			glNormal3f(inside.Normal(n).x, inside.Normal(n).y,
					inside.Normal(n).z);
			glVertex3f(inside[n].x, inside[n].y, inside[n].z);
		}
	}
	glEnd();
	inside.Paint(true);
	outside.Paint(true);
}

void Insole::FinishConstruction(const double dx)
{
	double x0 = DBL_MAX;
	double x1 = -DBL_MAX;

	for(auto & line : lines){
		const double r = line.y.FindZero(0.5);
		if(r < 0.0 || r > 1.0) continue;
		const double x = line.x(r);
		if(x < x0) x0 = x;
		if(x > x1) x1 = x;
	}

	inside.Clear();
	outside.Clear();

	inside.method = Polygon3::CalculateNormal::InPlayZX;
	outside.method = Polygon3::CalculateNormal::InPlayZX;

	inside.InsertPoint(x0, 0, 0);
	outside.InsertPoint(x0, 0, 0);
	for(double x = x0; x < x1; x += dx){
		double y0 = DBL_MAX;
		double y1 = -DBL_MAX;
		for(auto & line : lines){
			const double r = (line.x - x).FindZero(0.5);
			if(r < 0.0 || r > 1.0) continue;
			const double y = line.y(r);
			if(y < y0) y0 = y;
			if(y > y1) y1 = y;
		}
		inside.InsertPoint(x, y0, 0);
		outside.InsertPoint(x, y1, 0);
	}
	inside.InsertPoint(x1, 0, 0);
	outside.InsertPoint(x1, 0, 0);
}

void Insole::Shape(const Shoe& shoe, double legLengthDifference)
{
	// Calculate gamma0 and gamma1
	const double alpha0 = shoe.heelPitch.value;
	const double alpha1 = shoe.toeSpring.value;
	const double s0 = F.p.x - J.p.x;
	const double s1 = Z.p.x - F.p.x;
	const double dt = shoe.heelHeight.value - shoe.ballHeight.value
			+ legLengthDifference;

	const size_t NSample = 100;
	Polynom gammasample = Polynom::ByValue(0, 0, 100,
	M_PI * 100 / 180 - alpha0);
	double optg0 = 0;
	double optg1 = -1;
	double optd0 = 0;
	double optd1 = -1;
	for(size_t n = 0; n < NSample; ++n){
		const double gamma0 = gammasample(n);
		const double gamma1 = alpha0 + alpha1 + gamma0;
		double d0 = 0.0;
		if(fabs(gamma0) < 1e-9){
			d0 = s0 * sin(alpha0);
		}else{
			d0 = s0 * (cos(alpha0) - cos(gamma0 + alpha0)) / gamma0;
		}
		double d1 = 0.0;
		if(fabs(gamma1) < 1e-9){
			d1 = s1 * sin(-alpha1);
		}else{
			d1 = s1 * (cos(alpha1) - cos(gamma0 + alpha0)) / gamma1;
		}
		const double d = d0 + d1;
		optg1 = gamma0;
		optd1 = d;
		if(d > dt || n + 1 == NSample){
			break;
		}
		optg0 = gamma0;
		optd0 = d;
	}
	Polynom opt = Polynom::ByValue(optg0, optd0, optg1, optd1) - dt;
	const double gamma0 = opt.FindZero((optg0 + optg1) / 2);
	const double gamma1 = alpha0 + alpha1 + gamma0;

	{
		// Bend toes
		Bender b;
		b.from0.SetOrigin(Vector3(F.p.x, 0, F.p.z));
		b.from1.SetOrigin(Vector3(Z.p.x, 0, Z.p.z));
		b.to0 = b.from0;
		b.to1 = b.to0;
		b.to1 *= AffineTransformMatrix::RotationXYZ(0, -gamma1 / 2, 0);
		double L = s1;
		if(fabs(gamma1) > 1e-9){
			L = 2 * s1 / gamma1 * sin(gamma1 / 2.0);
		}
		b.to1.TranslateLocal(L, 0, 0);
		b.to1 *= AffineTransformMatrix::RotationXYZ(0, -gamma1 / 2, 0);
		b.Calculate();
		Transform(b);
	}
	{
		// Bend heel and mid-section
		Bender b;
		b.from0.SetOrigin(Vector3(J.p.x, 0, J.p.z));
		b.from1.SetOrigin(Vector3(F.p.x, 0, F.p.z));
		b.to0 = b.from0;
		b.to0 *= AffineTransformMatrix::RotationXYZ(0, alpha0, 0);
		b.to1 = b.to0;
		b.to1 *= AffineTransformMatrix::RotationXYZ(0, gamma0 / 2, 0);
		double L = s1;
		if(fabs(gamma0) > 1e-9){
			L = 2 * s0 / gamma0 * sin(gamma0 / 2.0);
		}
		b.to1.TranslateLocal(L, 0, 0);
		b.to1 *= AffineTransformMatrix::RotationXYZ(0, gamma0 / 2, 0);
		b.Calculate();
		Transform(b);
	}
	{
		// Set heel/platform height
		AffineTransformMatrix m;
		m.TranslateGlobal(0, 0, shoe.heelHeight.value + legLengthDifference);
		Transform(m);

	}
}

void Insole::Construct(const Shoe& shoe, const FootMeasurements& measurements)
{
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
	N.SetNormal(K, L);
	{
		const double s = sin(shoe.heelDirectionAngle.value);
		const double c = cos(shoe.heelDirectionAngle.value);
		K.n.Set(-c, s, 0);
		L.n.Set(c, -s, 0);
	}
	E.SetNormal(E, J);
	F.SetNormal(J, H);
	G.SetNormal(B, E);
	Z.SetNormal(L, C);
	B.SetNormal(H, G);

	lines.clear();
	Line temp;
	temp.Setup(F, Z, 0.39, 0.2);
	lines.push_back(temp);
	temp.Setup(Z, B, 0.4, 0.3);
	lines.push_back(temp);
	temp.Setup(B, G, 0.39, 0.39);
	lines.push_back(temp);
	temp.Setup(G, E, 0.2, 0.3);
	lines.push_back(temp);
	temp.Setup(E, K, 0.39, 0.7);
	lines.push_back(temp);
	temp.Setup(K, N);
	lines.push_back(temp);
	temp.Setup(N, L);
	lines.push_back(temp);
	temp.Setup(L, F, 0.3, 0.39);
	lines.push_back(temp);

	FinishConstruction(measurements.footLength.value / 100);
}

