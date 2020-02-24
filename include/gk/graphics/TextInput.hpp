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
#ifndef GK_TEXTINPUT_HPP_
#define GK_TEXTINPUT_HPP_

#include "gk/core/SDLHeaders.hpp"
#include "gk/graphics/RectangleShape.hpp"
#include "gk/graphics/Text.hpp"

namespace gk {

class TextInput : public Drawable, public Transformable {
	public:
		TextInput();

		void onEvent(const SDL_Event &event);

		const std::string &content() const { return m_content; }

		Vector2f getSize() const { return m_rectText.getSize(); }

		void setPosition(float x, float y);
		void setSize(u16 width, u16 height);
		void setCharacterLimit(u16 characterLimit) { m_characterLimit = characterLimit; }
		void setContent(const std::string &content) { m_content = content; m_text.setString(m_content + m_cursor); }
		void setKeyboardSound(const std::string &keyboardSound) { m_keyboardSound = keyboardSound; }
		void setCursor(const std::string &cursor) { m_cursor = cursor; m_text.setString(m_content + m_cursor); }

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		RectangleShape m_rectText;

		Text m_text;
		std::string m_content;

		u16 m_characterLimit = 0;

		std::string m_keyboardSound;

		std::string m_cursor = "|";
};

} // namespace gk

#endif // GK_TEXTINPUT_HPP_
