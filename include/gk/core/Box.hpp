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
#ifndef GK_BOX_HPP_
#define GK_BOX_HPP_

#include <algorithm>

#include "Vector3.hpp"

namespace gk {

template<typename T>
class Box {
	public:
		Box() = default;

		Box(T _x, T _y, T _z, T _sizeX, T _sizeY, T _sizeZ) {
			reset(_x, _y, _z, _sizeX, _sizeY, _sizeZ);
		}

		Box(const Vector3<T> &_position, const Vector3<T> &_size) {
			reset(_position.x, _position.y, _position.z, _size.x, _size.y, _size.z);
		}

		template<typename U>
		Box(const Box<U> &box)
			: Box(box.x, box.y, box.z, box.sizeX, box.sizeY, box.sizeZ) {}

		void reset(T _x, T _y, T _z, T _sizeX, T _sizeY, T _sizeZ) {
			x = _x;
			y = _y;
			z = _z;
			sizeX = _sizeX;
			sizeY = _sizeY;
			sizeZ = _sizeZ;
		}

		void reset(Box<T> box) { reset(box.x, box.y, box.z, box.sizeX, box.sizeY, box.sizeZ); }

		void reset(Vector3<T> _position, Vector3<T> _size) {
			reset(_position.x, _position.y, _position.z, _size.x, _size.y, _size.z);
		}

		void move(T _x, T _y, T _z) { x += _x; y += _y; z += _z; }
		void move(Vector3<T> d) { move(d.x, d.y, d.z); }

		bool intersects(const Box<T> &box) const {
			T r1MinX = std::min(x, static_cast<T>(x + sizeX));
			T r1MaxX = std::max(x, static_cast<T>(x + sizeX));
			T r1MinY = std::min(y, static_cast<T>(y + sizeY));
			T r1MaxY = std::max(y, static_cast<T>(y + sizeY));
			T r1MinZ = std::min(z, static_cast<T>(z + sizeZ));
			T r1MaxZ = std::max(z, static_cast<T>(z + sizeZ));

			T r2MinX = std::min(box.x, static_cast<T>(box.x + box.sizeX));
			T r2MaxX = std::max(box.x, static_cast<T>(box.x + box.sizeX));
			T r2MinY = std::min(box.y, static_cast<T>(box.y + box.sizeY));
			T r2MaxY = std::max(box.y, static_cast<T>(box.y + box.sizeY));
			T r2MinZ = std::min(box.z, static_cast<T>(box.z + box.sizeZ));
			T r2MaxZ = std::max(box.z, static_cast<T>(box.z + box.sizeZ));

			T interLeft   = std::max(r1MinX, r2MinX);
			T interRight  = std::min(r1MaxX, r2MaxX);
			T interBottom = std::max(r1MinY, r2MinY);
			T interTop    = std::min(r1MaxY, r2MaxY);
			T interFront  = std::max(r1MinZ, r2MinZ);
			T interBack   = std::min(r1MaxZ, r2MaxZ);

			return interLeft < interRight && interBottom < interTop && interFront < interBack;
		}

		Vector3<T> position() const { return {x, y, z}; }
		Vector3<T> size() const { return {sizeX, sizeY, sizeZ}; }

		void setPosition(Vector3<T> vector3) { x = vector3.x; y = vector3.y; z = vector3.z; }
		void setSize(Vector3<T> vector3) { sizeX = vector3.x; sizeY = vector3.y; sizeZ = vector3.z; }

		Box &operator+=(const Vector3<T> &vector3) { *this = operator+(vector3); return *this; }
		Box &operator-=(const Vector3<T> &vector3) { *this = operator-(vector3); return *this; }

		T x = 0;
		T y = 0;
		T z = 0;

		T sizeX = 0;
		T sizeY = 0;
		T sizeZ = 0;

		template<typename U>
		auto operator+(const Vector3<U> &vector3) const -> Box<decltype(x + vector3.x)> {
			return {x + vector3.x, y + vector3.y, z + vector3.z, sizeX, sizeY, sizeZ};
		}

		template<typename U>
		auto operator-(const Vector3<T> &vector3) const -> Box<decltype(x - vector3.x)> {
			return {x - vector3.x, y - vector3.y, z - vector3.z, sizeX, sizeY, sizeZ};
		}
};

using IntBox = Box<int>;
using FloatBox = Box<float>;
using DoubleBox = Box<double>;

}

#endif // GK_BOX_HPP_
