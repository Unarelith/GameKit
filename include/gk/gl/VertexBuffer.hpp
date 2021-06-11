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
#ifndef GK_VERTEXBUFFER_HPP_
#define GK_VERTEXBUFFER_HPP_

#include "gk/gl/VertexBufferLayout.hpp"
#include "gk/utils/NonCopyable.hpp"

namespace gk {

class VertexBuffer : public NonCopyable {
	public:
		VertexBuffer();
		VertexBuffer(VertexBuffer &&);
		~VertexBuffer() noexcept;

		VertexBuffer &operator=(VertexBuffer &&);

		void setData(GLsizeiptr size, const GLvoid *data, GLenum usage) const;
		void updateData(GLintptr offset, GLsizeiptr size, const GLvoid *data) const;

		static void bind(const VertexBuffer *vertexBuffer);

		VertexBufferLayout &layout() { return m_layout; }
		const VertexBufferLayout &layout() const { return m_layout; }

	private:
		GLuint m_id = 0;

		VertexBufferLayout m_layout;
};

} // namespace gk

#endif // GK_VERTEXBUFFER_HPP_
