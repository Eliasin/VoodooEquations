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

int main() {
	linsys::SessionEnvironment session;

	const menu::Menu menu {
		new menu::DisplayMenuChoice(session),
			new menu::CreateRandomSystemsMenuChoice(session),
			new menu::ChallengeUserMenuChoice(session),
			new menu::QuitMenuChoice()
	};

	menu.forEach([&](const menu::Menu::IndexType i, const menu::MenuChoice& choice){
			std::cout << i << ": " << choice.getName() << std::endl;
			});
	return 0;
}
