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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh
/// @brief Header for a pure virtual base class for CostFunctionNetworkOptimizationProblems.
/// @details CostFunctionNetworkOptimizationProblems define a numerical cost function network optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.  A cost function network problem consists
/// of N nodes with D_N candidate states per node.  A solution is a selection of one state per node.  For each candidate state,
/// there is a cost (or bonus) to selecting it, and for each pair of states, there is a possible cost (or bonus) to selecting
/// both of the pair.  Additional non-pairwise constraints can be added.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationProblem_hh
#define Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationProblem_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationProblem.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.fwd.hh>
#include <numeric/optimization/cost_function_network/CFNProblemScratchSpace.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <map>
#include <utility> //For std::pair.
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

/// @brief A pure virtual base class for CostFunctionNetworkOptimizationProblems.
/// @details CostFunctionNetworkOptimizationProblems define a numerical cost function network optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.  A cost function network problem consists
/// of N nodes with D_N candidate states per node.  A solution is a selection of one state per node.  For each candidate state,
/// there is a cost (or bonus) to selecting it, and for each pair of states, there is a possible cost (or bonus) to selecting
/// both of the pair.  Additional non-pairwise constraints can be added.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunctionNetworkOptimizationProblem : public masala::numeric::optimization::OptimizationProblem {

	typedef masala::numeric::optimization::OptimizationProblem Parent;
	typedef masala::numeric::optimization::OptimizationProblemSP ParentSP;
	typedef masala::numeric::optimization::OptimizationProblemCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CostFunctionNetworkOptimizationProblem() = default;

	/// @brief Copy constructor.
	CostFunctionNetworkOptimizationProblem( CostFunctionNetworkOptimizationProblem const & src );

	// @brief Assignment operator.
	CostFunctionNetworkOptimizationProblem &
	operator=( CostFunctionNetworkOptimizationProblem const & src );

	/// @brief Destructor.
	~CostFunctionNetworkOptimizationProblem() override = default;

	/// @brief Make a copy of this object, and return a shared pointer to the copy.
	/// @details Does NOT copy all the internal data, but retains pointers to existing data.
	ParentSP
	clone() const override;

	/// @brief Make a fully independent copy of this object.
	CostFunctionNetworkOptimizationProblemSP
	deep_clone() const;

