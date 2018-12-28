/*
 * =====================================================================================
 *
 *       Filename:  ApplicationState.hpp
 *
 *    Description:
 *
 *        Created:  05/06/2018 15:45:26
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_APPLICATIONSTATE_HPP_
#define GK_APPLICATIONSTATE_HPP_

#include "gk/core/SDLHeaders.hpp"
#include "gk/gl/IDrawable.hpp"
#include "gk/gl/Transformable.hpp"

namespace gk {

class ApplicationStateStack;

class ApplicationState : public IDrawable, public Transformable {
	public:
		ApplicationState(ApplicationState *parent = nullptr) : m_parent(parent) {}
		ApplicationState(const ApplicationState &) = delete;
		ApplicationState(ApplicationState &&) = default;
		virtual ~ApplicationState() = default;

		ApplicationState &operator=(const ApplicationState &) = delete;
		ApplicationState &operator=(ApplicationState &&) = default;

		virtual void onEvent(const SDL_Event &) {}

		virtual void update() = 0;

		void setStateStack(ApplicationStateStack *stateStack) { m_stateStack = stateStack; }

	protected:
		ApplicationState *m_parent = nullptr;

		ApplicationStateStack *m_stateStack = nullptr;
};

} // namespace gk

#endif // GK_APPLICATIONSTATE_HPP_
