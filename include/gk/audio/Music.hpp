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
#ifndef GK_MUSIC_HPP_
#define GK_MUSIC_HPP_

#include <memory>
#include <string>

#include "gk/core/SDLHeaders.hpp"

namespace gk {

class Music {
	public:
		Music() = default;
		Music(const std::string &filename);

		void openFromFile(const std::string &filename);

		void play();

		void setVolume(int volume) { m_volume = volume; }

	private:
		using Mix_MusicPtr = std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>;

		Mix_MusicPtr m_music{nullptr, Mix_FreeMusic};

		int m_volume = MIX_MAX_VOLUME;
};

} // namespace gk

#endif // GK_BACKGROUNDMUSIC_HPP_
