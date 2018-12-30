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
#include "gk/core/Mouse.hpp"
#include "gk/core/SDLHeaders.hpp"

namespace gk {

Window *Mouse::s_window = nullptr;

void Mouse::resetToWindowCenter() {
	SDL_WarpMouseInWindow(s_window->window(), s_window->width() / 2, s_window->height() / 2);
}

void Mouse::setCursorGrabbed(bool grabbed) {
	SDL_SetRelativeMouseMode((SDL_bool)grabbed);
}

void Mouse::setCursorVisible(bool visible) {
	SDL_ShowCursor(visible);
}

Vector2i Mouse::getPosition() {
	Vector2i pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}

bool Mouse::isInRect(const IntRect &rect) {
	return rect.contains(getPosition());
}

} // namespace gk

