/*
 * =====================================================================================
 *
 *       Filename:  GamePadMovement.hpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:41:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_GAMEPADMOVEMENT_HPP_
#define GK_GAMEPADMOVEMENT_HPP_

#include "gk/core/input/InputHandler.hpp"
#include "gk/scene/movement/Movement.hpp"

namespace gk {

class GamePadMovement : public Movement {
	public:
		void process(SceneObject &object) override;

		void setKeys(GameKey left, GameKey right, GameKey up, GameKey down) {
			m_left = left;
			m_right = right;
			m_up = up;
			m_down = down;
		}

	private:
		GameKey m_left;
		GameKey m_right;
		GameKey m_up;
		GameKey m_down;
};

} // namespace gk

#endif // GK_GAMEPADMOVEMENT_HPP_
