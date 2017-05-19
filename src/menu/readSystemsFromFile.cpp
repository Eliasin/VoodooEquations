#include "readSystemsFromFile.hpp"

#include <fstream>
#include <iostream>

#include "linsys/parser.h"
#include "linsys/systemParsingUtility.hpp"

namespace menu {

	void ReadSystemsFromFileMenuChoice::select() const {
		std::ifstream file;
		while (true) {
			std::string input;

			std::cout << "Please enter the name of the file: ";
			std::cin >> input;
			file.open(input);

			if (file) break;

			std::cout << "File could not be found, please try again." << std::endl;
			waitForEnterKey();
			clearScreen();
		}

		session.clear();
		linsys::LinearEquationParser<std::string::const_iterator> linearEquationParser;
		linsys::readLinearEquationsFromStream(std::move(file), session, linearEquationParser);
		std::cout << "Read " << session.size() << " systems from file." << std::endl;
	}

}
