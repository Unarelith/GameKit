/*
 * =====================================================================================
 *
 *       Filename:  Mouse.hpp
 *
 *    Description:
 *
 *        Created:  20/12/2014 15:38:51
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_MOUSE_HPP_
#define GK_MOUSE_HPP_

#include <SFML/Graphics/Rect.hpp>

#include "gk/core/Window.hpp"

namespace gk {

class Mouse {
	public:
		static void resetToWindowCenter();

		static void setWindow(Window *window) { s_window = window; }

		static void setCursorVisible(bool isVisible);
		static void setCursorGrabbed(bool isGrabbed);

		static sf::Vector2i getPosition();

		static bool isInRect(const sf::IntRect &rect);

	private:
		static Window *s_window;
};

} // namespace gk

#endif // GK_MOUSE_HPP_
