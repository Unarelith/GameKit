/*
 * =====================================================================================
 *
 *       Filename:  GameClock.hpp
 *
 *    Description:
 *
 *        Created:  14/12/2014 13:42:17
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_GAMECLOCK_HPP_
#define GK_GAMECLOCK_HPP_

#include <functional>

#include <SFML/System/Clock.hpp>

#include "gk/core/IntTypes.hpp"

namespace gk {

class GameClock {
	public:
		static u32 getTicks(bool realTime = false);

		void measureLastFrameDuration();

		void updateGame(const std::function<void(void)> &updateFunc);

		void drawGame(const std::function<void(void)> &drawFunc);

		void waitForNextFrame();

		void setTimestep(u8 timestep) { m_timestep = timestep; }

	private:
		static u32 ticks;
		static sf::Clock clock;

		u32 m_lastFrameDate = 0;
		u32 m_lag = 0;
		u32 m_timeDropped = 0;

		u8 m_timestep = 6;
		u8 m_numUpdates = 0;
};

} // namespace gk

#endif // GK_GAMECLOCK_HPP_
