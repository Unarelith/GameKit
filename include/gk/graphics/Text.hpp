/*
 * =====================================================================================
 *
 *       Filename:  Text.hpp
 *
 *    Description:
 *
 *        Created:  30/12/2018 19:03:58
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TEXT_HPP_
#define GK_TEXT_HPP_

#include "gk/graphics/Color.hpp"
#include "gk/core/Rect.hpp"
#include "gk/gl/IDrawable.hpp"
#include "gk/gl/Texture.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/graphics/Font.hpp"
#include "gk/graphics/Image.hpp"

namespace gk {

class Text : public IDrawable, public Transformable {
	public:
		Text() = default;
		Text(const std::string &fontResourceName, int ptsize);
		Text(const std::string &text, const std::string &fontResourceName, int ptsize);
		Text(const std::string &text, const Font &font, int ptsize);

		IntRect getLocalBounds();

		void setFont(const Font &font) { m_font = &font; m_isUpdateNeeded = true; }
		void setFont(const std::string &resourceName);

		const std::string &text() const { return m_text; }
		void setText(const std::string &text) { m_text = text; m_isUpdateNeeded = true; }

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

		void setSize(const gk::Vector2i &size) { m_size = size; m_isUpdateNeeded = true; }
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
		mutable Texture m_texture;

		std::string m_text;
		int m_characterSize = -1;

		gk::Vector2i m_size{0, 0};
		bool m_isCentered = false;
		bool m_isScaled = false;
		bool m_isWrapped = false;
};

} // namespace gk

#endif // GK_TEXT_HPP_
