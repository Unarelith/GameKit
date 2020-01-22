/*
 * =====================================================================================
 *
 *       Filename:  Shader.hpp
 *
 *    Description:
 *
 *        Created:  15/12/2014 16:30:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_SHADER_HPP_
#define GK_SHADER_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "gk/gl/OpenGL.hpp"

namespace gk {

class Transform;

class Shader {
	public:
		Shader() = default;
		Shader(const std::string &vertexFilename, const std::string &fragementFilename);
		~Shader();

		void loadFromFile(const std::string &vertexFilename, const std::string &fragementFilename);

		void createProgram();
		void linkProgram();

		void bindAttributeLocation(GLuint index, const std::string &name);
		void defaultAttributeLocationBinding();

		void addShader(GLenum type, const std::string &filename);

		GLint attrib(const std::string &name) const;
		GLint uniform(const std::string &name) const;

		void enableVertexAttribArray(const std::string &name) const;
		void disableVertexAttribArray(const std::string &name) const;

		void setUniform(const std::string &name, int n) const;
		void setUniform(const std::string &name, float x, float y) const;
		void setUniform(const std::string &name, const glm::mat4 &matrix) const;
		void setUniform(const std::string &name, const Transform &transform) const;

		static void bind(const Shader *shader);

		GLint program() const { return m_program; }

	private:
		std::vector<GLuint> m_vertexShaders;
		std::vector<GLuint> m_fragmentShaders;

		std::unordered_map<std::string, GLuint> m_attributes;

		GLuint m_program;
};

} // namespace gk

#endif // GK_SHADER_HPP_
