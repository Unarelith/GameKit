/*
 * =====================================================================================
 *
 *       Filename:  PositionComponent.hpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 00:04:22
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_POSITIONCOMPONENT_HPP_
#define GK_POSITIONCOMPONENT_HPP_

#include <SFML/System/Vector2.hpp>

namespace gk {

class PositionComponent : public sf::Vector2f {
	public:
		PositionComponent(float x, float y) : sf::Vector2f(x, y) {}
		PositionComponent(const sf::Vector2f &pos) : sf::Vector2f(pos) {}
};

} // namespace gk

#endif // GK_POSITIONCOMPONENT_HPP_
