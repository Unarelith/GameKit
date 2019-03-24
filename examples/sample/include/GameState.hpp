/*
 * =====================================================================================
 *
 *       Filename:  GameState.hpp
 *
 *    Description:
 *
 *        Created:  19/03/2019 13:48:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <SFML/Graphics/RectangleShape.hpp>

#include <gk/core/ApplicationState.hpp>

class GameState : public gk::ApplicationState {
	public:
		GameState();

		void update() override;

	private:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

		sf::RectangleShape m_rect;
};

#endif // GAMESTATE_HPP_
