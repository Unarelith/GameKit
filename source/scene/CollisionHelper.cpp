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
			FloatRect rect1 = *hitbox1.currentHitbox();
			FloatRect rect2 = *hitbox2.currentHitbox();

			auto &pos1 = object1.get<PositionComponent>();
			auto &pos2 = object2.get<PositionComponent>();

			rect1.x += pos1.x;
			rect1.y += pos1.y;

			rect2.x += pos2.x;
			rect2.y += pos2.y;

			if(object1.has<MovementComponent>()) {
				auto &movement = object1.get<MovementComponent>();
				rect1.x += movement.v.x;
				rect1.y += movement.v.y;
			}

			if(object2.has<MovementComponent>()) {
				auto &movement = object2.get<MovementComponent>();
				rect2.x += movement.v.x;
				rect2.y += movement.v.y;
			}

			if(rect1.intersects(rect2)) {
				return true;
			}
		}
	}

	return false;
}

} // namespace gk

