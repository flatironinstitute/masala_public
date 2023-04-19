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

/// @file src/numeric/optimization/cost_function_network/cost_function/SumOfUnsatisfiedChoiceFeaturesCostFunction.hh
/// @brief Header for a pure virtual base class for SumOfUnsatisfiedChoiceFeaturesCostFunctions.
/// @details SumOfUnsatisfiedChoiceFeaturesCostFunctions define a penalty function which is based on the following:
/// - One or more features are defined for each choice at each node.  (A feature could be a hydrogen bond
/// donor or acceptor, for instance, in a packing problem)
/// - Each feature has an expected minimum and maximum number of connections that can be set.
/// - For each pair of choices, the features that are connected can be set.
/// - At calculation time, the number of unsatisfied features (total features minus features
/// satisfied by connections) is returned.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_SumOfUnsatisfiedChoiceFeaturesCostFunction_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_SumOfUnsatisfiedChoiceFeaturesCostFunction_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/cost_function/SumOfUnsatisfiedChoiceFeaturesCostFunction.fwd.hh>

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

/// @brief A pure virtual base class for SumOfUnsatisfiedChoiceFeaturesCostFunctions.
/// @details SumOfUnsatisfiedChoiceFeaturesCostFunctions define a penalty function which is based on the following:
/// - One or more features are defined for each choice at each node.  (A feature could be a hydrogen bond
/// donor or acceptor, for instance, in a packing problem)
/// - Each feature has an expected minimum and maximum number of connections that can be set.
/// - For each pair of choices, the features that are connected can be set.
/// - At calculation time, the number of unsatisfied features (total features minus features
/// satisfied by connections) is returned.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T >
class SumOfUnsatisfiedChoiceFeaturesCostFunction : public masala::numeric::optimization::cost_function_network::cost_function::CostFunction {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	SumOfUnsatisfiedChoiceFeaturesCostFunction() = default;

	/// @brief Copy constructor.
	SumOfUnsatisfiedChoiceFeaturesCostFunction(
		SumOfUnsatisfiedChoiceFeaturesCostFunction<T> const & src
	);

	// @brief Assignment operator.
	SumOfUnsatisfiedChoiceFeaturesCostFunction<T> &
	operator=( SumOfUnsatisfiedChoiceFeaturesCostFunction<T> const & src );

	/// @brief Destructor.
	~SumOfUnsatisfiedChoiceFeaturesCostFunction() override = default;

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

	/// @brief Get the keywords for this plugin class.
	/// @returns { "optimization_problem", "cost_function", "numeric", "unsatisfied_choice_feature_sum_based" }
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


public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given a selection of choices at variable nodes, compute the cost function.
	/// @note No mutex-locking is performed!  Also note that this version does not multiply the
	/// result by the weight, since derived classes will likely do this after applying a nonlinear
	/// function.
	masala::base::Real
	compute_cost_function(
		std::vector< masala::base::Size > const & candidate_solution
	) const override;

	/// @brief Given an old selection of choices at variable nodes and a new selection,
	/// compute the cost function difference.
	/// @note No mutex-locking is performed!  Also note that this version does not multiply the
	/// result by the weight, since derived classes will likely do this after applying a nonlinear
	/// function.
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
	/// @details Throws if src is not a SumOfUnsatisfiedChoiceFeaturesCostFunction.
	void assign_mutex_locked( CostFunction const & src ) override;

	/// @brief Make this object fully independent.  Assumes mutex was already locked.
	/// Should be called by overrides.
	void
	make_independent_mutex_locked() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////


}; // class SumOfUnsatisfiedChoiceFeaturesCostFunction

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_SumOfUnsatisfiedChoiceFeaturesCostFunction_hh