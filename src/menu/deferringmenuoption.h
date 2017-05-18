/*
* Created by Mark on 5/18/2017.
*/

#pragma once

#include "menu.h"

namespace menu {
    class DeferringMenuChoice : public MenuChoice {
    public:
        explicit DeferringMenuChoice(const std::string&& name, std::function<void ()> runnable)
                : MenuChoice(std::move(name)), runnable(runnable) {}

        void select() override {
            runnable();
        }

    private:
        std::function<void ()> runnable;
    };
}