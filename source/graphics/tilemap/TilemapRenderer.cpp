/*
 * =====================================================================================
 *
 *       Filename:  TilemapRenderer.cpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 19:21:11
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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

	gk::VertexBuffer::bind(&m_vbo);
	m_vbo.setData(sizeof(gk::Vertex) * mapWidth * mapHeight * mapLayers * 6, nullptr, GL_DYNAMIC_DRAW);
	gk::VertexBuffer::bind(nullptr);
}

void TilemapRenderer::updateTile(u8 layer, u16 tileX, u16 tileY, u16 id, Tilemap &map) {
	if (id == 0) return;

	gk::VertexBuffer::bind(&m_vbo);

	float tileWidth  = map.tileset().tileWidth();
	float tileHeight = map.tileset().tileHeight();

	float x = tileX * tileWidth;
	float y = tileY * tileHeight;

	float texTileX = id % u16(map.tileset().getSize().x / tileWidth) * tileWidth  / map.tileset().getSize().x;
	float texTileY = id / u16(map.tileset().getSize().y / tileWidth) * tileHeight / map.tileset().getSize().y;

	float texTileWidth  = tileWidth  / map.tileset().getSize().x;
	float texTileHeight = tileHeight / map.tileset().getSize().y;

	gk::Vertex vertices[] = {
		{{x            , y             , 0, 1}, {texTileX               , texTileY                }, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x + tileWidth, y             , 0, 1}, {texTileX + texTileWidth, texTileY                }, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x + tileWidth, y + tileHeight, 0, 1}, {texTileX + texTileWidth, texTileY + texTileHeight}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x            , y             , 0, 1}, {texTileX               , texTileY                }, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x + tileWidth, y + tileHeight, 0, 1}, {texTileX + texTileWidth, texTileY + texTileHeight}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{x            , y + tileHeight, 0, 1}, {texTileX               , texTileY + texTileHeight}, {1.0f, 1.0f, 1.0f, 1.0f}}
	};

	m_vbo.updateData(sizeof(vertices) * (tileX + tileY * map.width() + layer * map.width() * map.height()), sizeof(vertices), vertices);

	gk::VertexBuffer::bind(nullptr);
}

void TilemapRenderer::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	if (!m_map) return;

	states.texture = &m_map->tileset();
	states.vertexAttributes = VertexAttribute::Only2d;

	glCheck(glDisable(GL_CULL_FACE));
	glCheck(glDisable(GL_DEPTH_TEST));

	for (u8 i = 0 ; i < m_map->layerCount() ; ++i) {
		target.draw(m_vbo, GL_TRIANGLES,
			(6 * m_map->width() * m_map->height()) * (m_map->layerCount() - 1 - i),
			6 * m_map->width() * m_map->height(), states);
	}
}

} // namespace gk

