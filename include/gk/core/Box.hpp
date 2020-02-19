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

		Box(T _x, T _y, T _z, T _xsize, T _ysize, T _zsize) {
			reset(_x, _y, _z, _xsize, _ysize, _zsize);
		}

		Box(const Vector3<T> &_position, const Vector3<T> &_size) {
			reset(_position, _size);
		}

		template<typename U>
		Box(const Box<U> &box)
			: Box(box.position, box.size) {}

		void reset(T _x, T _y, T _z, T _xsize, T _ysize, T _zsize) {
			position.x = _x;
			position.y = _y;
			position.z = _z;
			size.x = _xsize;
			size.y = _ysize;
			size.z = _zsize;
		}

		void reset(Vector3<T> _position, Vector3<T> _size) {
			position = _position;
			size = _size;
		}

		void reset(Box<T> box) {
			reset(box.position, box.size);
		}

		void move(Vector3<T> d) { position += d; }
		void move(T _x, T _y, T _z) { move(Vector3<T>{_x, _y, _z}); }

		bool intersects(const Box<T> &box) const {
			T r1MinX = std::min(position.x, static_cast<T>(position.x + size.x));
			T r1MaxX = std::max(position.x, static_cast<T>(position.x + size.x));
			T r1MinY = std::min(position.y, static_cast<T>(position.y + size.y));
			T r1MaxY = std::max(position.y, static_cast<T>(position.y + size.y));
			T r1MinZ = std::min(position.z, static_cast<T>(position.z + size.z));
			T r1MaxZ = std::max(position.z, static_cast<T>(position.z + size.z));

			T r2MinX = std::min(box.position.x, static_cast<T>(box.position.x + box.size.x));
			T r2MaxX = std::max(box.position.x, static_cast<T>(box.position.x + box.size.x));
			T r2MinY = std::min(box.position.y, static_cast<T>(box.position.y + box.size.y));
			T r2MaxY = std::max(box.position.y, static_cast<T>(box.position.y + box.size.y));
			T r2MinZ = std::min(box.position.z, static_cast<T>(box.position.z + box.size.z));
			T r2MaxZ = std::max(box.position.z, static_cast<T>(box.position.z + box.size.z));

			T interLeft   = std::max(r1MinX, r2MinX);
			T interRight  = std::min(r1MaxX, r2MaxX);
			T interBottom = std::max(r1MinY, r2MinY);
			T interTop    = std::min(r1MaxY, r2MaxY);
			T interFront  = std::max(r1MinZ, r2MinZ);
			T interBack   = std::min(r1MaxZ, r2MaxZ);

			return interLeft < interRight && interBottom < interTop && interFront < interBack;
		}

		Box operator+(const Vector3<T> &vector3) const { return Box{position + vector3, size}; }
		Box operator-(const Vector3<T> &vector3) const { return Box{position - vector3, size}; }

		Box &operator+=(const Vector3<T> &vector3) { *this = operator+(vector3); return *this; }
		Box &operator-=(const Vector3<T> &vector3) { *this = operator-(vector3); return *this; }

		Vector3<T> position = {0, 0, 0};

		Vector3<T> size = {0, 0, 0};
};

using IntBox = Box<int>;
using FloatBox = Box<float>;
using DoubleBox = Box<double>;

}

#endif // GK_BOX_HPP_
