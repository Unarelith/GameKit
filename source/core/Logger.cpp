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
#include "gk/core/Logger.hpp"

namespace gk {

bool Logger::isEnabled = true;
bool Logger::printFileAndLine = false;
bool Logger::printWithColor = false;

std::string Logger::textColor(LoggerColor color, bool bold) {
	return (!printWithColor) ? ""
		: std::string("\33[0;") + ((u8(color) < 10) ? "0" : "") + std::to_string(u8(color)) + ";0" + ((bold) ? "1" : "0") + "m";
}

void Logger::print() {
	if (!isEnabled) return;

	std::cout << m_color;

	char levels[4] = {'D', 'I', 'W', 'E'};
	std::cout << "[" + getCurrentTime("%H:%M:%S") + "] [" << levels[m_level] << "] ";

	if (printFileAndLine)
		std::cout << m_file << ":" << m_line << ": ";

	std::cout << m_stream.str() << LoggerColor::White << std::endl;
}

} // namespace gk

std::ostream &operator<<(std::ostream &stream, gk::LoggerColor color) {
	return stream << gk::Logger::textColor(color);
}

