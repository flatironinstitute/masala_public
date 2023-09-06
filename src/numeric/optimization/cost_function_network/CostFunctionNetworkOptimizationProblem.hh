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

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CostFunctionNetworkOptimizationProblem() = default;

	/// @brief Copy constructor.
	CostFunctionNetworkOptimizationProblem( CostFunctionNetworkOptimizationProblem const & ) = default;

	// @brief Assignment operator.
	CostFunctionNetworkOptimizationProblem &
	operator=( CostFunctionNetworkOptimizationProblem const & ) = default;

	/// @brief Destructor.
	~CostFunctionNetworkOptimizationProblem() override = default;

	/// @brief Make a fully independent copy of this object.
	CostFunctionNetworkOptimizationProblemSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
	void make_independent();

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

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset all data in this object.
	void
	reset() override;

	/// @brief Finalize problem setup: indicate that all problem setup is complete, and that
	/// the object should now be locked for read only.
	void
	finalize() override;

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

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

	/// @brief Given a candidate solution, compute the score.
	/// @details The candidate solution is expressed as a vector of choice indices, with
	/// one entry per variable position, in order of position indices.  (There may not be
	/// entries for every position, though, since not all positions have at least two choices.)
	/// @note This function does NOT lock the problem mutex.  This is only threadsafe from
	/// a read-only context.
	virtual
	masala::base::Real
	compute_absolute_score(
		std::vector< base::Size > const & candidate_solution
	) const;

	/// @brief Given a pair of candidate solutions, compute the difference in their scores.
	/// @details The candidate solution is expressed as a vector of choice indices, with
	/// one entry per variable position, in order of position indices.  (There may not be
	/// entries for every position, though, since not all positions have at least two choices.)
	/// @note This function does NOT lock the problem mutex.  This is only threadsafe from
	/// a read-only context.
	virtual
	masala::base::Real
	compute_score_change(
		std::vector< base::Size > const & old_solution,
		std::vector< base::Size > const & new_solution
	) const;

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
	virtual
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

	/// @brief Reset this object completely.  Mutex must be locked before calling.
	void protected_reset() override;

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

}; // class CostFunctionNetworkOptimizationProblem

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationProblem_hh