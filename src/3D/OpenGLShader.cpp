///////////////////////////////////////////////////////////////////////////////
// Name               : OpenGLShader.cpp
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

#define GL_GLEXT_PROTOTYPES
#ifdef __WXMAC__
//#include "OpenGL/gl.h"
#include "OpenGL/glext.h"
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include "OpenGLShader.h"
#include <iostream>

OpenGLShader::OpenGLShader()
{
	program = 0;
	showErrors = true;
}

OpenGLShader::~OpenGLShader()
{
	Reset();
}

void OpenGLShader::Reset()
{
	glDeleteProgram(program);
	program = 0;

	for(std::map <GLenum, GLuint>::iterator it = shader.begin();
			it != shader.end(); ++it)
		glDeleteShader(it->second);
	shader.clear();
}

bool OpenGLShader::AddShader(GLenum type, const std::string& program)
{
	GLuint shadernum = 0;
	if(shader.find(type) == shader.end()){
		shadernum = glCreateShader(type);
		shader[type] = shadernum;
	}else{
		shadernum = shader[type];
	}
	const GLchar* temp[] = {program.c_str()};
	glShaderSource(shadernum, 1, temp, NULL);
	glCompileShader(shadernum);

	GLint success;
	glGetShaderiv(shadernum, GL_COMPILE_STATUS, &success);

	if(!success){
		GLchar txt[512];
		glGetShaderInfoLog(shadernum, 512, NULL, txt);
		if(showErrors){
			std::cout << "Error while compiling shader:" << '\n';
			std::cout << txt << '\n';
			std::cout << std::endl;
		}
		return false;
	}
	return true;
}

bool OpenGLShader::LinkShader(void)
{
	glDeleteProgram(program);
	program = glCreateProgram();

	for(std::map <GLenum, GLuint>::iterator it = shader.begin();
			it != shader.end(); ++it)
		glAttachShader(program, it->second);

	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if(!success){
		GLchar info[512];
		glGetProgramInfoLog(program, 512, NULL, info);
		if(showErrors){
			std::cout << "Error while linking shader program:" << '\n';
			std::cout << info << '\n';
			std::cout << std::endl;
		}
		glDeleteProgram(program);
		program = 0;
		return false;
	}
	return true;
}

bool OpenGLShader::Start(void)
{
	if(program == 0) return false;
	glUseProgram(program);
	return true;
}

void OpenGLShader::Stop(void)
{
	glUseProgram(0);
}

bool OpenGLShader::SetUniformBool(const std::string& name,
		const GLboolean x) const
{
	if(program == 0) return false;
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform1i(location, x? -1 : 0);
	return true;
}

bool OpenGLShader::SetUniformInt(const std::string& name, const GLint x) const
{
	if(program == 0) return false;
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform1i(location, x);
	return true;
}

bool OpenGLShader::SetUniform(const std::string& name, const Vector3 x) const
{
	if(program == 0) return false;
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform3f(location, x.x, x.y, x.z);
	return true;
}

bool OpenGLShader::SetUniform(const std::string& name, const GLfloat x) const
{
	if(program == 0) return false;
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform1f(location, x);
	return true;
}

bool OpenGLShader::SetUniform(const std::string& name, const GLfloat x,
		const GLfloat y) const
{
	if(program == 0) return false;
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform2f(location, x, y);
	return true;
}

bool OpenGLShader::SetUniform(const std::string& name, const GLfloat x,
		const GLfloat y, const GLfloat z) const
{
	if(program == 0) return false;
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform3f(location, x, y, z);
	return true;
}

bool OpenGLShader::SetUniform(const std::string& name, const GLfloat x,
		const GLfloat y, const GLfloat z, const GLfloat w) const
{
	if(program == 0) return false;
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform4f(location, x, y, z, w);
	return true;
}

bool OpenGLShader::SetUniformMatrix(const std::string& name, const GLfloat* M,
		size_t size) const
{
	if(program == 0) return false;
	GLint location = glGetUniformLocation(program, name.c_str());
	switch(size){
	case 4:
		glUniformMatrix2fv(location, 1, GL_FALSE, M);
		break;
	case 9:
		glUniformMatrix3fv(location, 1, GL_FALSE, M);
		break;
	case 16:
		glUniformMatrix4fv(location, 1, GL_FALSE, M);
		break;
	default:
		return false;
	}
	return true;
}

GLint OpenGLShader::GetUniformLocation(const std::string& name) const
{
	if(program == 0) return -1;
	return glGetUniformLocation(program, name.c_str());
}

