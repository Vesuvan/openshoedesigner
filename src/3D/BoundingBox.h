///////////////////////////////////////////////////////////////////////////////
// Name               : BoundingBox.h
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

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
/*!\class BoundingBox
 * \brief Bounding Box aligned with x,y,z
 *
 * Stores the min and max values of Vector3%s, Triangle%s, other BoundingBox%es and Geometry.
 */

#include <string>
#include <cfloat>

struct Vector3;
class Triangle;
class AffineTransformMatrix;
class Geometry;

class BoundingBox {
	// Constructor / Destructor
public:
	BoundingBox() = default;
	BoundingBox(const Vector3 & v1, const Vector3 & v2);

	// Member variables
public:
	double xmin = DBL_MAX;
	double xmax = -DBL_MAX;
	double ymin = DBL_MAX;
	double ymax = -DBL_MAX;
	double zmin = DBL_MAX;
	double zmax = -DBL_MAX;

	// Methods
public:
	//! Reset the BoundingBox.
	void Clear(void);

	//! Insert a Geometry object into the box.
	void Insert(const Geometry& geometry, const AffineTransformMatrix& matrix);

	//! Insert a single vector.
	void Insert(const Vector3& point);

	//! Insert another BoungingBox.
	void Insert(const BoundingBox& bbox);

	//! Insert a single Triangle.
	void Insert(const Triangle& tri);

	BoundingBox& operator+=(const BoundingBox& rhs);
	const BoundingBox operator+(const BoundingBox& rhs) const;

	//! Check if the box is empty, i.e. nothing was inserted.
	bool IsEmpty(void) const;

	/*!\brief Check if the box has zero volume.
	 * This function checks if the box has no thickness in any direction.
	 * This is not the same as a check for IsEmpty.
	 */
	bool IsVolumeZero(void) const;

	void Set(const Vector3 & v1, const Vector3 & v2);

	void SetSize(float sx, float sy, float sz, float origx = 0.0, float origy =
			0.0, float origz = 0.0);

	void SetOrigin(float origx = 0.0, float origy = 0.0, float origz = 0.0);
	void SetOrigin(const Vector3 &orig);

	AffineTransformMatrix GetCoordinateSystem(void) const; ///< Return a (non-normal) coordinate system for mapping points in the box.

	//! Get the volume of the box.
	double GetVolume(void) const;

	//! Returns the size in x direction.
	double GetSizeX(void) const
	{
		if(xmax < xmin) return 0.0;
		return xmax - xmin;
	}

	//! Returns the size in x direction.
	double GetSizeY(void) const
	{
		if(ymax < ymin) return 0.0;
		return ymax - ymin;
	}

	//! Returns the size in x direction.
	double GetSizeZ(void) const
	{
		if(zmax < zmin) return 0.0;
		return zmax - zmin;
	}

	bool Overlaps(const BoundingBox &other) const;
	bool IsInside(const Vector3 &v) const;

	/*!\brief Transform BoundingBox by matrix
	 *
	 * @param matrix AffineTransformMatrix
	 */
	void Transform(const AffineTransformMatrix & matrix);

	std::string ToString(void) const;
	bool FromString(const std::string & string);

	//! Paint the box in OpenGL.
	void Paint(double overlap = 0.0) const;
	void PaintEdges(double cornerlength = 0.5,
			unsigned int edgewidth = 1) const;
	void PaintVertices(unsigned int extrapoints = 0,
			unsigned int pointsize = 1) const;
};

#endif /* BOUNDINGBOX_H_ */
