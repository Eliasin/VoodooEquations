#pragma once

#include "menu/menu.h"

#include "linsys/session.h"

namespace menu {

	class ReadSystemsFromFileMenuChoice : public MenuChoice {
		linsys::SessionEnvironment& session;
	public:
		ReadSystemsFromFileMenuChoice(linsys::SessionEnvironment& session) : MenuChoice("Read Linear Systems From File"), session(session) {}
		void select() const override;
	};

}
