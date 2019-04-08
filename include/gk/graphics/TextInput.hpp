/*
 * =====================================================================================
 *
 *       Filename:  TextInput.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 14:35:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TEXTINPUT_HPP_
#define GK_TEXTINPUT_HPP_

#include "gk/core/SDLHeaders.hpp"
#include "gk/graphics/RectangleShape.hpp"
#include "gk/graphics/Text.hpp"

namespace gk {

class TextInput : public IDrawable, public Transformable {
	public:
		TextInput();

		void onEvent(const SDL_Event &event);

		const std::string &content() const { return m_content; }

		Vector2f getSize() const { return m_rectText.getSize(); }

		void setPosition(float x, float y);
		void setSize(u16 width, u16 height);
		void setCharacterLimit(u16 characterLimit) { m_characterLimit = characterLimit; }

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		RectangleShape m_rectText;

		Text m_text;
		std::string m_content;

		u16 m_characterLimit = 0;
};

} // namespace gk

#endif // GK_TEXTINPUT_HPP_
