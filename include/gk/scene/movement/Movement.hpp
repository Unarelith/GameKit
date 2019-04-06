/*
 * =====================================================================================
 *
 *       Filename:  Movement.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:41:30
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_MOVEMENT_HPP_
#define GK_MOVEMENT_HPP_

#include "gk/scene/SceneObject.hpp"

namespace gk {

class Movement {
	public:
		virtual ~Movement() = default;

		virtual void process(SceneObject &object) = 0;

		bool isFinished() const { return m_isFinished; }

	protected:
		bool m_isFinished = false;
};

} // namespace gk

#endif // GK_MOVEMENT_HPP_
