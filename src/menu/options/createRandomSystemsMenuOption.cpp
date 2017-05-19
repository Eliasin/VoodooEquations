#include "createRandomSystemsMenuOption.hpp"

#include <random>

namespace menu {

	const static boost::rational<int> createRandomFraction(std::function<int()> numberGenerator) {
		const int denominator = numberGenerator();
		return boost::rational<int>{numberGenerator(), denominator != 0 ? denominator : 1};
	}

	template <typename RandomNumberGenerator>
		static linsys::LinearEquation createLinearEquationWithRandomCoefficients(const char firstVarName, const char secondVarName, RandomNumberGenerator& rng) {
			const auto gen = [&, dist = std::uniform_int_distribution<int>{-100, 100}]() mutable -> int { return dist(rng); };
			std::uniform_int_distribution<int> operationGen{0, 1};
			const linsys::Term firstTerm{createRandomFraction(gen), firstVarName};
			const linsys::Term secondTerm{createRandomFraction(gen), secondVarName};
			return {firstTerm, (operationGen(rng) ? '+' : '-'), secondTerm, createRandomFraction(gen)};
		}

	static void emplaceRandomLinearSystem(std::function<void (const linsys::LinearSystem&)> consumer) {
		std::mt19937 rng{std::random_device()()};
		std::uniform_int_distribution<char> variableNameGen{'a', 'z'};
		const char firstVarName = variableNameGen(rng);
		const char secondVarName = variableNameGen(rng);

		consumer(linsys::LinearSystem::of(createLinearEquationWithRandomCoefficients(firstVarName, secondVarName, rng),
					createLinearEquationWithRandomCoefficients(firstVarName, secondVarName, rng)));
	}

	static void emplaceNRandomLinearSystems(const unsigned int count, std::function<void (const linsys::LinearSystem&)> consumer) {
		for (int i = 0; i < count; i++) {
			emplaceRandomLinearSystem(consumer);
		}
	}

	void CreateRandomSystemsMenuChoice::select() const {
		unsigned int n;

		while (true) {
			std::cout << "Please enter the number of random systems to be created: ";
			if (!(std::cin >> n)) {
				std::cout << "Illegal input! Input must be a number!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else {
				break;
			}
		}

		emplaceNRandomLinearSystems(n, [&] (const linsys::LinearSystem& l)->void { session.addSystem(std::move(l)); });
	}

}
