/*
 * =====================================================================================
 *
 *       Filename:  Behaviour.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:44:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_BEHAVIOUR_HPP_
#define GK_BEHAVIOUR_HPP_

#include "gk/scene/SceneObject.hpp"

namespace gk {

class Behaviour {
	public:
		virtual void update(SceneObject &object) = 0;
};

} // namespace gk

#endif // GK_BEHAVIOUR_HPP_
