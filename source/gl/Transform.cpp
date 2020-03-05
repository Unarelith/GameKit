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
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "gk/gl/Transform.hpp"

namespace gk {

const Transform Transform::Identity;

Transform& Transform::combine(const Transform& transform) {
	m_matrix *= transform.m_matrix;
	return *this;
}

Transform& Transform::translate(float x, float y, float z) {
	m_matrix = glm::translate(m_matrix, {x, y, z});
	return *this;
}

Transform& Transform::rotate(float angle, const Vector3f& axis) {
	m_matrix = glm::rotate(m_matrix, glm::radians(angle), {axis.x, axis.y, axis.z});
	return *this;
}

Transform& Transform::scale(float scaleX, float scaleY, float scaleZ) {
	m_matrix = glm::scale(m_matrix, {scaleX, scaleY, scaleZ});
	return *this;
}

Transform operator*(const Transform& left, const Transform &right) {
	return Transform(left).combine(right);
}

Transform& operator*=(Transform &left, const Transform &right) {
	return left.combine(right);
}

}

