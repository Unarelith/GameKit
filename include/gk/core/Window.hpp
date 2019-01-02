/*
 * =====================================================================================
 *
 *       Filename:  Window.hpp
 *
 *    Description:
 *
 *        Created:  20/12/2014 00:16:51
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_WINDOW_HPP_
#define GK_WINDOW_HPP_

#include <memory>
#include <string>

#include "gk/core/IntTypes.hpp"
#include "gk/core/SDLHeaders.hpp"
#include "gk/gl/RenderTarget.hpp"

namespace gk {

class Window : public RenderTarget {
	public:
		void open(const std::string &caption, u16 width, u16 height);

		void clear();
		void display();

		void setVerticalSyncEnabled(bool enabled);

		Vector2u getSize() const override { return m_size; }

		void close() { m_isOpen = false; }
		bool isOpen() const { return m_isOpen; }

		SDL_Window *window() const { return m_window.get(); }

		const View &getDefaultView() const override { return m_defaultView; }

	private:
		using SDL_WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
		using SDL_GLContextPtr = std::unique_ptr<void, decltype(&SDL_GL_DeleteContext)>;

		SDL_WindowPtr m_window{nullptr, SDL_DestroyWindow};
		SDL_GLContextPtr m_context{nullptr, SDL_GL_DeleteContext};

		Vector2u m_size;

		bool m_isOpen;

		View m_defaultView;
};

} // namespace gk

#endif // GK_WINDOW_HPP_
