/*
 * =====================================================================================
 *
 *       Filename:  VertexArray.hpp
 *
 *    Description:
 *
 *        Created:  06/01/2020 19:17:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_VERTEXARRAY_HPP_
#define GK_VERTEXARRAY_HPP_

#include <unordered_map>

#include "gk/gl/OpenGL.hpp"
#include "gk/gl/Shader.hpp"
#include "gk/gl/VertexBuffer.hpp"
#include "gk/utils/NonCopyable.hpp"

namespace gk {

class VertexArray : public NonCopyable {
	public:
		VertexArray() = default;
		VertexArray(VertexArray &&);
		~VertexArray() noexcept;

		void init();

		VertexArray &operator=(VertexArray &&) = default;

		void addVertexAttribute(const Shader &shader, const std::string &name, GLint size,
				GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

		void enableVertexAttribArray(const std::string &name) const;
		void disableVertexAttribArray(const std::string &name) const;

		void setupVertexAttribute(const std::string &name) const;

		static void bind(const VertexArray *vertexBuffer);

	private:
		static GLuint boundBuffer;

		GLuint m_id = 0;

		struct VertexAttribute {
			GLint index;
			GLint size;
			GLenum type;
			GLboolean normalized;
			GLsizei stride;
			const void *pointer;
		};

		std::unordered_map<std::string, VertexAttribute> m_attributes;
};

} // namespace gk

#endif // GK_VERTEXARRAY_HPP_
