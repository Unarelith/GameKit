/*
 * =====================================================================================
 *
 *       Filename:  Font.cpp
 *
 *    Description:
 *
 *        Created:  30/12/2018 19:00:23
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/gui/Font.hpp"
#include "gk/system/Exception.hpp"

namespace gk {

TTF_Font *Font::getFont(int ptsize) const {
	auto it = m_fonts.find(ptsize);
	if (it == m_fonts.end()) {
		TTF_FontPtr font{TTF_OpenFont(m_filename.c_str(), ptsize), TTF_CloseFont};
		if (font) {
			// TTF_SetFontHinting(font.get(), TTF_HINTING_NONE);
			// TTF_SetFontKerning(font.get(), 0);
			// TTF_SetFontOutline(font.get(), 1);
			m_fonts.insert(std::pair<int, TTF_FontPtr>(ptsize, std::move(font)));
		}
		else
			throw EXCEPTION("Failed to load font '" + m_filename + "':", TTF_GetError());

	}

	return m_fonts.at(ptsize).get();
}

} // namespace gk

