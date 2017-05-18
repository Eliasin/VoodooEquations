#pragma once

#include "menu.h"

namespace menu {

	class QuitMenuChoice : public MenuChoice {
	public:
		void select() override;
	};

}
