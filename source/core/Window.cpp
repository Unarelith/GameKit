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
#include <SFML/Window/Event.hpp>

#include "gk/core/Window.hpp"
#include "gk/gl/GLCheck.hpp"
#include "gk/gl/OpenGL.hpp"
#include "gk/core/Exception.hpp"

namespace gk {

void Window::create(sf::VideoMode mode, const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings) {
	m_window.create(mode, title, style, settings);
	if (!m_window.setActive())
		throw EXCEPTION("Failed to open window");

	m_mode = mode;
	m_title = title;
	m_style = style;
	m_settings = settings;

	m_size.x = mode.width;
	m_size.y = mode.height;

	m_defaultView.reset(FloatRect{0, 0, (float)m_size.x, (float)m_size.y});
	setView(m_defaultView);

	m_isFullscreenModeEnabled = (style & sf::Style::Fullscreen) != 0;

	m_glFlagsSetupFunc = &Window::initOpenGL;

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
}

void Window::clear() {
	glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Window::onEvent(const sf::Event &event) {
	if (event.type == sf::Event::Resized) {
		setSize({event.size.width, event.size.height});
	}
}

void Window::setSize(const Vector2u &size) {
	m_window.setSize({size.x, size.y});
	m_size = size;

	glCheck(glViewport(0, 0, m_size.x, m_size.y));
}

void Window::setFullscreenMode(bool isFullscreenModeEnabled) {
	if (m_isFullscreenModeEnabled != isFullscreenModeEnabled) {
		if (isFullscreenModeEnabled) {
			m_basePosition = m_window.getPosition();
			m_baseSize = m_size;

			m_window.create(m_mode, m_title, m_style | sf::Style::Fullscreen, m_settings);
		}
		else {
			// FIXME: Find the best available fullscreen video mode

			m_window.create(m_mode, m_title, m_style & (~sf::Style::Fullscreen), m_settings);

			m_window.setPosition(m_basePosition);
			setSize({m_baseSize.x, m_baseSize.y});
		}

		m_window.setVerticalSyncEnabled(m_isVerticalSyncEnabled);

		if (m_glFlagsSetupFunc)
			m_glFlagsSetupFunc();

		m_isFullscreenModeEnabled = isFullscreenModeEnabled;
	}
}

void Window::setVerticalSyncEnabled(bool isVerticalSyncEnabled) {
	if (m_isVerticalSyncEnabled != isVerticalSyncEnabled) {
		m_window.setVerticalSyncEnabled(isVerticalSyncEnabled);
		m_isVerticalSyncEnabled = isVerticalSyncEnabled;
	}
}

void Window::initOpenGL() {
	glCheck(glEnable(GL_TEXTURE_2D));

	glCheck(glEnable(GL_BLEND));
	glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

} // namespace gk

