/*
 * =====================================================================================
 *
 *       Filename:  Color.hpp
 *
 *    Description:
 *
 *        Created:  27/09/2014 22:35:38
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_COLOR_HPP_
#define GK_COLOR_HPP_

#include "gk/core/IntTypes.hpp"

namespace gk {

class Color {
	public:
		Color() = default;
		Color(u8 _r, u8 _g, u8 _b, u8 _a = 255);

		// Only used in Asylia
		void invert() { r = 1 - r; g = 1 - g; b = 1 - b; }

		Color operator-(const Color &c) { return Color(r - c.r, g - c.g, b - c.b, a - c.a); }
		Color operator+(const Color &c) { return Color(r + c.r, g + c.g, b + c.b, a + c.a); }

		bool operator==(const Color &color) const {
			return r == color.r && g == color.g && b == color.b && a == color.a;
		}

		bool operator!=(const Color &color) const {
			return !(*this == color);
		}

		// Only used in Asylia
		u8 r255() const { return r * 255; }
		u8 g255() const { return g * 255; }
		u8 b255() const { return b * 255; }
		u8 a255() const { return a * 255; }

		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;
};

} // namespace gk

#endif // GK_COLOR_HPP_
