/*
 * =====================================================================================
 *
 *       Filename:  VertexBuffer.hpp
 *
 *    Description:
 *
 *        Created:  15/12/2014 17:09:58
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_VERTEXBUFFER_HPP_
#define GK_VERTEXBUFFER_HPP_

#include "gk/gl/OpenGL.hpp"
#include "gk/utils/NonCopyable.hpp"

namespace gk {

class VertexBuffer : public NonCopyable {
	public:
		VertexBuffer();
		VertexBuffer(VertexBuffer &&);
		~VertexBuffer() noexcept;

		VertexBuffer &operator=(VertexBuffer &&) = default;

		void setData(GLsizeiptr size, const GLvoid *data, GLenum usage) const;
		void updateData(GLintptr offset, GLsizeiptr size, const GLvoid *data) const;

		void setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) const;

		static void bind(const VertexBuffer *vertexBuffer);

	private:
		GLuint m_id = 0;
};

} // namespace gk

#endif // GK_VERTEXBUFFER_HPP_
