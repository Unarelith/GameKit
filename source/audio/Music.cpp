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
#include "gk/audio/Music.hpp"
#include "gk/core/Exception.hpp"

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

