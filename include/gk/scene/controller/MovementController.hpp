/*
 * =====================================================================================
 *
 *       Filename:  MovementController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:17:11
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_MOVEMENTCONTROLLER_HPP_
#define GK_MOVEMENTCONTROLLER_HPP_

#include "gk/scene/controller/AbstractController.hpp"

namespace gk {

class MovementController : public AbstractController {
	public:
		void update(SceneObject &object) override;
};

} // namespace gk

#endif // GK_MOVEMENTCONTROLLER_HPP_
