/*
 * =====================================================================================
 *
 *       Filename:  TilemapAnimator.cpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 19:20:46
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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

