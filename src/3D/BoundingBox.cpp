///////////////////////////////////////////////////////////////////////////////
// Name               : BoundingBox.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 22.06.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "BoundingBox.h"

#include <GL/gl.h>
#include <float.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfBoundingBox)

BoundingBox::BoundingBox()
{
	color.Set(0.3, 0.3, 0.3);
	alpha = 0.5;

	xmax = ymax = zmax = -DBL_MAX;
	xmin = ymin = zmin = DBL_MAX;

	this->Clear();
}

BoundingBox::BoundingBox(float x1, float y1, float z1, float x2, float y2,
		float z2)
{
	color.Set(0.3, 0.3, 0.3);
	alpha = 0.5;

	if(x1 > x2) std::swap(x1, x2);
	if(y1 > y2) std::swap(y1, y2);
	if(z1 > z2) std::swap(z1, z2);

	xmin = x1;
	ymin = y1;
	zmin = z1;

	xmax = x2;
	ymax = y2;
	zmax = z2;
}

void BoundingBox::Clear(void)
{
	xmax = ymax = zmax = -DBL_MAX;
	xmin = ymin = zmin = DBL_MAX;
}

bool BoundingBox::IsEmpty(void) const
{
	if(xmax < xmin) return true;
	if(ymax < ymin) return true;
	if(zmax < zmin) return true;
	return false;
}

bool BoundingBox::IsVolumeZero(void) const
{
	if(xmax <= xmin) return true;
	if(ymax <= ymin) return true;
	if(zmax <= zmin) return true;
	return false;
}

double BoundingBox::GetVolume(void) const
{
	if(xmax <= xmin) return 0.0;
	if(ymax <= ymin) return 0.0;
	if(zmax <= zmin) return 0.0;
	return (xmax - xmin) * (ymax - ymin) * (zmax - zmin);
}

void BoundingBox::Insert(const Geometry &geometry,
		const AffineTransformMatrix &matrix)
{
	size_t i, j;
	for(i = 0; i < geometry.triangles.GetCount(); i++){
		Triangle temp = geometry.triangles[i];
		temp.ApplyTransformation(matrix * geometry.matrix);
		for(j = 0; j < 3; j++){
			if(temp.p[j].x > xmax) xmax = temp.p[j].x;
			if(temp.p[j].x < xmin) xmin = temp.p[j].x;
			if(temp.p[j].y > ymax) ymax = temp.p[j].y;
			if(temp.p[j].y < ymin) ymin = temp.p[j].y;
			if(temp.p[j].z > zmax) zmax = temp.p[j].z;
			if(temp.p[j].z < zmin) zmin = temp.p[j].z;
		}
	}
}

void BoundingBox::Insert(const Vector3& point)
{
	if(point.x > xmax) xmax = point.x;
	if(point.x < xmin) xmin = point.x;
	if(point.y > ymax) ymax = point.y;
	if(point.y < ymin) ymin = point.y;
	if(point.z > zmax) zmax = point.z;
	if(point.z < zmin) zmin = point.z;
}

void BoundingBox::Insert(const BoundingBox& bbox)
{
	if(bbox.xmin < xmin) xmin = bbox.xmin;
	if(bbox.xmax > xmax) xmax = bbox.xmax;
	if(bbox.ymin < ymin) ymin = bbox.ymin;
	if(bbox.ymax > ymax) ymax = bbox.ymax;
	if(bbox.zmin < zmin) zmin = bbox.zmin;
	if(bbox.zmax > zmax) zmax = bbox.zmax;
}

void BoundingBox::Insert(const Triangle &tri)
{
	unsigned char i;
	for(i = 0; i < 3; i++){
		if(tri.p[i].x > xmax) xmax = tri.p[i].x;
		if(tri.p[i].x < xmin) xmin = tri.p[i].x;
		if(tri.p[i].y > ymax) ymax = tri.p[i].y;
		if(tri.p[i].y < ymin) ymin = tri.p[i].y;
		if(tri.p[i].z > zmax) zmax = tri.p[i].z;
		if(tri.p[i].z < zmin) zmin = tri.p[i].z;
	}
}

void BoundingBox::Paint(void) const
{

	float overlap = 0.1;

	if(xmax < xmin) return;
	if(ymax < ymin) return;
	if(zmax < zmin) return;

	::glBegin(GL_QUADS);

	::glColor4f(color.x, 0, 0, alpha);

	::glNormal3f(1, 0, 0);
	::glVertex3f(xmax, ymax + overlap, zmax + overlap);
	::glVertex3f(xmax, ymin - overlap, zmax + overlap);
	::glVertex3f(xmax, ymin - overlap, zmin - overlap);
	::glVertex3f(xmax, ymax + overlap, zmin - overlap);

	::glNormal3f(-1, 0, 0);
	::glVertex3f(xmin, ymax + overlap, zmax + overlap);
	::glVertex3f(xmin, ymax + overlap, zmin - overlap);
	::glVertex3f(xmin, ymin - overlap, zmin - overlap);
	::glVertex3f(xmin, ymin - overlap, zmax + overlap);

	::glColor4f(0, color.y, 0, alpha);
	::glNormal3f(0, 1, 0);
	::glVertex3f(xmax + overlap, ymax, zmax + overlap);
	::glVertex3f(xmax + overlap, ymax, zmin - overlap);
	::glVertex3f(xmin - overlap, ymax, zmin - overlap);
	::glVertex3f(xmin - overlap, ymax, zmax + overlap);

	::glNormal3f(0, -1, 0);
	::glVertex3f(xmax + overlap, ymin, zmax + overlap);
	::glVertex3f(xmin - overlap, ymin, zmax + overlap);
	::glVertex3f(xmin - overlap, ymin, zmin - overlap);
	::glVertex3f(xmax + overlap, ymin, zmin - overlap);

	::glColor4f(0, 0, color.z, alpha);
	::glNormal3f(0, 0, 1);
	::glVertex3f(xmax + overlap, ymax + overlap, zmax);
	::glVertex3f(xmin - overlap, ymax + overlap, zmax);
	::glVertex3f(xmin - overlap, ymin - overlap, zmax);
	::glVertex3f(xmax + overlap, ymin - overlap, zmax);

	::glNormal3f(0, 0, -1);
	::glVertex3f(xmax + overlap, ymax + overlap, zmin);
	::glVertex3f(xmax + overlap, ymin - overlap, zmin);
	::glVertex3f(xmin - overlap, ymin - overlap, zmin);
	::glVertex3f(xmin - overlap, ymax + overlap, zmin);

	::glEnd();
}

void BoundingBox::ToStream(wxTextOutputStream& stream)
{
	stream << _T("BoundingBox:") << endl;
	stream << xmin << _T(" ") << xmax << _T(" ");
	stream << ymin << _T(" ") << ymax << _T(" ");
	stream << zmin << _T(" ") << zmax << endl;
	stream << color.x << _T(" ");
	stream << color.y << _T(" ");
	stream << color.z << endl;
	stream << alpha << endl;
}

bool BoundingBox::FromStream(wxTextInputStream& stream)
{
	wxString temp = stream.ReadWord();
	if(temp.Cmp(_T("BoundingBox:")) != 0) return false;
	stream >> xmin;
	stream >> xmax;
	stream >> ymin;
	stream >> ymax;
	stream >> zmin;
	stream >> zmax;
	stream >> color.x;
	stream >> color.y;
	stream >> color.z;
	stream >> alpha;
	return true;
}