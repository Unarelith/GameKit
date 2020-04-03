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
#include "gk/core/Window.hpp"
#include "gk/gl/GLCheck.hpp"
#include "gk/gl/OpenGL.hpp"
#include "gk/core/Exception.hpp"

namespace gk {

void Window::open(const std::string &caption, u16 width, u16 height) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	m_window.reset(SDL_CreateWindow(caption.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));
	if(!m_window) {
		throw EXCEPTION("Window initialization failed:", SDL_GetError());
	}

	m_context.reset(SDL_GL_CreateContext(m_window.get()));
	if(!m_context) {
		throw EXCEPTION("OpenGL context creation failed:", SDL_GetError());
	}

	m_size.x = width;
	m_size.y = height;

	m_defaultView.reset(FloatRect{0, 0, (float)width, (float)height});
	setView(m_defaultView);

	m_isOpen = true;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__MINGW32__)
#ifdef USE_GLAD
	if(!gladLoadGL()) {
		throw EXCEPTION("glad init failed");
	}
#else
	if(glewInit() != GLEW_OK) {
		throw EXCEPTION("glew init failed");
	}
#endif
#endif

	glCheck(glEnable(GL_BLEND));
	glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	glCheck(glEnable(GL_TEXTURE_2D));
}

void Window::clear() {
	glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Window::display() {
	SDL_GL_SwapWindow(m_window.get());
}

void Window::onEvent(const SDL_Event &event) {
	if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
		glViewport(0, 0, event.window.data1, event.window.data2);

		m_size.x = event.window.data1;
		m_size.y = event.window.data2;
	}
}

void Window::setVerticalSyncEnabled(bool isVerticalSyncEnabled) {
	if(SDL_GL_SetSwapInterval(isVerticalSyncEnabled) < 0) {
		gkWarning() << "Can't enable VSync";
	}
	else {
		m_isVerticalSyncEnabled = isVerticalSyncEnabled;
	}
}

void Window::setWindowMode(Mode mode) {
	if (m_windowMode != mode) {
		if (mode == Mode::Windowed) {
			SDL_SetWindowFullscreen(m_window.get(), 0);
			SDL_SetWindowSize(m_window.get(), m_baseSize.x, m_baseSize.y);
			SDL_SetWindowPosition(m_window.get(), m_basePosition.x, m_basePosition.y);
		}
		else {
			m_baseSize = m_size;

			SDL_GetWindowPosition(m_window.get(), &m_basePosition.x, &m_basePosition.y);
			SDL_SetWindowFullscreen(m_window.get(), (mode == Mode::Fullscreen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_FULLSCREEN_DESKTOP);

			SDL_DisplayMode desktopMode;
			if (SDL_GetDesktopDisplayMode(0, &desktopMode) == 0)
				SDL_SetWindowDisplayMode(m_window.get(), &desktopMode);
		}

		m_windowMode = mode;
	}
}

Vector2u Window::getSize() const {
	if (m_windowMode == Mode::Windowed)
		return m_size;
	else {
		int w, h;
		SDL_GetWindowSize(m_window.get(), &w, &h);

		return Vector2u{
			static_cast<unsigned int>(w),
			static_cast<unsigned int>(h)
		};
	}
}

void Window::resize(unsigned int width, unsigned int height) {
	SDL_SetWindowSize(m_window.get(), width, height);
}

} // namespace gk

