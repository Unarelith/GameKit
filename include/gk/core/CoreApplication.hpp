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
		CoreApplication(int argc, char **argv);

		virtual void init();

		int run();

	protected:
		void createWindow(u16 screenWidth, u16 screenHeight, const char *windowTitle);

		virtual void onEvent(const SDL_Event &event);

		void handleEvents();
		void mainLoop();

		ApplicationStateStack m_stateStack;

		GameClock m_clock;

		ResourceHandler m_resourceHandler;

		SDLLoader m_sdlLoader;

		Window m_window;

		RenderStates m_renderStates = RenderStates::Default;
};

} // namespace gk

#endif // GK_COREAPPLICATION_HPP_
