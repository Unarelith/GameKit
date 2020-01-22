/*
 * =====================================================================================
 *
 *       Filename:  Shader.cpp
 *
 *    Description:
 *
 *        Created:  15/12/2014 16:30:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
	GLint attrib;
	glCheck(attrib = glGetAttribLocation(m_program, name.c_str()));

	if(attrib == -1) {
		DEBUG("Could not bind attribute:", name);
	}

	return attrib;
}

GLint Shader::uniform(const std::string &name) const {
	GLint uniform;
	glCheck(uniform = glGetUniformLocation(m_program, name.c_str()));

	if(uniform == -1) {
		DEBUG("Could not bind uniform:", name);
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

void Shader::setUniform(const std::string &name, const glm::mat4 &matrix) const {
	glCheck(glUniformMatrix4fv(uniform(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

void Shader::setUniform(const std::string &name, const Transform &transform) const {
	glCheck(glUniformMatrix4fv(uniform(name), 1, GL_FALSE, transform.getRawMatrix()));
}

void Shader::bind(const Shader *shader) {
	if(shader) {
		glCheck(glUseProgram(shader->m_program));
	} else {
		glCheck(glUseProgram(0));
	}
}

} // namespace gk
