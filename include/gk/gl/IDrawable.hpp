/*
 * =====================================================================================
 *
 *       Filename:  IDrawable.hpp
 *
 *    Description:
 *
 *        Created:  14/06/2018 19:53:57
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_IDRAWABLE_HPP_
#define GK_IDRAWABLE_HPP_

#include "gk/gl/RenderTarget.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Abstract base class for objects that can be drawn to a render target
///
////////////////////////////////////////////////////////////
class IDrawable {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Virtual destructor
		///
		////////////////////////////////////////////////////////////
		virtual ~IDrawable() = default;

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

#endif // GK_IDRAWABLE_HPP_

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
/// class MyDrawable : public gk::Drawable
/// {
/// public:
///
///    ...
///
/// private:
///
///     virtual void draw(gk::RenderTarget& target, gk::RenderStates states) const
///     {
///         // You can draw other high-level objects
///         target.draw(m_sprite, states);
///
///         // ... or use the low-level API
///         states.texture = &m_texture;
///         target.draw(m_vertices, GL_QUADS, 0, 16, states);
///
///         // ... or draw with OpenGL directly
///         glBegin(GL_QUADS);
///         ...
///         glEnd();
///     }
///
///     gk::Sprite m_sprite;
///     gk::Texture m_texture;
///     gk::VertexBuffer m_vbo;
/// };
/// \endcode
///
/// \see gk::RenderTarget
///
////////////////////////////////////////////////////////////
