/*
 * =====================================================================================
 *
 *       Filename:  CollisionHelper.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:39:36
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/scene/CollisionHelper.hpp"

#include "gk/scene/component/CollisionComponent.hpp"
#include "gk/scene/component/HitboxComponent.hpp"
#include "gk/scene/component/MovementComponent.hpp"
#include "gk/scene/component/PositionComponent.hpp"

namespace gk {

void CollisionHelper::checkCollision(SceneObject &object1, SceneObject &object2) {
	bool inCollision = CollisionHelper::inCollision(object1, object2);

	if(object1.has<CollisionComponent>()) {
		object1.get<CollisionComponent>().collisionActions(object1, object2, inCollision);
	}

	if(object2.has<CollisionComponent>()) {
		object2.get<CollisionComponent>().collisionActions(object2, object1, inCollision);
	}
}

bool CollisionHelper::inCollision(SceneObject &object1, SceneObject &object2) {
	if(object1.has<HitboxComponent>() && object2.has<HitboxComponent>()) {
		auto &hitbox1 = object1.get<HitboxComponent>();
		auto &hitbox2 = object2.get<HitboxComponent>();

		if(hitbox1.currentHitbox() && hitbox2.currentHitbox()) {
			FloatRect rect1 = *hitbox1.currentHitbox();
			FloatRect rect2 = *hitbox2.currentHitbox();

			rect1 += object1.get<PositionComponent>();
			rect2 += object2.get<PositionComponent>();

			if(object1.has<MovementComponent>()) {
				rect1 += object1.get<MovementComponent>().v;
			}

			if(object2.has<MovementComponent>()) {
				rect2 += object2.get<MovementComponent>().v;
			}

			if(rect1.intersects(rect2)) {
				return true;
			}
		}
	}

	return false;
}

} // namespace gk

