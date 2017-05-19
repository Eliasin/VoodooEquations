#include "systemparts.h"

#include <boost/lexical_cast.hpp>

namespace linsys {

	std::string Term::toString() const noexcept {
		return "(" + boost::lexical_cast<std::string>(coefficient) + ")" + variableName;
	}

	std::string LinearSystemSolution::toString() const noexcept {
		return "(" + boost::lexical_cast<std::string>(x) + "," + boost::lexical_cast<std::string>(y) + ")";
	}

	std::string LinearEquation::toString() const noexcept {
		return firstTerm.toString() + operation + secondTerm.toString();
	}

}
