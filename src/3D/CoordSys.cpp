///////////////////////////////////////////////////////////////////////////////
// Name               : CoordSys.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 30.05.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "CoordSys.h"

CoordSys::CoordSys()
{
	side = rhs;
	ex.Set(1, 0, 0);
	ey.Set(0, 1, 0);
	ez.Set(0, 0, 1);
	lastSet = zWasSet;
}

CoordSys::~CoordSys()
{
}

void CoordSys::SetOrientation(orientation side)
{
	this->side = side;
}

void CoordSys::SetCenter(const Vector3& center)
{
	this->center = center;
}

void CoordSys::SetX(const Vector3& x)
{
	ex = x;
	switch(lastSet){
	case none:
		break;
	case xWasSet:
		break;
	case yWasSet:
		RecalculateZ();
		break;
	case zWasSet:
		RecalculateY();
		break;
	}
	lastSet = xWasSet;
}

void CoordSys::SetY(const Vector3& y)
{
	ey = y;
	switch(lastSet){
	case none:
		break;
	case xWasSet:
		RecalculateZ();
		break;
	case yWasSet:
		break;
	case zWasSet:
		RecalculateX();
		break;
	}
	lastSet = xWasSet;
}

void CoordSys::SetZ(const Vector3& z)
{
	this->ez = z;
	switch(lastSet){
	case none:
	case xWasSet:
		RecalculateY();
		break;
	case yWasSet:
		RecalculateX();
		break;
	case zWasSet:
		break;
	}
	lastSet = xWasSet;
}

void CoordSys::RecalculateX(void)
{
	if(side == rhs)
		ex = ey * ez;
	else
		ex = ez * ey;
	ex.Normalize();
}

void CoordSys::RecalculateY(void)
{
	if(side == rhs)
		ey = ez * ex;
	else
		ey = ex * ez;
	ey.Normalize();
}

void CoordSys::RecalculateZ(void)
{
	if(side == rhs)
		ez = ex * ey;
	else
		ez = ey * ex;
	ez.Normalize();
}

double CoordSys::GetLocalX(const Vector3& vec) const
{
	return ex.Dot(vec - center);
}

double CoordSys::GetLocalY(const Vector3& vec) const
{
	return ey.Dot(vec - center);
}

double CoordSys::GetLocalZ(const Vector3& vec) const
{
	return ez.Dot(vec - center);
}

Vector3 CoordSys::GetGlobal(double x, double y, double z) const
{
	return (center + ex * x + ey * y + ez * z);
}