public:

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
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "numeric" }
	std::vector< std::string >
	get_keywords() const override;
	
	/// @brief Get the category for this MasalaDataRepresentation.
	/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem" } }.
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the keywords that this data representation plugin has.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "numeric" }
	std::vector< std::string >
	get_data_representation_keywords() const override;

	/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
	/// is compatible.
	/// @returns An empty list.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the properties of this MasalaDataRepresentation.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem" }.
	std::vector< std::string >
	get_present_data_representation_properties() const override;

	/// @brief Get the name of this class.
	/// @returns "CostFunctionNetworkOptimizationProblem".
	std::string
	class_name() const override;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric::optimization::cost_function_network".
	std::string
	class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the total number of nodes in this problem.
	/// @details This is the index of the highest-numbered node that has been
	/// referred to plus one (since nodes are zero-indexed), NOT the number of
	/// nodes with multiple choices.
	masala::base::Size
	total_nodes() const;

	/// @brief Get the total number of nodes in this problem that have at least
	/// two choices associated with them.
	masala::base::Size
	total_variable_nodes() const;

	/// @brief Get a map with one entry for each node (variable or not), where the key is
	/// the node's global index, and the value is the number of choices at that node.
	/// @note Keys in this map are node indices, since nodes with fewer than two choices are included.
	/// The length of the vector is total_nodes().
	std::map< masala::base::Size, masala::base::Size > const &
	n_choices_at_all_nodes() const;

	/// @brief Get a vector of pairs with one entry for each variable node, where the first entry in the pair indicates
	/// the variable node's index, and the second indicates the number of choices at that node.
	/// @note Indices in this vector are NOT node indices, since nodes with fewer than two choices are omitted.
	/// The length of the vector is total_variable_nodes(), not total_nodes().  This vector is guaranteed to be sorted
	/// in order of node index, though.
	std::vector< std::pair< masala::base::Size, masala::base::Size > >
	n_choices_at_variable_nodes() const;

	/// @brief Get the product of the number of choices at each node (the total number
	/// of combinatorial solutions to this cost function network problem).
	/// @note Due to integer overruns, this is a floating-point number, not an integer.
	masala::base::Real
	total_combinatorial_solutions() const;

	/// @brief Does this object have candidate starting solutions?  These can be used as starting points for
	/// some optimizers, or can be ignored.
	bool
	has_candidate_starting_solutions() const;

	/// @brief Get the optional vector of vectors of solutions to this CFN problem.  These can be used as starting points for
	/// some optimizers, or can be ignored.
	std::vector< std::vector< masala::base::Size > > const &
	candidate_starting_solutions() const;

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the (minimum) number of choices at a node.
    /// @details If the number of choices has already been set to greater than the
    /// specified number, this does nothing.
	void
	set_minimum_number_of_choices_at_node(
		masala::base::Size const node_index,
		masala::base::Size const min_choice_count
	);

	/// @brief Add a (non-quadratic) cost function.
	/// @details Stores the object directly; does not clone it.  The CostFunctionNetworkOptimizationProblem
	/// must not yet be finalized.
	void
	add_cost_function(
		masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP cost_function
	);

	/// @brief Add a candidate solution.
	/// @details Locks problem mutex; throws if the problem has already been finalized.
	void
	add_candidate_solution(
		std::vector< masala::base::Size > const & candidate_solution_in
	);

	/// @brief Remove all candidate solutions.
	/// @details Locks problem mutex; throws if the problem has already been finalized.
	void clear_candidate_solutions();

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

	/// @brief Generate a cost function network optimization problem scratch space for this object.
	/// @details Should include scratch spaces for those cost functions that take them.  Must be implemented by derived
	/// classes: base class implementation throws.  Should call protected_add_cost_function_scratch_spaces(), and then
	/// should call finalize() on the generated object.
	virtual
	CFNProblemScratchSpaceSP
	generate_cfn_problem_scratch_space() const;

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
	/// @param[in] candidate_solution The candidate solution, expressed as a vector of choice indices,
	/// indexed by variable node index.
	/// @param[in] cfn_problem_scratch_space Nullptr or a pointer to a mutable object that can be used
	/// to cache parts of the calcuation for faster recalcualtion on repeeated evaluation.
	virtual
	masala::base::Real
	compute_non_approximate_absolute_score(
		std::vector< base::Size > const & candidate_solution,
		CFNProblemScratchSpace * cfn_problem_scratch_space
	) const;

	/// @brief Given a candidate solution, compute the data representation score (which
	/// may be approximate).
	/// @details The candidate solution is expressed as a vector of choice indices, with
	/// one entry per variable position, in order of position indices.  (There may not be
	/// entries for every position, though, since not all positions have at least two choices.)
	/// @note This function does NOT lock the problem mutex.  This is only threadsafe from
	/// a read-only context.
	/// @param[in] candidate_solution The candidate solution, expressed as a vector of choice indices,
	/// indexed by variable node index.
	/// @param[in] cfn_problem_scratch_space Nullptr or a pointer to a mutable object that can be used
	/// to cache parts of the calcuation for faster recalcualtion on repeeated evaluation.
	virtual
	masala::base::Real
	compute_absolute_score(
		std::vector< base::Size > const & candidate_solution,
		CFNProblemScratchSpace * cfn_problem_scratch_space
	) const;

	/// @brief Given a pair of candidate solutions, compute the difference in their scores.
	/// This is the difference in the data representation scores (which may be an approximation
	/// of the actual scores).
	/// @details The candidate solution is expressed as a vector of choice indices, with
	/// one entry per variable position, in order of position indices.  (There may not be
	/// entries for every position, though, since not all positions have at least two choices.)
	/// @note This function does NOT lock the problem mutex.  This is only threadsafe from
	/// a read-only context.
	/// @param[in] old_solution The previous candidate solution, expressed as a vector of choice indices,
	/// indexed by variable node index.
	/// @param[in] new_solution The current candidate solution, expressed as a vector of choice indices,
	/// indexed by variable node index.
	/// @param[in] cfn_problem_scratch_space Nullptr or a pointer to a mutable object that can be used
	/// to cache parts of the calcuation for faster recalcualtion on repeeated evaluation.
	virtual
	masala::base::Real
	compute_score_change(
		std::vector< base::Size > const & old_solution,
		std::vector< base::Size > const & new_solution,
		CFNProblemScratchSpace * cfn_problem_scratch_space
	) const;

	/// @brief Create a solutions container for this type of optimization problem.
	/// @details Base class implementation creates a generic OptimizationSolutions container.
	/// This override creates a CostFunctionNetworkOptimizationSolutions container.
	OptimizationSolutionsSP
	create_solutions_container() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the CostFunctionNetworkOptimizationProblem class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the (minimum) number of choices at a node.
	/// @details If the number of choices has already been set to greater than the
	/// specified number, this does nothing.
	/// @note This version assumes that the problem mutex has already been set.
	void
	set_minimum_number_of_choices_at_node_mutex_locked(
		masala::base::Size const node_index,
		masala::base::Size const min_choice_count
	);

	/// @brief Add a (non-quadratic) cost function.
	/// @details Stores the object directly; does not clone it.  The CostFunctionNetworkOptimizationProblem
	/// must not yet be finalized.  This version assumes that the mutex for this object has already been locked.
	void
	add_cost_function_mutex_locked(
		masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP const & cost_function
	);

	/// @brief Add a candidate solution.
	/// @details Does not lock problem mutex; throws if the problem has already been finalized.
	void
	add_candidate_solution_mutex_locked(
		std::vector< masala::base::Size > const & candidate_solution_in
	);

	/// @brief Remove all candidate solutions.
	/// @details Does not lock problem mutex; throws if the problem has already been finalized.
	void clear_candidate_solutions_mutex_locked();

	/// @brief Access the number of choices by node index.
	/// @note This assumes that the problem mutex has already been set.
	std::map< masala::base::Size, masala::base::Size > &
	n_choices_by_node_index();

	/// @brief Const access to the number of choices by node index.
	/// @note This assumes that the problem mutex has already been set.
	inline
	std::map< masala::base::Size, masala::base::Size > const &
	n_choices_by_node_index_const() const {
		return n_choices_by_node_index_;
	}

	/// @brief Is this data representation empty?
	/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
	/// @returns True if no data have been loaded into this data representation, false otherwise.
	/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
	bool protected_empty() const override;

	/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
	/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
	void protected_clear() override;

	/// @brief Reset this object completely.  Mutex must be locked before calling.
	void protected_reset() override;

	/// @brief Make this object independent.
	/// @details Assumes mutex was already locked.
	/// @note Derived versions of this function should call the parent class version too.
	void protected_make_independent() override;

	/// @brief Inner workings of assignment operator.  Should be called with locked mutex.
	/// Should be implemented by derived classes, which shoudl call base class function.
	void protected_assign( masala::base::managers::engine::MasalaDataRepresentation const & src ) override;

	/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
	/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
	void protected_finalize() override;

	/// @brief Access the total number of variable nodes, precomputed by finalize() and cached.
	/// @details The finalize() function must be called before this function is used.
	masala::base::Size protected_total_variable_nodes() const;

	/// @brief Access the indices of variable nodes, and the number of choices
	/// (a vector of pairs, sorted by node index).
	/// @details The finalize() function must be called before this function is used.
	std::vector< std::pair< masala::base::Size, masala::base::Size > > const &
	protected_n_choices_at_variable_nodes() const;

	/// @brief Const iterators over the set of cost functions.  Starting iterator.
	inline
	std::vector< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP >::const_iterator
	cost_functions_begin() const {
		return cost_functions_.cbegin();
	}

	/// @brief Const iterators over the set of cost functions.  Ending iterator.
	inline
	std::vector< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP >::const_iterator
	cost_functions_end() const {
		return cost_functions_.cend();
	}

	/// @brief Const access to the vector of cost functions.
	inline
	std::vector< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP > const &
	cost_functions() const {
		return cost_functions_;
	}

	/// @brief Given a CFN problem scratch space, add scratch spaces for all of this problem's cost functions.
	/// @param[inout] cfn_problem_scratch_space The object to which we're adding scratch spaces for cost functinos.
	void
	protected_add_cost_function_scratch_spaces(
		CFNProblemScratchSpace & cfn_problem_scratch_space
	) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The number of choices at each node index.
	/// @details Resizes automatically.
	std::map< masala::base::Size, masala::base::Size > n_choices_by_node_index_;

	/// @brief The total number of variable nodes, populated by the finalize() function.
	masala::base::Size total_variable_nodes_ = 0;

	/// @brief The indices of variable nodes, and the number of choices (a vector of pairs, sorted
	/// by node index).
	/// @details Cached by the finalize() function.
	std::vector< std::pair< masala::base::Size, masala::base::Size > > n_choices_at_variable_nodes_;

	/// @brief A set of CostFunctions to impose.  The overall cost function is the sum of all of these.
	std::vector< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP > cost_functions_;

	/// @brief An optional vector of vectors of solutions to this CFN problem.  These can be used as starting points for
	/// some optimizers, or can be ignored.
	std::vector< std::vector< masala::base::Size > > candidate_starting_solutions_;

}; // class CostFunctionNetworkOptimizationProblem

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationProblem_hh