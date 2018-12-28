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

#include "OpenGL.hpp"
#include "RenderStates.hpp"

namespace gk {

class IDrawable;
class VertexBuffer;

class RenderTarget {
	public:
		void draw(const IDrawable &drawable, const RenderStates &states = RenderStates::Default);
		void draw(const VertexBuffer &vertexBuffer, GLenum mode, std::size_t firstVertex, std::size_t vertexCount, const RenderStates &states = RenderStates::Default);
};

} // namespace gk

#endif // GK_RENDERTARGET_HPP_
