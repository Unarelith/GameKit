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
#ifndef GK_DRAWABLE_HPP_
#define GK_DRAWABLE_HPP_

#include "gk/gl/RenderTarget.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Abstract base class for objects that can be drawn to a render target
///
////////////////////////////////////////////////////////////
class Drawable {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Virtual destructor
		///
		////////////////////////////////////////////////////////////
		virtual ~Drawable() = default;

	protected:
		friend class RenderTarget;

		////////////////////////////////////////////////////////////
		/// \brief Draw the object to a render target
		///
		/// This is a pure virtual function that has to be implemented
		/// by the derived class to define how the drawable should be
		/// drawn.
		///
		/// \param target Render target to draw to
		/// \param states Current render states
		///
		////////////////////////////////////////////////////////////
		virtual void draw(RenderTarget &target, RenderStates states) const = 0;
};

} // namespace gk

#endif // GK_DRAWABLE_HPP_

////////////////////////////////////////////////////////////
/// \class gk::Drawable
/// \ingroup graphics
///
/// This part of the documentation has been taken from SFML.
/// Once the migration to 2.6 is done, this file will be removed.
///
/// gk::Drawable is a very simple base class that allows objects
/// of derived classes to be drawn to a gk::RenderTarget.
///
/// All you have to do in your derived class is to override the
/// draw virtual function.
///
/// Note that inheriting from gk::Drawable is not mandatory,
/// but it allows this nice syntax "window.draw(object)" rather
/// than "object.draw(window)", which is more consistent with other
/// GameKit classes.
///
/// Example:
/// \code
/// class MyDrawable : public gk::Drawable {
///     public:
///        ...
///
///     private:
///         void draw(gk::RenderTarget &target, gk::RenderStates states) const override {
///             // You can draw other high-level objects
///             target.draw(m_sprite, states);
///
///             // ... or use the low-level API
///             states.texture = &m_texture;
///             target.draw(m_vertices, GL_QUADS, 0, 16, states);
///         }
///
///         gk::Sprite m_sprite;
///         gk::Texture m_texture;
///         gk::VertexBuffer m_vbo;
/// };
/// \endcode
///
/// \see gk::RenderTarget
///
////////////////////////////////////////////////////////////
