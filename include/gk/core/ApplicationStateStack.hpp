/*
 * =====================================================================================
 *
 *  GameKit
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2020 the GameKit contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of GameKit.
 *
 *  GameKit is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  GameKit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with GameKit; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#ifndef GK_APPLICATIONSTATESTACK_HPP_
#define GK_APPLICATIONSTATESTACK_HPP_

#include <memory>
#include <stack>

#include "gk/core/ApplicationState.hpp"

namespace gk {

class EventHandler;

////////////////////////////////////////////////////////////
/// \brief Stack containing ApplicationState instances
///
////////////////////////////////////////////////////////////
class ApplicationStateStack {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Push a new gk::ApplicationState to the stack
		///
		/// \param args Constructor arguments of type T
		///
		/// This function will populate ApplicationState::m_stateStack
		///
		////////////////////////////////////////////////////////////
		template<typename T, typename... Args>
		auto push(Args &&...args) -> typename std::enable_if<std::is_base_of<ApplicationState, T>::value, T&>::type {
			m_states.emplace(std::make_shared<T>(std::forward<Args>(args)...));
			m_states.top()->setStateStack(this);
			m_states.top()->setEventHandler(m_eventHandler);
			m_states.top()->init();
			return static_cast<T&>(top());
		}

		////////////////////////////////////////////////////////////
		/// \brief Remove the top ApplicationState in the stack
		///
		/// The state is moved to another stack while waiting for clearDeleteStates() to remove it.
		///
		////////////////////////////////////////////////////////////
		void pop();

		////////////////////////////////////////////////////////////
		/// \brief Clear the stack
		///
		////////////////////////////////////////////////////////////
		void clear() { while(!empty()) pop(); }

		////////////////////////////////////////////////////////////
		/// \brief Clear the removed states of the stack
		///
		/// This function is automatically called in CoreApplication::mainLoop()
		///
		////////////////////////////////////////////////////////////
		void clearDeletedStates();

		////////////////////////////////////////////////////////////
		/// \brief Get the top ApplicationState in the stack
		///
		/// \return The currently active ApplicationState
		///
		////////////////////////////////////////////////////////////
		ApplicationState &top() const { return *m_states.top().get(); }

		////////////////////////////////////////////////////////////
		/// \brief Check if the container is empty
		///
		/// \return `true` if the container is empty, otherwise `false`
		///
		////////////////////////////////////////////////////////////
		bool empty() const { return m_states.empty(); }

		////////////////////////////////////////////////////////////
		/// \brief Get the amount of ApplicationState in the stack
		///
		/// \return Size of the stack
		///
		////////////////////////////////////////////////////////////
		std::size_t size() const { return m_states.size(); }

		////////////////////////////////////////////////////////////
		/// \brief Set the event handler
		///
		/// \param eventHandler The event handler
		///
		////////////////////////////////////////////////////////////
		void setEventHandler(EventHandler &eventHandler) {
			m_eventHandler = &eventHandler;
		}

		////////////////////////////////////////////////////////////
		/// \brief Get the current singleton instance
		///
		/// \return Current singleton instance
		///
		/// \see setInstance
		///
		////////////////////////////////////////////////////////////
		static ApplicationStateStack &getInstance() {
			return *s_instance;
		}

		////////////////////////////////////////////////////////////
		/// \brief Set the current singleton instance
		///
		/// \param instance New singleton instance
		///
		/// \see getInstance
		///
		////////////////////////////////////////////////////////////
		static void setInstance(ApplicationStateStack &instance) {
			s_instance = &instance;
		}

	private:
		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		static ApplicationStateStack *s_instance;               ///< Current singleton instance

		std::stack<std::shared_ptr<ApplicationState>> m_states; ///< Stack containing the states
		std::stack<std::shared_ptr<ApplicationState>> m_trash;  ///< Removed states waiting to be deleted

		EventHandler *m_eventHandler = nullptr;                 ///< The event handler
};

} // namespace gk

#endif // GK_APPLICATIONSTATESTACK_HPP_

////////////////////////////////////////////////////////////
/// \class gk::ApplicationStateStack
/// \ingroup core
///
/// gk::ApplicationStateStack is a stack container of gk::ApplicationState instances.
///
/// Usage example:
/// \code
/// // In a gk::CoreApplication subclass
/// m_stateStack.push<MyApplicationState>(...);
///
/// // In a gk::ApplicationState subclass
/// m_stateStack->push<MyApplicationState>(...);
///
/// // Everywhere else
/// gk::ApplicationStateStack::getInstance().push<MyApplicationState>(...);
/// \endcode
///
/// \see gk::ApplicationState
///
////////////////////////////////////////////////////////////
