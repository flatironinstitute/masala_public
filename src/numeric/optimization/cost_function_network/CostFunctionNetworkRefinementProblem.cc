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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkRefinementProblem.cc
/// @brief Implementation for a pure virtual base class for CostFunctionNetworkRefinementProblems.
/// @details CostFunctionNetworkRefinementProblems define a numerical cost function network optimization problem to be refined
/// by a suitable refining Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkRefinementProblem.hh>

// STL headers:
#include <vector>
#include <string>
#include <numeric>

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.hh>
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.hh>

// Base headers:
#include <base/utility/execution_policy/util.hh>
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
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a fully independent copy of this object.
CostFunctionNetworkRefinementProblemSP
CostFunctionNetworkRefinementProblem::deep_clone() const {
	CostFunctionNetworkRefinementProblemSP new_problem( masala::make_shared< CostFunctionNetworkRefinementProblem >( *this ) );
	new_problem->make_independent();
	return new_problem;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "CostFunctionNetworkRefinementProblem" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
CostFunctionNetworkRefinementProblem::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "CostFunctionNetworkRefinementProblem" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "cost_function_network_refinement_problem", "numeric" }
std::vector< std::string >
CostFunctionNetworkRefinementProblem::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function_network_optimization_problem",
		"cost_function_network_refinement_problem",
		"numeric"
	};
}

/// @brief Get the category for this MasalaDataRepresentation.
/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "CostFunctionNetworkRefinementProblem" } }.
std::vector< std::vector< std::string > >
CostFunctionNetworkRefinementProblem::get_data_representation_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "CostFunctionNetworkRefinementProblem" }
	};
}

/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
/// is compatible.
/// @returns An empty list.
std::vector< std::string >
CostFunctionNetworkRefinementProblem::get_compatible_masala_engines() const {
	return std::vector< std::string >{};
}

/// @brief Get the properties of this MasalaDataRepresentation.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "cost_function_network_refinement_problem" }.
std::vector< std::string >
CostFunctionNetworkRefinementProblem::get_present_data_representation_properties() const {
	return std::vector< std::string >{ "optimization_problem", "cost_function_network_optimization_problem", "cost_function_network_refinement_problem" };
}

