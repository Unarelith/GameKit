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
#ifndef GK_RENDERSTATES_HPP_
#define GK_RENDERSTATES_HPP_

#include <glm/matrix.hpp>

#include "gk/core/IntTypes.hpp"
#include "gk/gl/Transform.hpp"

namespace gk {

class Shader;
class Texture;

namespace VertexAttribute {
	enum {
		Coord3d          = 1,
		TexCoord         = 2,
		Color            = 4,

		All              = Coord3d | TexCoord | Color,
	};
}

struct RenderStates {
	Transform projectionMatrix;
	Transform viewMatrix;
	Transform transform;

	const Texture *texture = nullptr;
	const Shader *shader = nullptr;

	u16 vertexAttributes = VertexAttribute::All;

	static const RenderStates Default; // Defined in RenderTarget.cpp
};

} // namespace gk

#endif // GK_RENDERSTATES_HPP_
