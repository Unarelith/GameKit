/*
 * =====================================================================================
 *
 *       Filename:  MovementComponent.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:41:03
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
