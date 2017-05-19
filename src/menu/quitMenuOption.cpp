#include "quitMenuOption.hpp"

#include <iostream>
#include <fstream>

namespace menu {

	void QuitMenuChoice::select() const {
		std::cout << "Goodbye! System solutions have been saved to system_solutions.txt :3" << std::endl;
		std::ofstream outputFile{"system_solutions.txt"};
		outputFile.clear()
		session.forEach([&](const linsys::LinearSystem& system) { outputFile << system.toString() << std::endl; });
		std::exit(0);
	}

	QuitMenuChoice::QuitMenuChoice(linsys::SessionEnvironment& session) : MenuChoice("Quit"), session(session) {}

}
