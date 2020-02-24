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
#include "gk/scene/component/LifetimeComponent.hpp"
#include "gk/scene/controller/LifetimeController.hpp"

namespace gk {

void LifetimeController::update(SceneObjectList &objects) {
	for(size_t i = 0 ; i < objects.size() ; i++) {
		if (objects[i].has<SceneObjectList>())
			update(objects[i].get<SceneObjectList>());

		if(objects[i].has<LifetimeComponent>()) {
			auto &lifetimeComponent = objects[i].get<LifetimeComponent>();
			if (lifetimeComponent.dead(objects[i]) && lifetimeComponent.areClientsNotified()) {
				bool canDelete = true;
				if (objects[i].has<SceneObjectList>()) {
					for (SceneObject &object : objects[i].get<SceneObjectList>()) {
						if (object.has<LifetimeComponent>() && !object.get<LifetimeComponent>().dead(object)) {
							canDelete = false;
							break;
						}
					}
				}

				if (canDelete)
					objects.remove(i--);
			}
		}
	}
}

} // namespace gk

