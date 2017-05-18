#include "createRandomSystemsMenuOption.hpp"

#include <iostream>
#include <limits>

#include "linsys/linearsystem.h"

namespace menu {

	void CreateRandomSystemsMenuChoice::select() {
		size_t n;

		while (true) {
			std::cout << "Please enter the amount of random systems to be created: ";
			if (!(std::cin >> n)) {
				std::cout << "Illegal input! Input must be a number!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else {
				break;
			}
		}
		std::vector<linsys::LinearSystem> generatedSystems = generateRandomSystems(n);

		linearSystems.reserve(linearSystems.size() + generatedSystems.size());
		std::move(std::begin(generatedSystems), std::end(generatedSystems), std::back_inserter(linearSystems));
		generatedSystems.clear();
	}

	static char generateAlphabeticalChar() {
		rand() % 2 ? rand() % ('z' - 'a' + 1) + 'a' : rand() % ('Z' - 'A' + 1) + 'A';
	}

	static int generateBoundedNumber() {
		return rand() % (CreateRandomSystemsMenuChoice::maxCoefficient - CreateRandomSystemsMenuChoice::minCoefficient + 1) + CreateRandomSystemsMenuChoice::minCoefficient;
	}

	static boost::rational<int> generateCoefficient() {
		return { generateBoundedNumber(), generateBoundedNumber() };
	}

	static linsys::LinearEquation generateEquation() {
		char variableName1, variableName2;

		return {{}, rand() % 2 ? '+' : '-', {}, generateBoundedNumber()};
	}

	static char generateOperator() {
		return rand() % 2 ? '+' : '-';
	}

	static linsys::LinearSystem generateLinearSystem() {
		char variableName1, variableName2;
		variableName1 = generateAlphabeticalChar();
		variableName2 = variableName1;
		while (variableName2 == variableName1)
			variableName2 = generateAlphabeticalChar();

		linsys::LinearEquation equation1{{generateCoefficient(), variableName1}, generateOperator(), {generateCoefficient(), variableName2}, generateBoundedNumber()};

		if (rand() % 2) {
			char temp = variableName1;
			variableName1 = variableName2;
			variableName2 = temp;
		}

		linsys::LinearEquation equation2{{generateCoefficient(), variableName1}, generateOperator(), {generateCoefficient(), variableName2}, generateBoundedNumber()};

		return linsys::LinearSystem::of(std::move(equation1), std::move(equation2));
	}

	std::vector<linsys::LinearSystem> CreateRandomSystemsMenuChoice::generateRandomSystems(size_t n) const {
		std::vector<linsys::LinearSystem> generatedSystems;
		for (size_t i = 0; i < n; i++) {
			generatedSystems.push_back(generateLinearSystem());
		}
		return generatedSystems;
	}

}
