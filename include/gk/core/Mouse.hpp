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
#include <SFML/Graphics/RenderWindow.hpp>

namespace gk {

class Mouse {
	public:
		static void resetToWindowCenter();

		static void setWindow(sf::RenderWindow *window) { s_window = window; }

		static void setCursorVisible(bool isVisible);
		static void setCursorGrabbed(bool isGrabbed);

		static sf::Vector2i getPosition();

		static bool isInRect(const sf::IntRect &rect);

	private:
		static sf::RenderWindow *s_window;
};

} // namespace gk

#endif // GK_MOUSE_HPP_
