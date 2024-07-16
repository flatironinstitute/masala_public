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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.cc
/// @brief Implementation for a pure virtual base class for CostFunctionNetworkOptimizationProblems.
/// @details CostFunctionNetworkOptimizationProblems define a numerical cost function network optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

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

/// @brief Make a copy of this object, and return a shared pointer to the copy.
/// @details Does NOT copy all the internal data, but retains pointers to existing data.
masala::numeric::optimization::OptimizationProblemSP
CostFunctionNetworkOptimizationProblem::clone() const {
	return masala::make_shared< CostFunctionNetworkOptimizationProblem >( *this );
}

/// @brief Make a fully independent copy of this object.
CostFunctionNetworkOptimizationProblemSP
CostFunctionNetworkOptimizationProblem::deep_clone() const {
	CostFunctionNetworkOptimizationProblemSP new_problem( std::static_pointer_cast< CostFunctionNetworkOptimizationProblem >( clone() ) );
	new_problem->make_independent();
	return new_problem;
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
CostFunctionNetworkOptimizationProblem::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem", "CostFunctionNetworkOptimizationProblem" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizationProblem::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function_network_optimization_problem",
		"numeric"
	};
}

/// @brief Get the category for this MasalaDataRepresentation.
/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem" } }.
std::vector< std::vector< std::string > >
CostFunctionNetworkOptimizationProblem::get_data_representation_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem", "CostFunctionNetworkOptimizationProblem" }
	};
}

/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
/// is compatible.
/// @returns An empty list.
std::vector< std::string >
CostFunctionNetworkOptimizationProblem::get_compatible_masala_engines() const {
	return std::vector< std::string >{};
}

/// @brief Get the properties of this MasalaDataRepresentation.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem" }.
std::vector< std::string >
CostFunctionNetworkOptimizationProblem::get_present_data_representation_properties() const {
	return std::vector< std::string >{ "optimization_problem", "cost_function_network_optimization_problem" };
}

