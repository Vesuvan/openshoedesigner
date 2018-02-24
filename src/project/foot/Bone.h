///////////////////////////////////////////////////////////////////////////////
// Name               : Bone.h
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

#ifndef BONE_H_
#define BONE_H_
/*!\class Bone
 * \brief Simple bone approximated by a capsule.
 *
 * Simple bone model with two radii for both ends.
 * Definition of a link may be confusing but is selected
 * this way to make every bone scaleable while keeping
 * the skeleton intact.
 *
 * Rotations are done with 50-50 split rotations.
 *
 * Parent bone provides an anchor, a bone normal and a length.
 *
 * First calculate the normal intersection from link and parent bond.
 *
 * p1Parent + normalParent*lengthParent*linkD
 *
 * add the offset vector linkN times the radius of the parent bone at this spot.
 *
 * + linkN*rLocalParent
 *
 * Second calculate p1. It is the link-point + anchor*(rLocalParent+r1)
 *
 * Third calculate p2 by adding p1 + normal*length
 *
 */

#include <wx/string.h>

#include "../../3D/AffineTransformMatrix.h"
#include "../../3D/Vector3.h"

class Bone {
public:
	Bone(const wxString &name);
	virtual ~Bone();

	enum stringIdentifier {
		stringAnchorD, stringLength, stringR1, stringR2, stringS1, stringS2
	};

	wxString name;

	size_t connectTo;

	// Formulas:
	wxString anchorNx;
	wxString anchorNy;
	wxString anchorNz;
	wxString linkx;
	wxString linky;
	wxString linkz;
	wxString normalx;
	wxString normaly;
	wxString normalz;
	wxString anchorDv;
	wxString lengthv;
	wxString r1v;
	wxString r2v;
	wxString s1v;
	wxString s2v;

	// Parent bone provides an anchor, a bone normal and a length.
	// First calculate the normal intersection from link and parent bond.
	Vector3 anchor;
	// p1Parent + normalParent*lengthParent*linkD
	double anchorD; ///< Relative position of link in parent bone.
	// add the offset vector linkN times the radius of the parent bone at this spot.
	// + linkN*rLocalParent
	Vector3 anchorN; ///< Point from the parent bone

	Vector3 normal;
	double length;

	double r1; //!< Radius of 1st sphere
	double r2; //!< Radius of 2nd sphere

	double s1; //!< Skin thickness on 1st sphere
	double s2; //!< Skin thickness on 2nd sphere

	double rotx; //!< Rotation along the x axis
	double roty; //!< Rotation along the y axis

	// Second calculate p1. It is the link-point + anchor*(rLocalParent+r1)
	Vector3 p1; //!< First point of bone.
	Vector3 link;

	// Third calculate p2 by adding p1 + normal*length
	Vector3 p2; //!< Second point of bone.

	AffineTransformMatrix matrix;

	bool Set(wxString text);
	wxString Get(void) const;

	void Setup(Bone *parent);

	void Render(void) const;

private:
	void Normal(const Vector3 v) const;
	void Vertex(const Vector3 v) const;
};

#endif /* BONE_H_ */
