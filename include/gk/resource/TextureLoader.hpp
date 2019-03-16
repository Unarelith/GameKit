/*
 * =====================================================================================
 *
 *       Filename:  TextureLoader.hpp
 *
 *    Description:
 *
 *        Created:  16/03/2019 18:30:52
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TEXTURELOADER_HPP_
#define GK_TEXTURELOADER_HPP_

#include "gk/resource/IResourceLoader.hpp"

namespace gk {

class TextureLoader : public IResourceLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler);
};

} // namespace gk

#endif // GK_TEXTURELOADER_HPP_
