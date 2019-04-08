/*
 * =====================================================================================
 *
 *       Filename:  KeyboardHandler.cpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 15:59:56
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/core/input/KeyboardHandler.hpp"
#include "gk/core/Debug.hpp"
#include "gk/core/IntTypes.hpp"
#include "gk/core/XMLFile.hpp"

namespace gk {

void KeyboardHandler::loadKeysFromFile(const std::string &filename) {
	XMLFile doc(filename);

	tinyxml2::XMLElement *keys = doc.FirstChildElement("keys").ToElement();
	if (keys) {
		GameKey key = 0;
		tinyxml2::XMLElement *keyElement = keys->FirstChildElement("key");
		while (keyElement) {
			m_keys[key] = SDL_GetScancodeFromName(keyElement->Attribute("key"));

			if(m_keys[key] == SDL_SCANCODE_UNKNOWN) {
				DEBUG("Key '", keyElement->Attribute("key"), "' not recognized");
			}

			InputHandler::addKey(key);

			++key;
			keyElement = keyElement->NextSiblingElement("key");
		}
	}
}

bool KeyboardHandler::isKeyPressed(GameKey key) {
	const u8 *keyboardState = SDL_GetKeyboardState(nullptr);
	SDL_Scancode keyScancode = m_keys[key];

	m_keysPressed[key] = keyboardState[keyScancode];

	return keyboardState[keyScancode];
}

} // namespace gk

