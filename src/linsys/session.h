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

		typedef std::vector<LinearSystem>::size_type IndexType;

		void addSystem(const LinearSystem&& linearSystem);

		void clear();

		unsigned long size() const noexcept;

		void forEach(std::function<void (LinearSystem&)> consumer);
		void forEach(std::function<void (const LinearSystem&)> consumer) const;

		const LinearSystem& at(IndexType i) const;

	private:
		std::vector<LinearSystem> linearSystems;
	};
}
