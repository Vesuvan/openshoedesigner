///////////////////////////////////////////////////////////////////////////////
// Name               : Bone.cpp
// Purpose            : Simple bone
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
#include <GL/gl.h>

#include <math.h>

Bone::Bone(const wxString &name)
{
	this->name = name;
	connectTo = 0;
	r1 = 0.0;
	r2 = 0.0;
	anchorD = 0;
	length = 0;
	s1 = 0.01;
	s2 = 0.01;
	rotx = 0.0;
	roty = 0.0;
}

Bone::~Bone()
{
}

void Bone::Vertex(const Vector3 v) const
{
	::glVertex3f(v.x, v.y, v.z);
}

void Bone::Normal(const Vector3 v) const
{
	::glNormal3f(v.x, v.y, v.z);
}

void Bone::Render(void) const
{
	const int N = 32; // Cap segments
	const int M = 16; // Segments around the bone

	if(r1 == 0.0 && r2 == 0.0) return;
	const float L = (p2 - p1).Abs(); // Length of the vector between the points.
	const float dr = fabs(r1 - r2); // Difference between the radii.

	int n, m;

	const float dv = 2.0 * M_PI / N;
	float v = 0.0;
	const float dw = 2.0 * M_PI / M;
	float w = 0.0;

	if(L <= dr){
		// Only one sphere need to be rendered.
		// The bigger one is rendered
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

	// Complete rendering of the bone.

	const float s1 = (r1 * r1 - r1 * r2) / L;
	const float s2 = (r1 * r2 - r2 * r2) / L;
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

	const double h1 = sqrt(r1 * r1 - s1 * s1);
	const double h2 = sqrt(r2 * r2 - s2 * s2);
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

bool Bone::Set(wxString text)
{
	wxString temp = text.BeforeFirst(_T('|'));
	if(temp.Cmp(name) != 0) return false;
	text = text.AfterFirst(_T('|'));
	anchorNx = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	anchorNy = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	anchorNz = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	linkx = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	linky = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	linkz = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	normalx = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	normaly = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	normalz = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	anchorDv = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	lengthv = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	r1v = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	r2v = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	s1v = text.BeforeFirst(_T('|'));
	text = text.AfterFirst(_T('|'));
	s2v = text;
	return true;
}

wxString Bone::Get(void) const
{
	wxString temp = name + _T("|");
	temp += anchorNx + _T("|");
	temp += anchorNy + _T("|");
	temp += anchorNz + _T("|");
	temp += linkx + _T("|");
	temp += linky + _T("|");
	temp += linkz + _T("|");
	temp += normalx + _T("|");
	temp += normaly + _T("|");
	temp += normalz + _T("|");
	temp += anchorDv + _T("|");
	temp += lengthv + _T("|");
	temp += r1v + _T("|");
	temp += r2v + _T("|");
	temp += s1v + _T("|");
	temp += s2v + _T("\n");
	return temp;
}

void Bone::Setup(Bone *parent)
{
	double rLocal;

	if(parent == NULL){
		matrix = AffineTransformMatrix::Identity();
		anchor.x = anchorN.x;
		anchor.y = anchorN.y;
		anchor.z = anchorD;
		rLocal = 1.0;
	}else{
		matrix = parent->matrix;
		// Set the base point of the bone.
		anchor = parent->normal * (parent->length * anchorD);

		// Position of the anchorpoint along the parent bone
		const double h = fmin(fmax(parent->anchorD, 0.0), 1.0);

		rLocal = parent->r1 + (parent->r2 - parent->r1) * h;
		anchor += anchorN * rLocal;
	}

	matrix.TranslateLocal(anchor.x, anchor.y, anchor.z);
	matrix = matrix
			* AffineTransformMatrix::RotateAroundVector(Vector3(1, 0, 0),
					rotx / 2);
	matrix = matrix
			* AffineTransformMatrix::RotateAroundVector(Vector3(0, 1, 0),
					roty / 2);

	Vector3 temp = link * (rLocal + r1);
	matrix.TranslateLocal(temp.x, temp.y, temp.z);

	matrix = matrix
			* AffineTransformMatrix::RotateAroundVector(Vector3(1, 0, 0),
					rotx / 2);
	matrix = matrix
			* AffineTransformMatrix::RotateAroundVector(Vector3(0, 1, 0),
					roty / 2);

	p1 = matrix.Transform(Vector3(0, 0, 0));
	p2 = matrix.Transform(normal * length);
}

