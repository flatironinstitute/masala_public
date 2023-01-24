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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.hh
/// @brief Header for a pure virtual base class for CostFunctionNetworkOptimizationSolutions.
/// @details A CostFunctionNetworkOptimizationSolution contains the solution to a particular
/// CostFunctionNetworkOptimizationProblem, after it is solved by a suitable CostFunctionNetworkOptimizer.
/// It does not contain any chemistry-specific concepts.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric__optimization_cost_function_network_CostFunctionNetworkOptimizationSolution_hh
#define Masala_src_numeric__optimization_cost_function_network_CostFunctionNetworkOptimizationSolution_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationSolution.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {


/// @brief A pure virtual base class for CostFunctionNetworkOptimizationSolutions.
/// @details A CostFunctionNetworkOptimizationSolution contains the solution to a particular
/// CostFunctionNetworkOptimizationProblem, after it is solved by a suitable CostFunctionNetworkOptimizer.
/// It does not contain any chemistry-specific concepts.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunctionNetworkOptimizationSolution : public masala::numeric_api::base_classes::optimization::OptimizationSolution {

public:

	/// @brief Default constructor.
	CostFunctionNetworkOptimizationSolution() = default;

	/// @brief Copy constructor.
	CostFunctionNetworkOptimizationSolution( CostFunctionNetworkOptimizationSolution const & ) = default;

	/// @brief Destructor.
	~CostFunctionNetworkOptimizationSolution() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "CostFunctionNetworkOptimizationSolution" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outher vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "optimization_solution", "cost_function_network_optimization_solution", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

}; // class CostFunctionNetworkOptimizationSolution

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric__optimization_cost_function_network_CostFunctionNetworkOptimizationSolution_hh