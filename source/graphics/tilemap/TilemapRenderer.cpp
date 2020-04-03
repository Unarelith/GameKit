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
#include "gk/gl/Shader.hpp"
#include "gk/gl/Vertex.hpp"
#include "gk/graphics/tilemap/TilemapRenderer.hpp"
#include "gk/graphics/Tilemap.hpp"

namespace gk {

void TilemapRenderer::init(Tilemap *map, u16 mapWidth, u16 mapHeight, u8 mapLayers) {
	m_map = map;

	VertexBuffer::bind(&m_vbo);
	m_vbo.setData(sizeof(Vertex) * mapWidth * mapHeight * mapLayers * 6, nullptr, GL_DYNAMIC_DRAW);
	VertexBuffer::bind(nullptr);
}

void TilemapRenderer::updateTile(u8 layer, u16 tileX, u16 tileY, u16 id, Tilemap &map) {
	if (id == 0) return;

	VertexBuffer::bind(&m_vbo);

	float tileWidth  = map.tileset().tileWidth();
	float tileHeight = map.tileset().tileHeight();

	float x = tileX * tileWidth;
	float y = tileY * tileHeight;

	float texTileX = id % u16(map.tileset().getSize().x / tileWidth) * tileWidth  / map.tileset().getSize().x;
	float texTileY = id / u16(map.tileset().getSize().x / tileWidth) * tileHeight / map.tileset().getSize().y;

	float texTileWidth  = tileWidth  / map.tileset().getSize().x;
	float texTileHeight = tileHeight / map.tileset().getSize().y;

	Vertex vertices[] = {
		{{x            , y             , 0, 1}, {texTileX               , texTileY                }, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x + tileWidth, y             , 0, 1}, {texTileX + texTileWidth, texTileY                }, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x + tileWidth, y + tileHeight, 0, 1}, {texTileX + texTileWidth, texTileY + texTileHeight}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x            , y             , 0, 1}, {texTileX               , texTileY                }, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x + tileWidth, y + tileHeight, 0, 1}, {texTileX + texTileWidth, texTileY + texTileHeight}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x            , y + tileHeight, 0, 1}, {texTileX               , texTileY + texTileHeight}, {1.0f, 1.0f, 1.0f, 1.0f}}
	};

	m_vbo.updateData(sizeof(vertices) * (tileX + tileY * map.width() + layer * map.width() * map.height()), sizeof(vertices), vertices);

	VertexBuffer::bind(nullptr);
}

void TilemapRenderer::draw(RenderTarget &target, RenderStates states) const {
	if (!m_map) return;

	states.texture = &m_map->tileset();
	states.vertexAttributes = VertexAttribute::All;

	glCheck(glDisable(GL_CULL_FACE));
	glCheck(glDisable(GL_DEPTH_TEST));

	for (u8 i = 0 ; i < m_map->layerCount() ; ++i) {
		target.draw(m_vbo, GL_TRIANGLES,
			(6 * m_map->width() * m_map->height()) * (m_map->layerCount() - 1 - i),
			6 * m_map->width() * m_map->height(), states);
	}
}

} // namespace gk

