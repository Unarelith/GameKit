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
	bool collision = inCollision(object1, object2);

	if(object1.has<CollisionComponent>()) {
		object1.get<CollisionComponent>().collisionActions(object1, object2, collision);
	}

	if(object2.has<CollisionComponent>()) {
		object2.get<CollisionComponent>().collisionActions(object2, object1, collision);
	}
}

bool CollisionHelper::inCollision(SceneObject &object1, SceneObject &object2) {
	if(object1.has<PositionComponent>() && object1.has<HitboxComponent>()
	&& object2.has<PositionComponent>() && object2.has<HitboxComponent>()) {
		auto &hitbox1 = object1.get<HitboxComponent>();
		auto &hitbox2 = object2.get<HitboxComponent>();

		if(hitbox1.currentHitbox() && hitbox2.currentHitbox()) {
			sf::FloatRect rect1 = *hitbox1.currentHitbox();
			sf::FloatRect rect2 = *hitbox2.currentHitbox();

			auto &pos1 = object1.get<PositionComponent>();
			auto &pos2 = object2.get<PositionComponent>();

			rect1.left += pos1.x;
			rect1.top  += pos1.y;

			rect2.left += pos2.x;
			rect2.top  += pos2.y;

			if(object1.has<MovementComponent>()) {
				auto &movement = object1.get<MovementComponent>();
				rect1.left += movement.v.x;
				rect1.top  += movement.v.y;
			}

			if(object2.has<MovementComponent>()) {
				auto &movement = object2.get<MovementComponent>();
				rect2.left += movement.v.x;
				rect2.top  += movement.v.y;
			}

			if(rect1.intersects(rect2)) {
				return true;
			}
		}
	}

	return false;
}

} // namespace gk

