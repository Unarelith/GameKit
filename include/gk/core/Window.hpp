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
#ifndef GK_WINDOW_HPP_
#define GK_WINDOW_HPP_

#include <functional>
#include <string>

#include <SFML/Window/Window.hpp>

#include "gk/core/IntTypes.hpp"
#include "gk/gl/RenderTarget.hpp"

namespace gk {

class Window : public RenderTarget {
	public:
		void create(sf::VideoMode mode, const sf::String &title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());
		void clear();

		void onEvent(const sf::Event &event);

		Vector2u getSize() const override { return m_size; }
		void setSize(const Vector2u &size);

		const View &getDefaultView() const override { return m_defaultView; }

		bool isFullscreenModeEnabled() const { return m_isFullscreenModeEnabled; }
		void setFullscreenMode(bool isFullscreenModeEnabled);

		bool isVerticalSyncEnabled() const { return m_isVerticalSyncEnabled; }
		void setVerticalSyncEnabled(bool isVerticalSyncEnabled);

		void setOpenGLFlagsSetupFunc(const std::function<void(void)> &func) { m_glFlagsSetupFunc = func; }

		sf::Window &window() { return m_window; }

	private:
		static void initOpenGL();

		sf::Window m_window;

		sf::VideoMode m_mode;
		sf::String m_title;
		sf::Uint32 m_style;
		sf::ContextSettings m_settings;

		Vector2u m_size{0, 0};
		Vector2u m_baseSize{0, 0};
		sf::Vector2i m_basePosition{0, 0};

		View m_defaultView;

		bool m_isFullscreenModeEnabled = false;
		bool m_isVerticalSyncEnabled = false;

		std::function<void(void)> m_glFlagsSetupFunc;
};

} // namespace gk

#endif // GK_WINDOW_HPP_
