///////////////////////////////////////////////////////////////////////////////
// Name               : Surface.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.06.2020
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

#include "Surface.h"

#include <cassert>
#include <GL/gl.h>

void Surface::Patch::Calculate(void)
{
	/* Axiom CAS code to get to the patch coefficient calculation:

	 )clear all
	 )set output length 125
	 )set output fortran off
	 )set fortran optlevel 2
	 )set fortran intrinsic on
	 f(u,v) == c0 + c1*u + c2*u^2 + c3*u^3 + (c4 + c5*u + c6*u^2 + c7*u^3)*v + (c8 + c9*u + c10*u^2 + c11*u^3)*v^2 + (c12 + c13*u + c14*u^2 + c15*u^3)*v^3
	 du(u,v) == D(f(u,v),u)
	 dv(u,v) == D(f(u,v),v)
	 duv(u,v) == D(f(u,v),[u,v])
	 p := [u0=0,u1=1,v0=0,v1=1];
	 S:=solve([eval(f(u0,v0),p)=v0,eval(f(u1,v0),p)=v1,eval(f(u0,v1),p)=v3,eval(f(u1,v1),p)=v2,eval(duv(u0,v0),p)=0,eval(duv(u1,v0),p)=0,eval(duv(u0,v1),p)=0,eval(duv(u1,v1),p)=0,eval(du(u0,v0),p)=n0u,eval(du(u1,v0),p)=n1u,eval(du(u0,v1),p)=n3u,eval(du(u1,v1),p)=n2u,eval(dv(u0,v0),p)=n0v,eval(dv(u1,v0),p)=n1v,eval(dv(u0,v1),p)=n3v,eval(dv(u1,v1),p)=n2v],[c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15])
	 )set output fortran on
	 S(1)
	 )set output fortran off

	 */
	const Vector3 T2 = -3 * p[0]->p;
	const Vector3 T3 = 2 * p[0]->dv;
	const Vector3 T4 = 3 * p[2]->du;
	const Vector3 T5 = 3 * p[3]->du;
	const Vector3 T6 = 3 * p[1]->du;
	const Vector3 T7 = -3 * p[0]->du;
	const Vector3 T8 = 2 * p[0]->p;
	const Vector3 T9 = 2 * p[0]->du;
	const Vector3 T10 = -6 * p[2]->p;
	const Vector3 T11 = 6 * p[3]->p;
	const Vector3 T12 = 6 * p[1]->p;
	const Vector3 T13 = -6 * p[0]->p;
	const Vector3 T14 = 3 * p[2]->dv;
	const Vector3 T15 = 3 * p[3]->dv;
	const Vector3 T16 = 3 * p[1]->dv;
	const Vector3 T17 = -3 * p[0]->dv;
	const Vector3 T18 = 2 * p[2]->dv;
	const Vector3 T19 = 2 * p[2]->du;
	const Vector3 T20 = 2 * p[3]->dv;
	const Vector3 T21 = -2 * p[3]->du;
	const Vector3 T22 = -2 * p[1]->dv;
	const Vector3 T23 = 2 * p[1]->du;
	c[0] = p[0]->p;
	c[1] = p[0]->du;
	c[2] = 3 * p[1]->p + T2 - p[1]->du - T9;
	c[3] = (-2 * p[1]->p) + T8 + p[1]->du + p[0]->du;
	c[4] = p[0]->dv;
	c[5].Zero();
	c[6] = T16 + T17;
	c[7] = T22 + T3;
	c[8] = 3 * p[3]->p + T2 - p[3]->dv - T3;
	c[9] = T5 + T7;
	c[10] = 9 * p[2]->p + (-9 * p[3]->p) + (-9 * p[1]->p) + 9 * p[0]->p - T14
			- T4 + T15 + (-6 * p[3]->du) + (-6 * p[1]->dv) + T6 + 6 * p[0]->dv
			+ 6 * p[0]->du;
	c[11] = T10 + T11 + T12 + T13 + T18 + T4 - T20 + T5 + 4 * p[1]->dv - T6
			+ (-4 * p[0]->dv) + T7;
	c[12] = (-2 * p[3]->p) + T8 + p[3]->dv + p[0]->dv;
	c[13] = T21 + T9;
	c[14] = T10 + T11 + T12 + T13 + T14 + T19 - T15 + 4 * p[3]->du + T16 - T23
			+ T17 + (-4 * p[0]->du);
	c[15] = 4 * p[2]->p + (-4 * p[3]->p) + (-4 * p[1]->p) + 4 * p[0]->p - T18
			- T19 + T20 + T21 + T22 + T23 + T3 + T9;
}

