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
#include "gk/core/SDLHeaders.hpp"
#include "gk/core/GameClock.hpp"

namespace gk {

u32 GameClock::ticks = 0;
u16 GameClock::fps = 0;

u32 GameClock::getTicks(bool realTime) {
	if(realTime) {
		return SDL_GetTicks();
	} else {
		return ticks;
	}
}

void GameClock::updateGame(std::function<void(void)> updateFunc) {
	m_numUpdates = 0;

	while(m_lag >= m_timestep && m_numUpdates < 10) {
		ticks += m_timestep;

		updateFunc();

		m_lag -= m_timestep;
		m_numUpdates++;
	}
}

void GameClock::drawGame(std::function<void(void)> drawFunc) {
	if(m_numUpdates > 0) {
		drawFunc();
		++m_frames;
	}

	computeFramesPerSecond();
	waitForNextFrame();
}

void GameClock::waitForNextFrame() {
	u32 lastFrameDuration = getTicks(true) - m_timeDropped - m_lastFrameDate;

	if(lastFrameDuration < m_timestep) {
		SDL_Delay(m_timestep - lastFrameDuration);
	}

	measureLastFrameDuration();
}

void GameClock::measureLastFrameDuration() {
	u32 now = getTicks(true) - m_timeDropped;
	u32 lastFrameDuration = now - m_lastFrameDate;

	m_lastFrameDate = now;
	m_lag += lastFrameDuration;

	if(m_lag >= 200) {
		m_timeDropped += m_lag - m_timestep;
		m_lag = m_timestep;
		m_lastFrameDate = getTicks(true) - m_timeDropped;
	}
}

void GameClock::computeFramesPerSecond() {
	if (m_fpsTimer.time() > 1000) {
		fps = m_frames / (m_fpsTimer.time() / 1000.0f);

		m_fpsTimer.reset();
		m_fpsTimer.start();

		m_frames = 0;
	}
}

} // namespace gk
