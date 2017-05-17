/*
* Created by Mark on 5/16/2017.
*/

#include "linearsystem.h"

namespace linsys {

    const std::experimental::optional<linsys::LinearSystemSolution>
    LinearSystem::findSolution(const linsys::LinearEquation &first, const linsys::LinearEquation &second) {
        const boost::rational<int> determinant = first.firstTerm.coefficient * second.secondTerm.coefficient -
                                                 first.secondTerm.coefficient * second.firstTerm.coefficient;
        if (determinant != 0) {
            const boost::rational<int> x =
                    (first.answer * second.secondTerm.coefficient - first.secondTerm.coefficient * second.answer) /
                    determinant;
            const boost::rational<int> y =
                    (first.firstTerm.coefficient * second.answer - first.answer * second.firstTerm.coefficient) /
                    determinant;
            return {LinearSystemSolution{{x}, {y}}};
        } else {
            return {};
        }
    }

    void LinearSystem::normalizeLinearEquation(linsys::LinearEquation &equation) {
        if (equation.operation == '-') {
            equation.secondTerm.coefficient = -equation.secondTerm.coefficient;
            equation.operation = '+';
        }
    }

    const bool LinearSystem::validateAndNormalizeLinearEquations(linsys::LinearEquation &firstEquation,
                                                          linsys::LinearEquation &secondEquation) {
        if (firstEquation.firstTerm.variableName != secondEquation.firstTerm.variableName) {
            if (firstEquation.secondTerm.variableName == secondEquation.firstTerm.variableName) {
                std::swap(secondEquation.firstTerm, secondEquation.secondTerm);
            } else {
                return false;
            }
        } else if (firstEquation.secondTerm.variableName != secondEquation.secondTerm.variableName) return false;
        else if (firstEquation.firstTerm.coefficient.numerator() == 0 &&
                 firstEquation.secondTerm.coefficient.numerator() == 0)
            return false;
        else if (secondEquation.firstTerm.coefficient.numerator() == 0 &&
                 secondEquation.secondTerm.coefficient.numerator() == 0)
            return false;

        normalizeLinearEquation(firstEquation);
        normalizeLinearEquation(secondEquation);

        return true;
    }
}