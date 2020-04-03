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
#ifndef GK_LOGGERUTILS_HPP_
#define GK_LOGGERUTILS_HPP_

#include "gk/core/Logger.hpp"

//======================================================================================
// gk::Vector2
//======================================================================================
#include "gk/core/Vector2.hpp"

template<typename T>
gk::Logger &operator<<(gk::Logger &stream, const gk::Vector2<T> &vec) {
	stream.addSpace();
	return stream << "gk::Vector2(" << vec.x << ", " << vec.y << ")";
}

//======================================================================================
// gk::Vector3
//======================================================================================
#include "gk/core/Vector3.hpp"

template<typename T>
gk::Logger &operator<<(gk::Logger &stream, const gk::Vector3<T> &vec) {
	stream.addSpace();
	return stream << "gk::Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

//======================================================================================
// gk::Vector4
//======================================================================================
#include "gk/core/Vector4.hpp"

template<typename T>
gk::Logger &operator<<(gk::Logger &stream, const gk::Vector4<T> &vec) {
	stream.addSpace();
	return stream << "gk::Vector4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
}

//======================================================================================
// gk::Color
//======================================================================================
#include "gk/graphics/Color.hpp"

gk::Logger &operator<<(gk::Logger &stream, const gk::Color &color);

//======================================================================================
// gk::Rect
//======================================================================================
#include "gk/core/Rect.hpp"

template<typename T>
gk::Logger &operator<<(gk::Logger &stream, const gk::Rect<T> &rect) {
	stream.addSpace();
	return stream << "gk::Rect(" << rect.x << ", " << rect.y << ", " << rect.sizeX << ", " << rect.sizeY << ")";
}

//======================================================================================
// gk::Box
//======================================================================================
#include "gk/core/Box.hpp"

template<typename T>
gk::Logger &operator<<(gk::Logger &stream, const gk::Box<T> &box) {
	stream.addSpace();
	return stream << "gk::Box(" << box.x << ", " << box.y << ", " << box.z << ", " << box.sizeX << ", " << box.sizeY << ", " << box.sizeZ << ")";
}

#endif // GK_LOGGERUTILS_HPP_
