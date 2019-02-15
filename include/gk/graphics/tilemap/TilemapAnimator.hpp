/*
 * =====================================================================================
 *
 *       Filename:  TilemapAnimator.hpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 19:20:31
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TILEMAPANIMATOR_HPP_
#define GK_TILEMAPANIMATOR_HPP_

#include "gk/core/Timer.hpp"
#include "gk/graphics/Tileset.hpp"

namespace gk {

class Tilemap;

class TilemapAnimator {
	public:
		void init(Tilemap &map);

		void animateTiles(Tilemap &map);

	private:
		struct TileAnimation {
			Timer timer;
			u16 currentFrame = 0;
		};

		std::vector<TileAnimation> m_tileAnimations;
};

} // namespace gk

#endif // GK_TILEMAPANIMATOR_HPP_
