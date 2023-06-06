/*
    Masala
    Copyright (C) 2023 Vikram K. Mulligan

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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizationProblem.fwd.hh
/// @brief Implementations for a base class for PluginCostFunctionNetworkOptimizationProblems.
/// @details A PluginCostFunctionNetworkOptimizationProblem defines a special case of a numerical cost function network optimization
/// problem, defined in a plug-in library, to be solved by a suitable Optimizer.  The PluginCostFunctionNetworkOptimizationProblem
/// class does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ThreeInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

// @brief Make a fully independent copy of this object.
// PluginCostFunctionNetworkOptimizationProblemSP
// PluginCostFunctionNetworkOptimizationProblem::deep_clone() const {
//     PluginCostFunctionNetworkOptimizationProblemSP new_problem( masala::make_shared< PluginCostFunctionNetworkOptimizationProblem >( *this ) );
//     new_problem->make_independent();
//     return new_problem;
// }

/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
void
PluginCostFunctionNetworkOptimizationProblem::make_independent() {
    masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem::make_independent();
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
PluginCostFunctionNetworkOptimizationProblem::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem", "CostFunctionNetworkOptimizationProblem" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "numeric" }
std::vector< std::string >
PluginCostFunctionNetworkOptimizationProblem::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function_network_optimization_problem",
		"numeric"
	};
}

// @brief Get the name of this class.
// @returns "PluginCostFunctionNetworkOptimizationProblem".
// std::string
// PluginCostFunctionNetworkOptimizationProblem::class_name() const {
//     return "PluginCostFunctionNetworkOptimizationProblem";
// }

// @brief Get the namespace for this class.
// @returns "masala::numeric_api::base_classes::optimization::cost_function_network".
// std::string
// PluginCostFunctionNetworkOptimizationProblem::class_namespace() const {
//     return "masala::numeric_api::base_classes::optimization::cost_function_network";
// }

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset all data in this object.
void
PluginCostFunctionNetworkOptimizationProblem::reset() {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    PluginCostFunctionNetworkOptimizationProblem::protected_reset();
}

/// @brief Finalize problem setup: indicate that all problem setup is complete, and that
/// the object should now be locked for read only.
void
PluginCostFunctionNetworkOptimizationProblem::finalize() {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    PluginCostFunctionNetworkOptimizationProblem::protected_finalize();
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

// @brief Given a candidate solution, compute the score.
// @details The candidate solution is expressed as a vector of choice indices, with
// one entry per variable position, in order of position indices.  (There may not be
// entries for every position, though, since not all positions have at least two choices.)
// @note This function does NOT lock the problem mutex.  This is only threadsafe from
// a read-only context.
// masala::base::Real
// PluginCostFunctionNetworkOptimizationProblem::compute_absolute_score(
//     std::vector< base::Size > const & candidate_solution
// ) const {
//     masala::base::Real accumulator(0.0);
//     for( auto const & entry : cost_functions_ ) {
//         accumulator += entry->compute_cost_function( candidate_solution );
//     }
//     return accumulator;
// }

// @brief Given a pair of candidate solutions, compute the difference in their scores.
// @details The candidate solution is expressed as a vector of choice indices, with
// one entry per variable position, in order of position indices.  (There may not be
// entries for every position, though, since not all positions have at least two choices.)
// @note This function does NOT lock the problem mutex.  This is only threadsafe from
// a read-only context.
// masala::base::Real
// PluginCostFunctionNetworkOptimizationProblem::compute_score_change(
//     std::vector< base::Size > const & old_solution,
//     std::vector< base::Size > const & new_solution
// ) const {
//     masala::base::Real accumulator(0.0);
//     for( auto const & entry : cost_functions_ ) {
//         accumulator += entry->compute_cost_function_difference( old_solution, new_solution );
//     }
//     return accumulator;
// }

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

// @brief Get a description of the API for the PluginCostFunctionNetworkOptimizationProblem class.
// masala::base::api::MasalaObjectAPIDefinitionCWP
// PluginCostFunctionNetworkOptimizationProblem::get_api_definition() {
//     using namespace masala::base::api;

//     std::lock_guard< std::mutex > lock( problem_mutex() );

//     if( api_definition() == nullptr ) {

//         MasalaObjectAPIDefinitionSP api_def(
//             masala::make_shared< MasalaObjectAPIDefinition >(
//                 *this,
//                 "The PluginCostFunctionNetworkOptimizationProblem class defines a numerical cost function "
//                 "optimization problem.  This is the problem reduced to numbers, with no chemical classes "
//                 "or concepts included.",
//                 false, false
//             )
//         );

//         // Constructors:
//         ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( PluginCostFunctionNetworkOptimizationProblem, api_def );

//         // Getters:
//         api_def->add_getter(
//             masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< base::Size > >(
//                 "total_nodes", "Get the total number of nodes in this problem.  This is the index of the "
//                 "highest-numbered node that has been referred to plus one (since nodes are zero-indexed), "
//                 "NOT the number of nodes with multiple choices.",

//                 "total_nodes", "The total number of nodes in this problem (whether or not they have choices).",

//                 false, false,

//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::total_nodes, this )
//             )
//         );
//         api_def->add_getter(
//             masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< base::Size > >(
//                 "total_variable_nodes", "Get the total number of nodes in this problem that have at least "
// 	            "two choices associated with them.",

//                 "total_variable_nodes", "The total number of nodes in this problem for which choices exist.",

//                 false, false,

//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::total_variable_nodes, this )
//             )
//         );
//         api_def->add_getter(
//             masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput<
//                 std::vector< std::pair< base::Size, base::Size > > >
//             >(
//                 "n_choices_at_variable_nodes", "Get a vector of pairs with one entry for each variable node, "
//                 "where the first entry in the pair indicates the variable node's index, and the second "
//                 "indicates the number of choices at that node.",
//                 "n_choices_at_variable_nodes", "A vector of pairs of ( node index, number of choices ) for all "
//                 "variable node indices (i.e. nodes with more than one choice).  Indices in this vector are NOT "
//                 "node indices, since nodes with fewer than two choices are omitted.  The length of the vector "
//                 "is total_variable_nodes(), not total_nodes().  This vector is guaranteed to be sorted in order "
//                 "of node index, though.", false, false,
//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::n_choices_at_variable_nodes, this )
//             )
//         );
//         api_def->add_getter(
//             masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< base::Real > >(
//                 "total_combinatorial_solutions", "Get the product of the number of choices at each node "
//                 "(the total number of combinatorial solutions to this cost function network problem).  "
//                 "Note that due to possible integer overruns, the return value is a floating-point number, "
//                 "not an integer.",

//                 "total_combinatorial_solutions", "The total number of combinatorial solutions to this problem.",

//                 false, false,

//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::total_combinatorial_solutions, this )
//             )
//         );
//         api_def->add_getter(
//             masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< bool > >(
//                 "finalized", "Has this problem description been finalized?  That is, is the problem setup "
//                 "complete and the object locked to now be read-only?",
//                 "finalized", "True if the object has been finalized, false otherwise.",
//                 false, false,
//                 std::bind( &OptimizationProblem::finalized, this )
//             )
//         );

//         // Setters:
//         api_def->add_setter(
//             masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
//                 "reset", "Completely reset the problem description, deleting all choices for each node.  "
//                 "Also resets finalization state.",
//                 false, true,
//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::reset, this )
//             )
//         );
//         api_def->add_setter(
//             masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
//                 "finalize", "Finalize this object completely -- i.e. indicate that all problem setup is complete, and "
//                 "the object should now be read-only.  May be overridden by derived classes.",
//                 false, true, std::bind( &PluginCostFunctionNetworkOptimizationProblem::finalize, this )
//             )
//         );
//         api_def->add_setter(
//             masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< base::Size, base::Size > >(
//                 "set_minimum_number_of_choices_at_node", "Set the (minimum) number of choices at a node.  "
//                 "If the number of choices has already been set to greater than the specified number, this does nothing.",
//                 "node_index", "The index of the node for which we're setting the minimum number of choices.",
//                 "min_choice_count", "The minimum number of choices at this node.  If the number of choices has already "
//                 "been set for this node to a value greater than this, then this does nothing.",
//                 false, false,
//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::set_minimum_number_of_choices_at_node, this, std::placeholders::_1, std::placeholders::_2 )            )
//         );
//         api_def->add_setter(
//             masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP > >(
//                 "add_cost_function", "Add a cost function to the set of cost functions that will be evaluated during optimization.",
//                 "cost_function", "The input cost function, which should be unfinalized.  This is used directly, not cloned.  "
//                 "The PluginCostFunctionNetworkOptimizationProblem takes ownership and manages the state of the cost function, "
//                 "including its finalization.", false, false,
//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::add_cost_function, this, std::placeholders::_1 )
//             )
//         );

//         // Work functions:
//         work_function::MasalaObjectAPIWorkFunctionDefinition_OneInputSP< base::Real, std::vector< base::Size > const & > comp_abs_score_fxn(
//             masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< base::Real, std::vector< base::Size > const & > >(
//                 "compute_absolute_score", "Given a candidate solution, compute the score.  "
//                 "The candidate solution is expressed as a vector of choice indices, with "
//                 "one entry per variable position, in order of position indices.",
//                 true, false, true, false,
//                 "candidate_solution", "The candidate solution, expressed as a vector of choice indices, with "
//                 "one entry per variable position, in order of position indices.  (There may not be "
//                 "entries for every position, though, since not all positions have at least two choices.)",
//                 "score", "The score for this candidate solution, computed by this function.",
//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::compute_absolute_score, this, std::placeholders::_1 )
//             )
//         );
//         comp_abs_score_fxn->set_triggers_no_mutex_lock();
//         api_def->add_work_function( comp_abs_score_fxn );


//         work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInputSP< base::Real, std::vector< base::Size > const &, std::vector< base::Size > const & > comp_score_change_fxn(
//             masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInput< base::Real, std::vector< base::Size > const &, std::vector< base::Size > const & > >(
//                 "compute_score_change", "Given two candidate solutions, compute the score difference.  "
// 	            "The candidate solutions are expressed as a vector of choice indices, with "
//                 "one entry per variable position, in order of position indices. (There may not be "
//                 "entries for every position, though, since not all positions have at least two choices.)",
//                 true, false, true, false,
//                 "old_solution", "The first candidate solution, expressed as a vector of choice indices, with "
//                 "one entry per variable position, in order of position indices.",
//                 "new_solution", "The second candidate solution, expressed as a vector of choice indices, with "
//                 "one entry per variable position, in order of position indices.",
//                 "delta_score", "The score change from old to new candidate solutions, computed by this function.",
//                 std::bind( &PluginCostFunctionNetworkOptimizationProblem::compute_score_change, this, std::placeholders::_1, std::placeholders::_2 )
//             )
//         );
//         comp_score_change_fxn->set_triggers_no_mutex_lock();
//         api_def->add_work_function( comp_score_change_fxn );

//         api_definition() = api_def; //Make const.
//     }

//     return api_definition();
// }

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object completely.  Mutex must be locked before calling.
void 
PluginCostFunctionNetworkOptimizationProblem::protected_reset() {
    masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem::protected_reset();
}

/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
void
PluginCostFunctionNetworkOptimizationProblem::protected_finalize() {
    masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem::protected_finalize();
}

} // namespace cost_function_network
} // namespace optimization
} // base_classes
} // namespace numeric_api
} // namespace masala
