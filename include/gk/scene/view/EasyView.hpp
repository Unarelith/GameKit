/*
 * =====================================================================================
 *
 *       Filename:  EasyView.hpp
 *
 *    Description:
 *
 *        Created:  20/04/2019 15:22:26
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_EASYVIEW_HPP_
#define GK_EASYVIEW_HPP_

#include <functional>

#include "gk/scene/view/AbstractView.hpp"

namespace gk {

class EasyView : public AbstractView {
	using Function = std::function<void(const SceneObject &object, gk::RenderTarget &target, gk::RenderStates states)>;

	public:
		EasyView(const Function &func) : m_func(func) {}

		void draw(const SceneObject &object, gk::RenderTarget &target, gk::RenderStates states) override {
			m_func(object, target, states);
		}

	private:
		Function m_func;
};

} // namespace gk

#endif // GK_EASYVIEW_HPP_
