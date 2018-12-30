/*
 * =====================================================================================
 *
 *       Filename:  Sound.cpp
 *
 *    Description:
 *
 *        Created:  15/09/2014 23:03:35
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/audio/Sound.hpp"
#include "gk/system/Exception.hpp"

namespace gk {

int Sound::s_lastUsedChannel = -1;

Sound::Sound(const std::string &filename) {
	openFromFile(filename);
}

void Sound::openFromFile(const std::string &filename) {
	m_channel = ++s_lastUsedChannel;

	m_sfx.reset(Mix_LoadWAV(filename.c_str()));
	if(!m_sfx) {
		throw EXCEPTION("Unable to load sound effect:", filename, ":", Mix_GetError());
	}

	m_timer.start();
}

void Sound::play() {
	Mix_Volume(m_channel, m_volume);
	Mix_PlayChannel(m_channel, m_sfx.get(), 0);
}

void Sound::repeat(u16 delay) {
	if(m_timer.time() > delay) {
		play();

		m_timer.reset();
		m_timer.start();
	}
}

} // namespace gk

