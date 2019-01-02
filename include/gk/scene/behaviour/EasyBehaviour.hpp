/*
 * =====================================================================================
 *
 *       Filename:  EasyBehaviour.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:52:45
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_EASYBEHAVIOUR_HPP_
#define GK_EASYBEHAVIOUR_HPP_

#include <functional>

#include "gk/scene/behaviour/Behaviour.hpp"

namespace gk {

class EasyBehaviour : public Behaviour {
	public:
		EasyBehaviour(const std::function<void(SceneObject &)> &func) : m_func(func) {}

		void update(SceneObject &object) override {
			m_func(object);
		}

	private:
		std::function<void(SceneObject &)> m_func;
};

} // namespace gk

#endif // GK_EASYBEHAVIOUR_HPP_
