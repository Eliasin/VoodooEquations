/*
* Created by Mark on 5/16/2017.
*/

#include "session.h"

namespace linsys {
    void SessionEnvironment::addSystem(const LinearSystem&& linearSystem) {
        linearSystems.emplace_back(linearSystem);
    }

    unsigned long SessionEnvironment::size() {
        return linearSystems.size();
    }

    void SessionEnvironment::forEach(std::function<void (LinearSystem&)> consumer) {
        for (LinearSystem& sys : linearSystems) {
            consumer(sys);
        }
    }
}