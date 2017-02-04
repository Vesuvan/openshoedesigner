///////////////////////////////////////////////////////////////////////////////
// Name               : Spline3.cpp
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
#include "Spline3.h"

#include <GL/gl.h>

Spline3::Spline3()
{
	color.Set(1.0, 1.0, 1.0);
	closed = false;
	pointsize = 5;
	length = 1.0;
}

Spline3::~Spline3()
{
}

void Spline3::Clear(void)
{
	points.clear();
}

void Spline3::AddVector(const Vector3& vector, bool corner)
{
	Point temp;
	temp.Set(vector.x, vector.y, vector.z);
	temp.corner = corner;
	points.push_back(temp);
}

void Spline3::Close(bool close)
{
	closed = close;
}

void Spline3::Calculate(bool symmetric)
{
	const size_t N = points.size();
	if(N == 0) return;
	points[0].r0 = 0.0;
	for(size_t n = 0; n < N - 1; n++)
		points[n].length = (points[n + 1] - points[n]).Abs();
	if(N == 1) return;
	if(symmetric && N > 2){
		for(size_t n = 0; n < ((N - 1) / 2); n++)
			points[n + 1].r0 = points[n].r0 + points[n].length;
		points[N - 1].r0 = points[0].r0 - points[N - 1].length;
		for(size_t n = (N - 2); n > ((N - 1) / 2); n--)
			points[n].r0 = points[n + 1].r0 - points[n].length;
	}else{
		for(size_t n = 0; n < N - 1; n++)
			points[n + 1].r0 = points[n].r0 + points[n].length;
	}
	if(N == 2){
		points[0].px.Set2(points[0].r0, points[0].x, points[1].r0, points[1].x);
		points[0].py.Set2(points[0].r0, points[0].y, points[1].r0, points[1].y);
		points[0].pz.Set2(points[0].r0, points[0].z, points[1].r0, points[1].z);
		if(symmetric){
			points[1].px.Set2(points[0].r0 - points[1].length, points[1].x,
					points[0].r0, points[0].x);
			points[1].py.Set2(points[0].r0 - points[1].length, points[1].y,
					points[0].r0, points[0].y);
			points[1].pz.Set2(points[0].r0 - points[1].length, points[1].z,
					points[0].r0, points[0].z);
		}else{
			points[1].px.Set2(points[1].r0, points[1].x,
					points[1].r0 + points[1].length, points[0].x);
			points[1].py.Set2(points[1].r0, points[1].y,
					points[1].r0 + points[1].length, points[0].y);
			points[1].pz.Set2(points[1].r0, points[1].z,
					points[1].r0 + points[1].length, points[0].z);
		}
		return;
	}

//	printf("\n");
//	for(size_t n = 0; n < N; n++){
//		printf("%6.3f  - %6.3f\n", points[n].r0, points[n].length);
//	}
//	printf("\n");

	size_t m0 = N - 3;
	size_t m1 = N - 2;
	size_t m2 = N - 1;
	size_t m3 = 0;
	signed char c = 0;
	if(closed){
		if(!points[m3].corner){
			c++;
			if(!points[m2].corner){
				c++;
				if(!points[m1].corner){
					c++;
				}
			}
		}
	}
	for(size_t n = 0; n < N; n++){
		switch(c){
		case 0:
			break;
		case 1:
			{
				const double r2 = points[m2].r0;
				const double r3 = r2 + points[m2].length;
				points[m2].px.Set2(r2, points[m2].x, r3, points[m3].x);
				points[m2].py.Set2(r2, points[m2].y, r3, points[m3].y);
				points[m2].pz.Set2(r2, points[m2].z, r3, points[m3].z);
				break;
			}
		case 2:
			{
				const double r2 = points[m2].r0;
				const double r3 = r2 + points[m2].length;
				points[m2].px.Set2(r2, points[m2].x, r3, points[m3].x);
				points[m2].py.Set2(r2, points[m2].y, r3, points[m3].y);
				points[m2].pz.Set2(r2, points[m2].z, r3, points[m3].z);
				break;
			}
		case 3:
			{
				const double r2 = points[m2].r0;
				const double r3 = r2 + points[m2].length;
				points[m2].px.Set2(r2, points[m2].x, r3, points[m3].x);
				points[m2].py.Set2(r2, points[m2].y, r3, points[m3].y);
				points[m2].pz.Set2(r2, points[m2].z, r3, points[m3].z);
				break;
			}
		case 4:
			{
				const double r2 = points[m2].r0;
				const double r3 = r2 + points[m2].length;
				points[m2].px.Set2(r2, points[m2].x, r3, points[m3].x);
				points[m2].py.Set2(r2, points[m2].y, r3, points[m3].y);
				points[m2].pz.Set2(r2, points[m2].z, r3, points[m3].z);
				break;
			}
		}

		if(points[m2].corner){
			c = 1;
		}else{
			if(c < 4) c++;
		}
		m0 = m1;
		m1 = m2;
		m2 = m3;
		m3 = n;
	}
}

void Spline3::SetZeroAt(size_t pos)
{
}

void Spline3::SetZeroOnPlane(size_t afterPos, Vector3 normal)
{
}

void Spline3::AddVector(float x, float y, float z, bool corner)
{
	Point temp;
	temp.Set(x, y, z);
	temp.corner = corner;
	points.push_back(temp);
}

void Spline3::Paint(void) const
{
	if(closed)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_LINE_STRIP);
	glNormal3f(0, 0, 1);
	glColor3f(0.4, 0.4, 0.4);
	size_t N = points.size();
	for(size_t i = 0; i < N; i++){
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glNormal3f(0, 0, 1);
	glColor3f(color.x, color.y, color.z);
	N = 301;
	float D = points[3].r0 - points[0].r0;
	for(size_t i = 0; i < N; i++){
		glVertex3f(points[0].px.Evaluate(D * i / N),
				points[0].py.Evaluate(D * i / N),
				points[0].pz.Evaluate(D * i / N));
	}
	glEnd();
}
