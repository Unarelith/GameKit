/*
 * =====================================================================================
 *
 *       Filename:  VertexArray.cpp
 *
 *    Description:
 *
 *        Created:  06/01/2020 19:18:42
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/core/Exception.hpp"
#include "gk/gl/GLCheck.hpp"
#include "gk/gl/VertexArray.hpp"

namespace gk {

GLuint VertexArray::boundBuffer = 0;

VertexArray::VertexArray(VertexArray &&vertexArray) {
	m_id = vertexArray.m_id;
	vertexArray.m_id = 0;
}

VertexArray::~VertexArray() noexcept {
	if (m_id != 0)
		glCheck(glDeleteVertexArrays(1, &m_id));
}

void VertexArray::init() {
	glCheck(glGenVertexArrays(1, &m_id));
}

void VertexArray::addVertexAttribute(const Shader &shader, const std::string &name, GLint size,
		GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
	m_attributes.emplace(name, VertexAttribute{shader.attrib(name), size, type, normalized, stride, pointer});
}

void VertexArray::enableVertexAttribArray(const std::string &name) const {
	auto it = m_attributes.find(name);
	if (it != m_attributes.end()) {
		glCheck(glEnableVertexAttribArray(it->second.index));
	}
	else {
		throw EXCEPTION("Cannot enable attribute '" + name + "': not found");
	}
}

void VertexArray::disableVertexAttribArray(const std::string &name) const {
	auto it = m_attributes.find(name);
	if (it != m_attributes.end()) {
		glCheck(glDisableVertexAttribArray(it->second.index));
	}
	else {
		throw EXCEPTION("Cannot disable attribute '" + name + "': not found");
	}
}

void VertexArray::setupVertexAttribute(const std::string &name) const {
	auto it = m_attributes.find(name);
	if (it != m_attributes.end()) {
		glCheck(glVertexAttribPointer(it->second.index, it->second.size, it->second.type,
				it->second.normalized, it->second.stride, it->second.pointer));
	}
	else {
		throw EXCEPTION("Cannot setup attribute '" + name + "': not found");
	}
}

void VertexArray::bind(const VertexArray *vertexArray) {
	if (!vertexArray || boundBuffer != vertexArray->m_id) {
		if(vertexArray) {
			glCheck(glBindVertexArray(vertexArray->m_id));

			boundBuffer = vertexArray->m_id;
		} else {
			glCheck(glBindVertexArray(0));
		}
	}
}

} // namespace gk

