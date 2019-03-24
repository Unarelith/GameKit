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

#include <string>

#include <SFML/Window/Window.hpp>

#include "gk/core/IntTypes.hpp"
#include "gk/gl/RenderTarget.hpp"

namespace gk {

class Window : public RenderTarget, public sf::Window {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Create window
		///
		/// \param width Window width
		/// \param height Window height
		/// \param caption Window caption
		///
		/// Opens a new window with defined size and title.
		///
		////////////////////////////////////////////////////////////
		void create(u16 width, u16 height, const std::string &caption);

		void clear();
};

} // namespace gk

#endif // GK_WINDOW_HPP_
