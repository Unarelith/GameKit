/*
 * =====================================================================================
 *
 *       Filename:  CollisionHelper.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:39:25
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_COLLISIONHELPER_HPP_
#define GK_COLLISIONHELPER_HPP_

#include "gk/scene/SceneObject.hpp"

namespace gk {

class CollisionHelper {
	public:
		virtual ~CollisionHelper() = default;

		void checkCollision(SceneObject &object1, SceneObject &object2);

		virtual bool inCollision(SceneObject &object1, SceneObject &object2);
};

} // namespace gk

#endif // GK_COLLISIONHELPER_HPP_
