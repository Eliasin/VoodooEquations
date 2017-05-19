#include "getSystemFromUserMenuOption.hpp"

#include <iostream>
#include <sstream>

#include "linsys/parser.h"
#include "linsys/systemParsingUtility.hpp"
#include "challengeUserMenuOption.hpp"

namespace menu {

	void GetSystemFromUserMenuChoice::select() const {
		std::string systemString;

		while (true) {
			std::string input;

			std::cout << "Please enter the first linear equation: ";
			std::getline(std::cin, input);
			systemString += input;
			systemString += '\n';

			std::cout << "Please enter the second linear equation: ";
			std::getline(std::cin, input);
			systemString += input;

			std::stringstream ss(systemString);
			unsigned long initialSize = session.size();

			linsys::LinearEquationParser<std::string::const_iterator> linearEquationParser;
			readLinearEquationsFromStream(std::move(ss), session, linearEquationParser);

			if (initialSize == session.size()) {
				systemString.clear();
				std::cout << "Invalid linear system!" << std::endl;
				waitForEnterKey();
				clearScreen();
			}
			else {
				std::cout << "System added!" << std::endl;
				linsys::LinearSystem system = session.at(session.size() - 1);
				challengeUserToSolveSystem(system);

				break;
			}
		}
	}

}
