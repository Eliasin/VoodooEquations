#include <fstream>
#include <experimental/optional>

#include <boost/spirit/include/qi.hpp>
#include <boost/rational.hpp>

#include "linsys/systemparts.h"
#include "linsys/linearsystem.h"
#include "linsys/session.h"
#include "linsys/parser.h"

#include "menu/menu.h"
#include "menu/challengeUserMenuOption.hpp"
#include "menu/createRandomSystemsMenuOption.hpp"
#include "menu/displayMenuOption.hpp"
#include "menu/quitMenuOption.hpp"
#include "menu/readSystemsFromFile.hpp"
#include "menu/getSystemFromUserMenuOption.hpp"

int main() {
	linsys::SessionEnvironment session;

	const menu::Menu menu {
            new menu::ReadSystemsFromFileMenuChoice(session),
            new menu::CreateRandomSystemsMenuChoice(session),
            new menu::GetSystemFromUserMenuChoice(session),
			new menu::ChallengeUserMenuChoice(session),
            new menu::DisplayMenuChoice(session),
			new menu::QuitMenuChoice()
	};

    for (;;) {
        menu::clearScreen();
        menu.forEach([&](const menu::Menu::IndexType i, const menu::MenuChoice &choice) {
            std::cout << i << ": " << choice.getName() << std::endl;
        });

        std::cout << "Enter an option: ";
        int input;
        if (!(std::cin >> input)) {
            std::cout << "Illegal input: must be a number between 1 and " << menu.size() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            menu::waitForEnterKey();
        } else {
            if (input >= 1 && input <= menu.size()) {
                menu.at(input).select();
            } else {
                std::cout << "Illegal option '" << input << "': Must be between 1 and " << menu.size() << std::endl;
            }
        }
        menu::waitForEnterKey();
    }
	return 0;
}
