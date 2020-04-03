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
#include "gk/core/Utils.hpp"

namespace gk {

enum class LoggerColor : u8 {
	White = 0,
	Red = 31,
	Blue = 36
};

enum LogLevel : u8 {
	Debug   = 0,
	Info    = 1,
	Warning = 2,
	Error   = 3
};

class Logger {
	public:
		Logger(LogLevel level = LogLevel::Debug, const char *file = nullptr, int line = -1)
			: m_level(level), m_file(file), m_line(line) {}
		~Logger() { print(); }

		void setColor(LoggerColor color) { m_color = color; }
		void setBold(bool isBold) { m_isBold = isBold; }

		void addSpace() { if (!m_stream.str().empty()) m_stream << " "; }

		template<typename T>
		Logger &operator<<(const T &object) { addSpace(); m_stream << object; return *this; }
		Logger &operator<<(const char *str) { addSpace(); m_stream << str; return *this; }
		Logger &operator<<(const std::string &str) { addSpace(); m_stream << "\"" << str << "\""; return *this; }

		static std::string textColor(LoggerColor color = LoggerColor::White, bool bold = false);

		static bool isEnabled;
		static bool printFileAndLine;
		static bool printWithColor;

	private:
		void print();

		LogLevel m_level;

		const char *m_file = nullptr;
		int m_line = -1;

		LoggerColor m_color = LoggerColor::White;
		bool m_isBold = false;

		std::stringstream m_stream;
};

} // namespace gk

std::ostream &operator<<(std::ostream &stream, gk::LoggerColor color);

#endif // GK_LOGGER_HPP_
