/*
 * =====================================================================================
 *
 *       Filename:  HitboxView.cpp
 *
 *    Description:
 *
 *        Created:  21/04/2018 09:24:07
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/graphics/RectangleShape.hpp"
#include "gk/scene/component/HitboxComponent.hpp"
#include "gk/scene/view/HitboxView.hpp"
#include "gk/scene/component/LifetimeComponent.hpp"
#include "gk/scene/component/PositionComponent.hpp"

namespace gk {

void HitboxView::draw(const SceneObject &object, RenderTarget &target, RenderStates states) {
	if (object.has<LifetimeComponent>() && object.get<LifetimeComponent>().dead(object))
		return;

	if (object.has<PositionComponent>()) {
		states.transform.translate(object.get<PositionComponent>().x, object.get<PositionComponent>().y);
	}

	if (object.has<HitboxComponent>()) {
		const FloatRect *hitbox = object.get<HitboxComponent>().currentHitbox();
		if(hitbox) {
			RectangleShape rect;
			rect.setPosition(hitbox->x, hitbox->y);
			rect.setSize(hitbox->width, hitbox->height);
			rect.setWireframeMode(true); // FIXME
			rect.setFillColor(Color::White);

			target.draw(rect, states);
		}
	}
}

} // namespace gk

