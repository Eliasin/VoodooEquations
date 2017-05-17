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
    };

    struct LinearSystemSolution {
        boost::rational<int> x, y;
    };

    struct LinearEquation {
        Term firstTerm;
        char operation;
        Term secondTerm;
        boost::rational<int> answer;
    };
}

BOOST_FUSION_ADAPT_STRUCT(
        linsys::Term,
        (boost::rational<int>, coefficient)
                (char, variableName)
)

BOOST_FUSION_ADAPT_STRUCT(
        linsys::LinearEquation,
        (linsys::Term, firstTerm)
                (char, operation)
                (linsys::Term, secondTerm)
                (boost::rational<int>, answer)
)