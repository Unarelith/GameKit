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

////////////////////////////////////////////////////////////
/// \brief Class for loading and manipulating character fonts
///
////////////////////////////////////////////////////////////
class Font : public NonCopyable {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// This constructor defines an empty font
		///
		////////////////////////////////////////////////////////////
		Font() = default;

		////////////////////////////////////////////////////////////
		/// \brief Construct the font from a file
		///
		/// \param filename Path of the font file to load
		///
		////////////////////////////////////////////////////////////
		Font(const std::string &filename) : m_filename(filename) {}

		////////////////////////////////////////////////////////////
		/// \brief Load the font from a file
		///
		/// \param filename Path of the font file to load
		///
		////////////////////////////////////////////////////////////
		void loadFromFile(const std::string &filename) { m_filename = filename; }

		////////////////////////////////////////////////////////////
		/// \brief Set font kerning
		///
		/// \param kerning New font kerning
		///
		////////////////////////////////////////////////////////////
		void setFontKerning(int kerning) { m_kerning = kerning; update(); }

		////////////////////////////////////////////////////////////
		/// \brief Set font hinting
		///
		/// \param kerning New font hinting
		///
		////////////////////////////////////////////////////////////
		void setFontHinting(int hinting) { m_hinting = hinting; update(); }

		////////////////////////////////////////////////////////////
		/// \brief Set font outline
		///
		/// \param outline New font outline
		///
		////////////////////////////////////////////////////////////
		void setFontOutline(int outline) { m_outline = outline; update(); }

		////////////////////////////////////////////////////////////
		/// \brief Load a new font size into this font
		///
		/// \param ptsize Font size
		///
		////////////////////////////////////////////////////////////
		void loadFont(int ptsize) const;

		////////////////////////////////////////////////////////////
		/// \brief Get the SDL font for a specific font size
		///
		/// \param ptsize Font size
		///
		////////////////////////////////////////////////////////////
		TTF_Font *getFont(int ptsize) const;

	private:
		////////////////////////////////////////////////////////////
		/// \brief Update kerning, hinting and outline of all font sizes
		///
		////////////////////////////////////////////////////////////
		void update();

		using TTF_FontPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		std::string m_filename;                                ///< Font filename

		int m_kerning = 1;                                     ///< Kerning value
		int m_hinting = TTF_HINTING_NORMAL;                    ///< Hinting value
		int m_outline = 0;                                     ///< Outline value

		mutable std::unordered_map<int, TTF_FontPtr> m_fonts;  ///< SDL font container
};

} // namespace gk

#endif // GK_FONT_HPP_

////////////////////////////////////////////////////////////
/// \class gk::Font
/// \ingroup graphics
///
/// gk::Font is a class that allows loading a font from a file.
///
/// This class can't display anything on its own and has to be used with gk::Text.
///
/// /warning Each different font size will result in another SDL object loaded, please avoid using a lot of different sizes for the same font.
///
////////////////////////////////////////////////////////////
