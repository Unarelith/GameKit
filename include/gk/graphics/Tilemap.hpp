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
#ifndef GK_TILEMAP_HPP_
#define GK_TILEMAP_HPP_

#include "gk/gl/Transformable.hpp"
#include "gk/graphics/tilemap/TilemapAnimator.hpp"
#include "gk/graphics/tilemap/TilemapRenderer.hpp"
#include "gk/graphics/Tileset.hpp"

namespace gk {

class Tilemap : public Drawable, public Transformable {
	public:
		Tilemap(u16 width, u16 height, Tileset &tileset, const std::vector<std::vector<u16>> &data);

		void reset();

		void update();

		void updateTiles();

		u16 getTile(u16 tileX, u16 tileY, u8 layer = 0);
		void setTile(u16 tileX, u16 tileY, u16 id, bool write = true, bool persistent = false);

		bool inTile(float x, float y, u16 tileID);

		u16 width() const { return m_width; }
		u16 height() const { return m_height; }

		u8 layerCount() const { return m_data.size(); }

		Tileset &tileset() { return m_tileset; }
		void setTilesetOffset(u16 tilesetOffset) { m_tilesetOffset = tilesetOffset; }

	protected:
		void draw(RenderTarget &target, RenderStates states) const override;

	private:
		Tileset &m_tileset;
		u16 m_tilesetOffset = 0; // FIXME

		u16 m_width = 0;
		u16 m_height = 0;

		std::vector<std::vector<u16>> m_baseData;
		std::vector<std::vector<u16>> m_data;

		TilemapAnimator m_animator;
		TilemapRenderer m_renderer;
};

} // namespace gk

#endif // GK_TILEMAP_HPP_
