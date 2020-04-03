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

#include <string>
#include <vector>

#include "gk/core/Rect.hpp"
#include "gk/gl/OpenGL.hpp"
#include "gk/gl/RenderStates.hpp"
#include "gk/gl/View.hpp"

namespace gk {

class Drawable;
class VertexBuffer;

struct VertexAttributeData {
	VertexAttributeData(u16 _id, const std::string &_name, GLint _size, GLenum _type, GLboolean _normalized, GLsizei _stride, const void *_pointer)
		: id(_id), name(_name), size(_size), type(_type), normalized(_normalized), stride(_stride), pointer(_pointer) {}

	u16 id;
	std::string name;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	const void *pointer;
};

class RenderTarget {
	public:
		RenderTarget();

		void addVertexAttribute(u16 id, const std::string &name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
		void clearVertexAttributes();

		void draw(const Drawable &drawable, const RenderStates &states = RenderStates::Default);
		void draw(const VertexBuffer &vertexBuffer, GLenum mode, std::size_t firstVertex, std::size_t vertexCount, const RenderStates &states = RenderStates::Default);
		void drawElements(const VertexBuffer &vertexBuffer, GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, const RenderStates &states = RenderStates::Default);

		virtual Vector2u getSize() const = 0;

		virtual const View &getDefaultView() const = 0;

		View *getView() { return m_view; }
		const View *getView() const { return m_view; }
		// FIXME: const_cast shouldn't be used here but it's required for OpenMiner
		void setView(const View &view) { m_view = const_cast<View*>(&view); m_viewChanged = true; }
		void disableView() { m_view = nullptr; }

	private:
		void beginDrawing(const RenderStates &states);
		void endDrawing(const RenderStates &states);

		IntRect getViewport(const View &view) const;

		void applyCurrentView(const RenderStates &states);

		bool m_viewChanged = false;
		View *m_view = nullptr;

		IntRect m_previousViewport;

		std::vector<VertexAttributeData> m_attributes;
};

} // namespace gk

#endif // GK_RENDERTARGET_HPP_
