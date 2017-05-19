#pragma once

#include "menu.h"

#include "linsys/session.h"

namespace menu {

	class QuitMenuChoice : public MenuChoice {
	public:
		explicit QuitMenuChoice(linsys::SessionEnvironment& session);

		void select() const override;

    private:
        linsys::SessionEnvironment& session;
	};

}
