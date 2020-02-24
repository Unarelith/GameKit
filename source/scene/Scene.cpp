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
#include "gk/scene/component/CollisionComponent.hpp"
#include "gk/scene/Scene.hpp"

namespace gk {

Scene::Scene() {
	setCollisionHelper<CollisionHelper>();
}

void Scene::reset() {
	for (auto &controller : m_controllerList)
		if (controller->isGlobal())
			controller->reset(m_objects);

	for (SceneObject &object : m_objects) {
		reset(object);
	}
}

void Scene::update() {
	for (auto &controller : m_controllerList)
		if (controller->isGlobal())
			controller->update(m_objects);

	for (SceneObject &object : m_objects) {
		update(object);
	}
}

void Scene::reset(SceneObject &object) {
	for (auto &controller : m_controllerList) {
		if (!controller->isGlobal()) {
			controller->reset(object);

			if (object.has<SceneObjectList>())
				controller->reset(object.get<SceneObjectList>());
		}
	}
}

void Scene::update(SceneObject &object) {
	for (auto &controller : m_controllerList) {
		if (!controller->isGlobal()) {
			controller->update(object);

			if (object.has<SceneObjectList>())
				controller->update(object.get<SceneObjectList>());
		}
	}
}

void Scene::draw(const SceneObject &object, RenderTarget &target, RenderStates states) const {
	for (auto &view : m_viewList) {
		view->draw(object, target, states);

		if (object.has<SceneObjectList>())
			view->draw(object.get<SceneObjectList>(), target, states);
	}
}

void Scene::draw(RenderTarget &target, RenderStates states) const {
	for (auto &view : m_viewList)
		view->draw(m_objects, target, states);
}

SceneObject &Scene::addObject(SceneObject &&object) {
	SceneObject &obj = m_objects.addObject(std::move(object));

	if(obj.has<CollisionComponent>()) {
		obj.get<CollisionComponent>().addChecker([&](SceneObject &object) {
			checkCollisionsFor(object);
		});
	}

	return obj;
}

void Scene::addCollisionChecker(std::function<void(SceneObject &)> checker) {
	for (SceneObject &object : m_objects) {
		if (object.has<CollisionComponent>()) {
			object.get<CollisionComponent>().addChecker(checker);
		}
	}
}

void Scene::checkCollisionsFor(SceneObject &object) {
	for(SceneObject &object2 : m_objects) {
		if(&object != &object2) {
			m_collisionHelper->checkCollision(object, object2);

			if (object.has<SceneObjectList>())
				for (SceneObject &child : object.get<SceneObjectList>())
					m_collisionHelper->checkCollision(child, object2);

			if (object2.has<SceneObjectList>())
				for (SceneObject &child : object2.get<SceneObjectList>())
					m_collisionHelper->checkCollision(object, child);
		}
	}
}

} // namespace gk

