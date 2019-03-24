/*
 * =====================================================================================
 *
 *       Filename:  Tilemap.hpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 19:17:12
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TILEMAP_HPP_
#define GK_TILEMAP_HPP_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "gk/graphics/tilemap/TilemapAnimator.hpp"
#include "gk/graphics/tilemap/TilemapRenderer.hpp"
#include "gk/graphics/Tileset.hpp"

namespace gk {

class Tilemap : public sf::Drawable, public sf::Transformable {
	public:
		Tilemap(u16 width, u16 height, Tileset &tileset, const std::vector<std::vector<u16>> &data);

		void reset();

		void update();

		void updateTiles();

		u16 getTile(u16 tileX, u16 tileY, u8 layer = 0);
		void setTile(u16 tileX, u16 tileY, u16 id, bool write = true, bool persistent = false);

		u16 width() const { return m_width; }
		u16 height() const { return m_height; }

		u8 layerCount() const { return m_data.size(); }

		Tileset &tileset() { return m_tileset; }
		void setTilesetOffset(u16 tilesetOffset) { m_tilesetOffset = tilesetOffset; }

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		Tileset &m_tileset;

	private:
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
