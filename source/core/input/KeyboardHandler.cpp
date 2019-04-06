/*
 * =====================================================================================
 *
 *       Filename:  KeyboardHandler.cpp
 *
 *    Description:
 *
 *        Created:  25/03/2019 23:17:56
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/core/Debug.hpp"
#include "gk/core/KeyboardUtils.hpp"
#include "gk/core/XMLFile.hpp"
#include "gk/core/input/KeyboardHandler.hpp"

namespace gk {

void KeyboardHandler::loadKeysFromFile(const std::string &filename) {
	XMLFile doc(filename);

	tinyxml2::XMLElement *keys = doc.FirstChildElement("keys").ToElement();

	// Reading keys from names as defined here: https://wiki.libsdl.org/SDL_Keycode
	auto addKey = [&](GameKey key, const char *name) {
		tinyxml2::XMLElement *keyElement = keys->FirstChildElement(name);
		m_keys[key] = KeyboardUtils::getKeyFromName(keyElement->Attribute("key"));

		if(m_keys[key] == sf::Keyboard::Unknown) {
			DEBUG("Key '", keyElement->Attribute("key"), "' not recognized");
		}
	};

	addKey(0, "Left");
	addKey(1, "Right");
	addKey(2, "Up");
	addKey(3, "Down");

	addKey(4, "A");
	addKey(5, "B");

	addKey(6, "Start");
	addKey(7, "Select");
}

bool KeyboardHandler::isKeyPressed(GameKey key) {
	m_keysPressed[key] = sf::Keyboard::isKeyPressed(m_keys[key]);

	return m_keysPressed[key];
}

} // namespace gk

