/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/// @file src/numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblem.fwd.hh
/// @brief Forward declarations for a class for a GradientBasedFunctionOptimizationProblem.
/// @details A GradientBasedFunctionOptimizationProblem defines a numerical minimization function to be solved by
/// gradient-based methods for an arbitrary loss function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationProblem_fwd_hh
#define Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationProblem_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {
namespace gradient_based {

	class GradientBasedFunctionOptimizationProblem;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using GradientBasedFunctionOptimizationProblemSP = MASALA_SHARED_POINTER< GradientBasedFunctionOptimizationProblem >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using GradientBasedFunctionOptimizationProblemCSP = MASALA_SHARED_POINTER< GradientBasedFunctionOptimizationProblem const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using GradientBasedFunctionOptimizationProblemWP = MASALA_WEAK_POINTER< GradientBasedFunctionOptimizationProblem >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using GradientBasedFunctionOptimizationProblemCWP = MASALA_WEAK_POINTER< GradientBasedFunctionOptimizationProblem const >;

} // namespace gradient_based
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationProblem_fwd_hh