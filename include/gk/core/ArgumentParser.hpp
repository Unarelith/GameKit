/*
 * =====================================================================================
 *
 *       Filename:  ArgumentParser.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2019 23:14:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
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
