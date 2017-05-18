#pragma once

#include <vector>
#include <iostream>

#include "menu.h"
#include "linsys/linearsystem.h"
#include "linsys/session.h"

namespace menu {

	class CreateRandomSystemsMenuChoice : public MenuChoice {
		linsys::SessionEnvironment& session;
	public:
		CreateRandomSystemsMenuChoice(std::string&& name, linsys::SessionEnvironment& session) : MenuChoice(std::move(name)), session(session) {}

		static const int maxCoefficient = 10000;
		static const int minCoefficient = -10000;
		void select() override;
	};

}
