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
#ifndef GK_VECTOR4_HPP_
#define GK_VECTOR4_HPP_

#include <stdexcept>
#include <utility>

#include "gk/core/IntTypes.hpp"
#include "gk/core/Vector2.hpp"
#include "gk/core/Vector3.hpp"

namespace gk {

template<typename T>
class Vector4 {
	public:
		Vector4() = default;
		Vector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

		template<typename U, typename U2>
		Vector4(const Vector2<U> &vector2, U _z, U2 _w) : x(vector2.x), y(vector2.y), z(_z), w(_w) {}

		template<typename U>
		Vector4(const Vector3<U> &vector3, U _w) : x(vector3.x), y(vector3.y), z(vector3.z), w(_w) {}

		template<typename U>
		Vector4(const Vector4<U> &vector4) : x(vector4.x), y(vector4.y), z(vector4.z), w(vector4.w) {}

		Vector4 operator-() const { return Vector4{-x, -y, -z, -w}; }

		Vector4 &operator=(T n)                     { x = n; y = n; z = n; w = n; return *this; }
		Vector4 &operator+=(const Vector4 &vector4) { *this = operator+(vector4); return *this; }
		Vector4 &operator-=(const Vector4 &vector4) { *this = operator-(vector4); return *this; }
		Vector4 &operator*=(T n)                    { *this = operator*(n); return *this; }
		Vector4 &operator/=(T n)                    { *this = operator/(n); return *this; }

		bool operator==(const Vector4<T> &vector4) const { return x == vector4.x && y == vector4.y && z == vector4.z && w == vector4.w; }
		bool operator!=(const Vector4<T> &vector4) const { return !operator==(vector4); }

		// Needed if Vector4 is used as a key in a std::map
		bool operator<(const Vector4<T> &vector4) const { return x < vector4.x && y < vector4.y && z < vector4.z && w < vector4.w; }
		bool operator>(const Vector4<T> &vector4) const { return x > vector4.x && y > vector4.y && z > vector4.z && w > vector4.w; }

		T x;
		T y;
		T z;
		T w;

		// Operators
		auto cross(const Vector4<T> &vector4) const {
			return x * vector4.x + y * vector4.y + z * vector4.z + w * vector4.w;
		}

		template<typename U>
		auto operator+(const Vector4<U> &vector4) const -> Vector4<decltype(x + vector4.x)> {
			return {x + vector4.x, y + vector4.y, z + vector4.z, w + vector4.w};
		}

		template<typename U>
		auto operator+(U n) const -> Vector4<decltype(x + n)> {
			return {x + n, y + n, z + n, w + n};
		}

		template<typename U>
		auto operator-(const Vector4<U> &vector4) const -> Vector4<decltype(x - vector4.x)> {
			return {x - vector4.x, y - vector4.y, z - vector4.z, w - vector4.w};
		}

		template<typename U>
		auto operator*(U n) const -> Vector4<decltype(x * n)> {
			return {x * n, y * n, z * n, w * n};
		}

		template<typename U>
		auto operator/(U n) const -> Vector4<decltype(x / n)> {
			if(n != 0) {
				return {x / n, y / n, z / n, w / n};
			} else {
				throw std::overflow_error("Divide by zero exception");
			}
		}
};

template<typename T, typename U>
Vector4<T> operator*(T n, Vector4<U> &vector4) { return vector4.operator*(n); }

using Vector4i = Vector4<int>;
using Vector4u = Vector4<unsigned int>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;

} // namespace gk

#endif // GK_VECTOR4_HPP_
