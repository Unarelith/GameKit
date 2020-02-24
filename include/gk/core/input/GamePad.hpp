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
#ifndef GK_GAMEPAD_HPP_
#define GK_GAMEPAD_HPP_

#include "gk/core/input/InputHandler.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Give access to the real time state of an input handler
///
////////////////////////////////////////////////////////////
class GamePad {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Initialize with an InputHandler
		///
		/// \param _inputHandler The gk::InputHandler to be bound to the GamePad
		///
		/// This function has to be called at init in your gk::CoreApplication subclass, with your own gk::InputHandler
		///
		/// \see getInputHandler
		///
		////////////////////////////////////////////////////////////
		static void init(InputHandler &_inputHandler) { inputHandler = &_inputHandler; }

		////////////////////////////////////////////////////////////
		/// \brief Check if a key is pressed
		///
		/// \param key Key to check
		///
		/// \return True if the key is pressed, false otherwise
		///
		////////////////////////////////////////////////////////////
		static bool isKeyPressed(GameKey key);

		////////////////////////////////////////////////////////////
		/// \brief Check if a key is pressed only one time
		///
		/// \param key Key to check
		///
		/// \return True if the key is pressed, false otherwise or if true has already been returned once
		///
		////////////////////////////////////////////////////////////
		static bool isKeyPressedOnce(GameKey key);

		////////////////////////////////////////////////////////////
		/// \brief Check if a key is pressed with delay
		///
		/// \param key Key to check
		/// \param delay Delay between key presses (in milliseconds)
		///
		/// \return True if the key is pressed, false otherwise or if true has already been returned before <delay> ms
		///
		////////////////////////////////////////////////////////////
		static bool isKeyPressedWithDelay(GameKey key, u16 delay);

		////////////////////////////////////////////////////////////
		/// \brief Get the current input handler
		///
		/// \return The currently active gk::InputHandler
		///
		/// \see init
		///
		////////////////////////////////////////////////////////////
		static InputHandler *getInputHandler() { return inputHandler; }

	private:
		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		static InputHandler *inputHandler; ///< Current input handler
};

} // namespace gk

#endif // GK_GAMEPAD_HPP_

////////////////////////////////////////////////////////////
/// \class gk::GamePad
/// \ingroup core
///
/// gk::GamePad provides an interface to the state of the keyboard.
///
/// \see gk::InputHandler
///
////////////////////////////////////////////////////////////
