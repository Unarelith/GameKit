/*
 * =====================================================================================
 *
 *       Filename:  AbstractView.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 00:41:03
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_ABSTRACTVIEW_HPP_
#define GK_ABSTRACTVIEW_HPP_

#include "gk/gl/RenderTarget.hpp"
#include "gk/scene/SceneObjectList.hpp"

namespace gk {

class AbstractView {
	public:
		virtual void draw(const SceneObject &object, RenderTarget &target, RenderStates states) = 0;

		virtual void draw(const SceneObjectList &objectList, RenderTarget &target, RenderStates states) {
			for(auto &object : objectList) {
				draw(object, target, states);

				if (object.has<SceneObjectList>())
					draw(object.get<SceneObjectList>(), target, states);
			}
		}
};

} // namespace gk

#endif // GK_ABSTRACTVIEW_HPP_
