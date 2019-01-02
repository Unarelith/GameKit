/*
 * =====================================================================================
 *
 *       Filename:  SpriteView.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:29:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_SPRITEVIEW_HPP_
#define GK_SPRITEVIEW_HPP_

#include "gk/scene/view/AbstractView.hpp"

namespace gk {

class SpriteView : public AbstractView {
	public:
		void draw(const SceneObject &object, RenderTarget &target, RenderStates states) override;
};

} // namespace gk

#endif // GK_SPRITEVIEW_HPP_
