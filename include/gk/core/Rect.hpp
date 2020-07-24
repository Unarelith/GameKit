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
#ifndef GK_RECT_HPP_
#define GK_RECT_HPP_

#include <algorithm>

#include "gk/core/Vector2.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Utility class for manipulating 2D axis aligned rectangles
///
////////////////////////////////////////////////////////////
template<typename T>
class Rect {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// Creates an empty rectangle (it is equivalent to calling
		/// Rect(0, 0, 0, 0)).
		///
		////////////////////////////////////////////////////////////
		Rect() = default;

		////////////////////////////////////////////////////////////
		/// \brief Construct the rectangle from its coordinates
		///
		/// Be careful, the last two parameters are the width
		/// and height, not the right and bottom coordinates!
		///
		/// \param _x      Left coordinate of the rectangle
		/// \param _y      Top coordinate of the rectangle
		/// \param _width  Width of the rectangle
		/// \param _height Height of the rectangle
		///
		////////////////////////////////////////////////////////////
		Rect(T _x, T _y, T _sizeX, T _sizeY)
			: x(_x), y(_y), sizeX(_sizeX), sizeY(_sizeY) {}

		////////////////////////////////////////////////////////////
		/// \brief Construct the rectangle from position and size
		///
		/// Be careful, the last parameter is the size,
		/// not the bottom-right corner!
		///
		/// \param position Position of the top-left corner of the rectangle
		/// \param size     Size of the rectangle
		///
		////////////////////////////////////////////////////////////
		Rect(const Vector2<T> &position, const Vector2<T> &size)
			: x(position.x), y(position.x), sizeX(size.x), sizeY(size.y) {}

		////////////////////////////////////////////////////////////
		/// \brief Construct the rectangle from another type of rectangle
		///
		/// This constructor doesn't replace the copy constructor,
		/// it's called only when U != T.
		/// A call to this constructor will fail to compile if U
		/// is not convertible to T.
		///
		/// \param rect Rectangle to convert
		///
		////////////////////////////////////////////////////////////
		template<typename U>
		explicit Rect(const Rect<U> &rect)
			: Rect(rect.x, rect.y, rect.sizeX, rect.sizeY) {}

		////////////////////////////////////////////////////////////
		/// \brief Check if a point is inside the rectangle's area
		///
		/// This check is partially inclusive. If the point lies on
		/// the right or bottom edge of the rectangle, this function
		/// will return false.
		///
		/// Assumes size is always positive.
		///
		/// \param _x X coordinate of the point to test
		/// \param _y Y coordinate of the point to test
		///
		/// \return True if the point is inside, false otherwise
		///
		/// \see intersects
		///
		////////////////////////////////////////////////////////////
		bool contains(T _x, T _y) const {
			T x2 = x + sizeX;
			T y2 = y + sizeY;

			return (_x >= x) && (_x < x2) && (_y >= y) && (_y < y2);
		}

		////////////////////////////////////////////////////////////
		/// \brief Check if a point is inside the rectangle's area
		///
		/// This check is partially inclusive. If the point lies on
		/// the right or bottom edge of the rectangle, this function
		/// will return false.
		///
		/// \param point Point to test
		///
		/// \return True if the point is inside, false otherwise
		///
		/// \see intersection, intersects, intersectionDirection
		///
		////////////////////////////////////////////////////////////
		bool contains(const Vector2<T> &point) const {
			return contains(point.x, point.y);
		}

		////////////////////////////////////////////////////////////
		/// \brief Check the intersection between two rectangles
		///
		/// Assumes size is always positive.
		///
		/// \param rect Rectangle to test
		///
		/// \return True if rectangles overlap, false otherwise
		///
		/// \see intersection, contains, intersectionDirection
		///
		////////////////////////////////////////////////////////////
		bool intersects(const Rect<T> &rect) const {
			/*
			 * Using && here implies short-circuit evaluation, which is
			 * compiled in this case as a conditional branch. We assume that
			 * the probability of an intersection is around 50%. Testing shows
			 * that the impact of evaluating all terms is less than that of
			 * mispredicted branches, so we avoid && and use & instead, which
			 * works fine on boolean conditions.
			 */
			return std::max(x, rect.x) < std::min(x + sizeX, rect.x + rect.sizeX)
			     & std::max(y, rect.y) < std::min(y + sizeY, rect.y + rect.sizeY);
		}

