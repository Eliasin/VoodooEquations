/*
* Created by Mark on 5/17/2017.
*/

#pragma once

#include <string>
#include <vector>
#include <functional>
#include <initializer_list>

namespace menu {

    class MenuChoice {
    public:
        explicit MenuChoice(const std::string &&name) : name(name) {}

        virtual void select() = 0;

        const std::string &getName() noexcept {
            return name;
        }

    private:
        const std::string name;
    };

    class Menu {
    public:
        typedef std::vector<const MenuChoice*>::size_type IndexType;

        Menu(const std::initializer_list<const MenuChoice*>&& menuChoices) : menuChoices(menuChoices) {}

        void forEach(const std::function<void(const IndexType, const MenuChoice&)> &consumer) const noexcept;

        const IndexType size() const noexcept;

        const MenuChoice& at(const IndexType index) const noexcept;

    private:
        const std::vector<const MenuChoice*> menuChoices;
    };

}