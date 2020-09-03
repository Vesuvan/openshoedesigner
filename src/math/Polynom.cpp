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

#include <cmath>
#include <stdexcept>

Polynom::Polynom(size_t N)
{
	c.assign(N, 0.0);
}

Polynom::Polynom(const std::vector <double> &vec)
		: c(vec)
{
}

// All formulas are calculated with the AXIOM computer algebra system.

Polynom Polynom::ByValue(double r0, double v0)
{
	Polynom temp;
	(void) (r0); // Suppresses "Unused parameter" warning.
	temp.c.assign(1, v0);
	return temp;
}

Polynom Polynom::ByValue(double r0, double v0, double r1, double v1)
{
	Polynom temp;
	const double T2 = r1 - r0;
	if(fabs(T2) < 1e-9) throw(std::domain_error(
	__FILE__ ": Polynom(r0,v0,r1,v1) - Both positions have the same r."));
	temp.c.resize(2);
	temp.c[1] = ((-r0 * v1) + r1 * v0) / T2;
	temp.c[0] = (v1 - v0) / T2;
	return temp;
}

Polynom Polynom::ByValue(double r0, double v0, double r1, double v1, double r2,
		double v2)
{
	Polynom temp;
	const double T2 = r0 * r0;
	const double T3 = r2 * r2;
	const double T4 = r1 * r1;
	const double T5 = r0 * T4;
	const double T6 = -T2 * r1;
	const double T7 = -T4 + T2;
	const double T8 = (r1 - r0) * T3 + T7 * r2 + T5 + T6;
	if(fabs(T8) < 1e-9) throw(std::domain_error(
	__FILE__ ": Polynom(r0,v0,r1,v1,r2,v2) - Some positions have the same r."));
	const double T9 = r1 - r0;
	temp.c.resize(3);
	temp.c[2] = ((T5 + T6) * v2 + ((-r0 * T3) + T2 * r2) * v1
			+ (r1 * T3 + (-T4 * r2)) * v0) / T8;
	temp.c[1] = (T7 * v2 + (T3 - T2) * v1 + (-T3 + T4) * v0) / T8;
	temp.c[0] = (T9 * v2 + (-r2 + r0) * v1 + (r2 - r1) * v0) / T8;
	return temp;
}

Polynom Polynom::ByValue(double r0, double v0, double r1, double v1, double r2,
		double v2, double r3, double v3)
{
	Polynom temp;
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
	if(fabs(T26) < 1e-9) throw(std::domain_error(
			__FILE__ ": Polynom(r0,v0,r1,v1,r2,v2,r3,v3) - Some positions have the same r."));
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
	temp.c.resize(4);
	temp.c[3] = ((T16 + T17 + T18) * v3
			+ ((T6 - T7) * T13 + (-T8 + T9) * T15 + (T10 - T11) * r3) * v2
			+ ((-T37 + T38) * T13 + (T30 - T31) * T15 + (-T22 + T23) * r3) * v1
			+ ((T39 - T40) * T13 + (-T32 + T33) * T15 + (T24 - T25) * r3) * v0)
			/ T26;
	temp.c[2] = (T19 * v3 + (T20 * T13 + T21 * T15 - T10 + T11) * v2
			+ ((T12 - T2) * T13 + (-T14 + T4) * T15 + T22 - T23) * v1
			+ ((-T12 + T5) * T13 + (T14 - T3) * T15 - T24 + T25) * v0) / T26;
	temp.c[1] = (T27 * v3 + (T28 * T13 + T29 * r3 + T8 - T9) * v2
			+ ((-r2 + r0) * T13 + (T14 - T4) * r3 - T30 + T31) * v1
			+ ((r2 - r1) * T13 + (-T14 + T3) * r3 + T32 - T33) * v0) / T26;
	temp.c[0] = (T34 * v3 + (T35 * T15 + T36 * r3 - T6 + T7) * v2
			+ ((r2 - r0) * T15 + (-T12 + T2) * r3 + T37 - T38) * v1
			+ ((-r2 + r1) * T15 + (T12 - T5) * r3 - T39 + T40) * v0) / T26;
	return temp;
}

