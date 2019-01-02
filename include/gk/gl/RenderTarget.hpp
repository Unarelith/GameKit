/*
 * =====================================================================================
 *
 *       Filename:  RenderTarget.hpp
 *
 *    Description:
 *
 *        Created:  14/06/2018 19:54:56
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_RENDERTARGET_HPP_
#define GK_RENDERTARGET_HPP_

#include "gk/core/Rect.hpp"
#include "gk/gl/OpenGL.hpp"
#include "gk/gl/RenderStates.hpp"
#include "gk/gl/View.hpp"

namespace gk {

class IDrawable;
class VertexBuffer;

class RenderTarget {
	public:
		void draw(const IDrawable &drawable, const RenderStates &states = RenderStates::Default);
		void draw(const VertexBuffer &vertexBuffer, GLenum mode, std::size_t firstVertex, std::size_t vertexCount, const RenderStates &states = RenderStates::Default);
		void drawElements(const VertexBuffer &vertexBuffer, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, const RenderStates &states = RenderStates::Default);

		virtual Vector2u getSize() const = 0;

		virtual const View &getDefaultView() const = 0;

		void setView(const View &view) { m_view = &view; m_viewChanged = true; }
		void disableView() { m_view = nullptr; }

	private:
		void beginDrawing(const RenderStates &states);
		void endDrawing(const RenderStates &states);

		IntRect getViewport(const View &view) const;

		void applyCurrentView(const RenderStates &states);

		bool m_viewChanged = false;
		const View *m_view = nullptr;

		IntRect m_previousViewport;
};

} // namespace gk

#endif // GK_RENDERTARGET_HPP_
