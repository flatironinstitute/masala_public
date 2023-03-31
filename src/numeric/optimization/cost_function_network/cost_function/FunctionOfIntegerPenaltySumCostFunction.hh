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

/// @file src/numeric/optimization/cost_function_network/cost_function/FunctionOfIntegerPenaltySumCostFunction.hh
/// @brief Header for a class for FunctionOfIntegerPenaltySumCostFunctions.
/// @details FunctionOfIntegerPenaltySumCostFunctions define a penalty function which is based on the following:
/// - A signed integer penalty is assigned to each choice.
/// - The selected choices' penalties are summed, and a constant is added.
/// - An arbitrary function (I->R) is applied to the sum, and this is returned as the penalty.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_FunctionOfIntegerPenaltySumCostFunction_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_FunctionOfIntegerPenaltySumCostFunction_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/cost_function/FunctionOfIntegerPenaltySumCostFunction.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/cost_function/ChoicePenaltySumBasedCostFunction.hh>

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

/// @brief A class for FunctionOfIntegerPenaltySumCostFunctions.
/// @details FunctionOfIntegerPenaltySumCostFunctions define a penalty function which is based on the following:
/// - A signed integer penalty is assigned to each choice.
/// - The selected choices' penalties are summed, and a constant is added.
/// - An arbitrary function (I->R) is applied to the sum, and this is returned as the penalty.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class FunctionOfIntegerPenaltySumCostFunction : public masala::numeric::optimization::cost_function_network::cost_function::ChoicePenaltySumBasedCostFunction < signed long int > {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	FunctionOfIntegerPenaltySumCostFunction() = default;

	/// @brief Copy constructor.
	FunctionOfIntegerPenaltySumCostFunction(
		FunctionOfIntegerPenaltySumCostFunction const & src
	);

	// @brief Assignment operator.
	FunctionOfIntegerPenaltySumCostFunction &
	operator=( FunctionOfIntegerPenaltySumCostFunction const & src );

	/// @brief Destructor.
	~FunctionOfIntegerPenaltySumCostFunction() override = default;

	/// @brief Make a copy of this object.
	CostFunctionSP
	clone() const override;

	/// @brief Make a copy of this object that is fully independent.
	FunctionOfIntegerPenaltySumCostFunctionSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
	void make_independent() override;

public:

