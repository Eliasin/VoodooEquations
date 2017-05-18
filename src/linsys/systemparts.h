/*
 * Created by Mark on 5/16/2017.
 */

#pragma once

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/rational.hpp>

namespace linsys {
	struct Term {
		boost::rational<int> coefficient;
		char variableName;

		std::string toString() const noexcept;
	};

	struct LinearSystemSolution {
		boost::rational<int> x, y;

		std::string toString() const noexcept;
	};

	struct LinearEquation {
		Term firstTerm;
		char operation;
		Term secondTerm;
		boost::rational<int> answer;

		std::string toString() const noexcept;
	};
}

BOOST_FUSION_ADAPT_STRUCT(
		linsys::Term,
		(boost::rational<int>, coefficient)
		(char, variableName)
		)

BOOST_FUSION_ADAPT_STRUCT(
		linsys::LinearSystemSolution,
		(boost::rational<int>, x)
		(boost::rational<int>, y)
		)

BOOST_FUSION_ADAPT_STRUCT(
		linsys::LinearEquation,
		(linsys::Term, firstTerm)
		(char, operation)
		(linsys::Term, secondTerm)
		(boost::rational<int>, answer)
		)