Polynom Polynom::ByDerivative(double r0, double v0, double dv0)
{
	Polynom temp;
	temp.c.resize(2);
	temp.c[1] = v0 + (-dv0 * r0);
	temp.c[0] = dv0;
	return temp;
}

Polynom Polynom::ByDerivative(double r0, double v0, double dv0, double r1,
		double v1)
{
	Polynom temp;
	const double T2 = r1 * r1;
	const double T3 = r0 * r0;
	const double T4 = -2 * r0 * r1;
	const double T5 = T2 + T4 + T3;
	if(fabs(T5) < 1e-9) throw(std::domain_error(
			__FILE__ ": InitByDerivative(r0,v0,dv0,r1,v1) - Both positions have the same r."));
	temp.c.resize(3);
	temp.c[2] = (T3 * v1 + (T2 + T4) * v0 + (-dv0 * r0 * T2) + dv0 * T3 * r1)
			/ T5;
	temp.c[1] = ((-2 * r0 * v1) + 2 * r0 * v0 + dv0 * T2 + (-dv0 * T3)) / T5;
	temp.c[0] = (v1 - v0 + (-dv0 * r1) + dv0 * r0) / T5;
	return temp;
}

Polynom Polynom::ByDerivative(double r0, double v0, double dv0, double r1,
		double v1, double dv1)
{
	Polynom temp;
	const double T3 = r0 * r0;
	const double T4 = r1 * r1;
	const double T2 = r1 * T4;
	const double T5 = r0 * T3;
	const double T6 = -3 * r0 * T4;
	const double T7 = 3 * T3 * r1;
	const double T8 = T2 + T6 + T7 - T5;
	if(fabs(T8) < 1e-9) throw(std::domain_error(
			__FILE__ ": InitByDerivative(r0,v0,dv0,r1,v1,dv1) - Both positions have the same r."));
	const double T9 = 3 * r1;
	const double T10 = 3 * r0;
	const double T11 = -dv1 + (-2 * dv0);
	const double T12 = -dv1 + dv0;
	const double T13 = 2 * dv1 + dv0;
	temp.c.resize(4);
	temp.c[3] = ((T7 - T5) * v1 + (T2 + T6) * v0 + (-dv0 * r0 * T2)
			+ T12 * T3 * T4 + dv1 * T5 * r1) / T8;
	temp.c[2] = ((-6 * r0 * r1 * v1) + 6 * r0 * r1 * v0 + dv0 * T2
			+ T13 * r0 * T4 + T11 * T3 * r1 + (-dv1 * T5)) / T8;
	temp.c[1] = ((T9 + T10) * v1 + (-T9 - T10) * v0 + T11 * T4 + T12 * r0 * r1
			+ T13 * T3) / T8;
	temp.c[0] = ((-2 * v1) + 2 * v0 + (dv1 + dv0) * r1 + (-dv1 - dv0) * r0)
			/ T8;
	return temp;
}

Polynom Polynom::ByBezier(double v0)
{
	Polynom temp;
	temp.c.resize(1);
	temp.c[0] = v0;
	return temp;
}

Polynom Polynom::ByBezier(double v0, double v1)
{
	Polynom temp;
	temp.c.resize(2);
	temp.c[0] = v1 - v0;
	temp.c[1] = v0;
	return temp;
}

Polynom Polynom::ByBezier(double v0, double v1, double v2)
{
	Polynom temp;
	temp.c.resize(3);
	temp.c[0] = v0 - 2 * v1 + v2;
	temp.c[1] = 2 * v1 - 2 * v0;
	temp.c[2] = v0;
	return temp;
}

Polynom Polynom::ByBezier(double v0, double v1, double v2, double v3)
{
	Polynom temp;
	temp.c.resize(4);
	temp.c[0] = -v0 + 3 * v1 - 3 * v2 + v3;
	temp.c[1] = 3 * v0 - 6 * v1 + 3 * v2;
	temp.c[2] = 3 * v1 - 3 * v0;
	temp.c[3] = v0;
	return temp;
}

