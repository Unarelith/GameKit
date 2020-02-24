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
#include "gk/core/Exception.hpp"
#include "gk/core/SDLHeaders.hpp"
#include "gk/core/SDLLoader.hpp"

namespace gk {

SDLLoader::~SDLLoader() {
	if(m_mixInitialized) Mix_CloseAudio();
	if(m_ttfInitialized) TTF_Quit();
	if(m_imgInitialized) IMG_Quit();
	if(m_sdlInitialized) SDL_Quit();
}

void SDLLoader::load() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw EXCEPTION("SDL init error:", SDL_GetError());
	} else {
		m_sdlInitialized = true;
	}

	int imgFlags = IMG_INIT_PNG;
	if((!IMG_Init(imgFlags)) & imgFlags) {
		throw EXCEPTION("SDL_image init error:", IMG_GetError());
	} else {
		m_imgInitialized = true;
	}

	if(TTF_Init() < 0) {
		throw EXCEPTION("SDL_ttf init error:", TTF_GetError());
	} else {
		m_ttfInitialized = true;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
		throw EXCEPTION("SDL_mixer init error:", Mix_GetError());
	} else {
		m_mixInitialized = true;
	}

	Mix_AllocateChannels(32);

	Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
	Mix_Volume(-1, MIX_MAX_VOLUME);
}

} // namespace gk

