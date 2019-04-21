/*
 * =====================================================================================
 *
 *       Filename:  EasyController.hpp
 *
 *    Description:
 *
 *        Created:  20/04/2019 15:26:02
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_EASYCONTROLLER_HPP_
#define GK_EASYCONTROLLER_HPP_

#include <functional>

#include "gk/scene/controller/AbstractController.hpp"

namespace gk {

class EasyController : public AbstractController {
	using Function = std::function<void(SceneObject &object)>;

	public:
		EasyController(const Function &func) : m_func(func) {}

		void update(SceneObject &object) override {
			m_func(object);
		}

	private:
		Function m_func;
};

} // namespace gk

#endif // GK_EASYCONTROLLER_HPP_
