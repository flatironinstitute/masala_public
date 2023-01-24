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
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationProblem_hh
#define Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationProblem_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationProblem.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

/// @brief A pure virtual base class for CostFunctionNetworkOptimizationProblems.
/// @details CostFunctionNetworkOptimizationProblems define a numerical cost function network optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
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

	/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "CostFunctionNetworkOptimizationProblem" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outher vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

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
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the Pose class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////


}; // class CostFunctionNetworkOptimizationProblem

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationProblem_hh