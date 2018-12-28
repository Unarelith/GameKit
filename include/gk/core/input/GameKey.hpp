/*
 * =====================================================================================
 *
 *       Filename:  GameKey.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:11:06
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_GAMEKEY_HPP_
#define GK_GAMEKEY_HPP_

namespace gk {

enum class GameKey {
	Left,
	Right,
	Up,
	Down,

	Jump,
	Fly,
	Sneak,

	Dig,
	Use,

	Inventory,
};

} // namespace gk

#endif // GK_GAMEKEY_HPP_
