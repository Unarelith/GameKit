/*
 * =====================================================================================
 *
 *       Filename:  scene.hpp
 *
 *    Description:
 *
 *        Created:  23/03/2019 15:02:19
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_SCENE_HPP_
#define GK_SCENE_HPP_

#include "gk/scene/Scene.hpp"

// Behaviours
#include "gk/scene/behaviour/EasyBehaviour.hpp"

// Controllers
#include "gk/scene/controller/BehaviourController.hpp"
#include "gk/scene/controller/LifetimeController.hpp"
#include "gk/scene/controller/MovementController.hpp"

// Components
#include "gk/scene/component/BehaviourComponent.hpp"
#include "gk/scene/component/CollisionComponent.hpp"
#include "gk/scene/component/HealthComponent.hpp"
#include "gk/scene/component/HitboxComponent.hpp"
#include "gk/scene/component/LifetimeComponent.hpp"
#include "gk/scene/component/MovementComponent.hpp"
#include "gk/scene/component/PositionComponent.hpp"

// Movements
#include "gk/scene/movement/EasyMovement.hpp"
#include "gk/scene/movement/GamePadMovement.hpp"

// Views
#include "gk/scene/view/HitboxView.hpp"
#include "gk/scene/view/SpriteView.hpp"

#endif // GK_SCENE_HPP_

///////////////////////////////////////////////////////////
/// \defgroup scene
/// \brief Game scene and entity management
///
////////////////////////////////////////////////////////////
