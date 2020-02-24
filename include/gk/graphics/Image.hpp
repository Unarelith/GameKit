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
#ifndef GK_IMAGE_HPP_
#define GK_IMAGE_HPP_

#include "gk/graphics/Color.hpp"
#include "gk/core/Rect.hpp"
#include "gk/gl/Drawable.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/gl/VertexBuffer.hpp"

namespace gk {

class Image : public Drawable, public Transformable {
	public:
		Image() = default;
		Image(const std::string &textureName);
		Image(const Texture &texture);

		void load(const Image &image);
		void load(const std::string &textureName);
		void load(const Texture &texture);

		void setTexture(const std::string &textureName);

		const FloatRect &clipRect() const { return m_clipRect; }
		void setClipRect(float x, float y, u16 width, u16 height);

		const FloatRect &posRect() const { return m_posRect; }
		void setPosRect(float x, float y, u16 width, u16 height);

		u16 width() const { return m_width * getScale().x; }
		u16 height() const { return m_height * getScale().y; }

		void setColor(const Color &color) { m_color = color; updateVertexBuffer(); }
		void setAlphaMod(u8 alpha) { m_color.a = alpha / 255.0f; updateVertexBuffer(); }
		void setFlip(bool isFlipped) { m_isFlipped = isFlipped; }

	protected:
		void updateVertexBuffer() const;

		void draw(RenderTarget &target, RenderStates states) const override;

		const Texture *m_texture = nullptr;

		VertexBuffer m_vbo;

	private:
		u16 m_width = 0;
		u16 m_height = 0;

		FloatRect m_clipRect;
		FloatRect m_posRect;

		Color m_color;

		bool m_isFlipped = false;
};

} // namespace gk

#endif // GK_IMAGE_HPP_
