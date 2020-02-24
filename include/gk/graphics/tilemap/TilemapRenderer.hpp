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
#ifndef GK_TILEMAPRENDERER_HPP_
#define GK_TILEMAPRENDERER_HPP_

#include "gk/gl/Drawable.hpp"
#include "gk/gl/VertexBuffer.hpp"
#include "gk/graphics/Tileset.hpp"

namespace gk {

class Tilemap;

class TilemapRenderer : public Drawable {
	public:
		void init(Tilemap *map, u16 mapWidth, u16 mapHeight, u8 mapLayers);

		void updateTile(u8 layer, u16 tileX, u16 tileY, u16 id, Tilemap &map);

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		VertexBuffer m_vbo;

		Tilemap *m_map = nullptr;
};

} // namespace gk

#endif // GK_TILEMAPRENDERER_HPP_
