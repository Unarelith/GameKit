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
#include "gk/gl/Vertex.hpp"
#include "gk/graphics/BoxShape.hpp"

namespace gk {

void BoxShape::updateVertexBuffer() const {
	constexpr u8f cubeVerts[6][4]{
		// Vertex numbers are encoded according to their binary digits,
		// where bit 0 is X, bit 1 is Y and bit 2 is Z.
		// ZYX    ZYX    ZYX    ZYX
		{0b010, 0b000, 0b100, 0b110},  // West
		{0b001, 0b011, 0b111, 0b101},  // East
		{0b000, 0b001, 0b101, 0b100},  // South
		{0b011, 0b010, 0b110, 0b111},  // North
		{0b010, 0b011, 0b001, 0b000},  // Bottom
		{0b100, 0b101, 0b111, 0b110},  // Top
	};

	u8f vertexPos[6 * 4][3] {
		// Order is important. It matches the bit order defined in cubeVerts.
		{0, 0, 0},
		{1, 0, 0},
		{0, 1, 0},
		{1, 1, 0},
		{0, 0, 1},
		{1, 0, 1},
		{0, 1, 1},
		{1, 1, 1},
	};

	Vertex vertices[6][4];
	for (u8 f = 0; f < 6; ++f) {
		for (u8f v = 0; v < 4; ++v) {
			vertices[f][v].coord3d[0] = vertexPos[cubeVerts[f][v]][0] * m_size.x;
			vertices[f][v].coord3d[1] = vertexPos[cubeVerts[f][v]][1] * m_size.y;
			vertices[f][v].coord3d[2] = vertexPos[cubeVerts[f][v]][2] * m_size.z;
			vertices[f][v].coord3d[3] = f;

			vertices[f][v].color[0] = m_color.r;
			vertices[f][v].color[1] = m_color.g;
			vertices[f][v].color[2] = m_color.b;
			vertices[f][v].color[3] = m_color.a;
		}
	}

	gk::VertexBuffer::bind(&m_vbo);
	m_vbo.setData(sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	gk::VertexBuffer::bind(nullptr);

	m_isVboInitialized = true;
}

void BoxShape::draw(RenderTarget &target, RenderStates states) const {
	if (!m_isVboInitialized) updateVertexBuffer();

	states.texture = nullptr;
	states.transform *= getTransform();
	states.vertexAttributes = VertexAttribute::All;

	glCheck(glEnable(GL_CULL_FACE));
	glCheck(glEnable(GL_DEPTH_TEST));

	target.draw(m_vbo, GL_QUADS, 0, 6 * 4, states);

	glCheck(glDisable(GL_CULL_FACE));
	glCheck(glDisable(GL_DEPTH_TEST));
}

} // namespace gk

