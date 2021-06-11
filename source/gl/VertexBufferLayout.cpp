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
#include "gk/gl/RenderStates.hpp"
#include "gk/gl/Vertex.hpp"
#include "gk/gl/VertexBufferLayout.hpp"

namespace gk {

void VertexBufferLayout::setupDefaultLayout() {
	addAttribute(0, "coord3d", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, coord3d)));
	addAttribute(1, "texCoord", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, texCoord)));
	addAttribute(2, "color", 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid *>(offsetof(Vertex, color)));
}

void VertexBufferLayout::enableLayout() const {
	for (auto &attr : m_attributes) {
		glCheck(glEnableVertexAttribArray(attr.id));
		glCheck(glVertexAttribPointer(attr.id, attr.size, attr.type, attr.normalized, attr.stride, attr.offset));
	}
}

void VertexBufferLayout::disableLayout() const {
	for (auto &attr : m_attributes)
		glCheck(glDisableVertexAttribArray(attr.id));
}

} // namespace gk

