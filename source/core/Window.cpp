/*
 * =====================================================================================
 *
 *       Filename:  Window.cpp
 *
 *    Description:
 *
 *        Created:  20/12/2014 00:17:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/core/Window.hpp"
#include "gk/gl/GLCheck.hpp"
#include "gk/gl/OpenGL.hpp"
#include "gk/core/Exception.hpp"

namespace gk {

void Window::create(u16 width, u16 height, const std::string &caption) {
	sf::ContextSettings context;
	context.depthBits = 24;
	context.stencilBits = 8;
	context.antialiasingLevel = 4;
	context.majorVersion = 2;
	context.minorVersion = 1;

	sf::Window::create(sf::VideoMode(width, height), caption, sf::Style::Close, context);
	if (!sf::Window::setActive())
		throw EXCEPTION("Failed to open window");

#ifdef __MINGW32__
#ifdef USE_GLAD
	if(!gladLoadGL()) {
		throw EXCEPTION("glad init failed");
	}
#else
	if(glewInit() != GLEW_OK) {
		throw EXCEPTION("glew init failed");
	}
#endif
#endif

	glCheck(glEnable(GL_BLEND));
	glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	glCheck(glEnable(GL_TEXTURE_2D));
}

void Window::clear() {
	glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

} // namespace gk

