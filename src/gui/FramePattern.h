///////////////////////////////////////////////////////////////////////////////
// Name               : FramePattern.h
// Purpose            :
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   : -lm
// Author             : toby
// Created            : 31.10.2015
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

#ifndef FRAMEPATTERN_H_
#define FRAMEPATTERN_H_

/*!\class FramePattern
 * \brief ...
 *
 * ...
 */

#include "gui.h"

#include "../project/Pattern.h"

class FramePattern:public GUIFramePattern {
public:
	FramePattern(wxWindow* parent, Pattern* pattern);
	virtual ~FramePattern();

	virtual void OnCloseX(wxCloseEvent& event);
	virtual void OnChoicePreset(wxCommandEvent& event);
	virtual void OnChoiceStyle(wxCommandEvent& event);
	virtual void OnScroll(wxScrollEvent& event);

	Pattern* pattern;
};

#endif /* FRAMEPATTERN_H_ */
