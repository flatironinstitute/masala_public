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

/// @file src/numeric_api/utility/optimization/cost_function_network/util.cc
/// @brief Implementations of utility functions for cost function network optimization problems.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/utility/optimization/cost_function_network/util.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem_API.hh>
#include <numeric_api/base_classes/optimization/cost_function_network/PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>
#include <base/managers/plugin_module/MasalaPluginAPI.hh>
#include <base/managers/plugin_module/MasalaPlugin.hh>

// STL headers:
#include <vector>

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
construct_test_problem(
    std::string const & name_of_problem_class,
    bool const gapped,
    bool const finalized
) {
    using namespace masala::numeric_api::base_classes::optimization::cost_function_network;
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;

    masala::base::Size const last_node( gapped ? 3 : 2 );

    masala::base::managers::plugin_module::MasalaPluginAPISP my_object(
        masala::base::managers::plugin_module::MasalaPluginModuleManager::get_instance()->create_plugin_object_instance_by_short_name(
            std::vector< std::string >{ "OptimizationProblem", "CostFunctionNetworkOptimizationProblem" },
            name_of_problem_class,
            true
        )
    );

    CostFunctionNetworkOptimizationProblem_APISP my_object_cast(
        std::dynamic_pointer_cast< CostFunctionNetworkOptimizationProblem_API >( my_object )
    );
    CHECK_OR_THROW( my_object_cast != nullptr, "masala::numeric_api::utility::optimization::cost_function_network", "construct_test_problem", "The returned " + name_of_problem_class + " object was not a CostFunctionNetworkOptimizationProblem." );

    PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem * problem(
        dynamic_cast< PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem * >( my_object_cast->get_inner_object().get() )
    );
    CHECK_OR_THROW( problem != nullptr, "masala::numeric_api::utility::optimization::cost_function_network", "construct_test_problem", "The returned " + name_of_problem_class + " object was not a PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem." );

    // Configure one-node penalties:
    problem->set_onebody_penalty( 0, 0, 25 );
    problem->set_onebody_penalty( 0, 1, 32 );
    problem->set_onebody_penalty( 0, 2, 0 );
    problem->set_onebody_penalty( 1, 0, 15 );
    problem->set_onebody_penalty( 1, 1, 43 );
    problem->set_onebody_penalty( 1, 2, 0 );
    problem->set_onebody_penalty( last_node, 0, 14 );
    problem->set_onebody_penalty( last_node, 1, 5 );
    problem->set_onebody_penalty( last_node, 2, 0 );

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

    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 0, 0 ), 5 );
    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 0, 1 ), 3 );
    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 0, 2 ), 9 );
    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 1, 0 ), 4 );
    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 1, 1 ), 1 );
    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 1, 2 ), 2 );
    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 2, 0 ), 1 );
    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 2, 1 ), 0 );
    problem->set_twobody_penalty( std::make_pair( 0, last_node ), std::make_pair( 2, 2 ), 3 );

    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 0, 0 ), 7 );
    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 0, 1 ), 1 );
    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 0, 2 ), 4 );
    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 1, 0 ), 6 );
    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 1, 1 ), 4 );
    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 1, 2 ), 8 );
    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 2, 0 ), 2 );
    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 2, 1 ), 0 );
    problem->set_twobody_penalty( std::make_pair( 1, last_node ), std::make_pair( 2, 2 ), 3 );

    if( gapped ) {
        // We set some penalties here that become fixed background.  The fixed background should be 17.0.
        problem->set_onebody_penalty( 2, 0, 12.0 );

        // The pairwise penalties for choices at node 0 with node 2 are effectively onebody penalties, so they have to be the same:
        problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 0, 0 ), 3.0 );
        problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 1, 0 ), 3.0 );
        problem->set_twobody_penalty( std::make_pair( 0, 2 ), std::make_pair( 2, 0 ), 3.0 );

        // The pairwise penalties for choices at node 1 with node 2 are also effectively onebody penalties, so they have to be the same:
        problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 0, 0 ), 2.0 );
        problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 1, 0 ), 2.0 );
        problem->set_twobody_penalty( std::make_pair( 1, 2 ), std::make_pair( 2, 0 ), 2.0 );
    }

    if( finalized ) {
        // Finalize the problem.
        problem->finalize();
    }
    
    // Return the problem.
    return my_object_cast;
}

} // namespace cost_function_network
} // namespace optimization
} // namespace utility
} // namespace numeric_api
} // namespace masala
