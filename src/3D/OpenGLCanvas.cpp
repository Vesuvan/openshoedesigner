///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLCanvas.cpp
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

#include "OpenGLCanvas.h"

#include <wx/wx.h>

#ifdef __WXMAC__
#include "OpenGL/glu.h"
//#include "OpenGL/gl.h"
#else
#include <GL/glu.h>
//#include <GL/gl.h>
#endif

//TODO: Change this to this->Connect(...) calls and get rid of that "#define" below!
BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas) EVT_SIZE(OpenGLCanvas::OnSize)
EVT_PAINT(OpenGLCanvas::OnPaint)
EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)
EVT_ENTER_WINDOW(OpenGLCanvas::OnEnterWindow)
EVT_MOUSE_EVENTS(OpenGLCanvas::OnMouseEvent)
END_EVENT_TABLE()

static int wx_gl_attribs[] =
	{WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 24, 0};

//wxGLCanvas(parent, wxID_ANY ,wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"));

OpenGLCanvas::OpenGLCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
		wxGLCanvas(parent, (wxGLCanvas*) NULL, id, pos, size,
				style | wxFULL_REPAINT_ON_RESIZE, name, wx_gl_attribs)
{
	// int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

	isInitialized = false;
	m_gllist = 0;
	x = y = 0;

	stereoMode = stereoOff;
	eyeDistance = 0.1;
	focalDistance = 1.0;
	backgroundGrayLevel = 102;
	rightEyeR = 0;
	rightEyeG = 77;
	rightEyeB = 102;
	leftEyeR = 179;
	leftEyeG = 0;
	leftEyeB = 0;

//	timer.SetOwner(this);
//	this->Connect(wxEVT_TIMER, wxTimerEventHandler(OpenGLCanvas::OnTimer),
//	NULL, this);
//	timer.Start(100);
}

OpenGLCanvas::~OpenGLCanvas()
{
//	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(OpenGLCanvas::OnTimer),
//	NULL, this);
}

void OpenGLCanvas::OnEnterWindow(wxMouseEvent& WXUNUSED(event))
{
	SetFocus();
}

void OpenGLCanvas::OnSize(wxSizeEvent& event)
{
	// This is also necessary to update the context on some platforms
	wxGLCanvas::OnSize(event);
	this->Refresh();
}

void OpenGLCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
	// Do nothing, to avoid flashing. OpenGL Repaint the entire drawing area on every frame.
	// There are not leftovers that need to be removed first.
}

