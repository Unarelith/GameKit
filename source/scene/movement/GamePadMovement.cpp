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
#include "gk/core/input/GamePad.hpp"
#include "gk/scene/movement/GamePadMovement.hpp"
#include "gk/scene/component/MovementComponent.hpp"

namespace gk {

void GamePadMovement::process(SceneObject &object) {
	auto &movementComponent = object.get<MovementComponent>();

	movementComponent.v.x = 0;
	movementComponent.v.y = 0;

	if(GamePad::isKeyPressed(m_left)) {
		movementComponent.v.x = -1;
	}
	else if(GamePad::isKeyPressed(m_right)) {
		movementComponent.v.x = 1;
	}

	if(GamePad::isKeyPressed(m_up)) {
		movementComponent.v.y = -1;
	}
	else if(GamePad::isKeyPressed(m_down)) {
		movementComponent.v.y = 1;
	}

	m_isFinished = true;
}

} // namespace gk

