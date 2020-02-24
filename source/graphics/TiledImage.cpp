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
#include "gk/graphics/TiledImage.hpp"

namespace gk {

TiledImage::TiledImage(const std::string &textureName) {
	load(textureName);
}

void TiledImage::load(const std::string &textureName) {
	m_textureName = textureName;
}

void TiledImage::setTile(u16 id, float x, float y, u16 width, u16 height, float clipX, float clipY, u16 clipWidth, u16 clipHeight, const gk::Color &color) {
	auto &tile = m_tiles.at(id);
	tile.setClipRect(clipX, clipY, clipWidth, clipHeight);
	tile.setPosRect(x, y, width, height);
	tile.setColor(color);
}

void TiledImage::setTilePosRect(u16 id, float x, float y, u16 width, u16 height) {
	m_tiles.at(id).setPosRect(x, y, width, height);
}

void TiledImage::setTileClipRect(u16 id, float x, float y, u16 clipWidth, u16 clipHeight) {
	m_tiles.at(id).setClipRect(x, y, clipWidth, clipHeight);
}

void TiledImage::setTileColor(u16 id, const gk::Color &color) {
	m_tiles.at(id).setColor(color);
}

void TiledImage::setTileCount(u16 tileCount) {
	m_tiles.resize(tileCount);

	for (auto &it : m_tiles)
		it.load(m_textureName);
}

void TiledImage::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	states.transform *= getTransform();

	for (auto &it : m_tiles)
		target.draw(it, states);
}

} // namespace gk

