#pragma once

#include <iostream>
#include <string>
#include <random>

#include <boost/spirit/include/qi.hpp>
#include <boost/rational.hpp>

#include "menu.h"

#include "linsys/session.h"
#include "linsys/parser.h"
#include "linsys/systemparts.h"

namespace menu {

	class ChallengeUserMenuChoice : public MenuChoice {
	public:
		ChallengeUserMenuChoice(const linsys::SessionEnvironment& session)
			: MenuChoice("Challenge User"), session(session), rng(std::random_device()())
		{
			namespace qi = boost::spirit::qi;

			fraction = qi::int_	>> ('/' >> qi::int_ | qi::attr(1));

			systemSolution = qi::char_('(') >> fraction >> qi::char_(',') >> fraction >> qi::char_(')');
		}

		void select() override {
			if (!session.size()) {
				std::cout << "No systems, please add some." << std::endl;
				return;
			}

			std::uniform_int_distribution<linsys::SessionEnvironment::IndexType> randomSystemIndexGenerator{0, session.size() - 1};

			const linsys::LinearSystem& system = session.at(randomSystemIndexGenerator(rng));

			std::cout << system.toString() << std::endl;

			std::string input;
			linsys::LinearSystemSolution equation;
			for (;;) {
				std::cout << "Take a shot at finding the solution in the form '(x, y)' or type 'none' for no solution: ";
				std::cin >> input;
				if (input == "none" && !system.solution) {
					std::cout << "You got the correct solution! Congratulations!" << std::endl;
				} else {
					std::cout << "You got the wrong solution! There was none!" << std::endl;
					waitForEnterKey();
					return;
				}
				const bool wasParseSuccess = boost::spirit::qi::phrase_parse(std::cbegin(input), std::cend(input), systemSolution,
															   boost::spirit::ascii::space, equation);
				if (wasParseSuccess) {
					break;
				} else {
					std::cout << "Malformed solution! Must be in the form (x, y)" << std::endl;
					waitForEnterKey();
					clearScreen();
				}
			}
			if (system.solution && equation.x == system.solution->x && equation.y == system.solution->y) {
				std::cout << "You got the correct solution! Congratulations!" << std::endl;
			} else {
				std::cout << "You got the wrong solution! The correct solution was " << system.solution->toString() << std::endl;
			}
			waitForEnterKey();
		}

	private:
		const linsys::SessionEnvironment& session;
		boost::spirit::qi::rule<std::string::const_iterator, boost::rational<int>()> fraction;
		boost::spirit::qi::rule<std::string::const_iterator, linsys::LinearSystemSolution()> systemSolution;
		std::mt19937 rng;
	};

}
