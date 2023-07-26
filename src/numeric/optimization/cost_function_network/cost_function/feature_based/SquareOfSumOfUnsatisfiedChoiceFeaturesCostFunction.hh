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

/// @file src/numeric/optimization/cost_function_network/cost_function/feature_based/SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction.hh
/// @brief Header for the SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunctions class.
/// @details SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunctions define a penalty function which is based on the following:
/// - One or more features are defined for each choice at each node.  (A feature could be a hydrogen bond
/// donor or acceptor, for instance, in a packing problem)
/// - Each feature has an expected minimum and maximum number of connections that can be set.
/// - For each pair of choices, the features that are connected can be set.
/// - At calculation time, the SQUARE OF THE number of unsatisfied features (total features minus features
/// satisfied by connections) is returned.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/SumOfUnsatisfiedChoiceFeaturesCostFunction.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.fwd.hh>

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
namespace feature_based {

/// @brief A class for SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunctions.
/// @details SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunctions define a penalty function which is based on the following:
/// - One or more features are defined for each choice at each node.  (A feature could be a hydrogen bond
/// donor or acceptor, for instance, in a packing problem)
/// - Each feature has an expected minimum and maximum number of connections that can be set.
/// - For each pair of choices, the features that are connected can be set.
/// - At calculation time, the SQUARE OF THE number of unsatisfied features (total features minus features
/// satisfied by connections) is returned.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction : public masala::numeric::optimization::cost_function_network::cost_function::feature_based::SumOfUnsatisfiedChoiceFeaturesCostFunction {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction() = default;

	/// @brief Copy constructor.
	SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction(
		SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction const & src
	);

	// @brief Assignment operator.
	SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction &
	operator=( SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction const & src );

	/// @brief Destructor.
	~SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction() override = default;

	/// @brief Return a shared pointer to a copy of this object.
	CostFunctionSP clone() const override;

	/// @brief Deep-clone all data stored in this class.
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
	/// @returns { "optimization_problem", "cost_function", "numeric", "not_pairwise_decomposible", "unsatisfied_choice_feature_sum_based" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Return the name of this class ("SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction").
	std::string class_name() const override;

	/// @brief Return the namespace of this class ("masala::numeric::optimization::cost_function_network::cost_function::feature_based");
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get an object describing the API for this object.
	/// @details Default implementation returns nullptr.  May be overridden by
	/// derived objects.
	/// @note This is a weak pointer rather than a shared pointer since the
	/// original object is expected to hold on to its API definition (which includes
	/// funciton pointers to the functions of the instance).  Querying whether the
	/// weak pointer can be converted to a shared pointer serves on a check as to
	/// whether it is safe to use the function pointers.  Not ideal, but better than
	/// nothing.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

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
	/// @note No mutex-locking is performed!
	masala::base::Real
	compute_cost_function(
		std::vector< masala::base::Size > const & candidate_solution
	) const override;

	/// @brief Given an old selection of choices at variable nodes and a new selection,
	/// compute the cost function difference.
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
	/// @details Throws if src is not a SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction.
	void assign_mutex_locked( CostFunction const & src ) override;

	/// @brief Make this object fully independent.  Assumes mutex was already locked.
	/// Should be called by overrides.
	void
	make_independent_mutex_locked() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

}; // class SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction_hh