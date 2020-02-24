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
#ifndef GK_HEALTHCOMPONENT_HPP_
#define GK_HEALTHCOMPONENT_HPP_

#include "gk/core/Timer.hpp"

namespace gk {

class HealthComponent {
	public:
		HealthComponent(const u16 maxLife, const u16 life = 0, const u16 hurtTime = 0)
			: m_maxLife(maxLife), m_life(life ? life : maxLife), m_hurtTime(hurtTime) {}

		void setLife(const u16 newLife) { m_life = (newLife > m_maxLife) ? m_maxLife : newLife; }
		void addLife(const u16 lifeAdded) { setLife(m_life + lifeAdded); }
		void removeLife(const u16 lifeRemoved) {
			if (!m_hurtTime || !m_hurtTimer.isStarted() || m_hurtTimer.time() > m_hurtTime) {
				(lifeRemoved > m_life) ? setLife(0) : setLife(m_life - lifeRemoved);

				if (m_hurtTime) {
					m_hurtTimer.reset();
					m_hurtTimer.start();
				}
			}
		}

		u16 life() const { return m_life; }
		u16 maxLife() const { return m_maxLife; }

		Timer hurtTimer() { return m_hurtTimer; }

	private:
		const u16 m_maxLife = 0;
		u16 m_life = 0;

		const u16 m_hurtTime = 0;

		Timer m_hurtTimer;
};

} // namespace gk

#endif // GK_HEALTHCOMPONENT_HPP_
