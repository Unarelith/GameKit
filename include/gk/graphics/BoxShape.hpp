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
#ifndef GK_BOXSHAPE_HPP_
#define GK_BOXSHAPE_HPP_

#include "gk/gl/Drawable.hpp"
#include "gk/gl/Transformable.hpp"
#include "gk/gl/VertexBuffer.hpp"
#include "gk/graphics/Color.hpp"

namespace gk {

class BoxShape : public Drawable, public Transformable {
	public:
		BoxShape() = default;
		BoxShape(float sizeX, float sizeY, float sizeZ, const Color &color = Color::White)
			: m_size(sizeX, sizeY, sizeZ), m_color(color) {}

		const gk::Vector3f &getSize() const { return m_size; }

		void resize(float sizeX, float sizeY, float sizeZ) { m_size.x = sizeX; m_size.y = sizeY; m_size.z = sizeZ; m_isVboInitialized = false; }

		void setColor(const Color &color) { m_color = color; m_isVboInitialized = false; }

	private:
		void updateVertexBuffer() const;

		void draw(RenderTarget &target, RenderStates states) const override;

		gk::Vector3f m_size{1, 1, 1};

		VertexBuffer m_vbo;

		Color m_color = Color::White;

		mutable bool m_isVboInitialized = false;
};

} // namespace gk

#endif // GK_BOXSHAPE_HPP_
