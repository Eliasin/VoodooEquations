#include "quitMenuOption.hpp"

#include <iostream>

namespace menu {

	void QuitMenuChoice::select() {
		std::cout << "Goodbye! :3" << std::endl;
		std::exit(0);
	}

}
