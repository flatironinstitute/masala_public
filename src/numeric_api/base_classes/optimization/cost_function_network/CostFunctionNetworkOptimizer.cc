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
#include <numeric_api/auto_generated_api/optimization/OptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions_API.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>

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

/// @brief Categories for engines.
/// @details Like plugin categories, engine categories are hierarchical.  The hieraruchy
/// is important for deciding what engines are equvalent. For instance, if I had
/// "Solver"->"KinematicSolver"->"AnalyticKinematicSolver", I could request only the analytic
/// kinematic solvers, all kinematic solvers, or all solvers in general.
/// @note An engine may exist in more than one hierarchical category.  The outer vector is
/// a list of hierarchical categories, and the inner vector is the particular hierarchical
/// category, from most general to most specific.  Also note that this function is pure
/// virtual, and must be defined for instantiable MasalaEngine subclasses.
/// @returns { {"Optimizer", "CostFunctionNetworkOptimizer"} }
std::vector< std::vector < std::string > >
CostFunctionNetworkOptimizer::get_engine_categories() const {
    return std::vector< std::vector < std::string > >{ { "Optimizer", "CostFunctionNetworkOptimizer" } };
}

/// @brief Keywords for engines.
/// @returns { "optimizer", "cost_function_network", "numeric" }
std::vector < std::string >
CostFunctionNetworkOptimizer::get_engine_keywords() const {
    return std::vector< std::string > {
		"optimizer",
        "cost_function_network",
		"numeric"
	};
}

/// @brief Run the optimizer on a set of optimization problems, and produce a set of solutions.
/// @details Must be implemented by derived classes.   Each solutions set in the vector of solutions corresponds to
/// the problem with the same index.
std::vector< masala::numeric_api::auto_generated_api::optimization::OptimizationSolutions_APICSP >
CostFunctionNetworkOptimizer::run_optimizer(
    masala::numeric_api::auto_generated_api::optimization::OptimizationProblems_API const & problems
) const {
    using namespace masala::numeric_api::auto_generated_api::optimization;
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
    CostFunctionNetworkOptimizationProblems_API const * problems_cast( dynamic_cast< CostFunctionNetworkOptimizationProblems_API const * >( &problems ) );
    CHECK_OR_THROW_FOR_CLASS(
        problems_cast != nullptr,
        "run_optimizer",
        "A set of optimization problems was passed to the run_optimizer function, but it was not "
        "a set of cost function network optimization problems."
    );

    std::vector< CostFunctionNetworkOptimizationSolutions_APICSP > const outvec1( run_cost_function_network_optimizer( *problems_cast ) );

    // Conversion to base class pointers requires another step, irritatingly:
    std::vector< OptimizationSolutions_APICSP > outvec2( outvec1.size() );
    for( base::Size i(0), imax(outvec1.size()); i<imax; ++i ) {
        outvec2[i] = outvec1[i];
    }

    return outvec2;
}

} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
