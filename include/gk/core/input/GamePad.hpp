/*
 * =====================================================================================
 *
 *       Filename:  GamePad.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:11:54
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_GAMEPAD_HPP_
#define GK_GAMEPAD_HPP_

#include "gk/core/input/InputHandler.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Give access to the real time state of the keyboard
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
