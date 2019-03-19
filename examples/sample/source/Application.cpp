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

	createWindow(640, 480, "sample");

	m_shader.loadFromFile("shaders/game.v.glsl", "shaders/game.f.glsl");
	m_renderStates.shader = &m_shader;

	m_stateStack.push<GameState>();
}

void Application::onEvent(const SDL_Event &event) {
	gk::CoreApplication::onEvent(event);

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
		m_window.close();
	}
}

