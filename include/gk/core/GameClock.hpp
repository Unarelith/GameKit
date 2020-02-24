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
#ifndef GK_GAMECLOCK_HPP_
#define GK_GAMECLOCK_HPP_

#include <functional>

#include "gk/core/Timer.hpp"

namespace gk {

class GameClock {
	public:
		static u32 getTicks(bool realTime = false);
		static u16 getFpsAverage() { return fps; }

		void updateGame(std::function<void(void)> updateFunc);
		void drawGame(std::function<void(void)> drawFunc);

		void waitForNextFrame();

		void startFpsTimer() { m_fpsTimer.start(); }

		void setTimestep(u8 timestep) { m_timestep = timestep; }

	private:
		void measureLastFrameDuration();
		void computeFramesPerSecond();

		static u32 ticks;
		static u16 fps;

		u32 m_lastFrameDate = 0;
		u32 m_lag = 0;
		u32 m_timeDropped = 0;

		u8 m_timestep = 6;
		u8 m_numUpdates = 0;

		Timer m_fpsTimer{true};
		u16 m_frames = 0;
};

} // namespace gk

#endif // GK_GAMECLOCK_HPP_
