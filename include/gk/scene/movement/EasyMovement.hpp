/*
 * =====================================================================================
 *
 *       Filename:  EasyMovement.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:27:45
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_EASYMOVEMENT_HPP_
#define GK_EASYMOVEMENT_HPP_

#include <functional>

#include "gk/scene/movement/Movement.hpp"

namespace gk {

class EasyMovement : public Movement {
	public:
		EasyMovement(const std::function<void(SceneObject &)> &func) : m_func(func) {}

		void process(SceneObject &object) override {
			m_func(object);
		}

	private:
		std::function<void(SceneObject &)> m_func;
};

} // namespace gk

#endif // EASYMOVEMENT_HPP_
