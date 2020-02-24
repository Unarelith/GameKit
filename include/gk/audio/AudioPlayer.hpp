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