Vector3 Surface::Patch::operator ()(float u, float v) const
{
	const Vector3 T0 = ((c[3] * u + c[2]) * u + c[1]) * u + c[0];
	const Vector3 T1 = ((c[7] * u + c[6]) * u + c[5]) * u + c[4];
	const Vector3 T2 = ((c[11] * u + c[10]) * u + c[9]) * u + c[8];
	const Vector3 T3 = ((c[15] * u + c[14]) * u + c[13]) * u + c[12];
	return ((T3 * v + T2) * v + T1) * v + T0;
}

Vector3 Surface::Patch::Normal(float u, float v) const
{
	const Vector3 T0 = ((3 * c[3] * u + 2 * c[2]) * u + c[1]);
	const Vector3 T1 = ((3 * c[7] * u + 2 * c[6]) * u + c[5]);
	const Vector3 T2 = ((3 * c[11] * u + 2 * c[10]) * u + c[9]);
	const Vector3 T3 = ((3 * c[15] * u + 2 * c[14]) * u + c[13]);
	const Vector3 du = ((T3 * v + T2) * v + T1) * v + T0;
	const Vector3 T4 = ((c[7] * u + c[6]) * u + c[5]) * u + c[4];
	const Vector3 T5 = ((c[11] * u + c[10]) * u + c[9]) * u + c[8];
	const Vector3 T6 = ((c[15] * u + c[14]) * u + c[13]) * u + c[12];
	const Vector3 dv = ((3 * T6 * v + 2 * T5) * v + T4);
	return (du * dv);
}

void Surface::Patch::Paint(void) const
{
	const float du = 0.02;
	const float dv = 0.02;
	for(float u = 0.0; u < 1.0 - du / 2; u += du){
		glBegin(GL_QUAD_STRIP);
		Vector3 v0 = this->operator()(u, 0.0);
		Vector3 v1 = this->operator()(u + du, 0.0);
		Vector3 n0 = Normal(u, 0.0).Normal();
		Vector3 n1 = Normal(u + du, 0.0).Normal();
		glNormal3f(n0.x, n0.y, n0.z);
		glVertex3f(v0.x, v0.y, v0.z);
		glNormal3f(n1.x, n1.y, n1.z);
		glVertex3f(v1.x, v1.y, v1.z);
		for(float v = 0.0; v < 1.0 - dv / 2; v += dv){
			Vector3 v0 = this->operator()(u, v + dv);
			Vector3 v1 = this->operator()(u + du, v + dv);
			Vector3 n0 = Normal(u, v + dv).Normal();
			Vector3 n1 = Normal(u + du, v + dv).Normal();
			glNormal3f(n0.x, n0.y, n0.z);
			glVertex3f(v0.x, v0.y, v0.z);
			glNormal3f(n1.x, n1.y, n1.z);
			glVertex3f(v1.x, v1.y, v1.z);
		}
		glEnd();
	}
	if(false){
		glBegin(GL_LINES);
		for(float u = 0.0; u < 1.0 - du / 2; u += du){
			for(float v = 0.0; v < 1.0 - dv / 2; v += dv){
				Vector3 v0 = this->operator()(u + du / 2, v + dv / 2);
				Vector3 n0 = Normal(u + du / 2, v + dv / 2);
				glNormal3f(n0.x, n0.y, n0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v0.x + n0.x / 5, v0.y + n0.y / 5, v0.z + n0.z / 5);
			}
		}
		glEnd();
	}
}

