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

#include <string>

#include <SFML/Window/Window.hpp>

#include "gk/core/IntTypes.hpp"
#include "gk/gl/RenderTarget.hpp"

namespace gk {

class Window : public RenderTarget, public sf::Window {
	public:
		void open(const std::string &caption, u16 width, u16 height);
		void clear();

		Vector2u getSize() const override { return m_size; }

		const View &getDefaultView() const override { return m_defaultView; }

	private:
		Vector2u m_size;

		View m_defaultView;
};

} // namespace gk

#endif // GK_WINDOW_HPP_
