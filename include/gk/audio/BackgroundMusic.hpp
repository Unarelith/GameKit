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
#ifndef BACKGROUNDMUSIC_HPP_
#define BACKGROUNDMUSIC_HPP_

#include <memory>
#include <string>

#include "gk/core/SDLHeaders.hpp"

namespace gk {

class BackgroundMusic {
	public:
		BackgroundMusic() = default;
		BackgroundMusic(const std::string &filename);

		void load(const std::string &filename);

		void play();

	private:
		using Mix_MusicPtr = std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>;

		Mix_MusicPtr m_music{nullptr, Mix_FreeMusic};
};

} // namespace gk

#endif // GK_BACKGROUNDMUSIC_HPP_
