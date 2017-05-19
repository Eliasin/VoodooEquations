#pragma once

#include "menu.h"
#include "linsys/session.h"

namespace menu {

	class GetSystemFromUserMenuChoice : public MenuChoice {
		linsys::SessionEnvironment& session;
	public:
		GetSystemFromUserMenuChoice(linsys::SessionEnvironment& session) : MenuChoice("Get Linear System From User"), session(session) {}
		void select() override;
	};

}
