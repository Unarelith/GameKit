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
#ifndef GK_TEXTURE_HPP_
#define GK_TEXTURE_HPP_

#include <string>

#include "gk/core/IntTypes.hpp"
#include "gk/core/SDLHeaders.hpp"
#include "gk/core/Vector2.hpp"
#include "gk/gl/OpenGL.hpp"
#include "gk/utils/NonCopyable.hpp"

namespace gk {

////////////////////////////////////////////////////////////
/// \brief Image living on the graphics card that can be used for drawing
///
////////////////////////////////////////////////////////////
class Texture : public NonCopyable {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// Creates an empty texture.
		///
		////////////////////////////////////////////////////////////
		Texture() = default;

		////////////////////////////////////////////////////////////
		/// \brief Load the texture from a file on the disk
		///
		/// \param filename Relative or absolute path to the file
		///
		////////////////////////////////////////////////////////////
		Texture(const std::string &filename);

		////////////////////////////////////////////////////////////
		/// \brief Load the texture from a SDL_Surface
		///
		/// \param surface Pointer to the surface where the data is stored
		///
		////////////////////////////////////////////////////////////
		Texture(SDL_Surface *surface);

		////////////////////////////////////////////////////////////
		/// \brief Move constructor
		///
		/// \param texture instance to move
		///
		////////////////////////////////////////////////////////////
		Texture(Texture &&texture);

		////////////////////////////////////////////////////////////
		/// \brief Destructor
		///
		////////////////////////////////////////////////////////////
		~Texture() noexcept;

		////////////////////////////////////////////////////////////
		/// \brief Move assignement operator
		///
		/// \param texture instance to move
		///
		////////////////////////////////////////////////////////////
		Texture &operator=(Texture &&texture);

		////////////////////////////////////////////////////////////
		/// \brief Load the texture from a file on the disk
		///
		/// \param filename Relative or absolute path to the file
		///
		////////////////////////////////////////////////////////////
		void loadFromFile(const std::string &filename);

		////////////////////////////////////////////////////////////
		/// \brief Load the texture from a SDL_Surface
		///
		/// \param surface Pointer to the surface where the data is stored
		///
		////////////////////////////////////////////////////////////
		void loadFromSurface(SDL_Surface *surface);

		////////////////////////////////////////////////////////////
		/// \brief Return the filename of the texture
		///
		/// \return Texture filename
		///
		////////////////////////////////////////////////////////////
		const std::string &filename() const { return m_filename; }

		////////////////////////////////////////////////////////////
		/// \brief Return the size of the texture
		///
		/// \return Size in pixels
		///
		////////////////////////////////////////////////////////////
		const gk::Vector2u &getSize() const { return m_size; }

		////////////////////////////////////////////////////////////
		/// \brief Bind a texture for rendering
		///
		/// \param texture Pointer to the texture to bind, can be null to use no texture
		///
		////////////////////////////////////////////////////////////
		static void bind(const Texture *texture);

	private:
		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		static const Texture *s_boundTexture;

		std::string m_filename; ///< Texture filename

		gk::Vector2u m_size;    ///< Size of the texture

		GLuint m_texture = 0;   ///< Internal OpenGL texture ID
};

} // namespace gk

#endif // GK_TEXTURE_HPP_

////////////////////////////////////////////////////////////
/// \class gk::Texture
/// \ingroup graphics
///
/// gk::Texture is an overlay to OpenGL texture system.
///
/// \see gk::Image, gk::Sprite
///
////////////////////////////////////////////////////////////
