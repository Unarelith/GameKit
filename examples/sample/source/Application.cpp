/*
 * =====================================================================================
 *
 *       Filename:  Application.cpp
 *
 *    Description:
 *
 *        Created:  19/03/2019 13:42:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "GameState.hpp"

void Application::init() {
	gk::CoreApplication::init();

	m_window.create(640, 480, "sample");

	m_shader.loadFromFile("shaders/game.v.glsl", "shaders/game.f.glsl");
	m_renderStates.shader = &m_shader;

	m_stateStack.push<GameState>();
}

void Application::onEvent(const sf::Event &event) {
	gk::CoreApplication::onEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		m_isRunning = false;
	}
}

