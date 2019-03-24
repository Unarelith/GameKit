/*
 * =====================================================================================
 *
 *       Filename:  HitboxComponent.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:53:26
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_HITBOXCOMPONENT_HPP_
#define GK_HITBOXCOMPONENT_HPP_

#include <vector>

#include <SFML/Graphics/Rect.hpp>

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

		const sf::FloatRect *currentHitbox() const {
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

		std::vector<sf::FloatRect> m_hitboxes;
};

} // namespace gk

#endif // GK_HITBOXCOMPONENT_HPP_
