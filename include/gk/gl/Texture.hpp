/*
 * =====================================================================================
 *
 *       Filename:  Texture.hpp
 *
 *    Description:
 *
 *        Created:  20/12/2014 01:15:27
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TEXTURE_HPP_
#define GK_TEXTURE_HPP_

#include <string>

#include "gk/core/IntTypes.hpp"
#include "gk/gl/OpenGL.hpp"
#include "gk/utils/NonCopyable.hpp"

namespace gk {

class Texture : public NonCopyable {
	public:
		Texture() = default;
		Texture(const std::string &filename);
		Texture(Texture &&);
		~Texture() noexcept;

		Texture &operator=(Texture &&) = default;

		void loadFromFile(const std::string &filename);

		static void bind(const Texture *texture);

		u16 width() const { return m_width; }
		u16 height() const { return m_height; }

	private:
		std::string m_filename;

		u16 m_width;
		u16 m_height;

		GLuint m_texture = 0;
};

} // namespace gk

#endif // GK_TEXTURE_HPP_
