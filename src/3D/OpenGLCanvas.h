///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLCanvas.h
// Purpose            : Class providing wxWidgets with an OpenGL canvas with extra functions.
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   : -lopengl32 -lglu
// Author             : Tobias Schaefer
// Created            : 13.09.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#ifndef OPENGLCANVAS_H_
#define OPENGLCANVAS_H_

#include "../StdInclude.h"
#include "AffineTransformMatrix.h"
#include <wx/glcanvas.h>
#include <wx/gdicmn.h>

/*!\class OpenGLCanvas
 * \brief Extending wxGLCanvas with some useful features
 *
 * Features like:
 *  * Mouse movement
 *  * 6-DOF controller support
 *  * Object picking
 *  * Stereo 3D (Anaglyph- and Shutterglasses)
 */

enum Stereo3DType {
	stereoOff = 0, stereoAnaglyph, stereoShutter
};

class OpenGLCanvas:public wxGLCanvas {
	//friend class ChildFrame;
	// Constructor / Destructor
public:
	OpenGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition, const wxSize& size =
					wxDefaultSize, long style = 0,
			const wxString& name = _T("OpenGLCanvas"));
	virtual ~OpenGLCanvas();

	// Member Variables
public:
	Stereo3DType stereoMode;
	float eyeDistance;
	float focalDistance;
	unsigned char backgroundGrayLevel;
	unsigned char rightEyeR;
	unsigned char rightEyeG;
	unsigned char rightEyeB;
	unsigned char leftEyeR;
	unsigned char leftEyeG;
	unsigned char leftEyeB;

protected:
	AffineTransformMatrix rotmat;
	AffineTransformMatrix transmat;

private:
	bool isInitialized;
	GLuint m_gllist;

//	wxTimer timer; ///> Timer for polling the controller

	int x; ///> Startpoint for mouse dragging
	int y; ///> Startpoint for mouse dragging

	// Methods

public:
	virtual void Render();
	virtual void OnInitGL();
	virtual void OnSetupLighting();

protected:

	void OnPaint(wxPaintEvent& WXUNUSED(event));
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& WXUNUSED(event));
	void OnEnterWindow(wxMouseEvent& WXUNUSED(event));
	void OnMouseEvent(wxMouseEvent& event);
	void OnTimer(wxTimerEvent& event);

DECLARE_EVENT_TABLE()
};

#endif /* OPENGLCANVAS_H_ */
