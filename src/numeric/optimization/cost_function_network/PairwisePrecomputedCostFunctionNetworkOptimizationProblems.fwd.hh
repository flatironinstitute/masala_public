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

/// @file src/numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblems.fwd.hh
/// @brief Forward declarations for a container for PairwisePrecomputedCostFunctionNetworkOptimizationProblems.
/// @details PairwisePrecomputedCostFunctionNetworkOptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_PairwisePrecomputedCostFunctionNetworkOptimizationProblems_fwd_hh
#define Masala_src_numeric_optimization_cost_function_network_PairwisePrecomputedCostFunctionNetworkOptimizationProblems_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
	
	class PairwisePrecomputedCostFunctionNetworkOptimizationProblems;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using PairwisePrecomputedCostFunctionNetworkOptimizationProblemsSP = MASALA_SHARED_POINTER< PairwisePrecomputedCostFunctionNetworkOptimizationProblems >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using PairwisePrecomputedCostFunctionNetworkOptimizationProblemsCSP = MASALA_SHARED_POINTER< PairwisePrecomputedCostFunctionNetworkOptimizationProblems const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using PairwisePrecomputedCostFunctionNetworkOptimizationProblemsWP = MASALA_WEAK_POINTER< PairwisePrecomputedCostFunctionNetworkOptimizationProblems >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using PairwisePrecomputedCostFunctionNetworkOptimizationProblemsCWP = MASALA_WEAK_POINTER< PairwisePrecomputedCostFunctionNetworkOptimizationProblems const >;

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_cost_function_network_PairwisePrecomputedCostFunctionNetworkOptimizationProblems_fwd_hh
