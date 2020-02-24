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
#include "gk/audio/AudioPlayer.hpp"
#include "gk/graphics/TextInput.hpp"
#include "gk/resource/ResourceHandler.hpp"

namespace gk {

TextInput::TextInput() {
	m_rectText.setFillColor(Color::Black);
	m_rectText.setOutlineThickness(2);
	m_rectText.setOutlineColor(Color::White);

	m_text.setFont(ResourceHandler::getInstance().get<Font>("font-default"));
	m_text.setCharacterSize(25);
	m_text.setString(m_cursor);
}

void TextInput::setPosition(float x, float y) {
	m_rectText.setPosition(x, y);
	m_text.setPosition(x + 7, y + 7);
}

void TextInput::setSize(u16 width, u16 height) {
	m_rectText.setSize(width, height);
}

void TextInput::onEvent(const SDL_Event &event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && !m_content.empty()) {
		m_content.erase(m_content.begin() + m_content.length() - 1);

		if (!m_keyboardSound.empty())
			AudioPlayer::playSound(m_keyboardSound);

		m_text.setString(m_content + m_cursor);
	}

  	if (event.type == SDL_TEXTINPUT) {
		std::string text = event.text.text;
		for (char c : text) {
			if (isprint(c) && (!m_characterLimit || m_content.size() < m_characterLimit)) {
				m_content += c;

				if (!m_keyboardSound.empty())
					AudioPlayer::playSound(m_keyboardSound);
			}

			m_text.setString(m_content + m_cursor);
		}
	}
}

void TextInput::draw(RenderTarget &target, RenderStates states) const {
	target.draw(m_rectText, states);
	target.draw(m_text, states);
}

} // namespace gk

