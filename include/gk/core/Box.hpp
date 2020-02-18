/*
 * =====================================================================================
 *
 *  GameKit
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#ifndef GK_BOX_HPP_
#define GK_BOX_HPP_

#include <algorithm>

#include "Vector3.hpp"

namespace gk {

template<typename T>
class Box {
	public:
		Box() = default;

		Box(T _x, T _y, T _z, T _width, T _height, T _depth) {
			reset(_x, _y, _z, _width, _height, _depth);
		}

		Box(const Vector3<T> &_position, const Vector3<T> &_size) {
			reset(_position.x, _position.y, _position.z, _size.x, _size.y, _size.z);
		}

		template<typename U>
		Box(const Box<U> &box)
			: Box(box.x, box.y, box.width, box.height) {}

		void reset(T _x, T _y, T _z, T _width, T _height, T _depth) {
			x = _x;
			y = _y;
			z = _z;
			width = _width;
			height = _height;
			depth = _depth;
		}

		void reset(Box<T> box) { reset(box.x, box.y, box.z, box.width, box.height, box.depth); }

		void move(T _x, T _y, T _z) { x += _x; y += _y; z += _z; }
		void move(Vector3<T> d) { move(d.x, d.y, d.z); }

		bool intersects(const Box<T> &box) const {
			T r1MinX = std::min(x, static_cast<T>(x + width));
			T r1MaxX = std::max(x, static_cast<T>(x + width));
			T r1MinY = std::min(y, static_cast<T>(y + height));
			T r1MaxY = std::max(y, static_cast<T>(y + height));
			T r1MinZ = std::min(z, static_cast<T>(z + depth));
			T r1MaxZ = std::max(z, static_cast<T>(z + depth));

			T r2MinX = std::min(box.x, static_cast<T>(box.x + box.width));
			T r2MaxX = std::max(box.x, static_cast<T>(box.x + box.width));
			T r2MinY = std::min(box.y, static_cast<T>(box.y + box.height));
			T r2MaxY = std::max(box.y, static_cast<T>(box.y + box.height));
			T r2MinZ = std::min(box.z, static_cast<T>(box.z + box.depth));
			T r2MaxZ = std::max(box.z, static_cast<T>(box.z + box.depth));

			T interLeft   = std::max(r1MinX, r2MinX);
			T interRight  = std::min(r1MaxX, r2MaxX);
			T interBottom = std::max(r1MinY, r2MinY);
			T interTop    = std::min(r1MaxY, r2MaxY);
			T interFront  = std::max(r1MinZ, r2MinZ);
			T interBack   = std::min(r1MaxZ, r2MaxZ);

			return interLeft < interRight && interBottom < interTop && interFront < interBack;
		}

		Vector3<T> position() const { return {x, y, z}; }

		void setPosition(Vector3<T> vector3) { x = vector3.x; y = vector3.y; z = vector3.z; }

		Box operator+(const Vector3<T> &vector3) const { return Box{x + vector3.x, y + vector3.y, z + vector3.z, width, height, depth}; }
		Box operator-(const Vector3<T> &vector3) const { return Box{x - vector3.x, y - vector3.y, z - vector3.z, width, height, depth}; }

		Box &operator+=(const Vector3<T> &vector3) { *this = operator+(vector3); return *this; }
		Box &operator-=(const Vector3<T> &vector3) { *this = operator-(vector3); return *this; }

		T x = 0;
		T y = 0;
		T z = 0;

		T width = 0;
		T height = 0;
		T depth = 0;
};

using IntBox = Box<int>;
using FloatBox = Box<float>;
using DoubleBox = Box<double>;

}

#endif // GK_BOX_HPP_
