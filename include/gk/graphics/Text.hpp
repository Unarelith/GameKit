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

// FIXME: update() should be called only once before draw
class Text : public IDrawable, public Transformable {
	public:
		Text() { update(); }
		Text(const std::string &fontResourceName, int ptsize);
		Text(const std::string &text, const std::string &fontResourceName, int ptsize);
		Text(const std::string &text, const Font &font, int ptsize);

		IntRect getLocalBounds();

		void setFont(const Font &font) { m_font = &font; update(); }
		void setFont(const std::string &resourceName);

		const std::string &text() const { return m_text; }
		void setText(const std::string &text) { m_text = text; update(); }

		enum Style {
			Normal        = TTF_STYLE_NORMAL,
			Bold          = TTF_STYLE_BOLD,
			Italic        = TTF_STYLE_ITALIC,
			Underline     = TTF_STYLE_UNDERLINE,
			Strikethrough = TTF_STYLE_STRIKETHROUGH,
		};

		void setStyle(Style style) { m_style = style; update(); }
		void setColor(const Color &color) { m_color = color; update(); }
		void setCharacterSize(int size) { m_size = size; update(); }

		void setSize(const gk::Vector2i &size) { m_size = size; update(); }
		void setCentered(bool isCentered) { m_isCentered = isCentered; update(); }
		void setScaled(bool isScaled) { m_isScaled = isScaled; update(); }
		void setWrapped(bool isWrapped) { m_isWrapped = isWrapped; update(); }

	private:
		void update();

		void draw(RenderTarget &target, RenderStates states) const override;

		const Font *m_font = nullptr;

		Style m_style = Style::Normal;
		Color m_color;
		Image m_image;
		Texture m_texture;

		std::string m_text;
		int m_characterSize = Font::defaultSize;

		gk::Vector2i m_size{0, 0};
		bool m_isCentered = false;
		bool m_isScaled = false;
		bool m_isWrapped = false;
};

} // namespace gk

#endif // GK_TEXT_HPP_
