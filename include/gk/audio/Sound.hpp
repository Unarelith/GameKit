/*
 * =====================================================================================
 *
 *       Filename:  Sound.hpp
 *
 *    Description:
 *
 *        Created:  15/09/2014 23:03:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
