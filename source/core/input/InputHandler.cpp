/*
 * =====================================================================================
 *
 *  GameKit
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include "gk/core/input/InputHandler.hpp"
#include "gk/core/GameClock.hpp"

namespace gk {

bool InputHandler::isKeyPressedOnce(GameKey key) {
	if(isKeyPressed(key)) {
		if(!m_keysPressedOnce[key]) {
			m_keysPressedOnce[key] = true;
			return true;
		} else {
			return false;
		}
	} else {
		m_keysPressedOnce[key] = false;
		return false;
	}
}

bool InputHandler::isKeyPressedWithDelay(GameKey key, u16 delay) {
	if(isKeyPressed(key) && GameClock::getTicks() - m_lastTimePressed[key] > delay) {
		m_lastTimePressed[key] = GameClock::getTicks();
		return true;
	} else {
		if(!isKeyPressed(key)) m_lastTimePressed[key] = 0;
		return false;
	}
}

void InputHandler::addKey(GameKey key) {
	m_keysPressed[key] = false;
	m_keysPressedOnce[key] = false;
	m_lastTimePressed[key] = 0;
}

} // namespace gk

