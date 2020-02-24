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
#include "gk/graphics/Font.hpp"
#include "gk/core/Exception.hpp"

namespace gk {

void Font::loadFont(int ptsize) const {
	TTF_FontPtr font{TTF_OpenFont(m_filename.c_str(), ptsize), TTF_CloseFont};
	if (font) {
		TTF_SetFontKerning(font.get(), m_kerning);
		TTF_SetFontHinting(font.get(), m_hinting);
		TTF_SetFontOutline(font.get(), m_outline);

		m_fonts.emplace(ptsize, std::move(font));

		// DEBUG((void*)this, "- Loaded new font:", m_filename, ptsize);
	}
	else
		throw EXCEPTION("Failed to load font '" + m_filename + "':", TTF_GetError());
}

TTF_Font *Font::getFont(int ptsize) const {
	auto it = m_fonts.find(ptsize);
	if (it == m_fonts.end())
		loadFont(ptsize);

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