size_t Polynom::Order(void) const
{
	return (c.empty())? 0 : (c.size() - 1);
}

size_t Polynom::Size(void) const
{
	return c.size();
}

void Polynom::Resize(size_t N)
{
	c.resize(N, 0.0);
}

double& Polynom::operator [](size_t index)
{
	return c[index];
}

double Polynom::operator [](size_t index) const
{
	return c[index];
}

Polynom& Polynom::operator +=(const double& b)
{
	const size_t N = c.size();
	c[N - 1] += b;
	return *this;
}

const Polynom Polynom::operator +(const double& b) const
{
	Polynom temp = *this;
	temp += b;
	return temp;
}

Polynom& Polynom::operator +=(const Polynom& b)
{
	size_t B = b.Size();
	if(B > c.size()){
		const size_t d = B - c.size();
		c.insert(c.begin(), d, 0.0);
		for(size_t n = 0; n < B; ++n)
			c[n] += b[n];
	}else{
		const size_t d = c.size() - B;
		for(size_t n = 0; n < B; ++n)
			c[n + d] += b[n];
	}
	return *this;
}

const Polynom Polynom::operator +(const Polynom& b) const
{
	Polynom temp = *this;
	temp += b;
	return temp;
}

Polynom& Polynom::operator -=(const double& b)
{
	const size_t N = c.size();
	c[N - 1] -= b;
	return *this;
}

const Polynom Polynom::operator -(const double& b) const
{
	Polynom temp = *this;
	temp -= b;
	return temp;
}

Polynom& Polynom::operator -=(const Polynom& b)
{
	size_t B = b.Size();
	if(B > c.size()){
		const size_t d = B - c.size();
		c.insert(c.begin(), d, 0.0);
		for(size_t n = 0; n < B; ++n)
			c[n] -= b[n];
	}else{
		const size_t d = c.size() - B;
		for(size_t n = 0; n < B; ++n)
			c[n + d] -= b[n];
	}
	return *this;
}

const Polynom Polynom::operator -(const Polynom& b) const
{
	Polynom temp = *this;
	temp -= b;
	return temp;
}

Polynom& Polynom::operator *=(const double& b)
{
	const size_t N = c.size();
	for(size_t n = 0; n < N; ++n)
		c[n] *= b;
	return *this;
}

const Polynom Polynom::operator *(const double& b) const
{
	Polynom temp = *this;
	temp *= b;
	return temp;
}

Polynom& Polynom::operator *=(const Polynom& b)
{
	const std::vector <double> cold = c;
	const size_t N = cold.size();
	const size_t M = b.Size();
	c.assign(N + M - 1, 0.0);
	for(size_t n = 0; n < N; ++n)
		for(size_t m = 0; m < M; ++m)
			c[n + m] += cold[n] * b[m];
	return *this;
}

const Polynom Polynom::operator *(const Polynom& b) const
{
	Polynom temp = *this;
	temp *= b;
	return temp;
}

Polynom& Polynom::operator /=(const double& b)
{
	const size_t N = c.size();
	for(size_t n = 0; n < N; ++n)
		c[n] /= b;
	return *this;
}

const Polynom Polynom::operator /(const double& b) const
{
	Polynom temp = *this;
	temp /= b;
	return temp;
}

void Polynom::ScaleX(double val)
{
	const size_t N = c.size();
	val = 1.0 / val;
	double temp = val;
// This is a reverse for-loop for unsigned variables counting down to and including 0.
	for(size_t n = N - 1; n-- > 0;){
		c[n] *= temp;
		temp *= val;
	}
}

void Polynom::ScaleY(double val)
{
	const size_t N = c.size();
	for(size_t n = 0; n < N; ++n)
		c[n] *= val;
}

