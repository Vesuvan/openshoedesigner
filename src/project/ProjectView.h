///////////////////////////////////////////////////////////////////////////////
// Name               : ProjectView.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
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

#ifndef PROJECTVIEW_H_
#define PROJECTVIEW_H_
/*!\class ProjectView
 * \brief Project view options
 *
 * This class contains viewing options for displaying the data of the project. Thus different windows can
 * use the same project data and only display a different aspect.
 */

#include <vector>

#include "Project.h"

#include "BackgroundImage.h"

class ProjectView {
public:
	ProjectView();
	virtual ~ProjectView();
	void SetProject(Project *project);
	void PaintBackground(void) const;
	void Paint(void) const;

	enum {
		Left, Both, Right
	};

	Project *project;
	std::vector <BackgroundImage> background;

	bool showFootScan;
	bool showFootModel;
	bool showLastScan;
	bool showLast;

	bool showBones;
	bool showInsole;
	bool showSole;
	bool showUpper;
	bool showCutaway;
	bool showFloor;

	double floorLevel;

private:
	void PaintBones(void) const;
	void PaintLast(void) const;
	void PaintInsole(void) const;
	void PaintSole(void) const;
	void PaintUpper(void) const;
	void PaintCutaway(void) const;
	void PaintFloor(void) const;
};

#endif /* PROJECTVIEW_H_ */
