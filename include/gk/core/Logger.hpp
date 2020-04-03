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
#ifndef GK_LOGGER_HPP_
#define GK_LOGGER_HPP_

#include <iostream>
#include <string>
#include <sstream>

#include "gk/core/IntTypes.hpp"

namespace gk {

enum LoggerColor {
	White = 0,
	Red = 31,
	Blue = 36
};

class Logger {
	public:
		Logger(const char *file = nullptr, int line = -1) : m_file(file), m_line(line) {}
		~Logger() { print(); }

		void setColor(LoggerColor color) { m_color = color; }
		void setBold(bool isBold) { m_isBold = isBold; }

		void addSpace() { if (!m_stream.str().empty()) m_stream << " "; }

		template<typename T>
		Logger &operator<<(const T &object) { m_stream << object; return *this; }

		static std::string textColor(u8 color = LoggerColor::White, bool bold = false) {
#ifdef DEBUG_COLOR
			return std::string("\33[0;") + ((color < 10) ? "0" : "") + std::to_string(color) + ";0" + ((bold) ? "1" : "0") + "m";
#else
			(void)color;
			(void)bold;
			return "";
#endif
		}

	private:
		void print() {
			std::cout << m_file << ":" << m_line << ": "
				<< textColor(m_color) << m_stream.str() << textColor() << std::endl;
		}

		const char *m_file = nullptr;
		int m_line = -1;

		LoggerColor m_color = LoggerColor::White;
		bool m_isBold = false;

		std::stringstream m_stream;
};

} // namespace gk

#endif // GK_LOGGER_HPP_
