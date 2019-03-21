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

#include "gk/core/ApplicationStateStack.hpp"
#include "gk/core/ArgumentParser.hpp"
#include "gk/core/SDLLoader.hpp"
#include "gk/core/Window.hpp"
#include "gk/resource/ResourceHandler.hpp"
#include "gk/core/GameClock.hpp"

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
		/// Loads SDL libraries, run init(), then mainLoop()
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
		/// \brief Open window
		///
		/// \param screenWidth Window width
		/// \param screenHeight Window height
		/// \param windowTitle Window caption
		///
		/// Opens a new window with defined size and title.
		///
		////////////////////////////////////////////////////////////
		void createWindow(u16 screenWidth, u16 screenHeight, const char *windowTitle);

		////////////////////////////////////////////////////////////
		/// \brief This function is called when a new window event is received
		///
		/// \param event Event received from SDL
		///
		/// This function is automatically called by handleEvents()
		///
		////////////////////////////////////////////////////////////
		virtual void onEvent(const SDL_Event &event);

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
		SDLLoader m_sdlLoader;                                 ///< Init and free SDL
		bool m_loadSDL = true;                                 ///< If this flag is set to false, SDL won't be loaded

		ApplicationStateStack m_stateStack;                    ///< Stack containing application states

		GameClock m_clock;                                     ///< Simulated time system

		ResourceHandler m_resourceHandler;                     ///< Container for all game resources

		Window m_window;                                       ///< The main window

		RenderStates m_renderStates = RenderStates::Default;   ///< The default render states

		ArgumentParser m_argumentParser;                       ///< Helper for argument management
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
