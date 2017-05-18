#include <fstream>
#include <experimental/optional>

#include <boost/spirit/include/qi.hpp>
#include <boost/rational.hpp>

#include "linsys/systemparts.h"
#include "linsys/linearsystem.h"
#include "linsys/session.h"
#include "linsys/parser.h"

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
