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
#ifndef GK_SHADER_HPP_
#define GK_SHADER_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "gk/gl/OpenGL.hpp"
#include "gk/graphics/Color.hpp"

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
		void setUniform(const std::string &name, const gk::Color &color) const;
		void setUniform(const std::string &name, const glm::mat4 &matrix) const;
		void setUniform(const std::string &name, const Transform &transform) const;

		GLint program() const { return m_program; }

		static void bind(const Shader *shader);

	private:
		static const Shader *s_boundShader;

		std::vector<GLuint> m_vertexShaders;
		std::vector<GLuint> m_fragmentShaders;

		std::unordered_map<std::string, GLuint> m_attributes;

		GLuint m_program;
};

} // namespace gk

#endif // GK_SHADER_HPP_
