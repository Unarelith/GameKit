/*
 * =====================================================================================
 *
 *       Filename:  GameState.cpp
 *
 *    Description:
 *
 *        Created:  19/03/2019 13:49:09
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "GameState.hpp"

GameState::GameState() {
	m_rect.setPosition(100, 100);
}

void GameState::update() {
}

void GameState::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	target.draw(m_rect, states);
}

