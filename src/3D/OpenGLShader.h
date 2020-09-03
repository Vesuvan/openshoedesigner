///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLShader.h
// Purpose            : 
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 01.04.2019
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

#ifndef SRC_3D_OPENGLSHADER_H_
#define SRC_3D_OPENGLSHADER_H_

/*!\class OpenGLShader
 * \brief Contains shaders and the compiled shader program
 * \ingroup View3D
 *
 * Function to add several shaders together to a shaderprogramm.
 */

#include <GL/gl.h>
#include <map>
#include <string>
#include "Vector3.h"

class OpenGLShader {
public:
	OpenGLShader();
	virtual ~OpenGLShader();

	void Reset();
	bool AddShader(GLenum type, const std::string &program);
	bool LinkShader(void);

	bool SetUniformBool(const std::string &name, const GLboolean x) const;
	bool SetUniformInt(const std::string &name, const GLint x) const;
	bool SetUniform(const std::string &name, const Vector3 & x) const;
	bool SetUniform(const std::string &name, const GLfloat x) const;
	bool SetUniform(const std::string &name, const GLfloat x,
			const GLfloat y) const;
	bool SetUniform(const std::string &name, const GLfloat x, const GLfloat y,
			const GLfloat z) const;
	bool SetUniform(const std::string &name, const GLfloat x, const GLfloat y,
			const GLfloat z, const GLfloat w) const;

	bool SetUniformMatrix(const std::string &name, const GLfloat *M,
			size_t size) const;

	GLint GetUniformLocation(const std::string &name) const;

	bool Start(void);
	static void Stop(void);

private:
	std::map <GLenum, GLuint> shader;
	GLuint program;
	bool showErrors;
};

#endif /* SRC_3D_OPENGLSHADER_H_ */
