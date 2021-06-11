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
		virtual ~RenderTarget() = default;

		void draw(const Drawable &drawable, const RenderStates &states = RenderStates::Default);
		void draw(const VertexBuffer &vertexBuffer, GLenum mode, GLint firstVertex, GLsizei vertexCount, const RenderStates &states = RenderStates::Default);
		void drawElements(const VertexBuffer &vertexBuffer, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, const RenderStates &states = RenderStates::Default);

		void drawVertexBuffer(const VertexBuffer &vertexBuffer, GLenum mode, GLint firstVertex, GLsizei vertexCount);

		void beginDrawing(const RenderStates &states);

		virtual Vector2u getSize() const = 0;

		virtual const View &getDefaultView() const = 0;

		View *getView() { return m_view; }
		const View *getView() const { return m_view; }
		// FIXME: const_cast shouldn't be used here but it's required for OpenMiner
		void setView(const View &view) { m_view = const_cast<View*>(&view); m_viewChanged = true; }
		void disableView() { m_view = nullptr; }

	private:
		IntRect getViewport(const View &view) const;

		void applyCurrentView(const RenderStates &states);

		bool m_viewChanged = false;
		View *m_view = nullptr;

		IntRect m_previousViewport;
};

} // namespace gk

#endif // GK_RENDERTARGET_HPP_
