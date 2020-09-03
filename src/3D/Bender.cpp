///////////////////////////////////////////////////////////////////////////////
// Name               : Bender.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 14.07.2020
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

#include "Bender.h"

void Bender::Calculate()
{
	inv0 = from0.Inverse();
	inv1 = from1.Inverse();
	diff0 = to0 * inv0;
	diff1 = to1 * inv1;

	auto rotf = RotationalAxis(from0, from1);
	auto rott = RotationalAxis(to0, to1);

	parallelf = rotf.parallel;
	parallelt = rott.parallel;

	if(parallelf){
		Lfrom = rotf.R;
	}else{
		nullf0.SetOrigin(rotf.p);
		nullf0.SetEz(rotf.n);
		nullf0.SetEy(from0.GetEx().Normal());
		nullf0.CalculateEx();
		nullf0inv = nullf0.Inverse();
		nullf1.SetOrigin(rotf.p);
		nullf1.SetEz(rotf.n);
		nullf1.SetEy(from1.GetEx().Normal());
		nullf1.CalculateEx();
		nullf1inv = nullf1.Inverse();
		Vector3 h = nullf0inv.Transform(from1.GetOrigin());
		Lfrom = atan2(h.y, h.x);
	}
	Lfrom = fmax(Lfrom, 1e-9);
	if(parallelt){
		Lto = rott.R;
	}else{
		nullt0.SetOrigin(rott.p);
		nullt0.SetEz(rott.n);
		nullt0.SetEy(to0.GetEx().Normal());
		nullt0.CalculateEx();
		nullt0inv = nullt0.Inverse();
		nullt1.SetOrigin(rott.p);
		nullt1.SetEz(rott.n);
		nullt1.SetEy(to1.GetEx().Normal());
		nullt1.CalculateEx();
		nullt1inv = nullt1.Inverse();
		Vector3 h = nullt0inv.Transform(to1.GetOrigin());
		Lto = atan2(h.y, h.x);
	}
	Lto = fmax(Lto, 1e-9);
}

Vector3 Bender::operator ()(const Vector3& v) const
{
	double s0 = inv0.GlobalX(v.x, v.y, v.z);
	double s1 = inv1.GlobalX(v.x, v.y, v.z);

	if(s0 <= 0.0) return diff0.Transform(v);
	if(s1 >= 0.0) return diff1.Transform(v);

	Vector3 b0;
	Vector3 b1;
	double a0;
	double a1;
	if(parallelf){
		Vector3 t0 = inv0.Transform(v);
		Vector3 t1 = inv1.Transform(v);
		a0 = t0.x;
		a1 = -t1.x;
		b0 = Vector3(0, t0.y, t0.z);
		b1 = Vector3(0, t1.y, t1.z);
	}else{
		Vector3 p0 = nullf0inv.Transform(v);
		Vector3 p1 = nullf1inv.Transform(v);
		double r0 = sqrt(p0.x * p0.x + p0.y * p0.y);
		double r1 = sqrt(p1.x * p1.x + p1.y * p1.y);
		a0 = atan2(p0.y, p0.x);
		a1 = -atan2(p1.y, p1.x);

		p0.x = (p0.x >= 0)? (r0) : (-r0);
		p0.y = 0;
		p1.x = (p1.x >= 0)? (r1) : (-r1);
		p1.y = 0;
		Vector3 h0 = nullf0.Transform(p0);
		Vector3 h1 = nullf1.Transform(p1);
		b0 = inv0.Transform(h0);
		b1 = inv1.Transform(h1);
	}

	a0 /= Lfrom;
	a1 /= Lfrom;

	if(parallelt){
		Vector3 v0 = to0.Transform(b0);
		Vector3 v1 = to1.Transform(b1);

		return (v0 * a1 + v1 * a0);

	}else{
		Vector3 h0 = to0.Transform(b0);
		Vector3 h1 = to1.Transform(b1);

		Vector3 c0 = nullt0inv.Transform(h0);
		Vector3 c1 = nullt1inv.Transform(h1);

		double r0 = c0.x;
		double r1 = c1.x;
		c0.x = cos(a0 * Lto) * r0;
		c0.y = sin(a0 * Lto) * r0;
		c1.x = cos(a1 * Lto) * r1;
		c1.y = -sin(a1 * Lto) * r1;

		Vector3 v0 = nullt0.Transform(c0);
		Vector3 v1 = nullt1.Transform(c1);

		return (v0 * a1 + v1 * a0);
	}
}

Bender::Rotation Bender::RotationalAxis(const AffineTransformMatrix& a,
		const AffineTransformMatrix& b)
{
	Vector3 na = a.GetEx();
	Vector3 nb = b.GetEx();
	na.Normalize();
	nb.Normalize();
	Vector3 n = na * nb;

	double da = na.Dot(a.GetOrigin());
	double db = nb.Dot(b.GetOrigin());

	Rotation rot;
	if(n.Abs2() < 1e-9){
		rot.parallel = true;
		rot.R = db - da;
		return rot;
	}
	n.Normalize();
	rot.parallel = false;
	rot.n = n;
	rot.R = asin(n.Abs());

	if(fabs(n.x) >= fabs(n.y) && fabs(n.x) >= fabs(n.z)){
		const double den = na.z * nb.y - na.y * nb.z;
		rot.p = Vector3(0.0, (db * na.z - da * nb.z) / den,
				(-db * na.y + da * nb.y) / den);
	}
	if(fabs(n.y) >= fabs(n.z) && fabs(n.y) >= fabs(n.x)){
		const double den = na.z * nb.x - na.x * nb.z;
		rot.p = Vector3((db * na.z - da * nb.z) / den, 0.0,
				(-db * na.x + da * nb.x) / den);
	}
	if(fabs(n.z) >= fabs(n.x) && fabs(n.z) >= fabs(n.y)){
		const double den = na.y * nb.x - na.x * nb.y;
		rot.p = Vector3((db * na.y - da * nb.y) / den,
				(-db * na.x + da * nb.x) / den, 0.0);
	}

	return rot;
}
