/*
 * =====================================================================================
 *
 *       Filename:  AbstractView.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 00:41:03
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_ABSTRACTVIEW_HPP_
#define GK_ABSTRACTVIEW_HPP_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "gk/scene/SceneObjectList.hpp"

namespace gk {

class AbstractView {
	public:
		virtual ~AbstractView() = default;

		virtual void draw(const SceneObject &object, sf::RenderTarget &target, sf::RenderStates states) = 0;

		virtual void draw(const SceneObjectList &objectList, sf::RenderTarget &target, sf::RenderStates states) {
			for(auto &object : objectList) {
				draw(object, target, states);

				if (object.has<SceneObjectList>())
					draw(object.get<SceneObjectList>(), target, states);
			}
		}
};

} // namespace gk

#endif // GK_ABSTRACTVIEW_HPP_
