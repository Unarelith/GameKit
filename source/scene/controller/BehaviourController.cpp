/*
 * =====================================================================================
 *
 *       Filename:  BehaviourController.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:26:06
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/scene/component/BehaviourComponent.hpp"
#include "gk/scene/component/LifetimeComponent.hpp"
#include "gk/scene/controller/BehaviourController.hpp"

namespace gk {

void BehaviourController::update(SceneObject &object) {
	if(object.has<BehaviourComponent>() && (!object.has<LifetimeComponent>() || !object.get<LifetimeComponent>().dead(object))) {
		object.get<BehaviourComponent>().update(object);
	}
}

} // namespace gk

