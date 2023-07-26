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

/// @file src/numeric/optimization/cost_function_network/cost_function/ChoicePenaltySumBasedCostFunction.hh
/// @brief Header for a pure virtual base class for ChoicePenaltySumBasedCostFunctions.
/// @details ChoicePenaltySumBasedCostFunctions define a penalty function which is based on the following:
/// - A penalty is assigned to each choice.
/// - The selected choices' penalties are summed, and a constant is added.
/// - An R->R (nonlinear) function is applied to the sum, and this is returned as the penalty.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_ChoicePenaltySumBasedCostFunction_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_ChoicePenaltySumBasedCostFunction_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/cost_function/ChoicePenaltySumBasedCostFunction.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.hh>

// Numeric headers:

// Base headers:
#include <base/types.hh>
#include <base/hash_types.hh>

// STL headers:
#include <unordered_map>
#include <utility> //For std::pair.

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

/// @brief A pure virtual base class for ChoicePenaltySumBasedCostFunctions.
/// @details ChoicePenaltySumBasedCostFunctions define a penalty function which is based on the following:
/// - A penalty is assigned to each choice.
/// - The selected choices' penalties are summed, and a constant is added.
/// - An R->R (nonlinear) function is applied to the sum, and this is returned as the penalty.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T >
class ChoicePenaltySumBasedCostFunction : public masala::numeric::optimization::cost_function_network::cost_function::CostFunction {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	ChoicePenaltySumBasedCostFunction() = default;

	/// @brief Copy constructor.
	ChoicePenaltySumBasedCostFunction(
		ChoicePenaltySumBasedCostFunction<T> const & src
	);

	// @brief Assignment operator.
	ChoicePenaltySumBasedCostFunction<T> &
	operator=( ChoicePenaltySumBasedCostFunction<T> const & src );

	/// @brief Destructor.
	~ChoicePenaltySumBasedCostFunction() override = default;

	/// @brief This class is pure virtual, and does not define the clone function.
	CostFunctionSP clone() const override = 0;

	/// @brief This class is pure virtual, and does not define the make independent function.
	void make_independent() override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// cost functions; may be overridden by derived classes.
	/// @returns { { "CostFunction" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the category for this MasalaDataRepresentation.
	/// @returns { { "CostFunction" } }.
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
	/// is compatible.
	/// @returns {"standard_masala_plugins::optimizers::cost_function_network::MonteCarloCostFunctionNetworkOptimizer"}.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the properties of this MasalaDataRepresentation.
	/// @returns { "choice_penalty_sum_based", "cost_function", "not_pairwise_decomposible" }.
	std::vector< std::string >
	get_present_data_representation_properties() const override;

	/// @brief Get the absent properties of this MasalaDataRepresentation.  This is of course a
	/// non-exhaustive list.
	/// @returns { "pairwise_decomposible" }.
	std::vector< std::string >
	get_absent_data_representation_properties() const override;

	/// @brief Get the keywords for this plugin class.
	/// @returns { "optimization_problem", "cost_function", "numeric", "choice_penalty_sum_based", "not_pairwise_decomposible" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief This class is pure virtual, and does not define the name function.
	std::string class_name() const override = 0;

	/// @brief This class is pure virtual, and does not define the namespace function.
	std::string class_namespace() const override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the penalties for all of the choices at one node.
	/// @param[in] absolute_node_index The absolute index of the node for which we're setting penalties.
	/// @param[in] penalties_by_choice_index The penalties for all of the choices, indexed by choice index.
	/// @note Only in debug mode do we check that these have not already been set.
	void
	set_penalties_for_all_choices_at_node(
		masala::base::Size const absolute_node_index,
		std::vector< T > const & penalties_by_choice_index
	);

	/// @brief Set the penalty for a choice at a node.
	/// @param[in] absolute_node_index The absolute index of the node for which we're setting penalties.
	/// @param[in] choice_index The index of the choice at this node for which we're setting penalties.
	/// @param[in] penalty_value The penalty value.
	/// @note Only in debug mode do we check that these have not already been set.
	void
	set_penalty_for_choice_at_node(
		masala::base::Size const absolute_node_index,
		masala::base::Size const choice_index,
		T const penalty_value
	);

	/// @brief Set the constant offset.
	void
	set_constant_offset(
		T const constant_offset
	);

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given a selection of choices at variable nodes, compute the cost function.
	/// @details This version just computes the sum of the penalties of the selected choices.
	/// @note No mutex-locking is performed!
	masala::base::Real
	compute_cost_function(
		std::vector< masala::base::Size > const & candidate_solution
	) const override;

	/// @brief Given an old selection of choices at variable nodes and a new selection,
	/// compute the cost function difference.
	/// @details This version just computes the difference of the sums of the penalties of the
	/// selected choices.  It isn't useful for much, and should probably not be called from other
	/// code.
	/// @note No mutex-locking is performed!
	masala::base::Real
	compute_cost_function_difference(
		std::vector< masala::base::Size > const & candidate_solution_old,
		std::vector< masala::base::Size > const & candidate_solution_new
	) const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given a selection of choices at variable nodes, compute the cost function.
	/// @details This version just computes the sum of the penalties of the selected choices.
	/// @note No mutex-locking is performed!  Also note that this version does not multiply the
	/// result by the weight, since derived classes will likely do this after applying a nonlinear
	/// function.
	T
	protected_compute_cost_function_no_weight(
		std::vector< masala::base::Size > const & candidate_solution
	) const;

	/// @brief Indicate that all data input is complete.  Performs no mutex-locking.
	/// @param[in] variable_node_indices A list of all of the absolute node indices
	/// for nodes that have more than one choice, indexed by variable node index.
	/// @details The base class function simply marks this object as finalized.  Should
	/// be overridden, and overrides should call parent class protected_finalize().
	void
	protected_finalize(
		std::vector< masala::base::Size > const & variable_node_indices
	) override;

	/// @brief Get the number of variable positions.
	/// @details Returns 0 if not finalized.
	/// @note Performs no mutex-locking!  If writing is possible, the mutex
	/// must be locked before calling this function.
	inline masala::base::Size n_variable_positions() const { return n_variable_positions_; }

	/// @brief Override of assign_mutex_locked().  Calls parent function.
	/// @details Throws if src is not a ChoicePenaltySumBasedCostFunction.
	void assign_mutex_locked( CostFunction const & src ) override;

	/// @brief Make this object fully independent.  Assumes mutex was already locked.
	/// Should be called by overrides.
	void
	make_independent_mutex_locked() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The penalties, stored as a pair of <absolute node index, choice index >.
	/// @details Used during input/write phase.  Cleared by finalize() operation.
	std::unordered_map< std::pair< masala::base::Size, masala::base::Size >, T, base::size_pair_hash > penalties_by_absolute_node_and_choice_;

	/// @brief The penalties, stored as vectors indexed first byvariable node index, then by choice index.
	/// @details Used during output/read phase.  Populated by finalize() operation.
	std::vector< std::vector< T > > penalties_by_variable_node_and_choice_;

	/// @brief The number of variable positions.
	/// @details Set by finalize() function.
	masala::base::Size n_variable_positions_ = 0;

	/// @brief A constant offset added to the sum of the penalties for the choices.
	T constant_offset_ = 0.0;

}; // class ChoicePenaltySumBasedCostFunction

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_ChoicePenaltySumBasedCostFunction_hh