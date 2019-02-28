/*
 * =====================================================================================
 *
 *       Filename:  Font.hpp
 *
 *    Description:
 *
 *        Created:  30/12/2018 18:54:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_FONT_HPP_
#define GK_FONT_HPP_

#include <memory>
#include <string>
#include <unordered_map>

#include "gk/core/SDLHeaders.hpp"
#include "gk/utils/NonCopyable.hpp"

namespace gk {

class Font : public NonCopyable {
	public:
		Font() = default;
		Font(const std::string &filename) : m_filename(filename) {}

		void loadFromFile(const std::string &filename) { m_filename = filename; }

		void setFontKerning(int kerning) { m_kerning = kerning; update(); }
		void setFontHinting(int hinting) { m_hinting = hinting; update(); }
		void setFontOutline(int outline) { m_outline = outline; update(); }

		void loadFont(int ptsize) const;
		TTF_Font *getFont(int ptsize) const;

	private:
		void update();

		using TTF_FontPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;

		std::string m_filename;

		int m_kerning = 1;
		int m_hinting = TTF_HINTING_NORMAL;
		int m_outline = 0;

		mutable std::unordered_map<int, TTF_FontPtr> m_fonts;
};

} // namespace gk

#endif // GK_FONT_HPP_
