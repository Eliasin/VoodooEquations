#include "challengeUserMenuOption.hpp"

namespace menu {

	void challengeUserToSolveSystem(const linsys::LinearSystem& system) {
		std::cout << system.firstEquation.toString() << "\n" << system.secondEquation.toString() << std::endl;

		std::string input;
		linsys::LinearSystemSolution equation;
		for (;;) {
			std::cout << "Take a shot at finding the solution in the form '(x, y)' or type 'none' for no solution: ";
			std::cin >> input;
			if (input == "none") {
				if (!system.solution) {
					std::cout << "You got the correct solution! Congratulations!" << std::endl;
				} else {
					std::cout << "You got the wrong solution! There was none!" << std::endl;
					waitForEnterKey();
					return;
				}
			}

			const bool wasParseSuccess = linsys::parseLinearSystemSolutionReturningResult(equation, std::cbegin(input), std::cend(input));
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

}
