/*
 * =====================================================================================
 *
 *       Filename:  MovementController.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:18:19
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/scene/controller/MovementController.hpp"

#include "gk/scene/component/CollisionComponent.hpp"
#include "gk/scene/component/MovementComponent.hpp"
#include "gk/scene/component/PositionComponent.hpp"

namespace gk {

void MovementController::update(SceneObject &object) {
	if(object.has<MovementComponent>()) {
		auto &movement = object.get<MovementComponent>();

		if(movement.movements.size() != 0 && movement.movements.top()) {
			movement.movements.top()->process(object);
		}

		movement.isBlocked.x = false;
		movement.isBlocked.y = false;
	}

	if(object.has<CollisionComponent>()) {
		object.get<CollisionComponent>().checkCollisions(object);
	}

	if(object.has<MovementComponent>()) {
		auto &movement = object.get<MovementComponent>();

		movement.isMoving = movement.v.x || movement.v.y;

		object.get<PositionComponent>() += movement.v * movement.speed;
	}
}

} // namespace gk

