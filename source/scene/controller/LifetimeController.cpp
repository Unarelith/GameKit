/*
 * =====================================================================================
 *
 *       Filename:  LifetimeController.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:20:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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

