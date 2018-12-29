/*
 * =====================================================================================
 *
 *       Filename:  SoundEffect.hpp
 *
 *    Description:
 *
 *        Created:  15/09/2014 23:03:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_SOUNDEFFECT_HPP_
#define GK_SOUNDEFFECT_HPP_

#include <memory>
#include <string>

#include "gk/core/SDLHeaders.hpp"
#include "gk/core/Timer.hpp"

namespace gk {

class SoundEffect {
	public:
		SoundEffect() = default;
		SoundEffect(const std::string &filename);

		void load(const std::string &filename);

		void play(s8 channel = -1);

		void repeat(u16 delay, s8 channel = -1);

	private:
		using Mix_ChunkPtr = std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>;

		Mix_ChunkPtr m_sfx{nullptr, Mix_FreeChunk};

		gk::Timer m_timer;
};

} // namespace gk

#endif // GK_SOUNDEFFECT_HPP_
