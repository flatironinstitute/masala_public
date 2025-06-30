/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/numeric/optimization/OptimizationSolution.fwd.hh
/// @brief Forward declarations for a pure virtual base class for OptimizationSolutions.
/// @details An OptimizationSolution contains the solution to a particular OptimizationProblem,
/// after it is solved by a suitable Optimizer.  It does not contain any chemistry-specific
/// concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_OptimizationSolution_fwd_hh
#define Masala_src_numeric_optimization_OptimizationSolution_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {

	class OptimizationSolution;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using OptimizationSolutionSP = MASALA_SHARED_POINTER< OptimizationSolution >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using OptimizationSolutionCSP = MASALA_SHARED_POINTER< OptimizationSolution const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using OptimizationSolutionWP = MASALA_WEAK_POINTER< OptimizationSolution >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using OptimizationSolutionCWP = MASALA_WEAK_POINTER< OptimizationSolution const >;

} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_OptimizationSolution_fwd_hh