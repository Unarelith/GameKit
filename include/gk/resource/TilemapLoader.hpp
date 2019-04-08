/*
 * =====================================================================================
 *
 *       Filename:  TilemapLoader.hpp
 *
 *    Description:
 *
 *        Created:  15/02/2019 19:31:39
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_TILEMAPLOADER_HPP_
#define GK_TILEMAPLOADER_HPP_

#include "gk/resource/ResourceHandler.hpp"

namespace gk {

class Tileset;

class TilemapLoader : public IResourceLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler) override;

	private:
		void loadMap(const std::string &name, Tileset &tileset, ResourceHandler &handler);
};

} // namespace gk

#endif // GK_TILEMAPLOADER_HPP_
