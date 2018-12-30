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

namespace gk {

class Font {
	public:
		Font() = default;
		Font(const std::string &filename) : m_filename(filename) {}

		void loadFromFile(const std::string &filename) { m_filename = filename; }

		TTF_Font *getFont(int ptsize) const;

	private:
		using TTF_FontPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;

		std::string m_filename;

		mutable std::unordered_map<int, TTF_FontPtr> m_fonts;
};

} // namespace gk

#endif // GK_FONT_HPP_
