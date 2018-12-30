/*
 * =====================================================================================
 *
 *       Filename:  AudioPlayer.hpp
 *
 *    Description:
 *
 *        Created:  28/04/2015 21:51:27
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_AUDIOPLAYER_HPP_
#define GK_AUDIOPLAYER_HPP_

#include <string>

#include "gk/core/IntTypes.hpp"

namespace gk {

class AudioPlayer {
	public:
		static void playMusic(const std::string &resourceName);

		static void playSound(const std::string &resourceName);
		static void repeatSound(const std::string &resourceName, u8 delay = 0);

		static void pauseMusic();
		static void resumeMusic();

		static bool isMusicPaused();
		static bool isMusicPlaying();

		static void setMuteState(bool muteState) { s_muteState = muteState; }

	private:
		static bool s_muteState;
};

} // namespace gk

#endif // GK_AUDIOPLAYER_HPP_
