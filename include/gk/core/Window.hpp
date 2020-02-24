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

#include <memory>
#include <string>

#include "gk/core/IntTypes.hpp"
#include "gk/core/SDLHeaders.hpp"
#include "gk/gl/RenderTarget.hpp"

namespace gk {

class Window : public RenderTarget {
	public:
		enum Mode {
			Windowed,
			Fullscreen,
			Borderless
		};

		void open(const std::string &caption, u16 width, u16 height);

		void clear();
		void display();

		void onEvent(const SDL_Event &event);

		bool isVerticalSyncEnabled() { return m_isVerticalSyncEnabled; }
		void setVerticalSyncEnabled(bool isVerticalSyncEnabled);

		Mode getWindowMode() const { return m_windowMode; }
		void setWindowMode(Mode mode);

		Vector2u getSize() const override;
		void resize(unsigned int width, unsigned int height);

		void close() { m_isOpen = false; }
		bool isOpen() const { return m_isOpen; }

		SDL_Window *window() const { return m_window.get(); }

		const View &getDefaultView() const override { return m_defaultView; }

	private:
		using SDL_WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
		using SDL_GLContextPtr = std::unique_ptr<void, decltype(&SDL_GL_DeleteContext)>;

		SDL_WindowPtr m_window{nullptr, SDL_DestroyWindow};
		SDL_GLContextPtr m_context{nullptr, SDL_GL_DeleteContext};

		Vector2u m_size;
		Vector2u m_baseSize{0, 0};
		Vector2i m_basePosition{0, 0};

		bool m_isOpen;

		View m_defaultView;

		Mode m_windowMode = Mode::Windowed;

		bool m_isVerticalSyncEnabled = false;
};

} // namespace gk

#endif // GK_WINDOW_HPP_
