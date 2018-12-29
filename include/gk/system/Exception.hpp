/*
 * =====================================================================================
 *
 *       Filename:  Exception.hpp
 *
 *    Description:
 *
 *        Created:  14/12/2014 05:02:53
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GK_EXCEPTION_HPP_
#define GK_EXCEPTION_HPP_

#include <exception>
#include <string>

#include "gk/system/Debug.hpp"

#define EXCEPTION(args...) (gk::Exception(__LINE__, _FILE, args))

namespace gk {

class Exception {
	public:
		template<typename... Args>
		Exception(u16 line, std::string filename, Args... args) noexcept {
			m_errorMsg = Debug::textColor(Debug::TextColor::Red, true);
			m_errorMsg += "at " + filename + ":" + std::to_string(line) + ": ";
			m_errorMsg += Debug::makeString(std::forward<Args>(args)...);
			m_errorMsg += Debug::textColor();
		}

		virtual const char *what() const noexcept {
			return m_errorMsg.c_str();
		}

	private:
		std::string m_errorMsg;
};

} // namespace gk

#endif // GK_EXCEPTION_HPP_
