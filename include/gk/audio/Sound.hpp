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
#ifndef GK_SOUND_HPP_
#define GK_SOUND_HPP_

#include <memory>
#include <string>

#include "gk/core/SDLHeaders.hpp"
#include "gk/core/Timer.hpp"

namespace gk {

class Sound {
	public:
		Sound() = default;
		Sound(const std::string &filename);

		void openFromFile(const std::string &filename);

		void play();

		void repeat(u16 delay);

		void setChannel(int channel) { m_channel = channel; }
		void setVolume(int volume) { m_volume = volume; }

	private:
		static int s_lastUsedChannel;

		using Mix_ChunkPtr = std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>;

		Mix_ChunkPtr m_sfx{nullptr, Mix_FreeChunk};

		Timer m_timer;

		int m_channel = -1;
		int m_volume = MIX_MAX_VOLUME;
};

} // namespace gk

#endif // GK_SOUND_HPP_
