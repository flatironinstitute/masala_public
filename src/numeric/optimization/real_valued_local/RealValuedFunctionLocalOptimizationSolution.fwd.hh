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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution.fwd.hh
/// @brief Forward declarations for a pure virtual base class for a RealValuedFunctionLocalOptimizationSolution.
/// @details A RealValuedFunctionLocalOptimizationSolution contains the solution to a particular
/// RealValuedFunctionLocalOptimizationProblem, after it is solved by a suitable
/// GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationSolution_fwd_hh
#define Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationSolution_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {
namespace real_valued_local {


	class RealValuedFunctionLocalOptimizationSolution;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using RealValuedFunctionLocalOptimizationSolutionSP = MASALA_SHARED_POINTER< RealValuedFunctionLocalOptimizationSolution >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using RealValuedFunctionLocalOptimizationSolutionCSP = MASALA_SHARED_POINTER< RealValuedFunctionLocalOptimizationSolution const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using RealValuedFunctionLocalOptimizationSolutionWP = MASALA_WEAK_POINTER< RealValuedFunctionLocalOptimizationSolution >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using RealValuedFunctionLocalOptimizationSolutionCWP = MASALA_WEAK_POINTER< RealValuedFunctionLocalOptimizationSolution const >;

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationSolution_fwd_hh