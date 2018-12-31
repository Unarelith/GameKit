/*
 * =====================================================================================
 *
 *       Filename:  Vertex.hpp
 *
 *    Description:
 *
 *        Created:  19/06/2018 23:37:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_VERTEX_HPP_
#define GK_VERTEX_HPP_

#include "OpenGL.hpp"

namespace gk {

struct Vertex {
	GLfloat coord3d[4]      = {0, 0, 0, 1};
	GLfloat texCoord[2]     = {-1, -1};
	GLfloat color[4]        = {0, 0, 0, 1};
	GLfloat normal[3]       = {0, 0, 0};
	GLfloat lightValue[2]   = {-1, -1}; // FIXME
	GLfloat blockType       = -1; // FIXME
	GLfloat ambientOcclusion = 5; // FIXME
};

} // namespace gk

#endif // GK_VERTEX_HPP_
