/*
 * =====================================================================================
 *
 *       Filename:  ApplicationStateStack.hpp
 *
 *    Description:
 *
 *        Created:  14/12/2014 13:48:48
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_APPLICATIONSTATESTACK_HPP_
#define GK_APPLICATIONSTATESTACK_HPP_

#include <memory>
#include <stack>

#include "gk/core/ApplicationState.hpp"

namespace gk {

class ApplicationStateStack {
	public:
		template<typename T, typename... Args>
		auto push(Args &&...args) -> typename std::enable_if<std::is_base_of<ApplicationState, T>::value, T&>::type {
			m_states.emplace(std::make_shared<T>(std::forward<Args>(args)...));
			m_states.top()->setStateStack(this);
			return static_cast<T&>(top());
		}

		void pop();
		void clear() { while(!empty()) pop(); }

		void clearDeletedStates();

		ApplicationState &top() const { return *m_states.top().get(); }

		bool empty() const { return m_states.empty(); }

		std::size_t size() const { return m_states.size(); }

		static ApplicationStateStack &getInstance() {
			return *s_instance;
		}

		static void setInstance(ApplicationStateStack &instance) {
			s_instance = &instance;
		}

	private:
		static ApplicationStateStack *s_instance;

		std::stack<std::shared_ptr<ApplicationState>> m_states;
		std::stack<std::shared_ptr<ApplicationState>> m_trash;
};

} // namespace gk

#endif // GK_APPLICATIONSTATESTACK_HPP_
