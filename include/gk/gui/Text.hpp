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

#include "gk/core/Color.hpp"
#include "gk/core/Rect.hpp"
#include "gk/gl/IDrawable.hpp"
#include "gk/gl/Texture.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/gui/Font.hpp"
#include "gk/gui/Image.hpp"

namespace gk {

class Text : public IDrawable, public Transformable {
	public:
		Text() { update(); }

		IntRect getLocalBounds();

		enum Style {
			Normal        = TTF_STYLE_NORMAL,
			Bold          = TTF_STYLE_BOLD,
			Italic        = TTF_STYLE_ITALIC,
			Underline     = TTF_STYLE_UNDERLINE,
			Strikethrough = TTF_STYLE_STRIKETHROUGH,
		};

		void setStyle(Style style) { m_style = style; update(); }
		void setColor(const Color &color) { m_color = color; update(); }
		void setFont(const Font &font) { m_font = &font; update(); }
		void setString(const std::string &text) { m_text = text; update(); }
		void setCharacterSize(int size) { m_size = size; update(); }

	private:
		void update();

		void draw(RenderTarget &target, RenderStates states) const override;

		const Font *m_font = nullptr;

		Style m_style = Style::Normal;
		Color m_color;
		Image m_image;
		Texture m_texture;

		std::string m_text;
		int m_size = -1;
};

} // namespace gk

#endif // GK_TEXT_HPP_
