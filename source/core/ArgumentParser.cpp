/*
 * =====================================================================================
 *
 *  GameKit
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include "gk/core/ArgumentParser.hpp"
#include "gk/core/Debug.hpp"

namespace gk {

ArgumentParser::ArgumentParser(int argc, char **argv) {
	for (int i = 0 ; i < argc ; ++i) {
		m_argv.emplace_back(argv[i]);
	}

	addArgument("help", {"", "--help"});
}

void ArgumentParser::parse() {
	for (std::size_t i = 0 ; i < m_argv.size() ; ++i) {
		for (auto &it : m_arguments) {
			if (m_argv[i] == it.second.longName || (!it.second.shortName.empty() && m_argv[i] == it.second.shortName)) {
				it.second.isFound = true;
				if (it.second.hasParameter && i + 1 < m_argv.size())
					it.second.parameter = m_argv[i + 1];
			}
		}
	}

	if (getArgument("help").isFound)
		printHelp();
}

void ArgumentParser::printHelp() {
	std::cout << "Available options:" << std::endl;
	for (auto &it : m_arguments)
		std::cout << "  " << it.second.longName << "/" << it.second.shortName << std::endl;
}

void ArgumentParser::debug() {
	DEBUG("========== ARGS ==========");
	for (auto &it : m_arguments)
		DEBUG(it.second.longName, "/", it.second.shortName, "=", it.second.isFound);
	DEBUG("==========================");
}

} // namespace gk

