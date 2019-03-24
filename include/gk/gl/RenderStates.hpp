/*
 * =====================================================================================
 *
 *       Filename:  RenderStates.hpp
 *
 *    Description:
 *
 *        Created:  14/06/2018 19:52:27
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_RENDERSTATES_HPP_
#define GK_RENDERSTATES_HPP_

#include <glm/matrix.hpp>

#include <SFML/Graphics/RenderStates.hpp>

#include "gk/core/IntTypes.hpp"
#include "gk/gl/Transform.hpp"

namespace gk {

class Shader;

namespace VertexAttribute {
	enum {
		Coord3d          = 1,
		Normal           = 2,
		TexCoord         = 4,
		Color            = 8,
		LightValue       = 16,
		BlockType        = 32,
		AmbientOcclusion = 64,

		Only2d      = Coord3d | TexCoord | Color,
		All         = 0xff,
	};
}

class RenderStates : public sf::RenderStates {
	public:
		Transform projectionMatrix;
		Transform viewMatrix;
		Transform transform;

		Shader *shader = nullptr;

		u8 vertexAttributes = VertexAttribute::All;

		static const RenderStates Default; // Defined in RenderTarget.cpp
};

} // namespace gk

#endif // GK_RENDERSTATES_HPP_
