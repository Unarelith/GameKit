/*
 * =====================================================================================
 *
 *       Filename:  Mouse.cpp
 *
 *    Description:
 *
 *        Created:  20/12/2014 15:39:17
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <SFML/Window/Mouse.hpp>

#include "gk/core/Mouse.hpp"

namespace gk {

sf::RenderWindow *Mouse::s_window = nullptr;

void Mouse::resetToWindowCenter() {
	// FIXME
	// SDL_WarpMouseInWindow(s_window->window(), s_window->getSize().x / 2, s_window->getSize().y / 2);
}

void Mouse::setCursorGrabbed(bool grabbed) {
	if (s_window)
		s_window->setMouseCursorGrabbed(grabbed);
}

void Mouse::setCursorVisible(bool visible) {
	if (s_window)
		s_window->setMouseCursorVisible(visible);
}

sf::Vector2i Mouse::getPosition() {
	return sf::Mouse::getPosition();
}

bool Mouse::isInRect(const sf::IntRect &rect) {
	return rect.contains(getPosition());
}

} // namespace gk

