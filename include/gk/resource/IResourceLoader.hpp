/*
 * =====================================================================================
 *
 *       Filename:  IResourceLoader.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:31:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_IRESOURCELOADER_HPP_
#define GK_IRESOURCELOADER_HPP_

#include <string>

namespace gk {

class ResourceHandler;

class IResourceLoader {
	public:
		virtual ~IResourceLoader() = default;

		virtual void load(const char *xmlFilename, ResourceHandler &handler) = 0;
};

} // namespace gk

#endif // GK_RESOURCELOADER_HPP_
