/*
* Created by Mark on 5/16/2017.
*/

#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/include/io.hpp>

#include "systemparts.h"

BOOST_FUSION_ADAPT_TPL_ADT(
        (IntType),
        (boost::rational) (IntType),
        (IntType, IntType, obj.numerator(), obj.assign(val, obj.denominator()))
        (IntType, IntType, obj.denominator(), obj.assign(obj.numerator(), val))
)

namespace linsys {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    template <typename Iterator>
    struct LinearEquationParser : qi::grammar<Iterator, linsys::LinearEquation(), ascii::space_type> {
        LinearEquationParser() : LinearEquationParser::base_type(equation) {
            using qi::int_;
            using qi::lit;
            using qi::double_;
            using qi::lexeme;
            using ascii::char_;
            using ascii::lower;
            using qi::attr;
            using qi::eoi;

            fraction = int_
                    >> ('/' >> int_ | attr(1));

            atom = '('
                    >> fraction
                    >> ')'
                    ;

            term = atom
                    >> lower
                    ;

            equation = term
                    >> (char_('+') | char_('-'))
                    >> term
                    >> "="
                    >> fraction
                    >> eoi
                    ;
        }

        qi::rule<Iterator, boost::rational<int>()> fraction;
        qi::rule<Iterator, boost::rational<int>()> atom;
        qi::rule<Iterator, linsys::Term()> term;
        qi::rule<Iterator, linsys::LinearEquation(), ascii::space_type> equation;
    };
}