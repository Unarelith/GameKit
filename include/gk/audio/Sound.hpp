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
#ifndef GK_SOUND_HPP_
#define GK_SOUND_HPP_

#include <memory>
#include <string>

#include "gk/core/SDLHeaders.hpp"
#include "gk/core/Timer.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Sound effect
///
////////////////////////////////////////////////////////////
class Sound {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		////////////////////////////////////////////////////////////
		Sound() = default;

		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param filename Path of the sound effect file to use
		///
		////////////////////////////////////////////////////////////
		Sound(const std::string &filename);

		////////////////////////////////////////////////////////////
		/// \brief Load file
		///
		/// \param filename Path of the sound effect file to use
		///
		////////////////////////////////////////////////////////////
		void openFromFile(const std::string &filename);

		////////////////////////////////////////////////////////////
		/// \brief Play the sound effect
		///
		////////////////////////////////////////////////////////////
		void play();

		////////////////////////////////////////////////////////////
		/// \brief Repeat the sound effect
		///
		/// \param delay Time in milliseconds to wait before replaying
		///
		////////////////////////////////////////////////////////////
		void repeat(u16 delay);

		////////////////////////////////////////////////////////////
		/// \brief Set the channel to use
		///
		/// \param channel Sound effect channel
		///
		////////////////////////////////////////////////////////////
		void setChannel(int channel) { m_channel = channel; }

		////////////////////////////////////////////////////////////
		/// \brief Set the volume
		///
		/// \param volume Volume
		///
		////////////////////////////////////////////////////////////
		void setVolume(int volume) { m_volume = volume; }

	private:
		static int s_lastUsedChannel;

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		using Mix_ChunkPtr = std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>;
		Mix_ChunkPtr m_sfx{nullptr, Mix_FreeChunk}; ///< Internal SDL_mixer sound effect pointer

		Timer m_timer;                              ///< Timer used for SoundEffect::repeat

		int m_channel = -1;                         ///< Sound effect channel
		int m_volume = MIX_MAX_VOLUME;              ///< Volume
};

} // namespace gk

#endif // GK_SOUND_HPP_

////////////////////////////////////////////////////////////
/// \class gk::SoundEffect
/// \ingroup audio
///
////////////////////////////////////////////////////////////
