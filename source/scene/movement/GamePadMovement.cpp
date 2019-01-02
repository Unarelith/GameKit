/*
 * =====================================================================================
 *
 *       Filename:  GamePadMovement.cpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:42:00
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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

