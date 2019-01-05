/*
 * =====================================================================================
 *
 *       Filename:  SpriteView.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:30:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/graphics/Image.hpp"
#include "gk/graphics/RectangleShape.hpp"
#include "gk/graphics/Sprite.hpp"
#include "gk/scene/component/HitboxComponent.hpp"
#include "gk/scene/component/LifetimeComponent.hpp"
#include "gk/scene/component/PositionComponent.hpp"
#include "gk/scene/view/SpriteView.hpp"

namespace gk {

void SpriteView::draw(const SceneObject &object, RenderTarget &target, RenderStates states) {
	if (object.has<LifetimeComponent>() && object.get<LifetimeComponent>().dead(object))
		return;

	if (object.has<PositionComponent>())
		states.transform.translate({object.get<PositionComponent>(), 0.f});

	if(object.has<Image>()) {
		target.draw(object.get<Image>(), states);
	}

	if(object.has<Sprite>()) {
		target.draw(object.get<Sprite>(), states);
	}
}

} // namespace gk

