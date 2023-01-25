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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/CostFunctionNetworkOptimizer.cc
/// @brief Implementation for a pure virtual base class for CostFunctionNetworkOptimizers.
/// @details CostFunctionNetworkOptimizers solve a numerical cost function network optimization
/// problem.  They have no chemical knowledge.  Cost function network problems include the packing
/// or side-chain optimization problem.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/cost_function_network/CostFunctionNetworkOptimizer.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/OptimizationProblem_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution_API.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all optimizers;
/// may be overridden by derived classes.
/// @returns { { "Optimizer", "CostFunctionNetworkOptimizer" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
CostFunctionNetworkOptimizer::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "Optimizer", "CostFunctionNetworkOptimizer" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
/// by derived classes.
/// @returns { "optimizer", "cost_function_network", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizer::get_keywords() const {
	return std::vector< std::string > {
		"optimizer",
        "cost_function_network",
		"numeric"
	};
}

/// @brief Run the optimizer on an optimization problem, and produce a solution.
/// @details Must be implemented by derived classes.
masala::numeric_api::auto_generated_api::optimization::OptimizationSolution_APICSP
CostFunctionNetworkOptimizer::run_optimizer(
    masala::numeric_api::auto_generated_api::optimization::OptimizationProblem_API const & problem
) const {
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
    CostFunctionNetworkOptimizationProblem_API const * problem_cast( dynamic_cast< CostFunctionNetworkOptimizationProblem_API const * >( &problem ) );
    CHECK_OR_THROW_FOR_CLASS(
        problem_cast != nullptr,
        "run_optimizer",
        "A problem was passed to the run_optimizer function, but it was not a cost function network optimization problem."
    );
    return run_cost_function_network_optimizer( *problem_cast );
}

} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namesapce masala