		////////////////////////////////////////////////////////////
		/// \brief Return the intersection between two rectangles
		///
		/// Assumes size is always positive.
		///
		/// \param rect Rectangle to test
		///
		/// \return The intersection if rectangles overlap, {0,0,0,0} otherwise.
		///
		/// \see intersects, contains, intersectionDirection
		///
		////////////////////////////////////////////////////////////
		Rect<T> intersection(const Rect<T> &rect) {
			T x1 = std::max(x, rect.x);
			T y1 = std::max(y, rect.y);
			T sx = std::min(x + sizeX, rect.x + rect.sizeX) - x1;
			T sy = std::min(y + sizeY, rect.y + rect.sizeY) - y1;
			if (sx <= 0 || sy <= 0) {
				return Rect<T>{0, 0, 0, 0};
			}
			return Rect<T>{x1, y1, sx, sy};
		}

		////////////////////////////////////////////////////////////
		/// \brief Check the intersection direction between two rectangles
		///
		/// Assumes size is always positive.
		///
		/// \param rect Rectangle to test
		///
		/// \return 1 for horizontal, 2 for vertical, 0 for no intersection
		///
		/// \see contains, intersects, intersection
		///
		////////////////////////////////////////////////////////////
		int intersectionDirection(const Rect<T> &rect) const {
			T x2  = x + sizeX;
			T rx2 = rect.x + rect.sizeX;
			T y2  = y + sizeY;
			T ry2 = rect.y + rect.sizeY;
			T interLeft   = std::max(x, rect.x);
			T interTop    = std::max(y, rect.y);
			T interRight  = std::min(x2, rx2);
			T interBottom = std::min(y2, ry2);

			if(interLeft < interRight && interTop < interBottom) {
				if(interRight - interLeft < interBottom - interTop) {
					return 1;
				} else {
					return 2;
				}
			} else {
				return 0;
			}
		}

		////////////////////////////////////////////////////////////
		/// \brief Overload of binary operator ==
		///
		/// This operator compares strict equality between two rectangles.
		///
		/// \param rect Rectangle to compare with
		///
		/// \return True if this rectangle is equal to \p rect
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Rect<T> &rect) const { return x == rect.x && y == rect.y && sizeX == rect.sizeX && sizeY == rect.sizeY; }

		////////////////////////////////////////////////////////////
		/// \brief Overload of binary operator !=
		///
		/// This operator compares strict difference between two rectangles.
		///
		/// \param rect Rectangle to compare with
		///
		/// \return True if this rectangle is not equal to \p rect
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Rect<T> &rect) const { return !operator==(rect); }

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		T x = 0;      ///< X coordinate of the rectangle
		T y = 0;      ///< Y coordinate of the rectangle
		T sizeX = 0;  ///< X size of the rectangle
		T sizeY = 0;  ///< Y size of the rectangle
};

// Create typedefs for the most common types
using IntRect = Rect<int>;
using FloatRect = Rect<float>;

} // namespace gk

#endif // GK_RECT_HPP_

////////////////////////////////////////////////////////////
/// \class gk::Rect
/// \ingroup core
///
/// This part of the documentation has been taken from SFML
///
/// A rectangle is defined by its top-left corner and its size.
/// It is a very simple class defined for convenience, so
/// its member variables (x, y, sizeX and sizeY) are public
/// and can be accessed directly, just like the vector classes
/// (Vector2 and Vector3).
///
/// To keep things simple, gk::Rect doesn't define
/// functions to emulate the properties that are not directly
/// members (such as right, bottom, center, etc.), it rather
/// only provides intersection functions.
///
/// gk::Rect uses the usual rules for its boundaries:
/// \li The left and top edges are included in the rectangle's area
/// \li The right (x + sizeX) and bottom (y + sizeY) edges are excluded from the rectangle's area
///
/// This means that gk::IntRect(0, 0, 1, 1) and gk::IntRect(1, 1, 1, 1)
/// don't intersect.
///
/// gk::Rect is a template and may be used with any numeric type, but
/// for simplicity the instantiations used by GameKit are typedef'd:
/// \li gk::Rect<int> is gk::IntRect
/// \li gk::Rect<float> is gk::FloatRect
///
/// So that you don't have to care about the template syntax.
///
/// Usage example:
/// \code
/// // Define a rectangle, located at (0, 0) with a size of 20x5
/// gk::IntRect r1(0, 0, 20, 5);
///
/// // Define another rectangle, located at (4, 2) with a size of 18x10
/// gk::Vector2i position(4, 2);
/// gk::Vector2i size(18, 10);
/// gk::IntRect r2(position, size);
///
/// // Test intersections with the point (3, 1)
/// bool b1 = r1.contains(3, 1); // true
/// bool b2 = r2.contains(3, 1); // false
///
/// // Test the intersection between r1 and r2
/// gk::IntRect result;
/// bool b3 = r1.intersects(r2, result); // true
/// // result == (4, 2, 16, 3)
/// \endcode
///
////////////////////////////////////////////////////////////
