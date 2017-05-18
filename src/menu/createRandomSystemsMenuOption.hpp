#pragma once

#include <vector>
#include <iostream>

#include "menu.h"
#include "linsys/linearsystem.h"

namespace menu {

	class CreateRandomSystemsMenuChoice : public MenuChoice {
		std::vector<linsys::LinearSystem>& linearSystems;
	public:
		CreateRandomSystemsMenuChoice(std::string&& name, std::vector<linsys::LinearSystem>& linearSystems) : MenuChoice(std::move(name)), linearSystems(linearSystems) {}

		static const int maxCoefficient = 10000;
		static const int minCoefficient = -10000;
		void select() override;
	};

}
