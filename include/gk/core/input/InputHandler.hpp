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
#ifndef GK_INPUTHANDLER_HPP_
#define GK_INPUTHANDLER_HPP_

#include <map>

#include "gk/core/IntTypes.hpp"

namespace gk {

using GameKey = u32; ///< Alias for game key type

////////////////////////////////////////////////////////////
/// \brief Give access to the real time state of an input device (keyboard, gamepad, etc...)
///
////////////////////////////////////////////////////////////
class InputHandler {
	public:
		virtual ~InputHandler() = default;

		////////////////////////////////////////////////////////////
		/// \brief Check if a key is pressed
		///
		/// \param key Key to check
		///
		/// \return True if the key is pressed, false otherwise
		///
		////////////////////////////////////////////////////////////
		virtual bool isKeyPressed(GameKey key) { return m_keysPressed[key]; }

		////////////////////////////////////////////////////////////
		/// \brief Check if a key is pressed only one time
		///
		/// \param key Key to check
		///
		/// \return True if the key is pressed, false otherwise or if true has already been returned once
		///
		////////////////////////////////////////////////////////////
		virtual bool isKeyPressedOnce(GameKey key);

		////////////////////////////////////////////////////////////
		/// \brief Check if a key is pressed with delay
		///
		/// \param key Key to check
		/// \param delay Delay between key presses (in milliseconds)
		///
		/// \return True if the key is pressed, false otherwise or if true has already been returned before <delay> ms
		///
		////////////////////////////////////////////////////////////
		virtual bool isKeyPressedWithDelay(GameKey key, u16 delay);

		////////////////////////////////////////////////////////////
		/// \brief Get current keys state
		///
		/// \return The current keys state
		///
		////////////////////////////////////////////////////////////
		const std::map<GameKey, bool> &keysPressed() const { return m_keysPressed; }

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Add a new key to this input handler
		///
		/// \key The key you want to add
		///
		////////////////////////////////////////////////////////////
		void addKey(GameKey key);

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		std::map<GameKey, bool> m_keysPressed;     ///< Keys state
		std::map<GameKey, bool> m_keysPressedOnce; ///< Keys state for isKeyPressedOnce
		std::map<GameKey, u32> m_lastTimePressed;  ///< Keys state for isKeyPressedWithDelay
};

} // namespace gk

#endif // GK_INPUTHANDLER_HPP_

////////////////////////////////////////////////////////////
/// \class gk::InputHandler
/// \ingroup core
///
/// gk::InputHandler is a base class for your own input handler.
///
/// \see gk::GamePad
///
////////////////////////////////////////////////////////////
