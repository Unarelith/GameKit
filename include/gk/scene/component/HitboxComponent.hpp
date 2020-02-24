/*
 * =====================================================================================
 *
 *  GameKit
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2020 the GameKit contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of GameKit.
 *
 *  GameKit is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  GameKit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with GameKit; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#ifndef GK_HITBOXCOMPONENT_HPP_
#define GK_HITBOXCOMPONENT_HPP_

#include <vector>

#include "gk/core/Rect.hpp"
#include "gk/core/Exception.hpp"

namespace gk {

class HitboxComponent {
	public:
		HitboxComponent(s8 currentHitboxID = 0)
			: m_currentHitboxID(currentHitboxID) {}

		HitboxComponent(s16 x, s16 y, u16 width, u16 height) : HitboxComponent(0) {
			addHitbox(x, y, width, height);
		}

		void addHitbox(s16 x, s16 y, u16 width, u16 height) {
			m_hitboxes.emplace_back(x, y, width, height);
		}

		const FloatRect *currentHitbox() const {
			if(m_currentHitboxID >= 0 && m_currentHitboxID < (s16)m_hitboxes.size()) {
				return &m_hitboxes[m_currentHitboxID];
			} else {
				return nullptr;
			}
		}

		void setCurrentHitbox(u8 id) {
			if(id < m_hitboxes.size()) {
				m_currentHitboxID = id;
			} else {
				throw EXCEPTION("Hitbox ID out of range:", (s16)id, "| Array size:", m_hitboxes.size());
			}
		}

		void resetCurrentHitbox() { m_currentHitboxID = -1; }

	private:
		s8 m_currentHitboxID = -1;

		std::vector<FloatRect> m_hitboxes;
};

} // namespace gk

#endif // GK_HITBOXCOMPONENT_HPP_
