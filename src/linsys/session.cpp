/*
 * Created by Mark on 5/16/2017.
 */

#include "session.h"

namespace linsys {
	void SessionEnvironment::addSystem(const LinearSystem&& linearSystem) {
		linearSystems.emplace_back(linearSystem);
	}

	void SessionEnvironment::clear() {
		linearSystems.clear();
	}

	unsigned long SessionEnvironment::size() {
		return linearSystems.size();
	}

	void SessionEnvironment::forEach(std::function<void (LinearSystem&)> consumer) {
		for (LinearSystem& sys : linearSystems) {
			consumer(sys);
		}
	}

	void SessionEnvironment::forEach(std::function<void (const LinearSystem&)> consumer) const {
		for (const LinearSystem& sys : linearSystems) {
			consumer(sys);
		}
	}

	const LinearSystem& SessionEnvironment::at(SessionEnvironment::IndexType i) const {
		return linearSystems.at(i);
	}
}
