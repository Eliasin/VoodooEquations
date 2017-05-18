#pragma once

#include <iostream>

#include "menu.h"
#include "linsys/linearsystem.h"
#include "linsys/session.h"

namespace menu {

	class DisplayMenuChoice : public MenuChoice {
		const linsys::SessionEnvironment& session;
	public:
		DisplayMenuChoice(std::string&& name, const linsys::SessionEnvironment& session) : MenuChoice(std::move(name)), session(session) {}
		void select() override;
	};

}