/// @brief Get the name of this class.
/// @returns "CostFunctionNetworkOptimizationProblem".
std::string
CostFunctionNetworkOptimizationProblem::class_name() const {
	return "CostFunctionNetworkOptimizationProblem";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkOptimizationProblem::class_namespace() const {
	return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the total number of nodes in this problem.
/// @details This is the index of the highest-numbered node that has been
/// referred to plus one (since nodes are zero-indexed), NOT the number of
/// nodes with multiple choices.
masala::base::Size
CostFunctionNetworkOptimizationProblem::total_nodes() const {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	if( n_choices_by_node_index_.empty() ) { return 0; }
	return n_choices_by_node_index_.rbegin()->first + 1; //Maps are sorted; last element is the biggest.
}

/// @brief Get the total number of nodes in this problem that have at least
/// two choices associated with them.
masala::base::Size
CostFunctionNetworkOptimizationProblem::total_variable_nodes() const {
	if( protected_finalized() ) {
		return total_variable_nodes_;
	}
	std::lock_guard< std::mutex > lock( problem_mutex() );
	if( n_choices_by_node_index_.empty() ) { return 0; }
	base::Size accumulator(0);
	for(
		std::map< base::Size, base::Size >::const_iterator it( n_choices_by_node_index_.begin() );
		it != n_choices_by_node_index_.end();
		++it
	) {
		if( it->second > 1 ) {
			++accumulator;
		}
	}
	return accumulator;
}

/// @brief Get a map with one entry for each node (variable or not), where the key is
/// the node's global index, and the value is the number of choices at that node.
/// @note Keys in this map are node indices, since nodes with fewer than two choices are included.
/// The length of the vector is total_nodes().
std::map< masala::base::Size, masala::base::Size > const &
CostFunctionNetworkOptimizationProblem::n_choices_at_all_nodes() const {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "n_choices_at_all_nodes", "This object must be finalized before this function may be called." );
	return n_choices_by_node_index_;
}

/// @brief Get a vector of pairs with one entry for each variable node, where the first entry in the pair indicates
/// the variable node's index, and the second indicates the number of choices at that node.
/// @note Indices in this vector are NOT node indices, since nodes with fewer than two choices are omitted.
/// The length of the vector is total_variable_nodes(), not total_nodes().  This vector is guaranteed to be sorted
/// in order of node index, though.
std::vector< std::pair< masala::base::Size, masala::base::Size > >
CostFunctionNetworkOptimizationProblem::n_choices_at_variable_nodes() const {
	using masala::base::Size;

	if( protected_finalized() ) {
		return n_choices_at_variable_nodes_;
	}
	std::vector< std::pair< Size, Size > > outvec;
	outvec.reserve( n_choices_by_node_index_.size() );
	{   // Scope for mutex lock.
		std::lock_guard< std::mutex > lock( problem_mutex() );
		for( std::map< Size, Size >::const_iterator it( n_choices_by_node_index_.begin() ); it != n_choices_by_node_index_.end(); ++it ) {
			if( it->second > 1 ) {
				outvec.push_back( std::make_pair( it->first, it->second ) );
			}
		}
	}   // Unlock mutex.
	outvec.shrink_to_fit();
	std::sort(
		outvec.begin(), outvec.end(),
		[](
			std::pair< Size, Size > const & first, std::pair< Size, Size > const & second
		){
			return first.first < second.first;
		}
	);

	return outvec;
}

/// @brief Get the product of the number of choices at each node (the total number
/// of combinatorial solutions to this cost function network problem).
/// @note Due to integer overruns, this is a floating-point number, not an integer.
masala::base::Real
CostFunctionNetworkOptimizationProblem::total_combinatorial_solutions() const {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	if( n_choices_by_node_index_.empty() ) { return 1.0; }
	base::Real product(1.0);
	for(
		std::map< base::Size, base::Size >::const_iterator it( n_choices_by_node_index_.begin() );
		it != n_choices_by_node_index_.end();
		++it
	) {
		if( it->second > 1 ) {
			product *= static_cast< base::Real >( it->second );
		}
	}
	return product;
}

/// @brief Does this object have candidate starting solutions?  These can be used as starting points for
/// some optimizers, or can be ignored.
bool
CostFunctionNetworkOptimizationProblem::has_candidate_starting_solutions() const {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "has_candidate_starting_solutions", "This object must be finalized before this function is called." );
	return !candidate_starting_solutions_.empty();
}

/// @brief Get the optional vector of vectors of solutions to this CFN problem.  These can be used as starting points for
/// some optimizers, or can be ignored.
std::vector< std::vector< masala::base::Size > > const &
CostFunctionNetworkOptimizationProblem::candidate_starting_solutions() const {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "candidate_starting_solutions", "This object must be finalized before this function is called." );
	return candidate_starting_solutions_;
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the (minimum) number of choices at a node.
/// @details If the number of choices has already been set to greater than the
/// specified number, this does nothing.
void
CostFunctionNetworkOptimizationProblem::set_minimum_number_of_choices_at_node(
	masala::base::Size const node_index,
	masala::base::Size const min_choice_count
) {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	set_minimum_number_of_choices_at_node_mutex_locked( node_index, min_choice_count ); // Checks that state is not finalized.
}

/// @brief Add a (non-quadratic) cost function.
/// @details Stores the object directly; does not clone it.  The CostFunctionNetworkOptimizationProblem
/// must not yet be finalized.
void
CostFunctionNetworkOptimizationProblem::add_cost_function(
	masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP cost_function
) {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	add_cost_function_mutex_locked( cost_function );
}

/// @brief Add a candidate solution.
/// @details Locks problem mutex; throws if the problem has already been finalized.
void
CostFunctionNetworkOptimizationProblem::add_candidate_solution(
	std::vector< masala::base::Size > const & candidate_solution_in
) {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	add_candidate_solution_mutex_locked( candidate_solution_in );
}

