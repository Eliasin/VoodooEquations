#include "quitMenuOption.hpp"

#include <iostream>

namespace menu {

	void QuitMenuChoice::select() const {
		std::cout << "Goodbye! :3" << std::endl;
		std::exit(0);
	}

	QuitMenuChoice::QuitMenuChoice() : MenuChoice("Quit") {}

}