////////////////////////////////////////////////////////////////////////////////
// STATIC PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given a penalty function behaviour enum, get the corresponding string.
	static
	std::string
	penalty_behaviour_string_from_enum(
		PenaltyFunctionBehaviourOutsideRange const behaviour_enum
	);

	/// @brief Given a penalty function behaviour string, get the corresponding enum.
	/// @details Returns PenaltyFunctionBehaviourOutsideRange::UNDEFINED_BEHAVIOUR if the string is not recognized.
	static
	PenaltyFunctionBehaviourOutsideRange
	penalty_behaviour_enum_from_string(
		std::string const & behaviour_string
	);

	/// @brief Get all allowed behaviours as a comma-separated list.
	static
	std::string
	list_penalty_behaviours();

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

	/// @brief Get the keywords for this plugin class.
	/// @returns { "optimization_problem", "cost_function", "numeric", "choice_penalty_sum_based", "function", "integer" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the name of this class ("FunctionOfIntegerPenaltySumCostFunction").
	/// @details Static version.
	static std::string class_name_static();

	/// @brief Get the name of this class ("FunctionOfIntegerPenaltySumCostFunction").
	std::string class_name() const override;

	/// @brief Get the namespace of this class ("masala::numeric::optimization::cost_function_network::cost_function").
	/// @details Static version.
	static std::string class_namespace_static();

	/// @brief Get the namespace of this class ("masala::numeric::optimization::cost_function_network::cost_function").
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the penalty function behaviour below the range of values specified.
	PenaltyFunctionBehaviourOutsideRange
	get_penalty_function_behaviour_low() const;

	/// @brief Set the penalty function behaviour below the range of values specified, by string.
	std::string
	get_penalty_function_behaviour_low_by_string() const;

	/// @brief Set the penalty function behaviour above the range of values specified.
	PenaltyFunctionBehaviourOutsideRange
	get_penalty_function_behaviour_high() const;

	/// @brief Set the penalty function behaviour above the range of values specified, by string.
	std::string
	get_penalty_function_behaviour_high_by_string() const;

	/// @brief Access the penalty function.
	std::vector< masala::base::Real > const &
	get_penalty_function() const;

	/// @brief Get the start of the penalty range.
	/// @details If the start of the range is S, and there are N penalty
	/// values provided, then the function is defined from S to S + N - 1.
	signed long int
	get_penalty_range_start() const;

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the penalty function behaviour below the range of values specified.
	void
	set_penalty_function_behaviour_low(
		PenaltyFunctionBehaviourOutsideRange const behaviour_low
	);

	/// @brief Set the penalty function behaviour below the range of values specified, by string.
	void
	set_penalty_function_behaviour_low_by_string(
		std::string const & behaviour_low_string
	);

	/// @brief Set the penalty function behaviour above the range of values specified.
	void
	set_penalty_function_behaviour_high(
		PenaltyFunctionBehaviourOutsideRange const behaviour_high
	);

	/// @brief Set the penalty function behaviour above the range of values specified, by string.
	void
	set_penalty_function_behaviour_high_by_string(
		std::string const & behaviour_high_string
	);

	/// @brief Set penalty function in a given range of values.
	void
	set_penalty_function(
		std::vector< masala::base::Real > const & penalty_function_in
	);

	/// @brief Set the value at which the penalty range starts.
	/// @details If the start of the range is S, and there are N penalty
	/// values provided, then the function is defined from S to S + N - 1.
	void
	set_penalty_range_start(
		signed long int const range_start
	);

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given a selection of choices at variable nodes, compute the cost function.
	/// @details This version computes the sum of the selected choices plus a constant,
	/// then squares the result.
	/// @note No mutex-locking is performed!
	masala::base::Real
	compute_cost_function(
		std::vector< masala::base::Size > const & candidate_solution
	) const override;

	/// @brief Given an old selection of choices at variable nodes and a new selection,
	/// compute the cost function difference.
	/// @details This version computes the sum of the old selected choices plus a constant,
	/// then squares the result.  It repeats this for the new selected choices, then returns
	/// the difference.
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

	/// @brief Get a description of the API of this object.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Indicate that all data input is complete.  Performs no mutex-locking.
	/// @param[in] variable_node_indices A list of all of the absolute node indices
	/// for nodes that have more than one choice, indexed by variable node index.
	/// @details The base class function simply marks this object as finalized.  Should
	/// be overridden, and overrides should call parent class protected_finalize().
	void
	protected_finalize(
		std::vector< masala::base::Size > const & variable_node_indices
	) override;

	/// @brief Override of assign_mutex_locked().  Calls parent function.
	/// @details Throws if src is not a FunctionOfIntegerPenaltySumCostFunction.
	void assign_mutex_locked( CostFunction const & src ) override;

	/// @brief Make this object fully independent.  Assumes mutex was already locked.
	/// Should be called by overrides.
	void
	make_independent_mutex_locked() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Compute the tail function outside of the range of penalty values specified.
	/// @param[in] behaviour The behaviour (constant, linear, or quadratic).
	/// @param[in] x The value of the input function.
	/// @param[in] a The constant offset.
	/// @param[in] b The slope.
	/// @param[in] c The quadratic term.
	/// @details The overall equation is cx^2 + bx + a for quadratic, bx+a for linear, a for constant.
	static
	masala::base::Real
	compute_outside_range_function(
		PenaltyFunctionBehaviourOutsideRange const behaviour,
		signed long int x,
		masala::base::Real a,
		masala::base::Real b,
		masala::base::Real c
	);

	/// @brief Compute the function that maps I->R.
	masala::base::Real
	function_of_sum(
		signed long int x
	) const;

private:

////////////////////////////////////////////////////////////////////////////////
// USER-INPUT PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The start of the specified penalty range.
	signed long int penalty_range_start_ = 0;

	/// @brief The penalty values.
	std::vector< masala::base::Real > penalty_values_;

	/// @brief The penalty function behaviour below the specified range.
	PenaltyFunctionBehaviourOutsideRange behaviour_low_ = PenaltyFunctionBehaviourOutsideRange::QUADRATIC;

	/// @brief The penalty function behaviour above the specified range.
	PenaltyFunctionBehaviourOutsideRange behaviour_high_ = PenaltyFunctionBehaviourOutsideRange::QUADRATIC;

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES COMPUTED BY FINALIZATION FUNCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Parameters of penalty function outside of defined range.
	/// @details Constant functions simply use a; linear functions use bx+a; quadratic functions use cx^2+bx+a.
	masala::base::Real c_high_ = 0.0;
	masala::base::Real b_high_ = 0.0;
	masala::base::Real a_high_ = 0.0;
	masala::base::Real c_low_ = 0.0;
	masala::base::Real b_low_ = 0.0;
	masala::base::Real a_low_ = 0.0;

}; // class FunctionOfIntegerPenaltySumCostFunction

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_FunctionOfIntegerPenaltySumCostFunction_hh