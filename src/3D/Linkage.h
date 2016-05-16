///////////////////////////////////////////////////////////////////////////////
// Name               : Linkage.h
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

#ifndef LINKAGE_H_
#define LINKAGE_H_

#include "AffineTransformMatrix.h"
#include "Vector3.h"

class LinkageVisitor;

/*!\class Linkage
 * \brief Linked 3D object trees
 *
 * Utilizes LinkageVisitor for traversing the object tree.
 *
 * \todo: add a copy constructor
 */

class Linkage {
public:
	Linkage();
	virtual ~Linkage();

	Linkage* AddChild(Linkage* child);
//	Linkage* AddChild(void);
//	Linkage* AddChild(Vector3 const &position);

	void Accept(LinkageVisitor & visitor);
	virtual void Process(LinkageVisitor & visitor) = 0;

	void Paint(void);
	virtual void Render(void)=0;

	AffineTransformMatrix matrix;
	Vector3 color;

protected:
	Linkage* parent;
private:
	Linkage* next;
	Linkage* children;
};

#endif /* LINKAGE_H_ */
