#include <fstream>
#include <string>
#include <experimental/optional>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/qi_char_class.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/rational.hpp>

namespace linsys {
    struct Term {
        boost::rational<int> coefficient;
        char variableName;
    };

    struct LinearEquation {
        Term firstTerm;
        char operation;
        Term secondTerm;
        boost::rational<int> answer;
    };

    struct LinearSystemSolution {
        boost::rational<int> x, y;
    };
}

BOOST_FUSION_ADAPT_TPL_ADT(
        (IntType),
        (boost::rational) (IntType),
        (IntType, IntType, obj.numerator(), obj.assign(val, obj.denominator()))
        (IntType, IntType, obj.denominator(), obj.assign(obj.numerator(), val)))

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

            atom = '('
                    >> int_
                    >> ('/' >> int_ | attr(1))
                    >> ')'
                    ;

            term = atom
                    >> lower
                    ;

            equation = term
                    >> (char_('+') | char_('-'))
                    >> term
                    >> "="
                    >> atom
                    >> eoi
                    ;
        }

        qi::rule<Iterator, boost::rational<int>()> atom;
        qi::rule<Iterator, linsys::Term()> term;
        qi::rule<Iterator, linsys::LinearEquation(), ascii::space_type> equation;
    };
}

//Cramer's rule, boys.
const static std::experimental::optional<linsys::LinearSystemSolution>
findSolution(const linsys::LinearEquation& first, const linsys::LinearEquation& second) {
    const boost::rational<int> determinant = first.firstTerm.coefficient * second.secondTerm.coefficient - first.secondTerm.coefficient * second.firstTerm.coefficient;
    if (determinant != 0) {
        const boost::rational<int> x = (first.answer*second.secondTerm.coefficient - first.secondTerm.coefficient * second.answer) / determinant;
        const boost::rational<int> y = (first.firstTerm.coefficient * second.answer - first.answer * second.firstTerm.coefficient) / determinant;
        return {linsys::LinearSystemSolution{{x}, {y}}};
    } else {
        return {};
    }
}

static void normalizeLinearEquation(linsys::LinearEquation& equation) {
    if (equation.operation == '-') {
        equation.secondTerm.coefficient = -equation.secondTerm.coefficient;
        equation.operation = '+';
    }
}

const static bool validateAndNormalizeLinearEquations(linsys::LinearEquation& firstEquation, linsys::LinearEquation& secondEquation) {
    normalizeLinearEquation(firstEquation);
    normalizeLinearEquation(secondEquation);

    if (firstEquation.firstTerm.variableName != secondEquation.firstTerm.variableName) return false;
    else if (firstEquation.secondTerm.variableName != secondEquation.secondTerm.variableName) return false;
    else if (firstEquation.firstTerm.coefficient.numerator() == 0 && firstEquation.secondTerm.coefficient.numerator() == 0) return 0;
    else if (secondEquation.firstTerm.coefficient.numerator() == 0 && secondEquation.secondTerm.coefficient.numerator() == 0) return 0;
    else return 1;
}

template <typename Iterator, typename Parser>
const static bool parseLinearEquationReturningResult(linsys::LinearEquation& equation, const Parser& parser, const Iterator&& begin, const Iterator&& end) {
    using namespace boost::spirit;

    const bool parseStatus = qi::phrase_parse(begin, end, parser, ascii::space, equation);

    return parseStatus;
}

int main() {
    typedef std::string::const_iterator iter_type;
    typedef linsys::LinearEquationParser<iter_type> parser_type;

    const parser_type parser;

    std::ifstream input {"input.txt"};

    while (input) {
        std::string firstEquationText;
        if (!std::getline(input, firstEquationText)) {
            std::cout << "Encountered end of stream! Exiting." << std::endl;
            break;
        }

        std::string secondEquationText;
        if (!std::getline(input, secondEquationText)) {
            std::cout << "Encountered end of stream! Exiting." << std::endl;
            break;
        }

        linsys::LinearEquation firstEquation;
        const bool firstEqStatus = parseLinearEquationReturningResult(firstEquation, parser, std::cbegin(firstEquationText), std::cend(firstEquationText));

        if (!firstEqStatus) {
            std::cout << "Extraneous input found while parsing linear equation! Exiting." << std::endl;
            break;
        }

        linsys::LinearEquation secondEquation;
        const bool secondEqStatus = parseLinearEquationReturningResult(secondEquation, parser, std::cbegin(secondEquationText), std::cend(secondEquationText));

        if (!secondEqStatus) {
            std::cout << "Failed to extraneous input found while parsing linear equation! Exiting." << std::endl;
            break;
        }

        if (!validateAndNormalizeLinearEquations(firstEquation, secondEquation)) {
            std::cout << "Found malformed linear equation! Exiting." << std::endl;
            break;
        }

        if (auto solution = findSolution(firstEquation, secondEquation)) {
            std::cout << "Found solution to linear system: "
                      << firstEquation.firstTerm.variableName << " = " << solution->x << ", "
                      << firstEquation.secondTerm.variableName << " = " << solution->y << std::endl;
        } else {
            std::cout << "No solution found to linear system "
                    << firstEquationText << ", " << secondEquationText << "." << std::endl;
        }

        std::string supposedEmptyText;
        if (!std::getline(input, supposedEmptyText)) {
            std::cout << "Finished reading linear systems! Exiting." << std::endl;
            break;
        } else if (supposedEmptyText.size() != 0 && supposedEmptyText.at(0) != 13) {
//            Careful for the carriage return on Windows. This might be 1 not 0 if reading a windows file
            std::cout << "Encountered malformed input between linear systems! Exiting." << std::endl;
            break;
        }
    }

    return 0;
}