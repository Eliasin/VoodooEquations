#pragma once

#include <iostream>

#include "menu.h"
#include "linsys/linearsystem.h"

namespace menu {

	class DisplayMenuChoice : public MenuChoice {
		const std::vector<linsys::LinearSystem>& linearSystems;
		std::ostream& out;
	public:
		DisplayMenuChoice(std::string&& name, const std::vector<linsys::LinearSystem>& linearSystems, std::ostream& out) : MenuChoice(std::move(name)), linearSystems(linearSystems), out(out) {}
		void select() override;
	};

}
