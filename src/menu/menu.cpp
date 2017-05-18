/*
 * Created by Mark on 5/17/2017.
 */

#include "menu.h"

namespace menu {

	void Menu::forEach(std::function<void(const Menu::IndexType, const MenuChoice&)> consumer) const noexcept {
		for (Menu::IndexType i = 0; i < menuChoices.size(); i++) {
			consumer(i + 1, *menuChoices[i]);
		}
	}

	const Menu::IndexType Menu::size() const noexcept {
		return menuChoices.size();
	}

	const MenuChoice& Menu::at(const Menu::IndexType index) const noexcept {
		return *menuChoices[index];
	}

}
