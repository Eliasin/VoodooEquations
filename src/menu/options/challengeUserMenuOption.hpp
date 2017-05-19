#pragma once

#include <iostream>
#include <string>
#include <random>

#include <boost/spirit/include/qi.hpp>
#include <boost/rational.hpp>

#include "menu/menu.h"

#include "linsys/session.h"
#include "linsys/parser.h"
#include "linsys/systemparts.h"
#include "linsys/util/systemSolutionParsingUtility.h"

namespace menu {

	void challengeUserToSolveSystem(const linsys::LinearSystem& system);

	class ChallengeUserMenuChoice : public MenuChoice {
	public:
		ChallengeUserMenuChoice(const linsys::SessionEnvironment& session)
			: MenuChoice("Challenge User"), session(session), rng(std::random_device()()) {}

		void select() const override {
			if (!session.size()) {
				std::cout << "No systems, please add some." << std::endl;
				return;
			}

			std::uniform_int_distribution<linsys::SessionEnvironment::IndexType> randomSystemIndexGenerator{0, session.size() - 1};

			const linsys::LinearSystem& system = session.at(randomSystemIndexGenerator(rng));
			challengeUserToSolveSystem(system);
		}

	private:
		const linsys::SessionEnvironment& session;
		mutable std::mt19937 rng;
	};

}
