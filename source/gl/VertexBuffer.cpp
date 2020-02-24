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
#include "gk/gl/GLCheck.hpp"
#include "gk/gl/VertexBuffer.hpp"

namespace gk {

VertexBuffer::VertexBuffer() {
	glCheck(glGenBuffers(1, &m_id));
}

VertexBuffer::VertexBuffer(VertexBuffer &&vertexBuffer) {
	m_id = vertexBuffer.m_id;
	vertexBuffer.m_id = 0;
}

VertexBuffer::~VertexBuffer() noexcept {
	glCheck(glDeleteBuffers(1, &m_id));
}

void VertexBuffer::setData(GLsizeiptr size, const GLvoid *data, GLenum usage) const {
	glCheck(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

void VertexBuffer::updateData(GLintptr offset, GLsizeiptr size, const GLvoid *data) const {
	glCheck(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void VertexBuffer::setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) const {
	glCheck(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
}

void VertexBuffer::bind(const VertexBuffer *vertexBuffer) {
	if(vertexBuffer) {
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->m_id));
	} else {
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}

} // namespace gk