void Polynom::ShiftX(double val)
{
	const size_t N = c.size();
	const std::vector <double> cold(c);
	std::vector <double> pascal(N, 1.0); // Stores a diagonal in Pascals triangle
	double valpower = val;
	double sign = -1.0;
	for(size_t nv = (N - 1); nv > 0; --nv){
		for(size_t n = N - 1; n > (N - nv - 1); --n){
			pascal[N - n] += pascal[N - n - 1];
			c[n] += sign * pascal[N - n - 1] * cold[n - (N - nv)] * valpower;
		}
		sign = -sign;
		valpower *= val;
	}
}

void Polynom::ShiftY(double val)
{
	const size_t N = c.size();
	c[N - 1] += val;
}

Polynom Polynom::Derivative(size_t order) const
{
	Polynom temp = *this;
	const size_t N = temp.Size();
	for(size_t m = 1; m <= order; ++m)
		for(size_t n = 0; n < (N - m); ++n)
			temp[n] *= (N - m - n);
	temp.Resize(N - order);
	return temp;
}

void Polynom::Derive(size_t order)
{
	const size_t N = c.size();
	for(size_t m = 1; m <= order; ++m)
		for(size_t n = 0; n < (N - m); ++n)
			c[n] *= (N - m - n);
	c.resize(N - order);
}

double Polynom::Integral(double a, double b) const
{
	Polynom temp = this->Integral();
	return temp(b) - temp(a);
}

Polynom Polynom::Integral(size_t order) const
{
	Polynom temp = *this;
	const size_t N = temp.Size();
	for(size_t m = 1; m <= order; ++m)
		for(size_t n = 0; n < N; ++n)
			temp[n] /= (N + m - n - 1);
	temp.Resize(N + order);
	return temp;
}

void Polynom::Integrate(size_t order)
{
	const size_t N = c.size();
	for(size_t m = 1; m <= order; ++m)
		for(size_t n = 0; n < N; ++n)
			c[n] /= (N + m - n - 1);
	c.resize(N + order, 0.0);
}

bool Polynom::ExtremumPos(double& x) const
{
	switch(c.size()){
	case 0:
	case 1:
	case 2:
		{
			return false;
		}
	case 3:
		{
			if(c[0] > -1e-9) return false;
			x = -c[1] / (2 * c[0]);
			return true;
		}
	case 4:
		{
			if(fabs(c[0]) < 1e-9) return false;
			const double h = c[1] * c[1] - 3 * c[0] * c[2];
			if(h < 0) return false;
			x = (-c[1] - sqrt(h)) / (3 * c[0]);
			return true;
		}
	default:
		throw(std::range_error(
				__FILE__" ExtremumPos - This function is only supported for an order up to three (= 4 coefficients)."));
	}

}

bool Polynom::ExtremumNeg(double& x) const
{
	switch(c.size()){
	case 0:
	case 1:
	case 2:
		{
			return false;
		}
	case 3:
		{
			if(c[0] < 1e-9) return false;
			x = -c[1] / (2 * c[0]);
			return true;
		}
	case 4:
		{
			if(fabs(c[0]) < 1e-9) return false;
			const double h = c[1] * c[1] - 3 * c[0] * c[2];
			if(h < 0) return false;
			x = (-c[1] + sqrt(h)) / (3 * c[0]);
			return true;
		}
	default:
		throw(std::range_error(
				__FILE__" ExtremumNeg - This function is only supported for an order up to 3 (= 4 coefficients)."));
	}
}

bool Polynom::InflectionPoint(double& x) const
{
	if(c.size() > 4) throw(std::range_error(
			__FILE__" InflectionPoint - This function is only supported for an order up to 3 (= 4 coefficients)."));
	if(c.size() < 4) return false;
	if(fabs(c[0]) < 1e-9) return false;
	x = -c[1] / (3 * c[0]);
	return true;
}

