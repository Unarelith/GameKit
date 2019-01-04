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
#include "gk/core/SDLLoader.hpp"
#include "gk/core/Window.hpp"
#include "gk/resource/ResourceHandler.hpp"
#include "gk/system/GameClock.hpp"

namespace gk {

class CoreApplication {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// \param argc `main()` argument count
		/// \param argv `main()` argument strings
		///
		////////////////////////////////////////////////////////////
		CoreApplication(int argc, char **argv);

		////////////////////////////////////////////////////////////
		/// \brief Run the application
		///
		/// \param isProtected Exceptions are catched if this parameter is set to `true` (default)
		///
		/// Loads SDL libraries, run `init()`, then `mainLoop()`
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

		virtual void onEvent(const SDL_Event &event);

		void handleEvents();
		void mainLoop();

		SDLLoader m_sdlLoader;

		ApplicationStateStack m_stateStack;

		GameClock m_clock;

		ResourceHandler m_resourceHandler;

		Window m_window;

		RenderStates m_renderStates = RenderStates::Default;
};

} // namespace gk

////////////////////////////////////////////////////////////
/// \class gk::CoreApplication
/// \ingroup core
///
/// This class provides an interface to create your own application.
///
/// You should add a class named `Application` that inherits from this class.
///
////////////////////////////////////////////////////////////

#endif // GK_COREAPPLICATION_HPP_
