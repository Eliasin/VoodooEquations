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

    struct LinearSystemSolution {
        boost::rational<int> x, y;
    };

    struct LinearEquation {
        Term firstTerm;
        char operation;
        Term secondTerm;
        boost::rational<int> answer;
    };

    struct LinearSystem {
    private:
        LinearSystem(const LinearEquation firstEquation, const LinearEquation secondEquation, const std::experimental::optional<LinearSystemSolution> solution)
                : firstEquation(firstEquation), secondEquation(secondEquation), solution(solution) {};

        const static std::experimental::optional<linsys::LinearSystemSolution>
        findSolution(const linsys::LinearEquation& first, const linsys::LinearEquation& second) {
            const boost::rational<int> determinant = first.firstTerm.coefficient * second.secondTerm.coefficient - first.secondTerm.coefficient * second.firstTerm.coefficient;
            if (determinant != 0) {
                const boost::rational<int> x = (first.answer*second.secondTerm.coefficient - first.secondTerm.coefficient * second.answer) / determinant;
                const boost::rational<int> y = (first.firstTerm.coefficient * second.answer - first.answer * second.firstTerm.coefficient) / determinant;
                return {LinearSystemSolution{{x}, {y}}};
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
            if (firstEquation.firstTerm.variableName != secondEquation.firstTerm.variableName) {
                if (firstEquation.secondTerm.variableName == secondEquation.firstTerm.variableName) {
                    std::swap(secondEquation.firstTerm, secondEquation.secondTerm);
                } else {
                    return false;
                }
            }
            else if (firstEquation.secondTerm.variableName != secondEquation.secondTerm.variableName) return false;
            else if (firstEquation.firstTerm.coefficient.numerator() == 0 && firstEquation.secondTerm.coefficient.numerator() == 0) return 0;
            else if (secondEquation.firstTerm.coefficient.numerator() == 0 && secondEquation.secondTerm.coefficient.numerator() == 0) return 0;

            normalizeLinearEquation(firstEquation);
            normalizeLinearEquation(secondEquation);

            return 1;
        }
    public:
        static LinearSystem of(LinearEquation&& firstEquation, LinearEquation&& secondEquation) {
            if (!validateAndNormalizeLinearEquations(firstEquation, secondEquation)) {
                throw "Invalid linear equations!";
            }
            return {firstEquation, secondEquation, findSolution(firstEquation, secondEquation)};
        }

        const LinearEquation firstEquation, secondEquation;
        const std::experimental::optional<LinearSystemSolution> solution;
    };

    class SessionEnvironment {
    public:
        void addSystem(const LinearSystem&& linearSystem) {
            linearSystems.emplace_back(linearSystem);
        }

        unsigned long size() {
            return linearSystems.size();
        }

        void forEach(std::function<void (LinearSystem&)> consumer) {
            for (LinearSystem& sys : linearSystems) {
                consumer(sys);
            }
        }

    private:
        std::vector<LinearSystem> linearSystems;
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

template <typename Iterator, typename Parser>
const static bool parseLinearEquationReturningResult(linsys::LinearEquation& equation, const Parser& parser, const Iterator&& begin, const Iterator&& end) {
    using namespace boost::spirit;

    const bool parseStatus = qi::phrase_parse(begin, end, parser, ascii::space, equation);

    return parseStatus;
}

static void skipUntilNextLinearEquation(std::istream& inputStream) {
    std::string line;
    for (; std::getline(inputStream, line);) {
        if (line.size() == 0 || line.at(0) == 13) break;
    }
}

template <typename Parser>
void readLinearEquationsFromStream(std::istream&& input, linsys::SessionEnvironment& session, const Parser& parser) {
    while (input) {
        std::string firstEquationText;
        if (!std::getline(input, firstEquationText)) {
            skipUntilNextLinearEquation(input);
            continue;
        }

        std::string secondEquationText;
        if (!std::getline(input, secondEquationText)) {
            skipUntilNextLinearEquation(input);
            continue;
        }

        linsys::LinearEquation firstEquation;
        const bool firstEqStatus = parseLinearEquationReturningResult(firstEquation, parser, std::cbegin(firstEquationText), std::cend(firstEquationText));

        if (!firstEqStatus) {
            skipUntilNextLinearEquation(input);
            continue;
        }

        linsys::LinearEquation secondEquation;
        const bool secondEqStatus = parseLinearEquationReturningResult(secondEquation, parser, std::cbegin(secondEquationText), std::cend(secondEquationText));

        if (!secondEqStatus) {
            skipUntilNextLinearEquation(input);
            continue;
        }

        try {
            const linsys::LinearSystem sys = linsys::LinearSystem::of(std::move(firstEquation), std::move(secondEquation));
            session.addSystem(std::move(sys));
        } catch (...) {}

        std::string supposedEmptyText;
        if (!std::getline(input, supposedEmptyText)) {
            break;
        } else if (supposedEmptyText.size() != 0 && supposedEmptyText.at(0) != 13) {
//            Careful for the carriage return on Windows. This might be 1 not 0 if reading a windows file
            break;
        }
    }
}

int main() {
    typedef std::string::const_iterator iter_type;
    typedef linsys::LinearEquationParser<iter_type> parser_type;

    linsys::SessionEnvironment session;
    const parser_type parser;

    readLinearEquationsFromStream(std::ifstream{"input.txt"}, session, parser);
    session.forEach([](linsys::LinearSystem& s) {
        std::cout << s.firstEquation.answer << std::endl;
    });

    return 0;
}