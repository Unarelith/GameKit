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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

#include "gk/utils/NonCopyable.hpp"

namespace gk {

class ApplicationStateStack;

////////////////////////////////////////////////////////////
/// \brief Abstract base class for game states
///
////////////////////////////////////////////////////////////
class ApplicationState : public sf::Drawable, public sf::Transformable, public NonCopyable {
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
		virtual ~ApplicationState() = default;

		////////////////////////////////////////////////////////////
		/// \brief Defaulted move assignment operator
		///
		////////////////////////////////////////////////////////////
		ApplicationState &operator=(ApplicationState &&) = default;

		////////////////////////////////////////////////////////////
		/// \brief Do an action in response to an SDL event
		///
		/// \param event The event sent from SFML
		///
		////////////////////////////////////////////////////////////
		virtual void onEvent(const sf::Event &) {}

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

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Draw the sprite to a render target
		///
		/// \param target Render target to draw to
		/// \param states Current render states
		///
		////////////////////////////////////////////////////////////
		void draw(sf::RenderTarget &, sf::RenderStates) const override {}

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		ApplicationState *m_parent = nullptr;          ///< Parent to this state

		ApplicationStateStack *m_stateStack = nullptr; ///< Stack where this state belongs to
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
///         void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
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
