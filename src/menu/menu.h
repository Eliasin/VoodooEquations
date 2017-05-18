/*
 * Created by Mark on 5/17/2017.
 */

#pragma once

#include <string>
#include <vector>
#include <functional>
#include <initializer_list>
#include <iostream>

namespace menu {

	static inline void waitForEnterKey() {
		#if defined(_WIN32)
		system("PAUSE");
		#elif defined (__CYGWIN__) || defined(__linux__)
		system("echo Please press the enter key to continue...");
		system("read");
		#endif
	}

    static inline void clearScreen() {
		#if defined(_WIN32)
		system("CLS");
		#elif defined (__CYGWIN__) || defined(__linux__)
		system("clear");
		#endif
	}

	class MenuChoice {
	public:
		explicit MenuChoice(const std::string &&name) : name(name) {}

		virtual void select() = 0;

		const std::string& getName() const noexcept {
			return name;
		}

	private:
		const std::string name;
	};

	class Menu {
	public:
		typedef std::vector<const MenuChoice*>::size_type IndexType;

		Menu(const std::initializer_list<const MenuChoice*>&& menuChoices) : menuChoices(menuChoices) {}

		void forEach(std::function<void(const IndexType, const MenuChoice&)> consumer) const noexcept;

		const IndexType size() const noexcept;

		const MenuChoice& at(IndexType index) const noexcept;

	private:
		const std::vector<const MenuChoice*> menuChoices;
	};

}
