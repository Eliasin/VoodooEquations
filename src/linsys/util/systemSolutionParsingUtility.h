/*
* Created by Mark on 5/19/2017.
*/

#pragma once

#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/rational.hpp>

#include "linsys/systemparts.h"

namespace linsys {
    namespace {
        namespace qi = boost::spirit::qi;

        qi::rule<std::string::const_iterator, boost::rational<int>()> fraction = qi::int_
                >> ('/' >> qi::int_ | qi::attr(1));
        qi::rule<std::string::const_iterator, linsys::LinearSystemSolution()> systemSolution = qi::char_('(')
                >> fraction >> qi::char_(',') >> fraction
                >> qi::char_(')');
    }

    template <typename Iterator>
    const bool parseLinearSystemSolutionReturningResult(
            LinearSystemSolution& solution, const Iterator&& begin, const Iterator&& end) {
        const bool parseStatus = ::boost::spirit::qi::phrase_parse(begin, end, systemSolution, ::boost::spirit::ascii::space, solution);

        return parseStatus;
    }
}