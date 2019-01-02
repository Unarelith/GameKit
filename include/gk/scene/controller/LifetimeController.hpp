/*
 * =====================================================================================
 *
 *       Filename:  LifetimeController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:19:16
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_LIFETIMECONTROLLER_HPP_
#define GK_LIFETIMECONTROLLER_HPP_

#include "gk/scene/controller/AbstractController.hpp"

namespace gk {

class LifetimeController : public AbstractController {
	public:
		void update(SceneObjectList &objectList) override;
		void update(SceneObject &) override {}

		bool isGlobal() const override { return true; }
};

} // namespace gk

#endif // GK_LIFETIMECONTROLLER_HPP_