/// @brief Get the name of this class.
/// @returns "CostFunctionNetworkRefinementProblem".
std::string
CostFunctionNetworkRefinementProblem::class_name() const {
	return "CostFunctionNetworkRefinementProblem";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkRefinementProblem::class_namespace() const {
	return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkRefinementProblem class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkRefinementProblem::get_api_definition() {
	using namespace masala::base::api;

	std::lock_guard< std::mutex > lock( problem_mutex() );

	if( api_definition() == nullptr ) {

		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this,
				"The CostFunctionNetworkRefinementProblem class defines a numerical cost function "
				"optimization problem for refinement.  This is the problem reduced to numbers, with no chemical classes "
				"or concepts included.  Refinement means that we have one or more initial solutions, and we want to find "
				"better solutions using these as a starting point.  A CostFunctionNetworkRefinementProblem is a "
				"CostFunctionNetworkOptimizationProblem, and can be solved by any CostFunctionNetworkOptimizer, regardless "
				"whether it pays attention to the candidate solutions.",
				false, false
			)
		);

		// Constructors:
		ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( CostFunctionNetworkRefinementProblem, api_def );

		// Getters:
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< base::Size > >(
				"total_nodes", "Get the total number of nodes in this problem.  This is the index of the "
				"highest-numbered node that has been referred to plus one (since nodes are zero-indexed), "
				"NOT the number of nodes with multiple choices.",

				"total_nodes", "The total number of nodes in this problem (whether or not they have choices).",

				false, false,

				std::bind( &CostFunctionNetworkRefinementProblem::total_nodes, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< base::Size > >(
				"total_variable_nodes", "Get the total number of nodes in this problem that have at least "
				"two choices associated with them.",

				"total_variable_nodes", "The total number of nodes in this problem for which choices exist.",

				false, false,

				std::bind( &CostFunctionNetworkRefinementProblem::total_variable_nodes, this )
			)
		);
		api_def->add_getter(
			masala::make_shared<
				getter::MasalaObjectAPIGetterDefinition_ZeroInput< std::map< base::Size, base::Size > const & >
			>(
				"n_choices_at_all_nodes", "Get a vector of pairs with one entry for each variable node, "
				"where the first entry in the pair indicates the variable node's index, and the second "
				"indicates the number of choices at that node.",
				"n_choices_at_all_nodes", "A vector of pairs of ( node index, number of choices ) for all "
				"node indices. The length of the vector total_nodes().", false, false,
				std::bind( &CostFunctionNetworkRefinementProblem::n_choices_at_all_nodes, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput<
				std::vector< std::pair< base::Size, base::Size > > >
			>(
				"n_choices_at_variable_nodes", "Get a vector of pairs with one entry for each variable node, "
				"where the first entry in the pair indicates the variable node's index, and the second "
				"indicates the number of choices at that node.",
				"n_choices_at_variable_nodes", "A vector of pairs of ( node index, number of choices ) for all "
				"variable node indices (i.e. nodes with more than one choice).  Indices in this vector are NOT "
				"node indices, since nodes with fewer than two choices are omitted.  The length of the vector "
				"is total_variable_nodes(), not total_nodes().  This vector is guaranteed to be sorted in order "
				"of node index, though.", false, false,
				std::bind( &CostFunctionNetworkRefinementProblem::n_choices_at_variable_nodes, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< base::Real > >(
				"total_combinatorial_solutions", "Get the product of the number of choices at each node "
				"(the total number of combinatorial solutions to this cost function network problem).  "
				"Note that due to possible integer overruns, the return value is a floating-point number, "
				"not an integer.",

				"total_combinatorial_solutions", "The total number of combinatorial solutions to this problem.",

				false, false,

				std::bind( &CostFunctionNetworkRefinementProblem::total_combinatorial_solutions, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< bool > >(
				"finalized", "Has this problem description been finalized?  That is, is the problem setup "
				"complete and the object locked to now be read-only?",
				"finalized", "True if the object has been finalized, false otherwise.",
				false, false,
				std::bind( &OptimizationProblem::finalized, this )
			)
		);

		// Setters:
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
				"reset", "Completely reset the problem description, deleting all choices for each node.  "
				"Also resets finalization state.",
				false, true,
				std::bind( &CostFunctionNetworkRefinementProblem::reset, this )
			)
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
				"finalize", "Finalize this object completely -- i.e. indicate that all problem setup is complete, and "
				"the object should now be read-only.  May be overridden by derived classes.",
				false, true, std::bind( &CostFunctionNetworkRefinementProblem::finalize, this )
			)
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< base::Size, base::Size > >(
				"set_minimum_number_of_choices_at_node", "Set the (minimum) number of choices at a node.  "
				"If the number of choices has already been set to greater than the specified number, this does nothing.",
				"node_index", "The index of the node for which we're setting the minimum number of choices.",
				"min_choice_count", "The minimum number of choices at this node.  If the number of choices has already "
				"been set for this node to a value greater than this, then this does nothing.",
				false, false,
				std::bind( &CostFunctionNetworkRefinementProblem::set_minimum_number_of_choices_at_node, this, std::placeholders::_1, std::placeholders::_2 )            )
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP > >(
				"add_cost_function", "Add a cost function to the set of cost functions that will be evaluated during optimization.",
				"cost_function", "The input cost function, which should be unfinalized.  This is used directly, not cloned.  "
				"The CostFunctionNetworkRefinementProblem takes ownership and manages the state of the cost function, "
				"including its finalization.", false, false,
				std::bind( &CostFunctionNetworkRefinementProblem::add_cost_function, this, std::placeholders::_1 )
			)
		);

		// Work functions:
		work_function::MasalaObjectAPIWorkFunctionDefinition_OneInputSP< base::Real, std::vector< base::Size > const & > comp_abs_score_fxn_nonapprox(
			masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< base::Real, std::vector< base::Size > const & > >(
				"compute_non_approximate_absolute_score", "Given a candidate solution, compute the score.  "
				"This computes the actual, non-approximate score (possibly more slowly), not the score "
				"that the data approximation uses (computed in a manner optimized for speed, which may "
				"involve approximations).  The candidate solution is expressed as a vector of choice indices, with "
				"one entry per variable position, in order of position indices.",
				true, false, true, false,
				"candidate_solution", "The candidate solution, expressed as a vector of choice indices, with "
				"one entry per variable position, in order of position indices.  (There may not be "
				"entries for every position, though, since not all positions have at least two choices.)",
				"score", "The score for this candidate solution, computed by this function.",
				std::bind( &CostFunctionNetworkRefinementProblem::compute_non_approximate_absolute_score, this, std::placeholders::_1 )
			)
		);
		comp_abs_score_fxn_nonapprox->set_triggers_no_mutex_lock();
		api_def->add_work_function( comp_abs_score_fxn_nonapprox );

		work_function::MasalaObjectAPIWorkFunctionDefinition_OneInputSP< base::Real, std::vector< base::Size > const & > comp_abs_score_fxn(
			masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< base::Real, std::vector< base::Size > const & > >(
				"compute_absolute_score", "Given a candidate solution, compute the score (which "
				"may be approximate, depending on the data representation).  "
				"The candidate solution is expressed as a vector of choice indices, with "
				"one entry per variable position, in order of position indices.",
				true, false, true, false,
				"candidate_solution", "The candidate solution, expressed as a vector of choice indices, with "
				"one entry per variable position, in order of position indices.  (There may not be "
				"entries for every position, though, since not all positions have at least two choices.)",
				"score", "The score for this candidate solution, computed by this function.",
				std::bind( &CostFunctionNetworkRefinementProblem::compute_absolute_score, this, std::placeholders::_1 )
			)
		);
		comp_abs_score_fxn->set_triggers_no_mutex_lock();
		api_def->add_work_function( comp_abs_score_fxn );

		work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInputSP< base::Real, std::vector< base::Size > const &, std::vector< base::Size > const & > comp_score_change_fxn(
			masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInput< base::Real, std::vector< base::Size > const &, std::vector< base::Size > const & > >(
				"compute_score_change", "Given two candidate solutions, compute the score difference.  This "
				"is the difference in the data representation scores (which may be an approximation of the "
				"actual scores).  The candidate solutions are expressed as a vector of choice indices, with "
				"one entry per variable position, in order of position indices. (There may not be "
				"entries for every position, though, since not all positions have at least two choices.)",
				true, false, true, false,
				"old_solution", "The first candidate solution, expressed as a vector of choice indices, with "
				"one entry per variable position, in order of position indices.",
				"new_solution", "The second candidate solution, expressed as a vector of choice indices, with "
				"one entry per variable position, in order of position indices.",
				"delta_score", "The score change from old to new candidate solutions, computed by this function.",
				std::bind( &CostFunctionNetworkRefinementProblem::compute_score_change, this, std::placeholders::_1, std::placeholders::_2 )
			)
		);
		comp_score_change_fxn->set_triggers_no_mutex_lock();
		api_def->add_work_function( comp_score_change_fxn );

        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput< OptimizationSolutionsSP > >(
                "create_solutions_container", "Create a solutions container for this type of optimization problem.  "
				"Base class implementation creates a generic OptimizationSolutions container.  This override creates a "
				"CostFunctionNetworkOptimizationSolutions container.",
				true, false, false, true,
				"solutions_container", "An OptimizationSolutions object (or instance of a derived class thereof) for holding "
				"solutions to this optimization problem.",
				std::bind( &CostFunctionNetworkRefinementProblem::create_solutions_container, this )
            )
        );

		api_definition() = api_def; //Make const.
	}

	return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object completely.  Mutex must be locked before calling.
void 
CostFunctionNetworkRefinementProblem::protected_reset() {
	starting_solutions_.clear();
	masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem::protected_reset();
}

/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
void
CostFunctionNetworkRefinementProblem::protected_finalize() {
	masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem::protected_finalize();
	std::vector<std::pair<masala::base::Size, masala::base::Size>> const choices_at_var_nodes( n_choices_at_variable_nodes() );
	for( auto const & solution : starting_solutions_ ) {
		CHECK_OR_THROW_FOR_CLASS( solution.size() == choices_at_var_nodes.size(), "protected_finalize", "Expected candidate solution "
			"vectors to have " + std::to_string( choices_at_var_nodes.size() ) + " entries (one per variable node), but got "
			"a solution with " + std::to_string( solution.size() ) + " entries."
		);
		for( masala::base::Size i(0); i<solution.size(); ++i ) {
			CHECK_OR_THROW_FOR_CLASS( solution[i] < choices_at_var_nodes[i].second, "protected_finalize", "Node "
			+ std::to_string( choices_at_var_nodes[i].first ) + " has " + std::to_string( choices_at_var_nodes[i].second )
			+ " choices associated with it, but got starting candidate choice " + std::to_string( solution[i] ) + " at this position."
			);
		}
	}
}


} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
