/*
 * =====================================================================================
 *
 *       Filename:  TilesetLoader.hpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 19:37:16
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TILESETLOADER_HPP_
#define GK_TILESETLOADER_HPP_

#include "gk/resource/IResourceLoader.hpp"

namespace gk {

class TilesetLoader : public IResourceLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler);
};

} // namespace gk

#endif // GK_TILESETLOADER_HPP_
