///////////////////////////////////////////////////////////////////////////////
// Name               : LinkageVisitor.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 27.09.2015
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

#ifndef LINKAGEVISITOR_H_
#define LINKAGEVISITOR_H_

/*!\class LinkageVisitor
 * \brief Visitor class for 3D object collections
 * Abstract Visitor class for the Linkage class.
 * Inherit this to a class that will operate on the objects in the tree.
 */

class LinkageVisitor {
public:
	virtual ~LinkageVisitor();

	// One ugly thing about the Visitor pattern is, that this class has to
	// know the Bone class.
	virtual void Visit(class Bone &) = 0;
};

#endif /* LINKAGEVISITOR_H_ */
