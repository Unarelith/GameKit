/*
 * =====================================================================================
 *
 *       Filename:  CoreApplication.cpp
 *
 *    Description:
 *
 *        Created:  14/06/2018 02:00:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <ctime>

#include "gk/core/input/GamePad.hpp"
#include "gk/core/CoreApplication.hpp"
#include "gk/core/Mouse.hpp"
#include "gk/core/Exception.hpp"
#include "gk/resource/AudioPlayer.hpp"

namespace gk {

CoreApplication::CoreApplication(int argc, char **argv) : m_argumentParser(argc, argv) {
}

void CoreApplication::init() {
	std::srand(std::time(nullptr));

	Mouse::setWindow(&m_window);

	ApplicationStateStack::setInstance(m_stateStack);
	ResourceHandler::setInstance(m_resourceHandler);

	m_argumentParser.addArgument("mute", {"", "--no-sound"});
	m_argumentParser.parse();
	if (m_argumentParser.getArgument("mute").isFound)
		AudioPlayer::setMuteState(true);
	// m_argumentParser.debug();
}

int CoreApplication::run(bool isProtected) {
	auto runGame = [&]() {
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

	return 0;
}

void CoreApplication::createWindow(sf::VideoMode mode, const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings) {
	m_window.create(mode, title, style, settings);

	auto desktop = sf::VideoMode::getDesktopMode();
	m_window.setPosition(sf::Vector2i(
		desktop.width / 2 - m_window.getSize().x / 2,
		desktop.height / 2 - m_window.getSize().y / 2
	));
}

void CoreApplication::onEvent(const sf::Event &event) {
	if (event.type == sf::Event::Closed) {
		m_isRunning = false;
	}
}

void CoreApplication::handleEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		onEvent(event);

		if (GamePad::getInputHandler())
			GamePad::getInputHandler()->updateState(event);

		if (!m_stateStack.empty())
			m_stateStack.top().onEvent(event);
	}
}

void CoreApplication::mainLoop() {
	while(m_isRunning && m_stateStack.size()) {
		handleEvents();

		m_clock.updateGame([&] {
			if (!m_stateStack.empty())
				m_stateStack.top().update();

			m_stateStack.clearDeletedStates();
		});

		m_clock.drawGame([&] {
			m_window.clear();

			if(!m_stateStack.empty())
				m_window.draw(m_stateStack.top());

			m_window.display();
		});
	}
}

} // namespace gk

