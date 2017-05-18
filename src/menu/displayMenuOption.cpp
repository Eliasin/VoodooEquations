#include "displayMenuOption.hpp"

namespace menu {

	void DisplayMenuChoice::select() {
		for (const linsys::LinearSystem& linearSystem : linearSystems) {
			out << linearSystem.toString() << std::endl;
		}
	}

}
