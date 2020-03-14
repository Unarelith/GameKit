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
#ifndef GK_APPLICATIONSTATE_HPP_
#define GK_APPLICATIONSTATE_HPP_

#include "gk/core/EventHandler.hpp"
#include "gk/core/SDLHeaders.hpp"
#include "gk/gl/Drawable.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/utils/NonCopyable.hpp"

namespace gk {

class ApplicationStateStack;

////////////////////////////////////////////////////////////
/// \brief Abstract base class for game states
///
////////////////////////////////////////////////////////////
class ApplicationState : public Drawable, public Transformable, public NonCopyable {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// \param parent The parent of this state
		///
		////////////////////////////////////////////////////////////
		ApplicationState(ApplicationState *parent = nullptr) : m_parent(parent) {}

		////////////////////////////////////////////////////////////
		/// \brief Defaulted move constructor
		///
		////////////////////////////////////////////////////////////
		ApplicationState(ApplicationState &&) = default;

		////////////////////////////////////////////////////////////
		/// \brief Virtual destructor
		///
		////////////////////////////////////////////////////////////
		virtual ~ApplicationState() {
			m_eventHandler->removeListeners(this);
		}

		////////////////////////////////////////////////////////////
		/// \brief Defaulted move assignment operator
		///
		////////////////////////////////////////////////////////////
		ApplicationState &operator=(ApplicationState &&) = default;

		////////////////////////////////////////////////////////////
		/// \brief Initialize the state
		///
		/// This is where you will be able to use `m_stateStack`
		/// and `m_eventHandler` pointers
		///
		////////////////////////////////////////////////////////////
		virtual void init() {}

		////////////////////////////////////////////////////////////
		/// \brief Do an action in response to an SDL event
		///
		/// \param event The event sent from SDL
		///
		////////////////////////////////////////////////////////////
		virtual void onEvent(const SDL_Event &) {}

		////////////////////////////////////////////////////////////
		/// \brief Execute actions every game tick
		///
		/// This is a pure virtual function that has to be implemented
		/// by the derived class to define what the state should do.
		///
		////////////////////////////////////////////////////////////
		virtual void update() = 0;

		////////////////////////////////////////////////////////////
		/// \brief Get the parent of this state
		///
		/// \return The parent of this state
		///
		////////////////////////////////////////////////////////////
		ApplicationState *parent() { return m_parent; }

		////////////////////////////////////////////////////////////
		/// \brief Change the stack this state belongs to
		///
		/// \param stateStack The new state stack
		///
		////////////////////////////////////////////////////////////
		void setStateStack(ApplicationStateStack *stateStack) { m_stateStack = stateStack; }

		////////////////////////////////////////////////////////////
		/// \brief Set the event handler
		///
		/// \param eventHandler The event handler
		///
		////////////////////////////////////////////////////////////
		void setEventHandler(EventHandler *eventHandler) { m_eventHandler = eventHandler; }

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Draw the sprite to a render target
		///
		/// \param target Render target to draw to
		/// \param states Current render states
		///
		////////////////////////////////////////////////////////////
		void draw(RenderTarget &, RenderStates) const override {}

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		ApplicationState *m_parent = nullptr;          ///< Parent to this state

		ApplicationStateStack *m_stateStack = nullptr; ///< Stack where this state belongs to

		EventHandler *m_eventHandler = nullptr;        ///< The event handler
};

} // namespace gk

#endif // GK_APPLICATIONSTATE_HPP_

////////////////////////////////////////////////////////////
/// \class gk::ApplicationState
/// \ingroup core
///
/// gk::ApplicationState is a very simple base class for designing your own game states.
///
/// Example:
/// \code
/// class MyState : public gk::ApplicationState {
///     public:
///         MyState(gk::ApplicationState *parent = nullptr) : gk::ApplicationState(parent) {
///             ...
///         }
///
///         void update() override {
///             ...
///         }
///
///     private:
///         void draw(gk::RenderTarget &target, gk::RenderStates states) const override {
///             ...
///         }
///
///         ...
/// };
/// \endcode
///
/// \see gk::ApplicationStateStack
///
////////////////////////////////////////////////////////////
