///////////////////////////////////////////////////////////////////////////////
// Name               : Polynom.cpp
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : toby
// Created            : 28.01.2017
// Copyright          : (C) 2017 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
#include "Polynom.h"

Polynom::Polynom()
{
	c0 = c1 = c2 = c3 = 0.0;
}

Polynom::~Polynom()
{
}

void Polynom::Set4(double r0, double v0, double r1, double v1, double r2,
		double v2, double r3, double v3)
{
	const double T2 = r0 * r0;
	const double T4 = r0 * T2;
	const double T5 = r1 * r1;
	const double T3 = r1 * T5;
	const double T6 = r0 * T5;
	const double T7 = T2 * r1;
	const double T8 = r0 * T3;
	const double T9 = T4 * r1;
	const double T10 = T2 * T3;
	const double T11 = T4 * T5;
	const double T12 = r2 * r2;
	const double T14 = r2 * T12;
	const double T15 = r3 * r3;
	const double T13 = r3 * T15;
	const double T16 = (-T6 + T7) * T14;
	const double T17 = (T8 - T9) * T12;
	const double T18 = (-T10 + T11) * r2;
	const double T19 = (T5 - T2) * T14 + (-T3 + T4) * T12 + T10 - T11;
	const double T20 = -T5 + T2;
	const double T21 = T3 - T4;
	const double T22 = T2 * T14;
	const double T23 = T4 * T12;
	const double T24 = T5 * T14;
	const double T25 = T3 * T12;
	const double T26 = ((r1 - r0) * T12 + T20 * r2 + T6 - T7) * T13
			+ ((-r1 + r0) * T14 + T21 * r2 - T8 + T9) * T15 + T19 * r3 + T16
			+ T17 + T18;
	const double T27 = (-r1 + r0) * T14 + T21 * r2 - T8 + T9;
	const double T28 = r1 - r0;
	const double T29 = -T3 + T4;
	const double T30 = r0 * T14;
	const double T31 = T4 * r2;
	const double T32 = r1 * T14;
	const double T33 = T3 * r2;
	const double T34 = T28 * T12 + T20 * r2 + T6 - T7;
	const double T35 = -r1 + r0;
	const double T36 = T5 - T2;
	const double T37 = r0 * T12;
	const double T38 = T2 * r2;
	const double T39 = r1 * T12;
	const double T40 = T5 * r2;
	c0 = ((T16 + T17 + T18) * v3
			+ ((T6 - T7) * T13 + (-T8 + T9) * T15 + (T10 - T11) * r3) * v2
			+ ((-T37 + T38) * T13 + (T30 - T31) * T15 + (-T22 + T23) * r3) * v1
			+ ((T39 - T40) * T13 + (-T32 + T33) * T15 + (T24 - T25) * r3) * v0)
			/ T26;
	c1 = (T19 * v3 + (T20 * T13 + T21 * T15 - T10 + T11) * v2
			+ ((T12 - T2) * T13 + (-T14 + T4) * T15 + T22 - T23) * v1
			+ ((-T12 + T5) * T13 + (T14 - T3) * T15 - T24 + T25) * v0) / T26;
	c2 = (T27 * v3 + (T28 * T13 + T29 * r3 + T8 - T9) * v2
			+ ((-r2 + r0) * T13 + (T14 - T4) * r3 - T30 + T31) * v1
			+ ((r2 - r1) * T13 + (-T14 + T3) * r3 + T32 - T33) * v0) / T26;
	c3 = (T34 * v3 + (T35 * T15 + T36 * r3 - T6 + T7) * v2
			+ ((r2 - r0) * T15 + (-T12 + T2) * r3 + T37 - T38) * v1
			+ ((-r2 + r1) * T15 + (T12 - T5) * r3 - T39 + T40) * v0) / T26;
}

void Polynom::Set3(double r0, double v0, double r1, double v1, double r2,
		double v2)
{
	const double T2 = r0 * r0;
	const double T3 = r2 * r2;
	const double T4 = r1 * r1;
	const double T5 = r0 * T4;
	const double T6 = -T2 * r1;
	const double T7 = -T4 + T2;
	const double T8 = (r1 - r0) * T3 + T7 * r2 + T5 + T6;
	const double T9 = r1 - r0;
	c0 = ((T5 + T6) * v2 + ((-r0 * T3) + T2 * r2) * v1
			+ (r1 * T3 + (-T4 * r2)) * v0) / T8;
	c1 = (T7 * v2 + (T3 - T2) * v1 + (-T3 + T4) * v0) / T8;
	c2 = (T9 * v2 + (-r2 + r0) * v1 + (r2 - r1) * v0) / T8;
	c3 = 0.0;
}

void Polynom::Set2(double r0, double v0, double r1, double v1)
{
	const double T2 = r1 - r0;
	c0 = ((-r0 * v1) + r1 * v0) / T2;
	c1 = (v1 - v0) / T2;
	c2 = 0.0;
	c3 = 0.0;
}

void Polynom::Set1(double r0, double v0)
{
	c0 = v0;
	c1 = 0.0;
	c2 = 0.0;
	c3 = 0.0;
}

Polynom Polynom::Derive() const
{
	Polynom temp;
	temp.c3 = 0.0;
	temp.c2 = 3.0 * c3;
	temp.c1 = 2.0 * c2;
	temp.c0 = c1;
	return temp;
}

Polynom Polynom::Derive2() const
{
	Polynom temp;
	temp.c3 = 0.0;
	temp.c2 = 0.0;
	temp.c1 = 6.0 * c3;
	temp.c0 = 2.0 * c2;
	return temp;
}

Polynom Polynom::Derive3() const
{
	Polynom temp;
	temp.c3 = 0.0;
	temp.c2 = 0.0;
	temp.c1 = 0.0;
	temp.c0 = 6.0 * c3;
	return temp;
}

double Polynom::Evaluate(double r) const
{
	return ((c3 * r + c2) * r + c1) * r + c0;
}