void Polynom::InvertLinear(void)
{
	if(c.size() != 2) throw(std::range_error(
			__FILE__" InvertLinear - This function is only supports lines (= 2 coefficients)."));
	if(fabs(c[0]) < 1e-9) throw(std::domain_error(
			__FILE__" InvertLinear - This function cannot invert constants (first coefficient is 0)."));
	c[0] = 1 / c[0];
	c[1] = -c[1] * c[0];
}

double Polynom::operator()(double r) const
{
	const size_t N = c.size();
	if(N == 0) return 0.0;
	double temp = c[0];
	for(size_t n = 1; n < N; ++n)
		temp = temp * r + c[n];
	return temp;
}

Polynom Polynom::Reduce(size_t newOrder, double a, double b) const
{
	Polynom d;
	if((c.size()) <= (newOrder + 1)){
		d = *this;
		d.c.resize(newOrder + 1, 0.0);
		return d;
	}
	d.c.resize(newOrder + 1, 0.0);
	switch(c.size() - 1){
	case 1:
		{
			d[0] = ((b + a) * c[0] + 2.0 * c[1]) / 2.0;
			break;
		}
	case 2:
		{
			switch(newOrder){
			case 0:
				{
					d[0] = ((2.0 * b * b + 2.0 * a * b + 2.0 * a * a) * c[0]
							+ (3.0 * b + 3.0 * a) * c[1] + 6.0 * c[2]) / 6.0;
					break;
				}
			case 1:
				{
					d[0] = c[1] + (a + b) * c[0];
					d[1] = ((-b * b - 4.0 * a * b - a * a) * c[0] + 6.0 * c[2])
							/ 6.0;
					break;
				}
			}
			break;
		}
	case 3:
		{
			switch(newOrder){
			case 0:
				{
					d[0] = ((3.0 * b * b * b + 3.0 * a * b * b + 3.0 * a * a * b
							+ 3.0 * a * a * a) * c[0]
							+ (4.0 * b * b + 4.0 * a * b + 4.0 * a * a) * c[1]
							+ (6.0 * b + 6.0 * a) * c[2] + 12.0 * c[3]) / 12.0;
					break;
				}
			case 1:
				{
					d[0] = c[2] + (a + b) * c[1]
							+ (a * a + a * b + b * b) * c[0];
					d[1] = ((-3 * b * b * b - 9.0 * a * b * b - 9.0 * a * a * b
							- 3.0 * a * a * a) * c[0]
							+ (-2 * b * b - 8.0 * a * b - 2.0 * a * a) * c[1]
							+ 12.0 * c[3]) / 12.0;
					break;
				}
			case 2:
				{
					d[0] = ((3.0 * b + 3.0 * a) * c[0] + 2.0 * c[1]) / 2.0;
					d[1] = ((-b * b - 4.0 * a * b - a * a) * c[0] + 2.0 * c[2])
							/ 2.0;
					d[2] = ((a * b * b + a * a * b) * c[0] + 2.0 * c[3]) / 2.0;
					break;
				}
			}
			break;
		}
	case 4:
		{
			switch(newOrder){
			case 0:
				{
					d[0] = ((12.0 * b * b * b * b + 12.0 * a * b * b * b
							+ 12.0 * a * a * b * b + 12.0 * a * a * a * b
							+ 12.0 * a * a * a * a) * c[0]
							+ (15.0 * b * b * b + 15.0 * a * b * b
									+ 15.0 * a * a * b + 15.0 * a * a * a)
									* c[1]
							+ (20.0 * b * b + 20.0 * a * b + 20.0 * a * a)
									* c[2] + (30.0 * b + 30.0 * a) * c[3]
							+ 60.0 * c[4]) / 60.0;
					break;
				}
			case 1:
				{
					d[0] = c[3] + (a + b) * c[2]
							+ (a * a + a * b + b * b) * c[1]
							+ (a * a * a + a * a * b + a * b * b + b * b * b)
									* c[0];
					d[1] = ((-18 * b * b * b * b - 48.0 * a * b * b * b
							- 48.0 * a * a * b * b - 48.0 * a * a * a * b
							- 18.0 * a * a * a * a) * c[0]
							+ (-15 * b * b * b - 45.0 * a * b * b
									- 45.0 * a * a * b - 15.0 * a * a * a)
									* c[1]
							+ (-10 * b * b - 40.0 * a * b - 10.0 * a * a) * c[2]
							+ 60.0 * c[4]) / 60.0;
					break;
				}
			case 2:
				{
					d[0] = ((4.0 * b * b + 4.0 * a * b + 4.0 * a * a) * c[0]
							+ (3.0 * b + 3.0 * a) * c[1] + 2.0 * c[2]) / 2.0;
					d[1] =
							((-2 * b * b * b - 6.0 * a * b * b - 6.0 * a * a * b
									- 2.0 * a * a * a) * c[0]
									+ (-b * b - 4.0 * a * b - a * a) * c[1]
									+ 2.0 * c[3]) / 2.0;
					d[2] = ((b * b * b * b + 26.0 * a * b * b * b
							+ 36.0 * a * a * b * b + 26.0 * a * a * a * b
							+ a * a * a * a) * c[0]
							+ (15.0 * a * b * b + 15.0 * a * a * b) * c[1]
							+ 30.0 * c[4]) / 30.0;
					break;
				}
			case 3:
				{
					d[0] = c[1] + (2.0 * a + 2.0 * b) * c[0];
					d[1] = c[2] + (-a * a - 4.0 * a * b - b * b) * c[0];
					d[2] = c[3] + (2.0 * a * a * b + 2.0 * a * b * b) * c[0];
					d[3] = ((b * b * b * b - 4.0 * a * b * b * b
							- 24.0 * a * a * b * b - 4.0 * a * a * a * b
							+ a * a * a * a) * c[0] + 30.0 * c[4]) / 30.0;
					break;
				}
			}
			break;
		}
	case 5:
		{
			switch(newOrder){
			case 0:
				{
					d[0] = ((10.0 * b * b * b * b * b + 10.0 * a * b * b * b * b
							+ 10.0 * a * a * b * b * b
							+ 10.0 * a * a * a * b * b
							+ 10.0 * a * a * a * a * b
							+ 10.0 * a * a * a * a * a) * c[0]
							+ (12.0 * b * b * b * b + 12.0 * a * b * b * b
									+ 12.0 * a * a * b * b
									+ 12.0 * a * a * a * b
									+ 12.0 * a * a * a * a) * c[1]
							+ (15.0 * b * b * b + 15.0 * a * b * b
									+ 15.0 * a * a * b + 15.0 * a * a * a)
									* c[2]
							+ (20.0 * b * b + 20.0 * a * b + 20.0 * a * a)
									* c[3] + (30.0 * b + 30.0 * a) * c[4]
							+ 60.0 * c[5]) / 60.0;
					break;
				}
			case 1:
				{
					d[0] = c[4] + (a + b) * c[3]
							+ (a * a + a * b + b * b) * c[2]
							+ (a * a * a + a * a * b + a * b * b + b * b * b)
									* c[1]
							+ (a * a * a * a + a * a * a * b + a * a * b * b
									+ a * b * b * b + b * b * b * b) * c[0];
					d[1] = ((-20 * b * b * b * b * b - 50.0 * a * b * b * b * b
							- 50.0 * a * a * b * b * b
							- 50.0 * a * a * a * b * b
							- 50.0 * a * a * a * a * b
							- 20.0 * a * a * a * a * a) * c[0]
							+ (-18 * b * b * b * b - 48.0 * a * b * b * b
									- 48.0 * a * a * b * b
									- 48.0 * a * a * a * b
									- 18.0 * a * a * a * a) * c[1]
							+ (-15 * b * b * b - 45.0 * a * b * b
									- 45.0 * a * a * b - 15.0 * a * a * a)
									* c[2]
							+ (-10 * b * b - 40.0 * a * b - 10.0 * a * a) * c[3]
							+ 60.0 * c[5]) / 60.0;
					break;
				}
			case 2:
				{
					d[0] = ((5.0 * b * b * b + 5.0 * a * b * b + 5.0 * a * a * b
							+ 5.0 * a * a * a) * c[0]
							+ (4.0 * b * b + 4.0 * a * b + 4.0 * a * a) * c[1]
							+ (3.0 * b + 3.0 * a) * c[2] + 2.0 * c[3]) / 2.0;
					d[1] =
							((-3 * b * b * b * b - 8.0 * a * b * b * b
									- 8.0 * a * a * b * b - 8.0 * a * a * a * b
									- 3.0 * a * a * a * a) * c[0]
									+ (-2 * b * b * b - 6.0 * a * b * b
											- 6.0 * a * a * b - 2.0 * a * a * a)
											* c[1]
									+ (-b * b - 4.0 * a * b - a * a) * c[2]
									+ 2.0 * c[4]) / 2.0;
					d[2] =
							((5.0 * b * b * b * b * b + 75.0 * a * b * b * b * b
									+ 100.0 * a * a * b * b * b
									+ 100.0 * a * a * a * b * b
									+ 75.0 * a * a * a * a * b
									+ 5.0 * a * a * a * a * a) * c[0]
									+ (2.0 * b * b * b * b
											+ 52.0 * a * b * b * b
											+ 72.0 * a * a * b * b
											+ 52.0 * a * a * a * b
											+ 2.0 * a * a * a * a) * c[1]
									+ (30.0 * a * b * b + 30.0 * a * a * b)
											* c[2] + 60.0 * c[5]) / 60.0;
					break;
				}
			case 3:
				{
					d[0] = ((10.0 * b * b + 10.0 * a * b + 10.0 * a * a) * c[0]
							+ (6.0 * b + 6.0 * a) * c[1] + 3.0 * c[2]) / 3.0;
					d[1] = ((-5 * b * b * b - 15.0 * a * b * b
							- 15.0 * a * a * b - 5.0 * a * a * a) * c[0]
							+ (-2 * b * b - 8.0 * a * b - 2.0 * a * a) * c[1]
							+ 2.0 * c[3]) / 2.0;
					d[2] = ((b * b * b * b + 26.0 * a * b * b * b
							+ 36.0 * a * a * b * b + 26.0 * a * a * a * b
							+ a * a * a * a) * c[0]
							+ (12.0 * a * b * b + 12.0 * a * a * b) * c[1]
							+ 6.0 * c[4]) / 6.0;
					d[3] =
							((5.0 * b * b * b * b * b - 25.0 * a * b * b * b * b
									- 100.0 * a * a * b * b * b
									- 100.0 * a * a * a * b * b
									- 25.0 * a * a * a * a * b
									+ 5.0 * a * a * a * a * a) * c[0]
									+ (2.0 * b * b * b * b - 8.0 * a * b * b * b
											- 48.0 * a * a * b * b
											- 8.0 * a * a * a * b
											+ 2.0 * a * a * a * a) * c[1]
									+ 60.0 * c[5]) / 60.0;
					break;
				}
			case 4:
				{
					d[0] = ((5 * b + 5 * a) * c[0] + 2 * c[1]) / 2;
					d[1] = ((-5 * b * b - 20 * a * b - 5 * a * a) * c[0]
							+ 3 * c[2]) / 3;
					d[2] = c[3] + (5 * a * a * b + 5 * a * b * b) * c[0];
					d[3] = ((b * b * b * b - 4 * a * b * b * b
							- 24 * a * a * b * b - 4 * a * a * a * b
							+ a * a * a * a) * c[0] + 6 * c[4]) / 6;
					d[4] = ((-a * b * b * b * b + 4 * a * a * b * b * b
							+ 4 * a * a * a * b * b - a * a * a * a * b) * c[0]
							+ 6 * c[5]) / 6;
					break;
				}

			}
			break;
		}
	default:
		throw(std::logic_error(
		__FILE__ "Polynom::Reduce - Cannot reduce from an order > 5."));
		break;
	}
	return d;
}

