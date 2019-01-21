/*
 * =====================================================================================
 *
 *       Filename:  ArgumentParser.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2019 23:18:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "gk/core/ArgumentParser.hpp"
#include "gk/core/Debug.hpp"

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

