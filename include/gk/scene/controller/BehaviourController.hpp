/*
 * =====================================================================================
 *
 *       Filename:  BehaviourController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:25:12
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_BEHAVIOURCONTROLLER_HPP_
#define GK_BEHAVIOURCONTROLLER_HPP_

#include "gk/scene/controller/AbstractController.hpp"

namespace gk {

class BehaviourController : public AbstractController {
	public:
		void update(SceneObject &object) override;
};

} // namespace gk

#endif // GK_BEHAVIOURCONTROLLER_HPP_
