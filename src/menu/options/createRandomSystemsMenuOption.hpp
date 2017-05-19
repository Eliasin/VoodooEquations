#pragma once

#include <vector>
#include <iostream>

#include "menu/menu.h"
#include "linsys/linearsystem.h"
#include "linsys/session.h"

namespace menu {

	class CreateRandomSystemsMenuChoice : public MenuChoice {
		linsys::SessionEnvironment& session;
	public:
        explicit CreateRandomSystemsMenuChoice(linsys::SessionEnvironment& session)
                : MenuChoice("Create Random Systems"), session(session) {}

		void select() const override;
	};

}
