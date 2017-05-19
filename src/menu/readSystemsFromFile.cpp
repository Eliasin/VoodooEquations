#include "readSystemsFromFile.hpp"

#include <fstream>
#include <iostream>

#include "linsys/parser.h"
#include "linsys/systemParsingUtility.hpp"

namespace menu {

	void ReadSystemsFromFileMenuChoice::select() {
		std::ifstream file;
		while (true) {
			std::string input;

			std::cout << "Please enter the name of the file: " << std::endl;
			std::cin >> input;
			file.open(input);

			if (file) break;

			std::cout << "File could not be found, please try again." << std::endl;
			waitForEnterKey();
			clearScreen();
		}

		linsys::LinearEquationParser<std::string::const_iterator> linearEquationParser;
		linsys::readLinearEquationsFromStream(std::move(file), session, linearEquationParser);
		std::cout << "There are now " << session.size() << " systems." << std::endl;
	}

}
