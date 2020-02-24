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
#ifndef GK_MOVEMENTCOMPONENT_HPP_
#define GK_MOVEMENTCOMPONENT_HPP_

#include <memory>
#include <stack>

#include "gk/core/Vector2.hpp"
#include "gk/scene/movement/Movement.hpp"

namespace gk {

class MovementStack {
	public:
		template<typename... Args>
		bool push(Args &&...args) {
			if(size() > 0 && top() && !top()->isFinished()) {
				return false;
			} else {
				m_movements.emplace(args...);
				return true;
			}
		}

		void pop() { m_movements.pop(); }

		std::unique_ptr<Movement> &top() { return m_movements.top(); }

		size_t size() const { return m_movements.size(); }

	private:
		std::stack<std::unique_ptr<Movement>> m_movements;
};

class MovementComponent {
	public:
		MovementComponent(Movement *_movement) {
			movements.push(_movement);
		}

		Vector2f v{0, 0};

		float speed = 1.0f;

		bool isMoving = false;
		bool isDirectionLocked = false;

		Vector2<bool> isBlocked;

		MovementStack movements;
};

} // namespace gk

#endif // GK_MOVEMENTCOMPONENT_HPP_
