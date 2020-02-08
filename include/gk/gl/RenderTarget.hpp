/*
 * =====================================================================================
 *
 *  GameKit
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
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

class Drawable;
class VertexBuffer;

class RenderTarget {
	public:
		void draw(const Drawable &drawable, const RenderStates &states = RenderStates::Default);
		void draw(const VertexBuffer &vertexBuffer, GLenum mode, std::size_t firstVertex, std::size_t vertexCount, const RenderStates &states = RenderStates::Default);
		void drawElements(const VertexBuffer &vertexBuffer, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, const RenderStates &states = RenderStates::Default);

		virtual Vector2u getSize() const = 0;

		virtual const View &getDefaultView() const = 0;

		const View *getView() const { return m_view; }
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
