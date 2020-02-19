/*
 * =====================================================================================
 *
 *  GameKit
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
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
			rect.setSize(hitbox->sizeX, hitbox->sizeY);
			rect.setWireframeMode(true); // FIXME
			rect.setFillColor(Color::White);

			target.draw(rect, states);
		}
	}
}

} // namespace gk

