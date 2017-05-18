#pragma once

#include "menu.h"
#include "linsys/linearsystem.h"
#include "linsys/session.h"

namespace menu {

	class DisplayMenuChoice : public MenuChoice {
		const linsys::SessionEnvironment& session;
	public:
		DisplayMenuChoice(const linsys::SessionEnvironment& session)
				: MenuChoice("Display Systems"), session(session) {}

		void select() override;
	};

}
