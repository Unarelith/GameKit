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
#include "gk/graphics/Font.hpp"
#include "gk/core/Exception.hpp"

namespace gk {

TTF_Font *Font::getFont(int ptsize) const {
	auto it = m_fonts.find(ptsize);
	if (it == m_fonts.end()) {
		TTF_FontPtr font{TTF_OpenFont(m_filename.c_str(), ptsize), TTF_CloseFont};
		if (font) {
			TTF_SetFontKerning(font.get(), m_kerning);
			TTF_SetFontHinting(font.get(), m_hinting);
			TTF_SetFontOutline(font.get(), m_outline);

			m_fonts.insert(std::pair<int, TTF_FontPtr>(ptsize, std::move(font)));
		}
		else
			throw EXCEPTION("Failed to load font '" + m_filename + "':", TTF_GetError());

	}

	return m_fonts.at(ptsize).get();
}

void Font::update() {
	for (auto &it : m_fonts) {
		TTF_SetFontKerning(it.second.get(), m_kerning);
		TTF_SetFontHinting(it.second.get(), m_hinting);
		TTF_SetFontOutline(it.second.get(), m_outline);
	}
}

} // namespace gk

