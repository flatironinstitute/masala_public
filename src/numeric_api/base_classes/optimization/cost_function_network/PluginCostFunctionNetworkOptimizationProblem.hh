/*
    Masala
    Copyright (C) 2023 Vikram K. Mulligan

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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizationProblem.hh
/// @brief Headers for a base class for PluginCostFunctionNetworkOptimizationProblems.
/// @details A PluginCostFunctionNetworkOptimizationProblem defines a special case of a numerical cost function network optimization
/// problem, defined in a plug-in library, to be solved by a suitable Optimizer.  The PluginCostFunctionNetworkOptimizationProblem
/// class does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizationProblem_hh
#define Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizationProblem_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <map>
#include <utility> //For std::pair.
#include <vector>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {

/// @brief A base class for PluginCostFunctionNetworkOptimizationProblems.
/// @details A PluginCostFunctionNetworkOptimizationProblem defines a special case of a numerical cost function network optimization
/// problem, defined in a plug-in library, to be solved by a suitable Optimizer.  The PluginCostFunctionNetworkOptimizationProblem
/// class does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginCostFunctionNetworkOptimizationProblem : public masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginCostFunctionNetworkOptimizationProblem() = default;

	/// @brief Copy constructor.
	PluginCostFunctionNetworkOptimizationProblem( PluginCostFunctionNetworkOptimizationProblem const & ) = default;

	// @brief Assignment operator.
	PluginCostFunctionNetworkOptimizationProblem &
	operator=( PluginCostFunctionNetworkOptimizationProblem const & ) = default;

	/// @brief Destructor.
	~PluginCostFunctionNetworkOptimizationProblem() override = default;

	// @brief Make a fully independent copy of this object.
	// PluginCostFunctionNetworkOptimizationProblemSP
	// deep_clone() const;

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

	/// @brief Get the name of this class.
	/// @returns "PluginCostFunctionNetworkOptimizationProblem".
	std::string
	class_name() const override = 0;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric_api::base_classes::optimization::cost_function_network".
	std::string
	class_namespace() const override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

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

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

	// @brief Given a candidate solution, compute the score.
	// @details The candidate solution is expressed as a vector of choice indices, with
	// one entry per variable position, in order of position indices.  (There may not be
	// entries for every position, though, since not all positions have at least two choices.)
	// @note This function does NOT lock the problem mutex.  This is only threadsafe from
	// a read-only context.
	// masala::base::Real
	// compute_absolute_score(
	// 	std::vector< base::Size > const & candidate_solution
	// ) const override;

	// @brief Given a pair of candidate solutions, compute the difference in their scores.
	// @details The candidate solution is expressed as a vector of choice indices, with
	// one entry per variable position, in order of position indices.  (There may not be
	// entries for every position, though, since not all positions have at least two choices.)
	// @note This function does NOT lock the problem mutex.  This is only threadsafe from
	// a read-only context.
	// masala::base::Real
	// compute_score_change(
	// 	std::vector< base::Size > const & old_solution,
	// 	std::vector< base::Size > const & new_solution
	// ) const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the PluginCostFunctionNetworkOptimizationProblem class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override = 0;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object completely.  Mutex must be locked before calling.
	void protected_reset() override;

	/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
	/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
	void protected_finalize() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

}; // class PluginCostFunctionNetworkOptimizationProblem

} // namespace cost_function_network
} // namespace optimization
} // base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizationProblem_hh