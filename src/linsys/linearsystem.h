/*
 * Created by Mark on 5/16/2017.
 */

#pragma once

#include <string>
#include <experimental/optional>
#include "systemparts.h"

namespace linsys {
	struct LinearSystem {
	private:
		LinearSystem(const LinearEquation firstEquation, const LinearEquation secondEquation,
				const std::experimental::optional<LinearSystemSolution> solution)
			: firstEquation(firstEquation), secondEquation(secondEquation), solution(solution) {};

		const static std::experimental::optional<linsys::LinearSystemSolution>
			findSolution(const linsys::LinearEquation &first, const linsys::LinearEquation &second);

		static void normalizeLinearEquation(linsys::LinearEquation &equation);

		const static bool validateAndNormalizeLinearEquations(linsys::LinearEquation &firstEquation,
				linsys::LinearEquation &secondEquation);

	public:
		static LinearSystem of(LinearEquation &&firstEquation, LinearEquation &&secondEquation) {
			if (!validateAndNormalizeLinearEquations(firstEquation, secondEquation)) {
				throw "Invalid linear equations!";
			}
			return {firstEquation, secondEquation, findSolution(firstEquation, secondEquation)};
		}

		std::string toString() const noexcept;

		const LinearEquation firstEquation, secondEquation;
		const std::experimental::optional<LinearSystemSolution> solution;
	};
}
