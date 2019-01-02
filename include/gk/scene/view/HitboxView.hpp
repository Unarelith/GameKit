/*
 * =====================================================================================
 *
 *       Filename:  HitboxView.hpp
 *
 *    Description:
 *
 *        Created:  21/04/2018 09:23:48
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_HITBOXVIEW_HPP_
#define GK_HITBOXVIEW_HPP_

#include "gk/scene/view/AbstractView.hpp"

namespace gk {

class HitboxView : public AbstractView {
	public:
		void draw(const SceneObject &object, RenderTarget &target, RenderStates states);
};

} // namespace gk

#endif // GK_HITBOXVIEW_HPP_
