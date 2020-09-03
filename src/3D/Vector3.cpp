///////////////////////////////////////////////////////////////////////////////
// Name               : Vector3.cpp
// Purpose            : A 3D vector class with support functions.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 28.01.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Vector3.h"

#include <sstream>
#include <regex>

Vector3::Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
{
}

Vector3::Vector3(const std::string & string)
{
	this->FromString(string);
}

std::string Vector3::ToString(void) const
{
	std::ostringstream os;
	os << "{x:" << x << ",y:" << y << ",z:" << z << '}';
	return os.str();
}

bool Vector3::FromString(const std::string & string)
{
	//TODO: Move the regex into a global static variable when it is really used a lot.
	std::regex e(
			"^\\s*\\{\\s*x\\s*:\\s*([eEfF0-9\\.\\-\\+]+)\\s*,\\s*y\\s*:\\s*([eEfF0-9\\.\\-\\+]+)\\s*,\\s*z\\s*:\\s*([eEfF0-9\\.\\-\\+]+)\\s*\\}\\s*$");
	std::smatch sm;
	std::regex_match(string.begin(), string.end(), sm, e);

	if(sm.size() != 3) return false;

	x = std::stof(sm[0]);
	y = std::stof(sm[1]);
	z = std::stof(sm[2]);
	return true;
}

void Vector3::Zero(void)
{
	x = y = z = 0.0;
}

void Vector3::Normalize(void)
{
	float d = Abs();
	if(d > 0){
		x /= d;
		y /= d;
		z /= d;
	}
}

Vector3 Vector3::Normal(void) const
{
	float d = Abs();
	if(d > 0){
		return Vector3(x / d, y / d, z / d);
	}else{
		return Vector3(x, y, z);
	}
}
bool Vector3::operator ==(const Vector3& b) const
{
	constexpr double epsilon = 1e-5;
	constexpr double epsilon2 = epsilon * epsilon;
	return (((this->x - b.x) * (this->x - b.x)
			+ (this->y - b.y) * (this->y - b.y)
			+ (this->z - b.z) * (this->z - b.z)) <= epsilon2);
}

Vector3 Vector3::Orthogonal(void) const
{
	Vector3 temp;
	const float ax = fabs(x);
	const float ay = fabs(y);
	const float az = fabs(z);
	if(ax <= ay && ax <= az) temp.Set(x, z, y);
	if(ay <= az && ay <= ax) temp.Set(z, y, x);
	if(az <= ax && az <= ay) temp.Set(y, x, z);
	temp *= (*this);
	return temp.Normal();
}

