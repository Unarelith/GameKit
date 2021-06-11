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
#include "gk/gl/VertexArray.hpp"

namespace gk {

VertexArray::VertexArray() {
	glCheck(glGenVertexArrays(1, &m_id));
}

VertexArray::VertexArray(VertexArray &&vertexArray) {
	m_id = vertexArray.m_id;
	vertexArray.m_id = 0;
}

VertexArray::~VertexArray() noexcept {
	if (m_id != 0)
		glCheck(glDeleteVertexArrays(1, &m_id));
}

VertexArray &VertexArray::operator=(VertexArray &&vertexArray) {
	m_id = vertexArray.m_id;
	vertexArray.m_id = 0;

	return *this;
}

void VertexArray::bind(const VertexArray *vertexArray) {
	if(vertexArray) {
		glCheck(glBindVertexArray(vertexArray->m_id));
	} else {
		glCheck(glBindVertexArray(0));
	}
}

} // namespace gk

