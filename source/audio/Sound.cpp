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
#include "gk/audio/Sound.hpp"
#include "gk/core/Exception.hpp"

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

