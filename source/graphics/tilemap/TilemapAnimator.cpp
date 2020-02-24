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
#include "gk/graphics/tilemap/TilemapAnimator.hpp"
#include "gk/graphics/Tilemap.hpp"

namespace gk {

void TilemapAnimator::init(Tilemap &map) {
	m_tileAnimations.assign(map.width() * map.height(), {});
}

void TilemapAnimator::animateTiles(Tilemap &map) {
	for (size_t x = 0 ; x < map.width() ; ++x) {
		for (size_t y = 0 ; y < map.height() ; ++y) {
			const Tile &tile = map.tileset().getTile(map.getTile(x, y));
			if (tile.getFrameCount()) {
				TileAnimation &tileAnimation = m_tileAnimations.at(x + y * map.width());
				if (!tileAnimation.timer.isStarted())
					tileAnimation.timer.start();

				if (tileAnimation.timer.time() > tile.getFrame(tileAnimation.currentFrame).duration) {
					tileAnimation.currentFrame++;
					tileAnimation.currentFrame %= tile.getFrameCount();

					map.setTile(x, y, tile.getFrame(tileAnimation.currentFrame).tileID, false);

					tileAnimation.timer.reset();
					tileAnimation.timer.start();
				}
			}
		}
	}
}

} // namespace gk

