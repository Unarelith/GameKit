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
#include <ctime>

#include "gk/audio/AudioPlayer.hpp"
#include "gk/core/CoreApplication.hpp"
#include "gk/core/Mouse.hpp"
#include "gk/core/Exception.hpp"

namespace gk {

CoreApplication::CoreApplication(int argc, char **argv) : m_argumentParser(argc, argv) {
}

void CoreApplication::init() {
	std::srand(std::time(nullptr));

	Mouse::setWindow(&m_window);

	ApplicationStateStack::setInstance(m_stateStack);
	GameClock::setInstance(m_clock);
	ResourceHandler::setInstance(m_resourceHandler);

	m_stateStack.setEventHandler(m_eventHandler);

	m_argumentParser.addArgument("mute", {"", "--mute", "Mute the program."});
	m_argumentParser.parse();
	if (m_argumentParser.getArgument("mute").isFound)
		AudioPlayer::setMuteState(true);
	// m_argumentParser.debug();
}

int CoreApplication::run(bool isProtected) {
	auto runGame = [&]() {
		if (m_loadSDL)
			m_sdlLoader.load();

		init();
		mainLoop();
	};

	if (isProtected) {
		try {
			runGame();
		}
		catch(const Exception &e) {
			std::cerr << "Fatal error " << e.what() << std::endl;
			return 1;
		}
		// catch(const std::exception &e) {
		// 	std::cerr << "Exception caught: " << e.what() << std::endl;
		// 	return 1;
		// }
		// catch(...) {
		// 	std::cerr << "Fatal error: Unknown error." << std::endl;
		// 	return 1;
		// }
	}
	else {
		runGame();
	}

	m_resourceHandler.clear();

	return 0;
}

void CoreApplication::createWindow(u16 screenWidth, u16 screenHeight, const char *windowTitle) {
	m_window.open(windowTitle, screenWidth, screenHeight);
}

void CoreApplication::onEvent(const SDL_Event &event) {
	if (event.type == SDL_QUIT) {
		m_window.close();
	}
}

void CoreApplication::handleEvents() {
	gk::ApplicationState *currentState = nullptr;
	if (!m_stateStack.empty())
		currentState = &m_stateStack.top();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		onEvent(event);

		m_window.onEvent(event);

		if (currentState && !m_stateStack.empty())
			currentState->onEvent(event);
	}
}

void CoreApplication::mainLoop() {
	m_clock.startFpsTimer();

	while(m_window.isOpen() && !m_stateStack.empty()) {
		handleEvents();

		m_eventHandler.processEvents();

		m_clock.updateGame([&] {
			if (!m_stateStack.empty())
				m_stateStack.top().update();

			m_stateStack.clearDeletedStates();
		});

		m_clock.drawGame([&] {
			m_window.clear();

			if(!m_stateStack.empty())
				m_window.draw(m_stateStack.top(), m_renderStates);

			m_window.display();
		});
	}
}

} // namespace gk

