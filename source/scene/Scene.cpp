/*
 * =====================================================================================
 *
 *       Filename:  Scene.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:34:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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

void Scene::draw(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states) const {
	for (auto &view : m_viewList) {
		view->draw(object, target, states);

		if (object.has<SceneObjectList>())
			view->draw(object.get<SceneObjectList>(), target, states);
	}
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
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

