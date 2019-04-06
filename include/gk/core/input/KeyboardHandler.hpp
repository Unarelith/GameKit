/*
 * =====================================================================================
 *
 *       Filename:  KeyboardHandler.hpp
 *
 *    Description:
 *
 *        Created:  25/03/2019 23:16:52
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_KEYBOARDHANDLER_HPP_
#define GK_KEYBOARDHANDLER_HPP_

#include <map>

#include <SFML/Window/Keyboard.hpp>

#include "gk/core/input/InputHandler.hpp"

namespace gk {

class KeyboardHandler : public InputHandler {
	public:
		void loadKeysFromFile(const std::string &filename);

		void updateState(const sf::Event &event) override;

		bool isKeyPressed(GameKey key) override;

	private:
		std::map<GameKey, sf::Keyboard::Key> m_keys;
};

} // namespace gk

#endif // GK_KEYBOARDHANDLER_HPP_
