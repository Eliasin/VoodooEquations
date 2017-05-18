#pragma once

#include <iostream>
#include <string>

#include "menu.h"
#include "linsys/session.h"
#include "linsys/parser.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/rational.hpp>
#include "linsys/systemparts.h"

namespace menu {

	class GetSystemFromUserMenuChoice : public MenuChoice {
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;

		const linsys::SessionEnvironment& session;
		qi::rule<std::string::const_iterator, boost::rational<int>()> fraction;
	public:
		GetSystemFromUserMenuChoice(const linsys::SessionEnvironment& session)
			: MenuChoice("Challenge User"), session(session)
		{
			fraction = qi::int_	>> ('/' >> qi::int_ | qi::attr(1));
		}

		void select() override {
			if (!session.size()) {
				std::cout << "No systems, please add some." << std::endl;
				return;
			}

			std::mt19937 rng{std::random_device()()};
			std::uniform_int_distribution<> randomSystemIndexGenerator{0, session.size()};

			std::cout session.at(randomSystemIndexGenerator(rng)).toString() << std::endl;

			std::string input;
			std::cout << "Please enter the solution: ";
			std::cin >> input;
			linsys::LinearSystemSolution firstEquation;
			const bool firstParseResult = qi::phrase_parse(std::cbegin(input), std::cend(input), parser, ascii::space, firstEquation);
		}
	};

}
