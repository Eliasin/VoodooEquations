#include "displayMenuOption.hpp"

#include <iostream>

namespace menu {

	void DisplayMenuChoice::select() {
		for (const linsys::LinearSystem& linearSystem : linearSystems) {
			std::cout << linearSystem.toString() << std::endl;
		}
	}

}
