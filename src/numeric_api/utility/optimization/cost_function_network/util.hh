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
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem_API.fwd.hh>

namespace masala {
namespace numeric_api {
namespace utility {
namespace optimization {
namespace cost_function_network {

	/// @brief This is a utility function to construct a standard test problem for
	/// testing out cost function network optimizers.  This problem has three nodes
	/// with three choices per node, for a total of 27 possible solutions.
	/// @param[in] name_of_problem_class The class name for the problem container.  Must be derived from
	/// PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.
	/// @param[in] gapped If true, we define the problem for nodes 0, 1, and 3, with only
	/// one rotamer at node 2.  If false, we define the problem for nodes 0, 1, and 2.  False
	/// by default.
	/// @param[in] finalized If true (the default), we return a finalized problem setup.  If
	/// false, we leave the problem unfinalized, permitting additional stuff to be added.
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
	/// 1 2 2 -> 39
	/// 2 0 0 -> 38
	/// 2 0 1 -> 22
	/// 2 0 2 -> 23
	/// 2 1 0 -> 67
	/// 2 1 1 -> 55
	/// 2 1 2 -> 57
	/// 2 2 0 -> 18
	/// 2 2 1 -> 6  <-- lowest
	/// 2 2 2 -> 7
	/// If gapped, all solutions shift up by 17.
	masala::numeric_api::auto_generated_api::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem_APISP
	construct_test_problem( std::string const & name_of_problem_class, bool const gapped=false, bool const finalized = true );

} // namespace cost_function_network
} // namespace optimization
} // namespace utility
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_api_utility_optimization_cost_function_network_util_hh