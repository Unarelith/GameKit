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

#include <gk/core/ApplicationState.hpp>
#include <gk/graphics/RectangleShape.hpp>

class GameState : public gk::ApplicationState {
	public:
		GameState();

		void update() override;

	private:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

		gk::RectangleShape m_rect{50, 50, gk::Color::Red};
};

#endif // GAMESTATE_HPP_
