/*
 * =====================================================================================
 *
 *       Filename:  Color.cpp
 *
 *    Description:
 *
 *        Created:  27/09/2014 22:35:45
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/graphics/Color.hpp"

namespace gk {

const Color Color::Black(0, 0, 0);
const Color Color::White(255, 255, 255);
const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Yellow(255, 255, 0);
const Color Color::Magenta(255, 0, 255);
const Color Color::Cyan(0, 255, 255);
const Color Color::Transparent(0, 0, 0, 0);

Color::Color(u8 _r, u8 _g, u8 _b, u8 _a) {
	r = _r / 255.0f;
	g = _g / 255.0f;
	b = _b / 255.0f;
	a = _a / 255.0f;
}

Color Color::operator-(const Color &color) {
	return Color(r - color.r, g - color.g, b - color.b, a - color.a);
}

} // namespace gk

