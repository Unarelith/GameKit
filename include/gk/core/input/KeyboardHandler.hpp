/*
 * =====================================================================================
 *
 *       Filename:  KeyboardHandler.hpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 15:59:40
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_KEYBOARDHANDLER_HPP_
#define GK_KEYBOARDHANDLER_HPP_

#include <map>

#include "gk/core/input/InputHandler.hpp"
#include "gk/core/SDLHeaders.hpp"

namespace gk {

class KeyboardHandler : public InputHandler {
	public:
		void loadKeysFromFile(const std::string &filename);

		bool isKeyPressed(GameKey key);

	protected:
		std::map<GameKey, SDL_Keycode> m_keys;
};

} // namespace gk

#endif // GK_KEYBOARDHANDLER_HPP_
