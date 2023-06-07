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

/// @file src/numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem.hh
/// @brief Header for a pure virtual base class for PairwisePrecomputedCostFunctionNetworkOptimizationProblems.
/// @details PairwisePrecomputedCostFunctionNetworkOptimizationProblems define a numerical cost function network optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.  A cost function network problem consists
/// of N nodes with D_N candidate states per node.  A solution is a selection of one state per node.  For each candidate state,
/// there is a cost (or bonus) to selecting it, and for each pair of states, there is a possible cost (or bonus) to selecting
/// both of the pair.  Additional non-pairwise constraints can be added.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_PairwisePrecomputedCostFunctionNetworkOptimizationProblem_hh
#define Masala_src_numeric_optimization_cost_function_network_PairwisePrecomputedCostFunctionNetworkOptimizationProblem_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

// Numeric headers:
#include <base/types.hh>
#include <base/hash_types.hh>

// STL headers:
#include <atomic>
#include <unordered_map>
#include <utility> //For std::pair.

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

/// @brief A pure virtual base class for PairwisePrecomputedCostFunctionNetworkOptimizationProblems.
/// @details PairwisePrecomputedCostFunctionNetworkOptimizationProblems define a numerical cost function network optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.  A cost function network problem consists
/// of N nodes with D_N candidate states per node.  A solution is a selection of one state per node.  For each candidate state,
/// there is a cost (or bonus) to selecting it, and for each pair of states, there is a possible cost (or bonus) to selecting
/// both of the pair.  Additional non-pairwise constraints can be added.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PairwisePrecomputedCostFunctionNetworkOptimizationProblem : public masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	/// @details Needs to be explicit due to use of std::atomic.
	PairwisePrecomputedCostFunctionNetworkOptimizationProblem();

	/// @brief Copy constructor.
	/// @details Needs to be explicit due to use of std::atomic.
	PairwisePrecomputedCostFunctionNetworkOptimizationProblem( PairwisePrecomputedCostFunctionNetworkOptimizationProblem const & );

	// @brief Assignment operator.
	/// @details Needs to be explicit due to use of std::atomic.
	PairwisePrecomputedCostFunctionNetworkOptimizationProblem &
	operator=( PairwisePrecomputedCostFunctionNetworkOptimizationProblem const & );

	/// @brief Destructor.
	~PairwisePrecomputedCostFunctionNetworkOptimizationProblem() override = default;

	/// @brief Make a fully independent copy of this object.
	PairwisePrecomputedCostFunctionNetworkOptimizationProblemSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "PairwisePrecomputedCostFunctionNetworkOptimizationProblem" } }
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

	/// @brief Get the name of this class.
	/// @returns "PairwisePrecomputedCostFunctionNetworkOptimizationProblem".
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

	/// @brief Get the fixed background constant offset.
	masala::base::Real
	background_constant_offset() const;

	/// @brief Get the constant offset for nodes.
	/// @details This is the sum of onebody energies for nodes that have exactly
	/// one choice, plus the twobdy energies between those nodes.
	masala::base::Real
	one_choice_node_constant_offset() const;

	/// @brief Get the total constant offset.
	/// @details This is the sum of background_constant_offset() and one_choice_node_constant_offset().
	masala::base::Real
	total_constant_offset() const;

	/// @brief Does this pariwise precomputed cost function network optimization problem have any non-pairwise
	/// components that must be computed on the fly?
	/// @details For now, returns false.  This will be implemented in the future.
	bool has_non_pairwise_scores() const;

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset all data in this object.
	void
	reset() override;

	/// @brief Indicates that problem setup is complete, locking the one- and two-node penalties
	/// and making the object read-only.
	void
	finalize() override;

	/// @brief Add onebody penalty for a choice at a node.
	/// @details If the node has not yet been listed, it's added to the n_choices_by_node_index_ map.
	/// If the number of choices at the node is currently less than the node index, the number of
	/// choices is increased.
	virtual
	void
	set_onebody_penalty(
		masala::base::Size const node_index,
		masala::base::Size const choice_index,
		masala::base::Real const penalty
	);

    /// @brief Set the two-node penalty for a particular pair of choice indices corresponding to a particular
    /// pair of node indices.
    /// @param[in] node_indices A pair of node indices.  The lower index should be first.  (This function will
    /// throw if it is not, since it makes the choice indices ambiguous).
    /// @param[in] choice_indices The corresponding pair of choice indices.  The first entry should be the choice
    /// index for the lower-numbered node, and the second should be the choice index for the higher-numbered node.
    /// @param[in] penalty The value of the two-node penalty (or, if negative, bonus).
	/// @details If a node has not yet been listed, it's added to the n_choices_by_node_index_ map.
	/// If the number of choices at the node is currently less than the node index, the number of
	/// choices is increased.
	virtual
    void
    set_twobody_penalty(
        std::pair< masala::base::Size, masala::base::Size > const & node_indices,
        std::pair< masala::base::Size, masala::base::Size > const & choice_indices,
        masala::base::Real penalty
    );

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

	/// @brief Given a candidate solution, compute the score.
	/// @details The candidate solution is expressed as a vector of choice indices, with
	/// one entry per variable position, in order of position indices.  (There may not be
	/// entries for every position, though, since not all positions have at least two choices.)
	/// @note This uses the one- and two-node penalties cached in this object to make this
	/// calculation efficient.  This function does NOT lock the problem mutex.  This is only
	/// threadsafe from a read-only context.
	masala::base::Real
	compute_absolute_score(
		std::vector< base::Size > const & candidate_solution
	) const override;

	/// @brief Given a pair of candidate solutions, compute the difference in their scores.
	/// @details The candidate solution is expressed as a vector of choice indices, with
	/// one entry per variable position, in order of position indices.  (There may not be
	/// entries for every position, though, since not all positions have at least two choices.)
	/// @note This uses the one- and two-node penalties cached in this object to make this
	/// calculation very efficient.  This function does NOT lock the problem mutex.  This is only
	/// threadsafe from a read-only context.
	masala::base::Real
	compute_score_change(
		std::vector< base::Size > const & old_solution,
		std::vector< base::Size > const & new_solution
	) const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the PairwisePrecomputedCostFunctionNetworkOptimizationProblem class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object.  Assumes mutex has been locked.
	/// @details Calls parent protected_reset().
	void protected_reset() override;

	/// @brief Indicates that problem setup is complete, locking the one- and two-node penalties
	/// and making the object read-only.  Must be called from a mutex-locked context.
	/// @details Calls parent protected_finalize().
	void protected_finalize() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Calculate the constant offset for nodes.
	/// @details This is the sum of onebody energies for nodes that have exactly
	/// one choice, plus the twobdy energies between those nodes.
	/// @note This function should be called from a mutex-locked context.  It is called from protected_finalized().
	masala::base::Real
	compute_one_choice_node_constant_offset();

	/// @brief Find all twobody energies involving one node with one choice and another node with more than
    /// one choice.  Transfer all of these to the onebody energies of the variable node, deleting the corresponding
    /// twobody energy.
	/// @note This function should be called from a mutex-locked context.  It is called from protected_finalized().
	void
	move_twobody_energies_involving_one_choice_nodes_to_onebody_for_variable_nodes();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The single-node penalties for each choice, indexed by node and then by choice index.
	/// @details Any penalty not specified is assumed to be zero.
	std::unordered_map< masala::base::Size, std::unordered_map< masala::base::Size, masala::base::Real > > single_node_penalties_;

	/// @brief The penalties for each pair of choices, indexed first by node indices (lowest first) and then
	/// by choice index (corresponding to node indices).
	std::unordered_map<
		std::pair< masala::base::Size, masala::base::Size >, //The node indices.
		std::unordered_map< std::pair< masala::base::Size, masala::base::Size >, masala::base::Real, masala::base::size_pair_hash >, //The choice indices.
		masala::base::size_pair_hash
	> pairwise_node_penalties_;

	/// @brief A constant offset for the fixed background to a problem.
	std::atomic< masala::base::Real > background_constant_offset_ = 0.0;

	/// @brief The constant offset for the nodes with one choice.
	/// @details This is the sum of onebody energies for nodes that have exactly
	/// one choice, plus the twobdy energies between those nodes.  Computed at
	/// finalize() time.
	std::atomic< masala::base::Real > one_choice_node_constant_offset_ = 0.0;

}; // class PairwisePrecomputedCostFunctionNetworkOptimizationProblem

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_PairwisePrecomputedCostFunctionNetworkOptimizationProblem_hh
