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
/// - An arbitrary function is applied to the sum, and this is returned as the penalty.
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
/// - An arbitrary function is applied to the sum, and this is returned as the penalty.
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
	/// @returns { "optimization_problem", "cost_function", "numeric", "choice_penalty_sum_based", "quadratic", "squared" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the name of this class ("FunctionOfIntegerPenaltySumCostFunction").
	std::string class_name() const override;

	/// @brief Get the namespace of this class ("masala::numeric::optimization::cost_function_network::cost_function").
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////


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
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

}; // class FunctionOfIntegerPenaltySumCostFunction

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_FunctionOfIntegerPenaltySumCostFunction_hh