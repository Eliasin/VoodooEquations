/*
* Created by Mark on 5/16/2017.
*/

#pragma once

#include <functional>
#include <vector>

#include "linearsystem.h"

namespace linsys {
    class SessionEnvironment {
    public:
        void addSystem(const LinearSystem&& linearSystem);

        unsigned long size();

        void forEach(std::function<void (LinearSystem&)> consumer);

    private:
        std::vector<LinearSystem> linearSystems;
    };
}