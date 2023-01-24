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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.cc
/// @brief Implementation for a pure virtual base class for CostFunctionNetworkOptimizationSolutions.
/// @details A CostFunctionNetworkOptimizationSolution contains the solution to a particular
/// CostFunctionNetworkOptimizationProblem, after it is solved by a suitable CostFunctionNetworkOptimizer.
/// It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {


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
CostFunctionNetworkOptimizationSolution::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunctionNetworkOptimizationSolution" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "optimization_solution", "cost_function_network_optimization_solution", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizationSolution::get_keywords() const {
	return std::vector< std::string > {
		"optimization_solution",
        "cost_function_network_optimization_solution",
		"numeric"
	};
}

/// @brief Get the name of this class.
/// @returns "CostFunctionNetworkOptimizationSolution".
std::string
CostFunctionNetworkOptimizationSolution::class_name() const {
    return "CostFunctionNetworkOptimizationProblem";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkOptimizationSolution::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