/// @brief Remove all candidate solutions.
void
CostFunctionNetworkOptimizationProblem::clear_candidate_solutions() {
	std::lock_guard< std::mutex > lock( problem_mutex() );
	clear_candidate_solutions_mutex_locked();
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

/// @brief Given a candidate solution, compute the score.  This computes the actual,
/// non-approximate score (possibly more slowly), not the score that the data approximation
/// uses (computed in a manner optimized for speed, which may involve approximations).
/// @details The candidate solution is expressed as a vector of choice indices, with
/// one entry per variable position, in order of position indices.  (There may not be
/// entries for every position, though, since not all positions have at least two choices.)
/// @note This function does NOT lock the problem mutex.  This is only threadsafe from
/// a read-only context.  The default implementation calls compute_absolute_score(), but this
/// may be overridden if the data representation uses an approximation or lower level of precision
/// to compute the score.
masala::base::Real
CostFunctionNetworkOptimizationProblem::compute_non_approximate_absolute_score(
	std::vector< base::Size > const & candidate_solution
) const {
	return compute_absolute_score( candidate_solution ); /*This behaviour should be override if a derived class uses an approximation.*/
}

/// @brief Given a candidate solution, compute the data representation score (which
/// may be approximate).
/// @details The candidate solution is expressed as a vector of choice indices, with
/// one entry per variable position, in order of position indices.  (There may not be
/// entries for every position, though, since not all positions have at least two choices.)
/// @note This function does NOT lock the problem mutex.  This is only threadsafe from
/// a read-only context.
masala::base::Real
CostFunctionNetworkOptimizationProblem::compute_absolute_score(
	std::vector< base::Size > const & candidate_solution
) const {
	masala::base::Real accumulator(0.0);
	for( auto const & entry : cost_functions_ ) {
		accumulator += entry->compute_cost_function( candidate_solution );
	}
	return accumulator;
}

/// @brief Given a pair of candidate solutions, compute the difference in their scores.
/// This is the difference in the data representation scores (which may be an approximation
/// of the actual scores).
/// @details The candidate solution is expressed as a vector of choice indices, with
/// one entry per variable position, in order of position indices.  (There may not be
/// entries for every position, though, since not all positions have at least two choices.)
/// @note This function does NOT lock the problem mutex.  This is only threadsafe from
/// a read-only context.
masala::base::Real
CostFunctionNetworkOptimizationProblem::compute_score_change(
	std::vector< base::Size > const & old_solution,
	std::vector< base::Size > const & new_solution
) const {
	return std::transform_reduce(
		MASALA_UNSEQ_EXECUTION_POLICY
		cost_functions_.cbegin(), cost_functions_.cend(), 0.0, std::plus{},
		[&old_solution, &new_solution]( masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP const & costfunction ) {
			return costfunction->compute_cost_function_difference( old_solution, new_solution );
		}
	);
}

/// @brief Create a solutions container for this type of optimization problem.
/// @details Base class implementation creates a generic OptimizationSolutions container.
/// This override creates a CostFunctionNetworkOptimizationSolutions container.",
OptimizationSolutionsSP
CostFunctionNetworkOptimizationProblem::create_solutions_container() const {
	return masala::make_shared< CostFunctionNetworkOptimizationSolutions >();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkOptimizationProblem class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkOptimizationProblem::get_api_definition() {
	using namespace masala::base::api;

	std::lock_guard< std::mutex > lock( problem_mutex() );

	if( api_definition() == nullptr ) {

		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this,
				"The CostFunctionNetworkOptimizationProblem class defines a numerical cost function "
				"optimization problem.  This is the problem reduced to numbers, with no chemical classes "
				"or concepts included.",
				false, false
			)
		);

		// Constructors:
		ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( CostFunctionNetworkOptimizationProblem, api_def );

		// Getters:
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< base::Size > >(
				"total_nodes", "Get the total number of nodes in this problem.  This is the index of the "
				"highest-numbered node that has been referred to plus one (since nodes are zero-indexed), "
				"NOT the number of nodes with multiple choices.",

				"total_nodes", "The total number of nodes in this problem (whether or not they have choices).",

				false, false,

				std::bind( &CostFunctionNetworkOptimizationProblem::total_nodes, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< base::Size > >(
				"total_variable_nodes", "Get the total number of nodes in this problem that have at least "
				"two choices associated with them.",

				"total_variable_nodes", "The total number of nodes in this problem for which choices exist.",

				false, false,

				std::bind( &CostFunctionNetworkOptimizationProblem::total_variable_nodes, this )
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
				std::bind( &CostFunctionNetworkOptimizationProblem::n_choices_at_all_nodes, this )
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
				std::bind( &CostFunctionNetworkOptimizationProblem::n_choices_at_variable_nodes, this )
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

				std::bind( &CostFunctionNetworkOptimizationProblem::total_combinatorial_solutions, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< bool > >(
				"has_candidate_starting_solutions", "Does this cost function network optimization problem have "
				"one or more candidate solutions defined?  These can be used as starting points for some optimizers, "
				"or can be ignored.",
				"has_candidate_starting_solutions", "True if there is at least one candidate starting solution, false otherwise.",
				false, false, std::bind( &CostFunctionNetworkOptimizationProblem::has_candidate_starting_solutions, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< std::vector< std::vector< masala::base::Size > > const & > >(
				"candidate_starting_solutions", "Returns candidate starting solutions for this cost functoin network optimization problem.  "
				"These can be used as starting points for some optimizers, or can be ignored.",
				"candidate_starting_solutions", "A vector of vectors of candidate starting solutions for this problem, where the length of "
				"each vector matches the number of variable positions and the entries are choice indices.",
				false, false, std::bind( &CostFunctionNetworkOptimizationProblem::candidate_starting_solutions, this )
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
				false, false,
				std::bind( &CostFunctionNetworkOptimizationProblem::reset, this )
			)
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
				"finalize", "Finalize this object completely -- i.e. indicate that all problem setup is complete, and "
				"the object should now be read-only.  May be overridden by derived classes.",
				false, false, std::bind( &CostFunctionNetworkOptimizationProblem::finalize, this )
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
				std::bind( &CostFunctionNetworkOptimizationProblem::set_minimum_number_of_choices_at_node, this, std::placeholders::_1, std::placeholders::_2 ) )
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP > >(
				"add_cost_function", "Add a cost function to the set of cost functions that will be evaluated during optimization.",
				"cost_function", "The input cost function, which should be unfinalized.  This is used directly, not cloned.  "
				"The CostFunctionNetworkOptimizationProblem takes ownership and manages the state of the cost function, "
				"including its finalization.", false, false,
				std::bind( &CostFunctionNetworkOptimizationProblem::add_cost_function, this, std::placeholders::_1 )
			)
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< std::vector< masala::base::Size > const & > >(
				"add_candidate_solution", "Add a candidate solution.  This may or may not be used as a starting point by a given solver.  This function "
				"locks the problem mutex.  It throws if the problem has already been finalized.",
				"candidate_solution_in", "The input candidate solution.  This should be a vector of zero-based choice indices, with one "
				"index for each variable node in the problem.", false, false,
				std::bind( &CostFunctionNetworkOptimizationProblem::add_candidate_solution, this, std::placeholders::_1 )
			)
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
				"clear_candidate_solutions", "Remove all candidate solutions.  This function "
				"locks the problem mutex.  It throws if the problem has already been finalized.",
				false, false,
				std::bind( &CostFunctionNetworkOptimizationProblem::clear_candidate_solutions, this )
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
				std::bind( &CostFunctionNetworkOptimizationProblem::compute_non_approximate_absolute_score, this, std::placeholders::_1 )
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
				std::bind( &CostFunctionNetworkOptimizationProblem::compute_absolute_score, this, std::placeholders::_1 )
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
				std::bind( &CostFunctionNetworkOptimizationProblem::compute_score_change, this, std::placeholders::_1, std::placeholders::_2 )
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
				std::bind( &CostFunctionNetworkOptimizationProblem::create_solutions_container, this )
			)
		);

		api_definition() = api_def; //Make const.
	}

	return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the (minimum) number of choices at a node.
/// @details If the number of choices has already been set to greater than the
/// specified number, this does nothing.
/// @note This version assumes that the problem mutex has already been set.
/*virtual*/
void
CostFunctionNetworkOptimizationProblem::set_minimum_number_of_choices_at_node_mutex_locked(
	masala::base::Size const node_index,
	masala::base::Size const min_choice_count
) {
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "set_minimum_number_of_choices_at_node_mutex_locked",
		"This object has already been finalized.  Cannot set the minimum number of choices at a node at this point!"
	);

	std::map< masala::base::Size, masala::base::Size >::iterator it( n_choices_by_node_index_.find(node_index) );
	if( it == n_choices_by_node_index_.end() ) {
		n_choices_by_node_index_[node_index] = min_choice_count;
	} else {
		if( it->second < min_choice_count ) {
			it->second = min_choice_count;
		}
	}
}

/// @brief Add a (non-quadratic) cost function.
/// @details Stores the object directly; does not clone it.  The CostFunctionNetworkOptimizationProblem
/// must not yet be finalized.  This version assumes that the mutex for this object has already been locked.
void
CostFunctionNetworkOptimizationProblem::add_cost_function_mutex_locked(
	masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP const & cost_function
) {
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "add_cost_function_mutex_locked",
		"This object has already been finalized.  Cannot add a cost function at this point!"
	);
	CHECK_OR_THROW_FOR_CLASS( !cost_function->finalized(), "add_cost_function", "The input " + cost_function->class_name()
		+ " is already finalized.  Expected an unfinalized object!"
	);
	cost_functions_.push_back( cost_function );
}

/// @brief Add a candidate solution.
/// @details Does not lock problem mutex; throws if the problem has already been finalized.
void
CostFunctionNetworkOptimizationProblem::add_candidate_solution_mutex_locked(
	std::vector< masala::base::Size > const & candidate_solution_in
) {
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "add_candidate_solution_mutex_locked",
		"This object has already been finalized.  Cannot add a candidate solution at this point!"
	);
	candidate_starting_solutions_.push_back( candidate_solution_in );
}

/// @brief Remove all candidate solutions.
/// @details Does not lock problem mutex; throws if the problem has already been finalized.
void
CostFunctionNetworkOptimizationProblem::clear_candidate_solutions_mutex_locked() {
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "clear_candidate_solutions_mutex_locked",
		"This object has already been finalized.  Cannot clear candidate solutions at this point!"
	);
	candidate_starting_solutions_.clear();
}

