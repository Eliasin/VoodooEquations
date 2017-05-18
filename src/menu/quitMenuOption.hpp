#pragma once

#include "menu.h"

namespace menu {

	class QuitMenuChoice : public MenuChoice {
	public:
		QuitMenuChoice();

		void select() override;
	};

}
