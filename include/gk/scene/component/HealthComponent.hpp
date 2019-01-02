/*
 * =====================================================================================
 *
 *       Filename:  HealthComponent.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 16:38:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
