/*
 * =====================================================================================
 *
 *       Filename:  Filesystem.hpp
 *
 *    Description:
 *
 *        Created:  22/02/2015 16:25:51
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_FILESYSTEM_HPP_
#define GK_FILESYSTEM_HPP_

#include <string>

namespace gk {

class Filesystem {
	public:
		static bool fileExists(const std::string &filename);
};

} // namespace gk

#endif // GK_FILESYSTEM_HPP_
