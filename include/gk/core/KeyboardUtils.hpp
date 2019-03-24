/*
 * =====================================================================================
 *
 *       Filename:  KeyboardUtils.hpp
 *
 *    Description:
 *
 *        Created:  24/03/2019 20:36:12
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_KEYBOARDUTILS_HPP_
#define GK_KEYBOARDUTILS_HPP_

#include <string>

#include <SFML/Window/Keyboard.hpp>

namespace gk {
	namespace KeyboardUtils {
		std::string getNameFromKey(sf::Keyboard::Key key);
		sf::Keyboard::Key getKeyFromName(const std::string &name);
	}
} // namespace gk

#endif // GK_KEYBOARDUTILS_HPP_