void OpenGLCanvas::OnSetupLighting()
{
	GLfloat ambient0[] =
		{0.5f, 0.5f, 0.5f};
	GLfloat diffuse0[] =
		{0.6f, 0.6f, 0.6f};
	GLfloat specular0[] =
		{0.9f, 0.9f, 0.9f};
	GLfloat position0[] =
		{-20, 20, 50, 0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glEnable(GL_LIGHT0);

	::glEnable(GL_LIGHTING);
}

void OpenGLCanvas::OnInitGL()
{
	/* set viewing projection */
	//	glMatrixMode(GL_PROJECTION);
	//	glFrustum( -0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);
	// Is done in OnSize(...)
	//	GLfloat attenuation[] =
	//		{1.0f, -0.01f, -.000001f};
	//::glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation, 0);
	::glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	::glEnable(GL_COLOR_MATERIAL);

	::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	::glBlendFunc(GL_ONE, GL_ZERO); // disable alpha blending

	::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	::glClearDepth(1.0f);

	::glEnable(GL_BLEND);
	::glEnable(GL_POINT_SMOOTH);
	::glEnable(GL_DEPTH_TEST);

	::glFrontFace(GL_CCW);
	::glCullFace(GL_BACK);
	::glEnable(GL_CULL_FACE);

	OnSetupLighting();

//  Refreshing is done anyway or else OnPaint would not have been called.
//	this->Refresh();
}

void OpenGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	if(!IsShown()) return;
#ifndef __WXMOTIF__
	if(!GetContext()) return;
#endif

	wxGLCanvas::SetCurrent(); // Link OpenGL to this area
	wxPaintDC(this); // Set the clipping for this area

	// Init OpenGL once, but after SetCurrent
	if(!isInitialized){
		OnInitGL();
		isInitialized = true;
	}

	// set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
	int w, h;
	GetClientSize(&w, &h);
	::glViewport(0, 0, (GLint) w, (GLint) h);

	//	float specReflection[] = { 0.8f, 0.0f, 0.8f, 1.0f };
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
	//	glMateriali(GL_FRONT, GL_SHININESS, 96);

	// Clear color and depth buffers
	glEnable(GL_COLOR_MATERIAL);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Background

	if(stereoMode == stereoAnaglyph){
		::glEnable(GL_COLOR_MATERIAL);
		::glColor3ub(backgroundGrayLevel, backgroundGrayLevel,
				backgroundGrayLevel);
		::glDisable(GL_COLOR_MATERIAL);
	}

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluOrtho2D(0, 1, 0, 1);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	glNormal3b(0, 0, 1);
	glBegin(GL_QUADS);
	glColor3ub(50, 50, 50);
	glVertex2i(1, 1);
	glVertex2i(0, 1);
	glColor3ub(50, 50, 255);
	glVertex2i(0, 0);
	glVertex2i(1, 0);
	glEnd();

	// Clear the depth buffer bit again. Now the rest of the
	// image is always painted in front of the background.
	glClear( GL_DEPTH_BUFFER_BIT);
//	}

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	GLdouble ar = (GLdouble) w / (GLdouble) h; // Calculate perspective
	::gluPerspective(45, ar, 0.01, 10);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	if(stereoMode == stereoAnaglyph){
		::glColorMask((leftEyeR == 0)? GL_FALSE : GL_TRUE,
				(leftEyeG == 0)? GL_FALSE : GL_TRUE,
				(leftEyeB == 0)? GL_FALSE : GL_TRUE, GL_TRUE);
		::glEnable(GL_COLOR_MATERIAL);
		::glColor3ub(leftEyeR, leftEyeG, leftEyeB);
		::glDisable(GL_COLOR_MATERIAL);
	}
	if(stereoMode == stereoShutter){
		::glDrawBuffer(GL_BACK_LEFT);
	}

	if(stereoMode != stereoOff){
		::glRotatef(
				atan(eyeDistance / 2 / (focalDistance - transmat.a[14] + 1.0))
						* 180.0 / M_PI, 0, 1, 0);
		::glTranslatef(eyeDistance / 2, 0, 0);
	}

	::glTranslatef(0.0, 0.0, -1.0);
	::glMultMatrixd(transmat.a);
	::glMultMatrixd(rotmat.a);
	//	if(m_gllist == 0){
	//		m_gllist = glGenLists(1); // Make one (1) empty display list.
	//		glNewList(m_gllist, GL_COMPILE_AND_EXECUTE);
	Render();
	//		glEndList();
	//	}else{
	//		glCallList(m_gllist);
	//	}

	if(stereoMode != stereoOff) ::glLoadIdentity();

	if(stereoMode == stereoAnaglyph){
		::glColorMask((rightEyeR == 0)? GL_FALSE : GL_TRUE,
				(rightEyeG == 0)? GL_FALSE : GL_TRUE,
				(rightEyeB == 0)? GL_FALSE : GL_TRUE, GL_TRUE);
		::glEnable(GL_COLOR_MATERIAL);
		::glColor3ub(rightEyeR, rightEyeG, rightEyeB);
		::glDisable(GL_COLOR_MATERIAL);
	}
	if(stereoMode == stereoShutter){
		::glDrawBuffer(GL_BACK_RIGHT);
	}

	if(stereoMode != stereoOff){
		glClear(GL_DEPTH_BUFFER_BIT);

		::glRotatef(
				-atan(eyeDistance / 2 / (focalDistance - transmat.a[14] + 1.0))
						* 180.0 / M_PI, 0, 1, 0);
		::glTranslatef(-eyeDistance / 2, 0, 0);
		::glTranslatef(0.0, 0.0, -1.0);
		::glMultMatrixd(transmat.a);
		::glMultMatrixd(rotmat.a);
		Render();
		//glCallList(m_gllist);

		::glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}

	glFlush();
	SwapBuffers();

}

