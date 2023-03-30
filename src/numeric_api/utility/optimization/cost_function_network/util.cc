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

/// @file src/numeric_api/utility/optimization/cost_function_network/util.cc
/// @brief Implementations of utility functions for cost function network optimization problems.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/utility/optimization/cost_function_network/util.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/cost_function_network/cost_function/SquareOfChoicePenaltySumCostFunction_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem_API.hh>

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
construct_test_problem( bool const finalized ) {
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
    PairwisePrecomputedCostFunctionNetworkOptimizationProblem_APISP problem(
        masala::make_shared< PairwisePrecomputedCostFunctionNetworkOptimizationProblem_API >()
    );

    // Configure one-node penalties:
    problem->set_onebody_penalty( 0, 0, 25 );
    problem->set_onebody_penalty( 0, 1, 32 );
    problem->set_onebody_penalty( 0, 2, 0 );
    problem->set_onebody_penalty( 1, 0, 15 );
    problem->set_onebody_penalty( 1, 1, 43 );
    problem->set_onebody_penalty( 1, 2, 0 );
    problem->set_onebody_penalty( 2, 0, 14 );
    problem->set_onebody_penalty( 2, 1, 5 );
    problem->set_onebody_penalty( 2, 2, 0 );

    // Configure pairwise two-node penalties:
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 0, 0 ), 5 );
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 0, 1 ), 3 );
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 0, 2 ), 9 );
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 1, 0 ), 4 );
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 1, 1 ), 1 );
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 1, 2 ), 2 );
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 2, 0 ), 1 );
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 2, 1 ), 3 );
    problem->set_twobody_penalty( std::make_pair( 0, 1 ), std::make_pair( 2, 2 ), 1 );

    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 0, 0 ), 5 );
    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 0, 1 ), 3 );
    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 0, 2 ), 9 );
    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 1, 0 ), 4 );
    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 1, 1 ), 1 );
    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 1, 2 ), 2 );
    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 2, 0 ), 1 );
    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 2, 1 ), 0 );
    problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 2, 2 ), 3 );

    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 0, 0 ), 7 );
    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 0, 1 ), 1 );
    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 0, 2 ), 4 );
    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 1, 0 ), 6 );
    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 1, 1 ), 4 );
    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 1, 2 ), 8 );
    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 2, 0 ), 2 );
    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 2, 1 ), 0 );
    problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 2, 2 ), 3 );

    if( finalized ) {
        // Finalize the problem.
        problem->finalize();
    }
    
    // Return the problem.
    return problem;
}

/// @brief Construct a variant of the problem above, with penalties on each of the choices and a desired
/// penalty count that makes what was previously the third-lowest energy solution the new lowest-energy
/// solution.
masala::numeric_api::auto_generated_api::optimization::cost_function_network::PairwisePrecomputedCostFunctionNetworkOptimizationProblem_APISP
construct_test_problem_with_squared_choice_count_penalties( bool const finalized ) {
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network::cost_function;

    PairwisePrecomputedCostFunctionNetworkOptimizationProblem_APISP problem( construct_test_problem(false) );

    SquareOfChoicePenaltySumCostFunction_APISP cost_func( masala::make_shared< SquareOfChoicePenaltySumCostFunction_API >() );

    TODO TODO TODO;

    problem->add_cost_function( cost_func );

    if( finalized ) {
        // Finalize the problem.
        problem->finalize();
    }
    
    // Return the problem.
    return problem;
}

} // namespace cost_function_network
} // namespace optimization
} // namespace utility
} // namespace numeric_api
} // namesapce masala
