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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.hh
/// @brief Header for a container for CostFunctionNetworkOptimizationSolutions.
/// @details CostFunctionNetworkOptimizationSolutions define a numerical optimization solution produced
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolutions_hh
#define Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolutions_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationSolutions.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.fwd.hh>

// STL headers:
#include <mutex>
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

/// @brief A container for CostFunctionNetworkOptimizationSolutions.
/// @details CostFunctionNetworkOptimizationSolutions define a numerical optimization solution produced
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunctionNetworkOptimizationSolutions : public masala::numeric::optimization::OptimizationSolutions {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CostFunctionNetworkOptimizationSolutions() = default;

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.  Copies the pointers to, but does not deep-clone,
	/// the optimization solutions.
	CostFunctionNetworkOptimizationSolutions( CostFunctionNetworkOptimizationSolutions const & ) = default;

	/// @brief Assignment operator.
	/// @details Copies the pointers to, but does not deep-clone,
	/// the optimization solutions.
	CostFunctionNetworkOptimizationSolutions &
	operator=(
		CostFunctionNetworkOptimizationSolutions const &
	) = default;

	/// @brief Destructor.
	~CostFunctionNetworkOptimizationSolutions() override = default;

	/// @brief Make a fully independent copy of this object.
	CostFunctionNetworkOptimizationSolutionsSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared
	/// (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { { "CostFunctionNetworkOptimizationSolutions" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "cost_function_network_optimization_solutions", "optimization_solutions", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the class name.
	/// @returns "CostFunctionNetworkOptimizationSolutions".
	std::string class_name() const override;

	/// @brief Get the class namespace.
	/// @returns "masala::numeric::optimization::cost_function_network".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the CostFunctionNetworkOptimizationSolutions class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object, clearing its solution list.
	void
	reset() override;

	/// @brief Add an optimization solution to the list of optimization solutions
	/// stored in this container.
	/// @details Throws if the added solution is not a CostFunctionNetworkOptimizationSolution.
	void
	add_optimization_solution(
		OptimizationSolutionSP solution_in
	) override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////


}; // class CostFunctionNetworkOptimizationSolutions

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolutions_hh