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
#ifndef GK_COLLISIONCOMPONENT_HPP_
#define GK_COLLISIONCOMPONENT_HPP_

#include <functional>
#include <vector>

#include "gk/scene/SceneObject.hpp"

namespace gk {

class CollisionComponent {
	using CollisionChecker = std::function<void(SceneObject&)>;
	using CollisionAction  = std::function<void(SceneObject&, SceneObject&, bool)>;

	public:
		void checkCollisions(SceneObject &object) {
			for(auto &it : m_checkers) {
				it(object);
			}
		}

		void collisionActions(SceneObject &object1, SceneObject &object2, bool inCollision) {
			for(auto &it : m_actions) {
				it(object1, object2, inCollision);
			}
		}

		void addChecker(CollisionChecker checker) {
			m_checkers.push_back(checker);
		}

		void addAction(CollisionAction action) {
			m_actions.push_back(action);
		}

	private:
		std::vector<CollisionChecker> m_checkers;

		std::vector<CollisionAction> m_actions;
};

} // namespace gk

#endif // GK_COLLISIONCOMPONENT_HPP_
