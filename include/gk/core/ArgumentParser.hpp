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
#ifndef GK_ARGUMENTPARSER_HPP_
#define GK_ARGUMENTPARSER_HPP_

#include <string>
#include <unordered_map>
#include <vector>

namespace gk {

struct Argument {
	std::string shortName;
	std::string longName;
	bool hasParameter = false;
	std::string parameter = "";
	bool isFound = false;
};

class ArgumentParser {
	public:
		ArgumentParser(int argc, char **argv);

		void parse();

		void printHelp();
		void debug();

		void addArgument(const std::string &name, const Argument &argument) { m_arguments.emplace(name, argument); }
		const Argument &getArgument(const std::string &name) { return m_arguments.at(name); }

	private:
		std::vector<std::string> m_argv;
		std::unordered_map<std::string, Argument> m_arguments;
};

} // namespace gk

#endif // GK_ARGUMENTPARSER_HPP_
