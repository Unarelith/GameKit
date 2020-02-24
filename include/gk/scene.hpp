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
