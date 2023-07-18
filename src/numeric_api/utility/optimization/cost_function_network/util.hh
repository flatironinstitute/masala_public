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
	/// If gapped, all solutions shift up by 17.
	masala::numeric_api::auto_generated_api::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem_APISP
	construct_test_problem( std::string const & name_of_problem_class, bool const gapped=false, bool const finalized = true );

	/// @brief Construct a variant of the problem above, satisfiable features on some of the choices.
	/// @param[in] name_of_problem_class The class name for the problem container.  Must be derived from
	/// PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.
	/// @param[in] gapped If true, we define the problem for nodes 0, 1, and 3, with only
	/// one rotamer at node 2.  If false, we define the problem for nodes 0, 1, and 2.  False
	/// by default.
	/// @param[in] finalized If true (the default), we return a finalized problem setup.  If
	/// false, we leave the problem unfinalized, permitting additional stuff to be added.
	/// @details  The solutions and solutions scores are as follows if ungapped:
	/// 0 0 0 -> 86
	/// 0 0 1 -> 114
	/// 0 0 2 -> 118
	/// 0 1 0 -> 156
	/// 0 1 1 -> 98
	/// 0 1 2 -> 223
	/// 0 2 0 -> 55
	/// 0 2 1 -> 57
	/// 0 2 2 -> 61
	/// 1 0 0 -> 76
	/// 1 0 1 -> 73
	/// 1 0 2 -> 72
	/// 1 1 0 -> 115
	/// 1 1 1 -> 146
	/// 1 1 2 -> 146
	/// 1 2 0 -> 69
	/// 1 2 1 -> 40
	/// 1 2 2 -> 99
	/// 2 0 0 -> 53
	/// 2 0 1 -> 82
	/// 2 0 2 -> 83
	/// 2 1 0 -> 127
	/// 2 1 1 -> 70
	/// 2 1 2 -> 192
	/// 2 2 0 -> 18
	/// 2 2 1 -> 21
	/// 2 2 2 -> 22
	///
	/// The solutions and solutions scores are as follows if gapped:
	/// 0 0 0 -> 103
	/// 0 0 1 -> 131
	/// 0 0 2 -> 135
	/// 0 1 0 -> 173
	/// 0 1 1 -> 115
	/// 0 1 2 -> 240
	/// 0 2 0 -> 72
	/// 0 2 1 -> 74
	/// 0 2 2 -> 78
	/// 1 0 0 -> 93
	/// 1 0 1 -> 90
	/// 1 0 2 -> 89
	/// 1 1 0 -> 132
	/// 1 1 1 -> 163
	/// 1 1 2 -> 163
	/// 1 2 0 -> 86
	/// 1 2 1 -> 57
	/// 1 2 2 -> 116
	/// 2 0 0 -> 70
	/// 2 0 1 -> 99
	/// 2 0 2 -> 100
	/// 2 1 0 -> 144
	/// 2 1 1 -> 87
	/// 2 1 2 -> 209
	/// 2 2 0 -> 35
	/// 2 2 1 -> 38
	/// 2 2 2 -> 39
	masala::numeric_api::auto_generated_api::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem_APISP
	construct_test_problem_with_squared_unsatisfied_feature_penalties(std::string const & name_of_problem_class,  bool const gapped=false, bool const finalized = true );

	/// @brief Construct a variant of the problem above, with penalties on each of the choices and a desired
	/// penalty count that makes what was previously the third-lowest energy solution the new lowest-energy
	/// solution.  This emulates what is done in Rosetta with the voids_penalty scoreterm.
	/// @param[in] name_of_problem_class The class name for the problem container.  Must be derived from
	/// PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.
	/// @param[in] gapped If true, we define the problem for nodes 0, 1, and 3, with only
	/// one rotamer at node 2.  If false, we define the problem for nodes 0, 1, and 2.  False
	/// by default.
	/// @param[in] finalized If true (the default), we return a finalized problem setup.  If
	/// false, we leave the problem unfinalized, permitting additional stuff to be added.
	/// @details  The solutions and solutions scores are as follows if ungapped:
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
	///
	/// The solutions and solutions scores are as follows if gapped:
	/// 0 0 0 -> 113
	/// 0 0 1 -> 152
	/// 0 0 2 -> 156
	/// 0 1 0 -> 177
	/// 0 1 1 -> 244
	/// 0 1 2 -> 249
	/// 0 2 0 -> 88
	/// 0 2 1 -> 123
	/// 0 2 2 -> 127
	/// 1 0 0 -> 109
	/// 1 0 1 -> 139
	/// 1 0 2 -> 138
	/// 1 1 0 -> 166
	/// 1 1 1 -> 224
	/// 1 1 2 -> 224
	/// 1 2 0 -> 80
	/// 1 2 1 -> 106
	/// 1 2 2 -> 105
	/// 2 0 0 -> 64
	/// 2 0 1 -> 88
	/// 2 0 2 -> 89
	/// 2 1 0 -> 120
	/// 2 1 1 -> 172
	/// 2 1 2 -> 174
	/// 2 2 0 -> 39  <-- lowest
	/// 2 2 1 -> 59
	/// 2 2 2 -> 60
	masala::numeric_api::auto_generated_api::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem_APISP
	construct_test_problem_with_squared_choice_count_penalties( std::string const & name_of_problem_class, bool const gapped=false, bool const finalized = true );

	/// @brief Construct a variant of the problem above, with some of the choices in a "countable"
	/// category and a desired count of those choices.  That makes what was previously the second-lowest
	/// energy solution the new lowest-energy solution.  This emulates what is done in Rosetta with the
	/// aa_composition scoreterm.
	/// @param[in] name_of_problem_class The class name for the problem container.  Must be derived from
	/// PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.
	/// @param[in] gapped If true, we define the problem for nodes 0, 1, and 3, with only
	/// one rotamer at node 2.  If false, we define the problem for nodes 0, 1, and 2.  False
	/// by default.
	/// @param[in] finalized If true (the default), we return a finalized problem setup.  If
	/// false, we leave the problem unfinalized, permitting additional stuff to be added.
	/// @details  The solutions and solutions scores are as follows if ungapped:
	/// 0 0 0 -> 96
	/// 0 0 1 -> 79
	/// 0 0 2 -> 73
	/// 0 1 0 -> 111
	/// 0 1 1 -> 98
	/// 0 1 2 -> 88
	/// 0 2 0 -> 70
	/// 0 2 1 -> 57
	/// 0 2 2 -> 46
	/// 1 0 0 -> 91
	/// 1 0 1 -> 73
	/// 1 0 2 -> 57
	/// 1 1 0 -> 100
	/// 1 1 1 -> 86
	/// 1 1 2 -> 108
	/// 1 2 0 -> 54
	/// 1 2 1 -> 40
	/// 1 2 2 -> 61
	/// 2 0 0 -> 63
	/// 2 0 1 -> 47
	/// 2 0 2 -> 38
	/// 2 1 0 -> 82
	/// 2 1 1 -> 70
	/// 2 1 2 -> 57
	/// 2 2 0 -> 33
	/// 2 2 1 -> 21
	/// 2 2 2 -> 7  <-- lowest
	///
	/// The solutions and solutions scores are as follows if gapped:
	/// 0 0 0 -> 88
	/// 0 0 1 -> 71
	/// 0 0 2 -> 97
	/// 0 1 0 -> 135
	/// 0 1 1 -> 122
	/// 0 1 2 -> 193
	/// 0 2 0 -> 94
	/// 0 2 1 -> 81
	/// 0 2 2 -> 151
	/// 1 0 0 -> 115
	/// 1 0 1 -> 97
	/// 1 0 2 -> 162
	/// 1 1 0 -> 205
	/// 1 1 1 -> 191
	/// 1 1 2 -> 301
	/// 1 2 0 -> 159
	/// 1 2 1 -> 145
	/// 1 2 2 -> 254
	/// 2 0 0 -> 55
	/// 2 0 1 -> 39  <-- lowest
	/// 2 0 2 -> 62
	/// 2 1 0 -> 106
	/// 2 1 1 -> 94
	/// 2 1 2 -> 162
	/// 2 2 0 -> 57
	/// 2 2 1 -> 45
	/// 2 2 2 -> 112
	masala::numeric_api::auto_generated_api::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem_APISP
	construct_test_problem_with_function_of_integer_penalty_sum_penalties( std::string const & name_of_problem_class, bool const gapped=false, bool const finalized = true );

} // namespace cost_function_network
} // namespace optimization
} // namespace utility
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_api_utility_optimization_cost_function_network_util_hh