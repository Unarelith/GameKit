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
#include <cmath>

#include "gk/core/SDLHeaders.hpp"
#include "gk/core/GameClock.hpp"

namespace gk {

GameClock *GameClock::s_instance = nullptr;

u32 GameClock::getTicks(bool realTime) {
	std::lock_guard<std::mutex> lock(m_mutex);

	if(realTime) {
		return SDL_GetTicks();
	} else {
		return m_ticks;
	}
}

void GameClock::updateGame(std::function<void(void)> updateFunc) {
	std::unique_lock<std::mutex> lock(m_mutex);

	m_numUpdates = 0;

	while(m_lag >= m_timestep && m_numUpdates < 10) {
		m_ticks += m_timestep;

		lock.unlock();
		updateFunc();
		lock.lock();

		m_lag -= m_timestep;
		m_numUpdates++;
	}
}

void GameClock::drawGame(std::function<void(void)> drawFunc) {
	std::unique_lock<std::mutex> lock(m_mutex);

	if(m_numUpdates > 0) {
		lock.unlock();
		drawFunc();
		lock.lock();
		++m_frames;
	}

	lock.unlock();

	computeFramesPerSecond();
	waitForNextFrame();
}

void GameClock::waitForNextFrame() {
	u32 currentTicks = getTicks(true);

	std::unique_lock<std::mutex> lock(m_mutex);

	u32 lastFrameDuration = currentTicks - m_timeDropped - m_lastFrameDate;

	if(lastFrameDuration < m_timestep) {
		SDL_Delay(m_timestep - lastFrameDuration);
	}

	lock.unlock();

	measureLastFrameDuration();
}

void GameClock::measureLastFrameDuration() {
	u32 currentTicks = getTicks(true);

	std::lock_guard<std::mutex> lock(m_mutex);

	u32 now = currentTicks - m_timeDropped;
	u32 lastFrameDuration = now - m_lastFrameDate;

	m_lastFrameDate = now;
	m_lag += lastFrameDuration;

	if(m_lag >= 200) {
		m_timeDropped += m_lag - m_timestep;
		m_lag = m_timestep;
		m_lastFrameDate = currentTicks - m_timeDropped;
	}
}

void GameClock::computeFramesPerSecond() {
	u32 currentTicks = getTicks(true);

	std::unique_lock<std::mutex> lock(m_mutex);

	if (currentTicks - m_fpsTimer > 1000) {
		m_fps = floor(m_frames / ((currentTicks - m_fpsTimer) / 1000.0) + 0.5);
		m_fpsTimer = currentTicks;

		m_frames = 0;
	}
}

} // namespace gk
