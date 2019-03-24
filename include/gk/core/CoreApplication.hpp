/*
 * =====================================================================================
 *
 *       Filename:  CoreApplication.hpp
 *
 *    Description:
 *
 *        Created:  14/06/2018 01:59:51
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_COREAPPLICATION_HPP_
#define GK_COREAPPLICATION_HPP_

#include <SFML/Window/Event.hpp>

#include "gk/core/ApplicationStateStack.hpp"
#include "gk/core/ArgumentParser.hpp"
#include "gk/core/GameClock.hpp"
#include "gk/core/Window.hpp"
#include "gk/resource/ResourceHandler.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Base class for your own Application
///
////////////////////////////////////////////////////////////
class CoreApplication {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param argc Argument count
		/// \param argv Argument strings
		///
		////////////////////////////////////////////////////////////
		CoreApplication(int argc, char **argv);

		////////////////////////////////////////////////////////////
		/// \brief Run the application
		///
		/// \param isProtected Exceptions are catched if this parameter is set to `true` (default)
		///
		/// Run init(), then mainLoop()
		///
		////////////////////////////////////////////////////////////
		int run(bool isProtected = true);

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Initialization function
		///
		/// This function is used to init engine and singletons.
		///
		////////////////////////////////////////////////////////////
		virtual void init();

		////////////////////////////////////////////////////////////
		/// \brief This function is called when a new window event is received
		///
		/// \param event Event received from SDL
		///
		/// This function is automatically called by handleEvents()
		///
		////////////////////////////////////////////////////////////
		virtual void onEvent(const sf::Event &event);

		////////////////////////////////////////////////////////////
		/// \brief Poll window events and send them to onEvent() and ApplicationStateStack
		///
		/// This function is automatically called by mainLoop()
		///
		////////////////////////////////////////////////////////////
		virtual void handleEvents();

		////////////////////////////////////////////////////////////
		/// \brief Game main loop, automatically called by run()
		///
		////////////////////////////////////////////////////////////
		virtual void mainLoop();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		ApplicationStateStack m_stateStack;                    ///< Stack containing application states

		GameClock m_clock;                                     ///< Simulated time system

		ResourceHandler m_resourceHandler;                     ///< Container for all game resources

		Window m_window;                                       ///< The main window

		RenderStates m_renderStates = RenderStates::Default;   ///< The default render states

		ArgumentParser m_argumentParser;                       ///< Helper for argument management

		bool m_isRunning = true;                               ///< The application will stop if this flag is set to false
};

} // namespace gk

#endif // GK_COREAPPLICATION_HPP_

////////////////////////////////////////////////////////////
/// \class gk::CoreApplication
/// \ingroup core
///
/// This class provides an interface to create your own application.
///
/// You should add a class named `Application` that inherits from this class.
///
////////////////////////////////////////////////////////////