/// @brief Access the number of choices by node index.
/// @note This assumes that the problem mutex has already been set.
std::map< masala::base::Size, masala::base::Size > &
CostFunctionNetworkOptimizationProblem::n_choices_by_node_index() {
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "n_choices_by_node_index",
		"Can only get nonconst access to the number of choices by node index if the problem has not been finalized!"
	);
	return n_choices_by_node_index_;
}

/// @brief Reset this object completely.  Mutex must be locked before calling.
void 
CostFunctionNetworkOptimizationProblem::protected_reset() {
	n_choices_by_node_index_.clear();
	total_variable_nodes_ = 0;
	n_choices_at_variable_nodes_.clear();
	candidate_starting_solutions_.clear();
	masala::numeric::optimization::OptimizationProblem::protected_reset();
}

/// @brief Make this object independent.
/// @details Assumes mutex was already locked.
/// @note Derived versions of this function should call the parent class version too.
void
CostFunctionNetworkOptimizationProblem::protected_make_independent() {
	for( auto & cost_function : cost_functions_ ) {
		cost_function::CostFunctionSP cf_copy( cost_function->deep_clone() );
		cost_function = cf_copy;
	}
	masala::numeric::optimization::OptimizationProblem::protected_make_independent();
}

/// @brief Inner workings of assignment operator.  Should be called with locked mutex.
/// Should be implemented by derived classes, which shoudl call base class function.
void
CostFunctionNetworkOptimizationProblem::protected_assign(
	masala::numeric::optimization::OptimizationProblem const & src
) {
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "protected_assign", "Could not assign to this " + class_name() + " object, since it has already been finalized." );
	CostFunctionNetworkOptimizationProblem const * src_ptr_cast( dynamic_cast< CostFunctionNetworkOptimizationProblem const * >( &src ) );
	CHECK_OR_THROW_FOR_CLASS( src_ptr_cast != nullptr, "protected_assign", "Could not assign an object of type " + src.class_name() + " to an object of type CostFunctionNetworkOptimizationProblem." );
	n_choices_by_node_index_ = src_ptr_cast->n_choices_by_node_index_;
	cost_functions_ = src_ptr_cast->cost_functions_;
	candidate_starting_solutions_ = src_ptr_cast->candidate_starting_solutions_;
	// The rest is populated by finalize().
	masala::numeric::optimization::OptimizationProblem::protected_assign( src );
}


