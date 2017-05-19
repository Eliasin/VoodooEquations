#pragma once

#include "menu.h"

#include "linsys/session.h"

namespace menu {

	class ReadSystemsFromFileMenuChoice : public MenuChoice {
		linsys::SessionEnvironment& session;
	public:
		void select() override;
	}

}
