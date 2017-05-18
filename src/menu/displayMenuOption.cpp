#include "displayMenuOption.hpp"

#include <iostream>

namespace menu {

	void DisplayMenuChoice::select() {
		session.forEach([&] (const linsys::LinearSystem& system)->void { std::cout << system.toString() << std::endl;  });
	}

}
