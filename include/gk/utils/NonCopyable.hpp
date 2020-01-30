/*
 * =====================================================================================
 *
 *       Filename:  NonCopyable.hpp
 *
 *    Description:
 *
 *        Created:  12/06/2018 22:23:46
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_NONCOPYABLE_HPP_
#define GK_NONCOPYABLE_HPP_

namespace gk {

class NonCopyable {
	protected:
		NonCopyable() = default;
		NonCopyable(const NonCopyable &) = delete;
		NonCopyable(NonCopyable &&) = default;

		NonCopyable &operator=(const NonCopyable &) = delete;
		NonCopyable &operator=(NonCopyable &&) = default;
};

}

#endif // GK_NONCOPYABLE_HPP_
