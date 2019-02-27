/*
 * =====================================================================================
 *
 *       Filename:  GLCheck.hpp
 *
 *    Description:
 *
 *        Created:  27/02/2019 01:40:51
 *
 *         Author:  SFML
 *
 * =====================================================================================
 */
#ifndef GK_GLCHECK_HPP_
#define GK_GLCHECK_HPP_

// #ifdef DEBUG_ENABLED
	#define glCheck(expr) do { expr; gk::priv::glCheckError(__FILE__, __LINE__, #expr); } while (false)
// #else
// 	#define glCheck(expr) (expr)
// #endif

namespace gk {
	namespace priv {
		void glCheckError(const char* file, unsigned int line, const char* expression);
	}
}

#endif // GK_GLCHECK_HPP_
