///////////////////////////////////////////////////////////////////////////////
// Name               : CollectionFilepaths.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 18.02.2019
// Copyright          : (C) 2019 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef SRC_GUI_COLLECTIONFILEPATHS_H_
#define SRC_GUI_COLLECTIONFILEPATHS_H_

/*!\class CollectionFilepaths
 * \brief Collection of paths
 *
 * Collects the various paths used in the GUI. The paths can be stored in the
 * programs config file / registry.
 */

#include <wx/string.h>
#include <wx/config.h>

class CollectionFilepaths {
public:
	CollectionFilepaths();
	virtual ~CollectionFilepaths();

	wxString lastFootDirectory;
	wxString lastShoeDirectory;
	wxString lastOutputDirectory;

	bool Load(wxConfig * config);
	bool Save(wxConfig * config);
};

#endif /* SRC_GUI_COLLECTIONFILEPATHS_H_ */
