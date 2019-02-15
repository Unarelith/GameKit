/*
 * =====================================================================================
 *
 *       Filename:  Tiletilemap.cpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 19:18:26
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>

#include "gk/graphics/Tilemap.hpp"
#include "gk/resource/ResourceHandler.hpp"

namespace gk {

Tilemap::Tilemap(u16 width, u16 height, Tileset &tileset, const std::vector<u16> &data) : m_tileset(tileset) {
	m_width = width;
	m_height = height;

	m_baseData = data;
	m_data = m_baseData;

	setPosition(0, 16);

	m_animator.init(*this);
	m_renderer.init(this, m_width, m_height);

	updateTiles();
}

void Tilemap::reset() {
	m_data = m_baseData;
}

void Tilemap::update() {
	m_animator.animateTiles(*this);
}

void Tilemap::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_renderer, states);
}

void Tilemap::updateTiles() {
	for(u16 tileY = 0 ; tileY < m_height ; tileY++) {
		for(u16 tileX = 0 ; tileX < m_width ; tileX++) {
			u16 tileID = getTile(tileX, tileY);

			m_renderer.updateTile(tileX, tileY, tileID, *this);
		}
	}
}

u16 Tilemap::getTile(u16 tileX, u16 tileY) {
	if(tileX + tileY * m_width < m_width * m_height) {
		return m_data[tileX + tileY * m_width];
	} else {
		return 0;
	}
}

void Tilemap::setTile(u16 tileX, u16 tileY, u16 id, bool write, bool persistent) {
	if(write && tileX + tileY * m_width < m_width * m_height) {
		m_data[tileX + tileY * m_width] = id;

		if (persistent) m_baseData[tileX + tileY * m_width] = id;
	}

	m_renderer.updateTile(tileX, tileY, id, *this);
}

} // namespace gk

