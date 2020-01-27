/*
 * =====================================================================================
 *
 *       Filename:  GameClock.cpp
 *
 *    Description:
 *
 *        Created:  14/12/2014 13:42:26
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
