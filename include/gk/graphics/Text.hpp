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
#ifndef GK_TEXT_HPP_
#define GK_TEXT_HPP_

#include "gk/graphics/Color.hpp"
#include "gk/core/Rect.hpp"
#include "gk/gl/Drawable.hpp"
#include "gk/gl/Texture.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/graphics/Font.hpp"
#include "gk/graphics/Image.hpp"

namespace gk {

class Text : public Drawable, public Transformable {
	public:
		Text() = default;
		Text(const std::string &fontResourceName, int ptsize);
		Text(const std::string &str, const std::string &fontResourceName, int ptsize);
		Text(const std::string &str, const Font &font, int ptsize);

		IntRect getLocalBounds();

		void setFont(const Font &font) { m_font = &font; m_isUpdateNeeded = true; }
		void setFont(const std::string &resourceName);

		const std::string &string() const { return m_string; }
		void setString(const std::string &str) { m_string = str; m_isUpdateNeeded = true; }

		enum Style {
			Normal        = TTF_STYLE_NORMAL,
			Bold          = TTF_STYLE_BOLD,
			Italic        = TTF_STYLE_ITALIC,
			Underline     = TTF_STYLE_UNDERLINE,
			Strikethrough = TTF_STYLE_STRIKETHROUGH,
		};

		void setStyle(Style style) { m_style = style; m_isUpdateNeeded = true; }
		void setColor(const Color &color) { m_color = color; m_isUpdateNeeded = true; }
		void setCharacterSize(int size) { m_characterSize = size; m_isUpdateNeeded = true; }

		void setSize(const Vector2i &size) { m_size = size; m_isUpdateNeeded = true; }
		void setCentered(bool isCentered) { m_isCentered = isCentered; m_isUpdateNeeded = true; }
		void setScaled(bool isScaled) { m_isScaled = isScaled; m_isUpdateNeeded = true; }
		void setWrapped(bool isWrapped) { m_isWrapped = isWrapped; m_isUpdateNeeded = true; }

	private:
		void update() const;

		void draw(RenderTarget &target, RenderStates states) const override;

		const Font *m_font = nullptr;

		Style m_style = Style::Normal;
		Color m_color;

		mutable bool m_isUpdateNeeded = false;
		mutable Image m_image;
		mutable std::shared_ptr<Texture> m_texture;

		std::string m_string;
		int m_characterSize = -1;

		Vector2i m_size{0, 0};
		bool m_isCentered = false;
		bool m_isScaled = false;
		bool m_isWrapped = false;
};

} // namespace gk

#endif // GK_TEXT_HPP_
