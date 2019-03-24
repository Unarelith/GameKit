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
#include <SFML/Graphics/RectangleShape.hpp>

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
		const sf::FloatRect *hitbox = object.get<HitboxComponent>().currentHitbox();
		if(hitbox) {
			sf::RectangleShape rect;
			rect.setPosition(hitbox->left, hitbox->top);
			rect.setSize({hitbox->width, hitbox->height});
			rect.setOutlineThickness(true); // FIXME
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::White);

			// target.draw(rect, states); // FIXME
		}
	}
}

} // namespace gk