/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
void
CostFunctionNetworkOptimizationProblem::protected_finalize() {
	using masala::base::Size;

	n_choices_at_variable_nodes_.clear();
	total_variable_nodes_ = 0;
	n_choices_at_variable_nodes_.reserve( n_choices_by_node_index_.size() );
	for( auto const choices : n_choices_by_node_index_ ) {
		if( choices.second > 1 ) {
			++total_variable_nodes_;
			n_choices_at_variable_nodes_.push_back(choices);
		}
	}
	n_choices_at_variable_nodes_.shrink_to_fit();
	std::sort(
		n_choices_at_variable_nodes_.begin(), n_choices_at_variable_nodes_.end(),
		[](
			std::pair< Size, Size > const & first, std::pair< Size, Size > const & second
		){
			return first.first < second.first;
		}
	);

	// Finalize cost functions:
	if( !cost_functions_.empty() ) {
		std::vector< Size > variable_indices( n_choices_at_variable_nodes_.size() );
		for( Size i(0), imax(n_choices_at_variable_nodes_.size()); i<imax; ++i ) {
			variable_indices[i] = n_choices_at_variable_nodes_[i].first;
		}
		for( auto const & cost_function : cost_functions_ ) {
			CHECK_OR_THROW_FOR_CLASS( !(cost_function->finalized()), "protected_finalize", "A " + cost_function->class_name()
				+ " cost function was already finalized.  Expected all cost functions to be unfinalized!"
			)
			cost_function->finalize( variable_indices );
		}
	}

	masala::numeric::optimization::OptimizationProblem::protected_finalize();

	// Check the candidate solutions:
	candidate_starting_solutions_.shrink_to_fit();
	std::vector<std::pair<masala::base::Size, masala::base::Size>> const choices_at_var_nodes( protected_n_choices_at_variable_nodes() );
	for( auto const & solution : candidate_starting_solutions_ ) {
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

/// @brief Access the total number of variable nodes, precomputed by finalize() and cached.
/// @details The finalize() function must be called before this function is used.
masala::base::Size
CostFunctionNetworkOptimizationProblem::protected_total_variable_nodes() const {
	DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "protected_total_variable_nodes", "This object must be finalized before this function is called!" );
	return total_variable_nodes_;
}

/// @brief Access the  indices of variable nodes, and the number of choices
/// (a vector of pairs, sorted by node index).
/// @details The finalize() function must be called before this function is used.
std::vector< std::pair< masala::base::Size, masala::base::Size > > const &
CostFunctionNetworkOptimizationProblem::protected_n_choices_at_variable_nodes() const {
	DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "protected_n_choices_at_variable_nodes", "This object must be finalized before this function is called!" );
	return n_choices_at_variable_nodes_;
}


} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
