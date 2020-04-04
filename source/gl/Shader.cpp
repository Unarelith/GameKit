/*
 * =====================================================================================
 *
 *  GameKit
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2020 the GameKit contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of GameKit.
 *
 *  GameKit is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  GameKit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with GameKit; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

#include "gk/gl/GLCheck.hpp"
#include "gk/gl/Shader.hpp"
#include "gk/gl/Transform.hpp"
#include "gk/core/Exception.hpp"

namespace gk {

const Shader *Shader::s_boundShader = nullptr;

Shader::Shader(const std::string &vertexFilename, const std::string &fragmentFilename) {
	loadFromFile(vertexFilename, fragmentFilename);
}

Shader::~Shader() {
	while(m_vertexShaders.size() != 0) {
		glCheck(glDeleteShader(m_vertexShaders.back()));
		m_vertexShaders.pop_back();
	}

	while(m_fragmentShaders.size() != 0) {
		glCheck(glDeleteShader(m_fragmentShaders.back()));
		m_fragmentShaders.pop_back();
	}

	glCheck(glDeleteProgram(m_program));
}

void Shader::loadFromFile(const std::string &vertexFilename, const std::string &fragmentFilename) {
	createProgram();

	addShader(GL_VERTEX_SHADER, vertexFilename);
	addShader(GL_FRAGMENT_SHADER, fragmentFilename);

	linkProgram();
}

void Shader::createProgram() {
	glCheck(m_program = glCreateProgram());

	defaultAttributeLocationBinding();
}

void Shader::linkProgram() {
	glCheck(glLinkProgram(m_program));

	GLint linkOK = GL_FALSE;
	glCheck(glGetProgramiv(m_program, GL_LINK_STATUS, &linkOK));
	if(!linkOK){
		GLint errorSize = 0;
		glCheck(glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &errorSize));

		char *errorMsg = new char[errorSize + 1];

		glCheck(glGetProgramInfoLog(m_program, errorSize, &errorSize, errorMsg));
		errorMsg[errorSize] = '\0';

		std::string error = std::string(errorMsg);

		delete[] errorMsg;
		glCheck(glDeleteProgram(m_program));

		throw EXCEPTION("Program", m_program, "link failed:", error);
	}
}

void Shader::bindAttributeLocation(GLuint index, const std::string &name) {
	if (attrib(name) == -1) {
		glCheck(glBindAttribLocation(m_program, index, name.c_str()));

		m_attributes.emplace(name, index);
	}
}

void Shader::defaultAttributeLocationBinding() {
	bindAttributeLocation(0, "coord3d");
	bindAttributeLocation(1, "texCoord");
	bindAttributeLocation(2, "color");
	bindAttributeLocation(3, "normal");
	bindAttributeLocation(4, "lightValue");
	bindAttributeLocation(5, "ambientOcclusion");
}

void Shader::addShader(GLenum type, const std::string &filename) {
	GLuint shader;
	glCheck(shader = glCreateShader(type));

	if(type == GL_VERTEX_SHADER) {
		m_vertexShaders.push_back(shader);
	} else {
		m_fragmentShaders.push_back(shader);
	}

	std::ifstream file(filename);
	if(!file) {
		glCheck(glDeleteShader(shader));

		throw EXCEPTION("Failed to open", filename);
	}

	std::string line;
	std::string sourceCode;

	while(getline(file, line)) sourceCode += line + '\n';
	file.close();

	const GLchar *sourceCodeString = sourceCode.c_str();

	glCheck(glShaderSource(shader, 1, &sourceCodeString, nullptr));

	glCheck(glCompileShader(shader));

	GLint compileOK = GL_FALSE;
	glCheck(glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOK));
	if(!compileOK) {
		GLint errorSize = 0;
		glCheck(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize));

		char *errorMsg = new char[errorSize + 1];

		glCheck(glGetShaderInfoLog(shader, errorSize, &errorSize, errorMsg));
		errorMsg[errorSize] = '\0';

		std::string error = std::string(errorMsg);

		delete[] errorMsg;
		glCheck(glDeleteShader(shader));

		throw EXCEPTION("Shader", filename, "compilation failed:", error);
	}

	glCheck(glAttachShader(m_program, shader));
}

GLint Shader::attrib(const std::string &name) const {
	auto it = m_attributes.find(name);
	if (it == m_attributes.end())
		return -1;

	return it->second;
}

GLint Shader::uniform(const std::string &name) const {
	GLint uniform;
	glCheck(uniform = glGetUniformLocation(m_program, name.c_str()));

	if(uniform == -1) {
		gkDebug() << "Could not bind uniform:" << name;
	}

	return uniform;
}

void Shader::enableVertexAttribArray(const std::string &name) const {
	glCheck(glEnableVertexAttribArray(attrib(name)));
}

void Shader::disableVertexAttribArray(const std::string &name) const {
	glCheck(glDisableVertexAttribArray(attrib(name)));
}

void Shader::setUniform(const std::string &name, int n) const {
	glCheck(glUniform1i(uniform(name), n));
}

void Shader::setUniform(const std::string &name, float x, float y) const {
	glCheck(glUniform2f(uniform(name), x, y));
}

void Shader::setUniform(const std::string &name, const gk::Color &color) const {
	glCheck(glUniform4f(uniform(name), color.r, color.g, color.b, color.a));
}

void Shader::setUniform(const std::string &name, const glm::mat4 &matrix) const {
	glCheck(glUniformMatrix4fv(uniform(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

void Shader::setUniform(const std::string &name, const Transform &transform) const {
	glCheck(glUniformMatrix4fv(uniform(name), 1, GL_FALSE, transform.getRawMatrix()));
}

void Shader::bind(const Shader *shader) {
	if (shader != s_boundShader) {
		glCheck(glUseProgram((shader) ? shader->m_program : 0));
		s_boundShader = shader;
	}
}

} // namespace gk

