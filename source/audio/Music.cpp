/*
 * =====================================================================================
 *
 *       Filename:  BackgroundMusic.cpp
 *
 *    Description:
 *
 *        Created:  15/09/2014 23:03:51
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/audio/Music.hpp"
#include "gk/system/Exception.hpp"

namespace gk {

Music::Music(const std::string &filename) {
	openFromFile(filename);
}

void Music::openFromFile(const std::string &filename) {
	m_music.reset(Mix_LoadMUS(filename.c_str()));
	if(!m_music) {
		throw EXCEPTION("Unable to load music:", filename, ":", Mix_GetError());
	}
}

void Music::play() {
	Mix_VolumeMusic(m_volume);
	Mix_PlayMusic(m_music.get(), -1);
}

} // namespace gk

