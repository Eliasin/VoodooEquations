#pragma once

#include <iostream>

#include "menu.h"
#include "linsys/linearsystem.h"

namespace menu {

	class DisplayMenuChoice : public MenuChoice {
		const std::vector<linsys::LinearSystem>& linearSystems;
	public:
		DisplayMenuChoice(std::string&& name, const std::vector<linsys::LinearSystem>& linearSystems) : MenuChoice(std::move(name)), linearSystems(linearSystems) {}
		void select() override;
	};

}
