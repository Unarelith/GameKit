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

		Color operator-(const Color &color);

		bool operator==(const Color &color) const {
			return r == color.r && g == color.g && b == color.b && a == color.a;
		}

		bool operator!=(const Color &color) const {
			return !(*this == color);
		}

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