void OpenGLCanvas::Render()
{
	::glPushMatrix();

	GLfloat x = 1.0;
	GLfloat y = 0.5;
	GLfloat z = 2.0;

	GLfloat t = sqrt(x * x + y * y + z * z);
	GLfloat nx = x / t;
	GLfloat ny = y / t;
	GLfloat nz = z / t;

	::glBegin(GL_QUADS);
	::glNormal3f(nx, ny, nz);
	::glVertex3f(x, y, z);
	::glNormal3f(nx, -ny, nz);
	::glVertex3f(x, -y, z);
	::glNormal3f(nx, -ny, -nz);
	::glVertex3f(x, -y, -z);
	::glNormal3f(nx, ny, -nz);
	::glVertex3f(x, y, -z);

	::glNormal3f(-nx, ny, nz);
	::glVertex3f(-x, y, z);
	::glNormal3f(-nx, ny, -nz);
	::glVertex3f(-x, y, -z);
	::glNormal3f(-nx, -ny, -nz);
	::glVertex3f(-x, -y, -z);
	::glNormal3f(-nx, -ny, nz);
	::glVertex3f(-x, -y, z);

	::glNormal3f(nx, ny, nz);
	::glVertex3f(x, y, z);
	::glNormal3f(nx, ny, -nz);
	::glVertex3f(x, y, -z);
	::glNormal3f(-nx, ny, -nz);
	::glVertex3f(-x, y, -z);
	::glNormal3f(-nx, ny, nz);
	::glVertex3f(-x, y, z);

	::glNormal3f(nx, -ny, nz);
	::glVertex3f(x, -y, z);
	::glNormal3f(-nx, -ny, nz);
	::glVertex3f(-x, -y, z);
	::glNormal3f(-nx, -ny, -nz);
	::glVertex3f(-x, -y, -z);
	::glNormal3f(nx, -ny, -nz);
	::glVertex3f(x, -y, -z);

	::glNormal3f(nx, ny, nz);
	::glVertex3f(x, y, z);
	::glNormal3f(-nx, ny, nz);
	::glVertex3f(-x, y, z);
	::glNormal3f(-nx, -ny, nz);
	::glVertex3f(-x, -y, z);
	::glNormal3f(nx, -ny, nz);
	::glVertex3f(x, -y, z);

	::glNormal3f(nx, ny, -nz);
	::glVertex3f(x, y, -z);
	::glNormal3f(nx, -ny, -nz);
	::glVertex3f(x, -y, -z);
	::glNormal3f(-nx, -ny, -nz);
	::glVertex3f(-x, -y, -z);
	::glNormal3f(-nx, ny, -nz);
	::glVertex3f(-x, y, -z);

	::glEnd();

	::glPopMatrix();
}

void OpenGLCanvas::OnMouseEvent(wxMouseEvent& event)
{
	if(event.ButtonDown(wxMOUSE_BTN_RIGHT)
			|| event.ButtonDown(wxMOUSE_BTN_MIDDLE)){
		x = event.m_x;
		y = event.m_y;
	}
	if(event.Dragging() && event.RightIsDown()){
		rotmat = AffineTransformMatrix::RotateXY(event.m_x - x, event.m_y - y,
				0.5) * rotmat;
		x = event.m_x;
		y = event.m_y;

		this->Refresh();
	}

	if(event.Dragging() && event.MiddleIsDown()){
		float dx = (float) (event.m_x - x) / 1000.0;
		float dy = (float) (event.m_y - y) / 1000.0;
		transmat.TranslateGlobal(dx, -dy, 0);
		x = event.m_x;
		y = event.m_y;

		this->Refresh();
	}

	int x = event.GetWheelRotation();
	if(x != 0){
		transmat.TranslateGlobal(0, 0, (float) -x / 1000.0);
		this->Refresh();
	}

}

void OpenGLCanvas::OnTimer(wxTimerEvent& event)
{

}

