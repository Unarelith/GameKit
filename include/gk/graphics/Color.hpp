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
#ifndef GK_COLOR_HPP_
#define GK_COLOR_HPP_

#include "gk/core/IntTypes.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Utility class for manipulating RGBA colors
///
////////////////////////////////////////////////////////////
class Color {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// Constructs an opaque white color. It is equivalent to
		/// gk::Color(255, 255, 255, 255).
		///
		////////////////////////////////////////////////////////////
		Color() = default;

		////////////////////////////////////////////////////////////
		/// \brief Construct the color from its 4 RGBA components
		///
		/// \param _r Red component (in the range [0, 255])
		/// \param _g Green component (in the range [0, 255])
		/// \param _b Blue component (in the range [0, 255])
		/// \param _a Alpha (opacity) component (in the range [0, 255])
		///
		////////////////////////////////////////////////////////////
		Color(u8 _r, u8 _g, u8 _b, u8 _a = 255);

		// Only used in Asylia
		void invert() { r = 1 - r; g = 1 - g; b = 1 - b; }

		////////////////////////////////////////////////////////////
		/// \brief Overload of the binary + operator
		///
		/// This operator returns the component-wise sum of two colors.
		/// Components that exceed 255 are clamped to 255.
		///
		/// \param c Right operand
		///
		/// \return Result of \a left + \a right
		///
		////////////////////////////////////////////////////////////
		Color operator+(const Color &c) { return Color(r + c.r, g + c.g, b + c.b, a + c.a); }

		////////////////////////////////////////////////////////////
		/// \brief Overload of the binary - operator
		///
		/// This operator returns the component-wise subtraction of two colors.
		/// Components below 0 are clamped to 0.
		///
		/// \param c Right operand
		///
		/// \return Result of \a left - \a right
		///
		////////////////////////////////////////////////////////////
		Color operator-(const Color &c) { return Color(r - c.r, g - c.g, b - c.b, a - c.a); }

		////////////////////////////////////////////////////////////
		/// \brief Overload of binary operator ==
		///
		/// This operator compares strict equality between two colors.
		///
		/// \param color Color to compare with
		///
		/// \return True if this color is equal to \a color
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Color &color) const {
			return r == color.r && g == color.g && b == color.b && a == color.a;
		}

		////////////////////////////////////////////////////////////
		/// \brief Overload of binary operator !=
		///
		/// This operator compares strict difference between two colors.
		///
		/// \param color Color to compare with
		///
		/// \return True if this color is not equal to \a color
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Color &color) const {
			return !(*this == color);
		}

		// Only used in Asylia
		u8 r255() const { return r * 255; }
		u8 g255() const { return g * 255; }
		u8 b255() const { return b * 255; }
		u8 a255() const { return a * 255; }

		// FIXME: Use u8 instead of float and normalize when sending to OpenGL
		float r = 1.0f; ///< Red component
		float g = 1.0f; ///< Green component
		float b = 1.0f; ///< Blue component
		float a = 1.0f; ///< Alpha (opacity) component

		static const Color Black;       ///< Black predefined color
		static const Color White;       ///< White predefined color
		static const Color Red;         ///< Red predefined color
		static const Color Green;       ///< Green predefined color
		static const Color Blue;        ///< Blue predefined color
		static const Color Yellow;      ///< Yellow predefined color
		static const Color Magenta;     ///< Magenta predefined color
		static const Color Cyan;        ///< Cyan predefined color
		static const Color Transparent; ///< Transparent (black) predefined color
};

} // namespace gk

#endif // GK_COLOR_HPP_

////////////////////////////////////////////////////////////
/// \class gk::Color
/// \ingroup graphics
///
/// This part of the documentation has been taken from SFML
/// Once the migration to SFML 2.6 is done, this file will be removed
///
/// gk::Color is a simple color class composed of 4 components:
/// \li Red
/// \li Green
/// \li Blue
/// \li Alpha (opacity)
///
/// Each component is a public member, an unsigned integer in
/// the range [0, 255]. Thus, colors can be constructed and
/// manipulated very easily:
///
/// \code
/// gk::Color color(255, 0, 0); // red
/// color.r = 0;                // make it black
/// color.b = 0.5f;             // make it dark blue
/// \endcode
///
/// The fourth component of colors, named "alpha", represents
/// the opacity of the color. A color with an alpha value of
/// 255 will be fully opaque, while an alpha value of 0 will
/// make a color fully transparent, whatever the value of the
/// other components is.
///
/// The most common colors are already defined as static variables:
/// \code
/// gk::Color black       = gk::Color::Black;
/// gk::Color white       = gk::Color::White;
/// gk::Color red         = gk::Color::Red;
/// gk::Color green       = gk::Color::Green;
/// gk::Color blue        = gk::Color::Blue;
/// gk::Color yellow      = gk::Color::Yellow;
/// gk::Color magenta     = gk::Color::Magenta;
/// gk::Color cyan        = gk::Color::Cyan;
/// gk::Color transparent = gk::Color::Transparent;
/// \endcode
///
/// Colors can also be added and modulated (multiplied) using the
/// overloaded operators + and *.
///
////////////////////////////////////////////////////////////
