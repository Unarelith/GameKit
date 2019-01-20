/*
 * =====================================================================================
 *
 *       Filename:  AbstractController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 00:40:03
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_ABSTRACTCONTROLLER_HPP_
#define GK_ABSTRACTCONTROLLER_HPP_

#include "gk/scene/SceneObjectList.hpp"

namespace gk {

class AbstractController {
	public:
		virtual ~AbstractController() = default;

		virtual void reset(SceneObject &) {}
		virtual void update(SceneObject &object) = 0;

		virtual void reset(SceneObjectList &objectList) { for(auto &object : objectList) reset(object); }
		virtual void update(SceneObjectList &objectList) { for(auto &object : objectList) update(object); }

		virtual bool isGlobal() const { return false; }
};

} // namespace gk

#endif // GK_ABSTRACTCONTROLLER_HPP_
