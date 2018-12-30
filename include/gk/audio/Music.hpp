/*
 * =====================================================================================
 *
 *       Filename:  BackgroundMusic.hpp
 *
 *    Description:
 *
 *        Created:  15/09/2014 23:03:43
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
