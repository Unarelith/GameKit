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
#include "gk/gui/Text.hpp"
#include "gk/system/Debug.hpp"

namespace gk {

IntRect Text::getLocalBounds() {
	return {{(int)getPosition().x, (int)getPosition().y}, {m_image.width(), m_image.height()}};
}

void Text::update() {
	if (m_text.empty()) return;

	// FIXME: Add a conversion function between gk::Color and SDL_Color
	// FIXME: Find why red and blue are inverted
	SDL_Color color;
	color.r = m_color.b * 255.0f;
	color.g = m_color.g * 255.0f;
	color.b = m_color.r * 255.0f;
	color.a = m_color.a * 255.0f;

	SDL_Surface* surface = TTF_RenderUTF8_Blended(m_font->getFont(m_size), m_text.c_str(), color);
	if (surface) {
		m_texture.loadFromSurface(surface);
		SDL_FreeSurface(surface);

		m_image.load(m_texture);
	}
	else
		DEBUG("Unable to create text image for '" + m_text + "':", TTF_GetError());
}

void Text::draw(RenderTarget &target, RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_image, states);
}

} // namespace gk

