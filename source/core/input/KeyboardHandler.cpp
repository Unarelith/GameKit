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

	// Reading keys from names as defined here: https://wiki.libsdl.org/SDL_Keycode
	auto addKey = [&](GameKey key, const char *name) {
		tinyxml2::XMLElement *keyElement = keys->FirstChildElement(name);
		m_keys[key] = SDL_GetKeyFromName(keyElement->Attribute("key"));

		if(m_keys[key] == SDLK_UNKNOWN) {
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
	const u8 *keyboardState = SDL_GetKeyboardState(nullptr);
	SDL_Scancode keyScancode = SDL_GetScancodeFromKey(m_keys[key]);

	m_keysPressed[key] = keyboardState[keyScancode];

	return keyboardState[keyScancode];
}

} // namespace gk

