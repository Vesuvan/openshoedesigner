///////////////////////////////////////////////////////////////////////////////
// Name               : Bone.cpp
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 12.08.2015
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

#include "Bone.h"
#include "LinkageVisitor.h"
#include <GL/gl.h>

#include <math.h>

Bone::Bone()
{
	r1 = 0.0;
	r2 = 0.0;
}

Bone::~Bone()
{
}

void Bone::Render(void)
{
	if(r1 == 0.0 && r2 == 0.0) return;
	float d = (p2 - p1).Abs();
	float r = fabs(r1 - r2);
	int n;
	const int N = 32;
	int m;
	const int M = 16;

	float dv = 2.0 * M_PI / N;
	float v = 0.0;
	float dw = 2.0 * M_PI / M;
	float w = 0.0;
	if(d < r){

		if(r1 > r2){
			v = 0;
			for(n = 0; n <= N; n++){
				::glBegin(GL_TRIANGLE_STRIP);
				w = 0.0;
				for(m = 0; m <= M; m++){
					::glNormal3f(sin(v) * cos(w), -sin(v) * sin(w), -cos(v));
					::glVertex3f(p1.x + sin(v) * cos(w) * r1,
							p1.y - sin(v) * sin(w) * r1, p1.z - cos(v) * r1);
					::glNormal3f(sin(v + dv) * cos(w), -sin(v + dv) * sin(w),
							-cos(v + dv));
					::glVertex3f(p1.x + sin(v + dv) * cos(w) * r1,
							p1.y - sin(v + dv) * sin(w) * r1,
							p1.z - cos(v + dv) * r1);

					w += dw;
				}
				::glEnd();
				v += dv;
			}
		}else{
			v = 0;
			for(n = 0; n <= N; n++){
				::glBegin(GL_TRIANGLE_STRIP);
				w = 0.0;
				for(m = 0; m <= M; m++){
					::glNormal3f(sin(v) * cos(w), -sin(v) * sin(w), -cos(v));
					::glVertex3f(p2.x + sin(v) * cos(w) * r2,
							p2.y - sin(v) * sin(w) * r2, p1.z - cos(v) * r2);
					::glNormal3f(sin(v + dv) * cos(w), -sin(v + dv) * sin(w),
							-cos(v + dv));
					::glVertex3f(p2.x + sin(v + dv) * cos(w) * r2,
							p2.y - sin(v + dv) * sin(w) * r2,
							p2.z - cos(v + dv) * r2);

					w += dw;
				}
				::glEnd();
				v += dv;
			}

		}
		return;
	}

	float s1 = (r1 * r1 - r1 * r2) / d;
	float s2 = (r1 * r2 - r2 * r2) / d;
	Vector3 s = p2 - p1;
	Vector3 g;
	if(s.x <= s.y && s.x <= s.z) g.Set(0, s.z, -s.y);
	if(s.y <= s.z && s.y <= s.x) g.Set(-s.z, 0, s.x);
	if(s.z <= s.x && s.z <= s.y) g.Set(s.y, -s.x, 0);
	Vector3 h;
	s.Normalize();
	g.Normalize();
	h = s * g;
	h.Normalize();

	double h1 = sqrt(r1 * r1 - s1 * s1);
	double h2 = sqrt(r2 * r2 - s2 * s2);
//	double f = s1 / r1;

	Vector3 zyl;
	zyl.Set(s1, h1, 0);
	zyl.Normalize();

	::glBegin(GL_TRIANGLE_STRIP);

	w = 0.0;
	for(m = 0; m <= M; m++){
		Normal(s * zyl.x + g * zyl.y * cos(w) + h * zyl.y * sin(w));
		Vertex(p2 + s * s2 + (g * h2 * cos(w)) + (h * h2 * sin(w)));
		Vertex(p1 + s * s1 + (g * h1 * cos(w)) + (h * h1 * sin(w)));
		w += dw;
	}
	::glEnd();

	v = 0.0;
	float vg = atan2(h1, -s1);
	float v2;
	while(v < vg){
		v2 = fmin(v + dv, vg);
		::glBegin(GL_TRIANGLE_STRIP);
		w = 0.0;
		for(m = 0; m <= M; m++){
			Normal(-s * cos(v2) + g * cos(w) * sin(v2) + h * sin(w) * sin(v2));
			Vertex(
					p1 - s * r1 * cos(v2) + (g * r1 * cos(w) * sin(v2))
							+ (h * r1 * sin(w) * sin(v2)));
			Normal(-s * cos(v) + g * cos(w) * sin(v) + h * sin(w) * sin(v));
			Vertex(
					p1 - s * r1 * cos(v) + (g * r1 * cos(w) * sin(v))
							+ (h * r1 * sin(w) * sin(v)));
			w += dw;
		}
		::glEnd();
		v += dv;
	}

	v = 0.0;
	vg = atan2(h2, s2);
	while(v < vg){
		v2 = fmin(v + dv, vg);
		::glBegin(GL_TRIANGLE_STRIP);
		w = 0.0;
		for(m = 0; m <= M; m++){
			Normal(s * cos(v) + g * cos(w) * sin(v) + h * sin(w) * sin(v));
			Vertex(
					p2 + s * r2 * cos(v) + (g * r2 * cos(w) * sin(v))
							+ (h * r2 * sin(w) * sin(v)));
			Normal(s * cos(v2) + g * cos(w) * sin(v2) + h * sin(w) * sin(v2));
			Vertex(
					p2 + s * r2 * cos(v2) + (g * r2 * cos(w) * sin(v2))
							+ (h * r2 * sin(w) * sin(v2)));
			w += dw;
		}
		::glEnd();
		v += dv;
	}

}

void Bone::Normal(const Vector3 v) const
{
	::glNormal3f(v.x, v.y, v.z);
}

void Bone::Vertex(const Vector3 v) const
{
	::glVertex3f(v.x, v.y, v.z);
}

void Bone::Process(LinkageVisitor& visitor)
{
	// GoF visitor pattern
	visitor.Visit(*this);
}
