///////////////////////////////////////////////////////////////////////////////
// Name               : Volume.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 19.08.2015
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

#ifndef VOLUME_H_
#define VOLUME_H_

#include "MatlabMatrix.h"
#include "HeightField.h"
#include "AffineTransformMatrix.h"
#include "Geometry.h"
#include "Vector3.h"

/*!\class Volume
 * \brief Marching Cube Volume
 *
 * Sets up a density map by using morph-objects.
 * Applies the marching cubes algorithm to convert the density map into a surface.
 *
 * In the internal data structure X is the first axis, Y the second one, Z the last one.
 *
 * XYZ
 *
 * 000
 * 100
 * 200
 * 010
 * 110
 * 210
 * 020
 * 120
 * 220
 * 001
 * 101
 * 201
 * 011
 * 111
 * 211
 * 021
 * 121
 * 221
 * 002
 * ...
 *
 */

class Volume:public MatlabMatrix {
public:
	enum Axis {
		X, Y, Z
	};

public:
	Volume();
	virtual ~Volume();

	/*! \brief Set the Origin
	 *
	 * Set the origin of the Volume to this point. Together with SetCount or SetSize
	 * it determines the start and end coordinates of the Volume.
	 *
	 * @param origin Vector3 of origin
	 */
	void SetOrigin(Vector3 origin);
	void SetCount(unsigned int nx, unsigned int ny, unsigned int nz,
			float resolution);
	void SetSize(float x, float y, float z, float resolution);

	void AddHalfplane(const Vector3 &p1, float d0, float k0);
	void AddSphere(const Vector3 &p1, float r1, float k1);
	void AddCylinder(const Vector3 &p1, const Vector3 &p2, const float r1,
			const float k1);
	void AddCylinder(const Vector3 &p1, const Vector3 &p2, const float r1,
			const float r2, const float k1);
	void AddCylinder(const Vector3 &p1, const Vector3 &p2, const float r1,
			const float r2, const float k1, const float k2);

	/*! \brief Marching cubes algorithm
	 *
	 * Rund the Marching-cubes algorithm to generate a geometry of the surface
	 * of the data in the volume. The surface is assumed at the level of the
	 * internal variable "surface".
	 */
	void MarchingCubes(void);

	/*! \brief Render the data
	 *
	 * After the MarchingCubes algorithm has run, the generated Geometry can be
	 * rendered with OpenGL commands.
	 */
	void Paint(void) const;

	/*! \brief Return the Value at a point
	 *
	 * Returns the interpolated value of the field at the point p. Points
	 * outside the volume are 0.
	 *
	 * @param p Vector3 point
	 * @return Value at the point p
	 */
	double GetValue(Vector3 p) const;

	/*! \brief Return the Value at a point
	 *
	 * Returns the interpolated value of the field at the point x,y,z. Points
	 * outside the volume are 0.
	 *
	 * @param x coordinate
	 * @param y coordinate
	 * @param z coordinate
	 * @return Value at the point p
	 */
	double GetValue(double x, double y, double z) const;

	/*! \brief Calculate the gradient at point p
	 *
	 * Calculates the gradient in a point by deriving the value of the field in x,y and z.
	 * The returned vector points in the direction of the steppest ascent in the field.
	 * @param p Vector3 point
	 * @return Vector3 gradient at point p
	 */
	Vector3 GetGrad(Vector3 p) const;

	/*! \brief Point on the surface
	 *
	 *
	 * @param p0
	 * @param n
	 * @return
	 */
	Vector3 GetSurface(Vector3 p0, Vector3 n) const;

	/*! \brief Rotate Volume
	 *
	 * Rotate the Volume around an axis. Some functions use this feature to access the model from all sides.
	 *
	 * @param quarters Number of 90 degree turns to do.
	 */
	void Rotate(Axis a, int quarters);

	/*! \brief Mirror Volume
	 *
	 * Mirror the volume along an axis.
	 */
	void Mirror(Axis a);

	/*! \brief Fill a HeightField with the underside of the volume
	 *
	 * Calculate the lower surface of the volume and returns this data in a HeightField.
	 *
	 * @param heightfield Pointer to a HeightField
	 */
	void FillHeightField(HeightField * heightfield) const;

	Vector3 color; ///< Color of the volume
	Geometry geometry; ///< Generated geometry

private:
	double surface; ///< Value of the surface: values greater than surface are inside the volume

	Vector3 origin; ///< Origin of the volume

	float dx;
	float dy;
	float dz;
};

#endif /* VOLUME_H_ */
