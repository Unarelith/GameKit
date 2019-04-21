/*
 * =====================================================================================
 *
 *       Filename:  TiledImage.hpp
 *
 *    Description:
 *
 *        Created:  20/04/2019 14:35:46
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TILEDIMAGE_HPP_
#define GK_TILEDIMAGE_HPP_

#include <vector>

#include "gk/graphics/Image.hpp"

namespace gk {

class TiledImage : public Drawable, public Transformable {
	public:
		TiledImage() = default;
		TiledImage(const std::string &textureName);

		void load(const std::string &textureName);

		void setTile(u16 id, float x, float y, u16 width, u16 height, float clipX, float clipY, u16 clipWidth, u16 clipHeight, const gk::Color &color = gk::Color::White);
		void setTilePosRect(u16 id, float x, float y, u16 width, u16 height);
		void setTileClipRect(u16 id, float x, float y, u16 clipWidth, u16 clipHeight);
		void setTileColor(u16 id, const gk::Color &color);

		void setTileCount(u16 tileCount);

	protected:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

	private:
		std::vector<Image> m_tiles;

		std::string m_textureName;
};

} // namespace gk

#endif // GK_TILEDIMAGE_HPP_
