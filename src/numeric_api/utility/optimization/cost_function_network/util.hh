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

/// @file src/numeric_api/utility/optimization/cost_function_network/util.hh
/// @brief Prototypes for utility functions for cost function network optimization problems.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_utility_optimization_cost_function_network_util_hh
#define Masala_src_numeric_api_utility_optimization_cost_function_network_util_hh

// Forward declarations:
#include <numeric_api/auto_generated_api/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem_API.fwd.hh>

namespace masala {
namespace numeric_api {
namespace utility {
namespace optimization {
namespace cost_function_network {

	/// @brief This is a utility funciton to construct a standard test problem for
	/// testing out cost function network optimizers.  This problem has three nodes
	/// with three choices per node, for a total of 27 possible solutions.
	/// @details  The solutions and solutions scores are as follows:
	/// 0 0 0 -> 71
	/// 0 0 1 -> 54
	/// 0 0 2 -> 58
	/// 0 1 0 -> 96
	/// 0 1 1 -> 83
	/// 0 1 2 -> 88
	/// 0 2 0 -> 55
	/// 0 2 1 -> 42
	/// 0 2 2 -> 46
	/// 1 0 0 -> 76
	/// 1 0 1 -> 58
	/// 1 0 2 -> 57
	/// 1 1 0 -> 100
	/// 1 1 1 -> 86
	/// 1 1 2 -> 86
	/// 1 2 0 -> 54
	/// 1 2 1 -> 40
	/// 1 2 2 -> 399
	/// 2 0 0 -> 38
	/// 2 0 1 -> 22
	/// 2 0 2 -> 23
	/// 2 1 0 -> 67
	/// 2 1 1 -> 55
	/// 2 1 2 -> 57
	/// 2 2 0 -> 18
	/// 2 2 1 -> 6  <-- lowest
	/// 2 2 2 -> 7
	masala::numeric_api::auto_generated_api::optimization::cost_function_network::PairwisePrecomputedCostFunctionNetworkOptimizationProblem_APISP
	construct_test_problem( bool const finalized = true );

	/// @brief Construct a variant of the problem above, with penalties on each of the choices and a desired
	/// penalty count that makes what was previously the third-lowest energy solution the new lowest-energy
	/// solution.  This emulates what is done in Rosetta with the voids_penalty scoreterm.
	/// @details  The solutions and solutions scores are as follows:
	/// 0 0 0 -> 80
	/// 0 0 1 -> 103
	/// 0 0 2 -> 107
	/// 0 1 0 -> 132
	/// 0 1 1 -> 183
	/// 0 1 2 -> 188
	/// 0 2 0 -> 59
	/// 0 2 1 -> 78
	/// 0 2 2 -> 82
	/// 1 0 0 -> 80
	/// 1 0 1 -> 94
	/// 1 0 2 -> 93
	/// 1 1 0 -> 125
	/// 1 1 1 -> 167
	/// 1 1 2 -> 167
	/// 1 2 0 -> 55
	/// 1 2 1 -> 65
	/// 1 2 2 -> 64
	/// 2 0 0 -> 39
	/// 2 0 1 -> 47
	/// 2 0 2 -> 48
	/// 2 1 0 -> 83
	/// 2 1 1 -> 119
	/// 2 1 2 -> 121
	/// 2 2 0 -> 18  <-- lowest
	/// 2 2 1 -> 22
	/// 2 2 2 -> 23
	masala::numeric_api::auto_generated_api::optimization::cost_function_network::PairwisePrecomputedCostFunctionNetworkOptimizationProblem_APISP
	construct_test_problem_with_squared_choice_count_penalties( bool const finalized = true );

} // namespace cost_function_network
} // namespace optimization
} // namespace utility
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_api_utility_optimization_cost_function_network_util_hh