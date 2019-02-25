/*
 * =====================================================================================
 *
 *       Filename:  Text.cpp
 *
 *    Description:
 *
 *        Created:  30/12/2018 19:05:40
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>

#include "gk/graphics/Text.hpp"
#include "gk/resource/ResourceHandler.hpp"
#include "gk/core/Debug.hpp"

namespace gk {

Text::Text(const std::string &fontResourceName, int ptsize) {
	m_characterSize = ptsize;

	setFont(fontResourceName);
}

Text::Text(const std::string &text, const std::string &fontResourceName, int ptsize) {
	m_text = text;
	m_characterSize = ptsize;

	setFont(fontResourceName);
}

Text::Text(const std::string &text, const Font &font, int ptsize) {
	m_text = text;
	m_font = &font;
	m_characterSize = ptsize;

	update();
}

IntRect Text::getLocalBounds() {
	return {{(int)getPosition().x, (int)getPosition().y}, {m_image.width(), m_image.height()}};
}

void Text::setFont(const std::string &resourceName) {
	setFont(gk::ResourceHandler::getInstance().get<gk::Font>(resourceName));
}

void Text::update() {
	if (m_text.empty()) return;

	// FIXME: Add a conversion function between gk::Color and SDL_Color
	SDL_Color color;
	color.r = m_color.r * 255.0f;
	color.g = m_color.g * 255.0f;
	color.b = m_color.b * 255.0f;
	color.a = m_color.a * 255.0f;

	TTF_Font *font = m_font->getFont(m_characterSize);
	TTF_SetFontStyle(font, m_style);

	SDL_Surface* surface = nullptr;
	if (m_isWrapped)
		surface = TTF_RenderUTF8_Blended_Wrapped(font, m_text.c_str(), color, m_size.x);
	else
		surface = TTF_RenderUTF8_Blended(font, m_text.c_str(), color);

	if (surface) {
		m_texture.loadFromSurface(surface);
		SDL_FreeSurface(surface);

		m_image.load(m_texture);

		if (m_isCentered)
			m_image.setPosition(
				m_size.x / 2 - m_texture.width() / 2,
				m_size.y / 2 - m_texture.height() / 2
			);
		else
			m_image.setPosition(0, 0);

		if (m_isScaled) {
			int width = std::min((int)m_texture.width(), m_size.x);
			int height = std::min((int)m_texture.height(), m_size.y);
			m_image.setPosRect(0, 0, width, height);
		}
		else
			m_image.setPosRect(0, 0, m_texture.width(), m_texture.height());
	}
	else
		DEBUG("Unable to create text image for '" + m_text + "':", TTF_GetError());

	// FIXME: Save old style instead of restoring Normal
	TTF_SetFontStyle(font, Style::Normal);
}

void Text::draw(RenderTarget &target, RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_image, states);
}

} // namespace gk

