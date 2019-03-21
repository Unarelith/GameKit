/*
 * =====================================================================================
 *
 *       Filename:  InputHandler.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:09:57
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
