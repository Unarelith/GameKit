/*
 * =====================================================================================
 *
 *       Filename:  Application.hpp
 *
 *    Description:
 *
 *        Created:  19/03/2019 13:42:14
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <gk/core/CoreApplication.hpp>

class Application : public gk::CoreApplication {
	public:
		Application(int argc, char **argv) : gk::CoreApplication(argc, argv) {}

		void init() override;

	private:
		void onEvent(const sf::Event &event) override;
};

#endif // APPLICATION_HPP_
