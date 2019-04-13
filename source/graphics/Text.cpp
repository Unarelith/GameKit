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

Text::Text(const std::string &str, const std::string &fontResourceName, int ptsize) {
	m_string = str;
	m_characterSize = ptsize;

	setFont(fontResourceName);
}

Text::Text(const std::string &str, const Font &font, int ptsize) {
	m_string = str;
	m_font = &font;
	m_characterSize = ptsize;

	m_isUpdateNeeded = true;
}

IntRect Text::getLocalBounds() {
	if (m_isUpdateNeeded) update();

	return {{(int)getPosition().x, (int)getPosition().y}, {m_image.width(), m_image.height()}};
}

void Text::setFont(const std::string &resourceName) {
	setFont(ResourceHandler::getInstance().get<Font>(resourceName));
}

void Text::update() const {
	m_isUpdateNeeded = false;

	if (!m_font || m_string.empty() || m_characterSize < 0) return;

	// FIXME: Add a conversion function between Color and SDL_Color
	SDL_Color color;
	color.r = m_color.r * 255.0f;
	color.g = m_color.g * 255.0f;
	color.b = m_color.b * 255.0f;
	color.a = m_color.a * 255.0f;

	TTF_Font *font = m_font->getFont(m_characterSize);
	TTF_SetFontStyle(font, m_style);

	SDL_Surface* surface = nullptr;
	if (m_isWrapped)
		surface = TTF_RenderUTF8_Blended_Wrapped(font, m_string.c_str(), color, m_size.x);
	else
		surface = TTF_RenderUTF8_Blended(font, m_string.c_str(), color);

	if (surface) {
		m_texture = std::make_shared<Texture>();
		m_texture->loadFromSurface(surface);
		SDL_FreeSurface(surface);

		m_image.load(*m_texture);

		if (m_isCentered)
			m_image.setPosition(
				m_size.x / 2 - m_texture->getSize().x / 2,
				m_size.y / 2 - m_texture->getSize().y / 2
			);
		else
			m_image.setPosition(0, 0);

		if (m_isScaled) {
			int width = std::min((int)m_texture->getSize().x, m_size.x);
			int height = std::min((int)m_texture->getSize().y, m_size.y);
			m_image.setPosRect(0, 0, width, height);
		}
		else
			m_image.setPosRect(0, 0, m_texture->getSize().x, m_texture->getSize().y);
	}
	else
		DEBUG("Unable to create text image for '" + m_string + "':", TTF_GetError());

	// FIXME: Save old style instead of restoring Normal
	TTF_SetFontStyle(font, Style::Normal);
}

void Text::draw(RenderTarget &target, RenderStates states) const {
	if (m_isUpdateNeeded)
		update();

	states.transform *= getTransform();
	states.texture = m_texture.get();
	target.draw(m_image, states);
}

} // namespace gk