void Surface::SetSize(size_t U, size_t V)
{
	assert(U > 1);
	assert(V > 1);
	p.resize(U * V);
	this->U = U;
	this->V = V;

	a.resize((U - (uCyclic? 0 : 1)) * (V - (vCyclic? 0 : 1)));

	size_t ia = 0;
	for(size_t j = 0; j < V - 1; ++j){
		for(size_t i = 0; i < U - 1; ++i){
			a[ia].p[0] = &(p[i + j * U]);
			a[ia].p[1] = &(p[i + 1 + j * U]);
			a[ia].p[2] = &(p[i + 1 + (j + 1) * U]);
			a[ia].p[3] = &(p[i + (j + 1) * U]);
			++ia;
		}
		if(uCyclic){
			a[ia].p[0] = &(p[U - 1 + j * U]);
			a[ia].p[1] = &(p[0 + j * U]);
			a[ia].p[2] = &(p[0 + (j + 1) * U]);
			a[ia].p[3] = &(p[U - 1 + (j + 1) * U]);
			++ia;
		}
	}
	if(vCyclic){
		for(size_t i = 0; i < U - 1; ++i){
			a[ia].p[0] = &(p[i + (V - 1) * U]);
			a[ia].p[1] = &(p[i + 1 + (V - 1) * U]);
			a[ia].p[2] = &(p[i + 1 + 0 * U]);
			a[ia].p[3] = &(p[i + 0 * U]);
			++ia;
		}
		if(uCyclic){
			a[ia].p[0] = &(p[U - 1 + (V - 1) * U]);
			a[ia].p[1] = &(p[0 + (V - 1) * U]);
			a[ia].p[2] = &(p[0 + 0 * U]);
			a[ia].p[3] = &(p[U - 1 + 0 * U]);
			++ia;
		}
	}
}

Surface::Point& Surface::P(const size_t idxu, const size_t idxv)
{
	return p[idxu + idxv * U];
}

const Surface::Point& Surface::P(const size_t idxu, const size_t idxv) const
{
	return p[idxu + idxv * U];
}

void Surface::Calculate(void)
{
	for(auto & patch : a)
		patch.Calculate();
}

void Surface::CalculateDirections(void)
{
	assert(U * V == p.size());
	assert(U > 1);
	assert(V > 1);

	for(size_t j = 0; j < V; ++j){
		for(size_t i = 1; i < U - 1; ++i){
			p[i + j * U].du = (p[i + 1 + j * U].p - p[i - 1 + j * U].p) / 2;
		}
	}
	if(uCyclic){
		for(size_t j = 0; j < V; ++j){
			p[0 + j * U].du = (p[1 + j * U].p - p[U - 1 + j * U].p) / 2;
			p[U - 1 + j * U].du = (p[0 + j * U].p - p[U - 2 + j * U].p) / 2;
		}
	}else{
		for(size_t j = 0; j < V; ++j){
			p[0 + j * U].du = (p[1 + j * U].p - p[0 + j * U].p);
			p[U - 1 + j * U].du = (p[U - 1 + j * U].p - p[U - 2 + j * U].p);
		}
	}

	for(size_t i = 0; i < U; ++i){
		for(size_t j = 1; j < V - 1; ++j){
			p[i + j * U].dv = (p[i + (j + 1) * U].p - p[i + (j - 1) * U].p) / 2;
		}
	}
	if(vCyclic){
		for(size_t i = 0; i < U; ++i){
			p[i + 0 * U].dv = (p[i + 1 * U].p - p[i + (V - 1) * U].p) / 2;
			p[i + (V - 1) * U].dv = (p[i + 0 * U].p - p[i + (V - 2) * U].p) / 2;
		}
	}else{
		for(size_t i = 0; i < U; ++i){
			p[i + 0 * U].dv = (p[i + 1 * U].p - p[i + 0 * U].p);
			p[i + (V - 1) * U].dv =
					(p[i + (V - 1) * U].p - p[i + (V - 2) * U].p);
		}
	}
}

void Surface::Paint(void) const
{
	for(auto & patch : a)
		patch.Paint();
}

