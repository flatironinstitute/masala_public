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

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Constructor that initializes from the problem description.
/// @details The problem definition is deep-cloned, and a shared pointer to
/// a copy is stored with the solution.
CostFunctionNetworkOptimizationSolution::CostFunctionNetworkOptimizationSolution(
    CostFunctionNetworkOptimizationProblem const & problem_in
) :
    masala::numeric::optimization::OptimizationSolution(),
    problem_( problem_in.deep_clone() )
{}


/// @brief Make a fully independent copy of this object.
CostFunctionNetworkOptimizationSolutionSP
CostFunctionNetworkOptimizationSolution::deep_clone() const {
    CostFunctionNetworkOptimizationSolutionSP new_problem( masala::make_shared< CostFunctionNetworkOptimizationSolution >( *this ) );
    new_problem->make_independent();
    return new_problem;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
CostFunctionNetworkOptimizationSolution::make_independent() {
    masala::numeric::optimization::OptimizationSolution::make_independent();
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "CostFunctionNetworkOptimizationSolution" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
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
    return "CostFunctionNetworkOptimizationSolution";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkOptimizationSolution::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkOptimizationSolution class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkOptimizationSolution::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( solution_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The CostFunctionNetworkOptimizationSolution class stores the solution to a numerical "
                "cost function optimization problem.  This is the problem reduced to numbers, with no "
                "chemical classes or concepts included.",
                false
            )
        );

        // Constructors:

        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < CostFunctionNetworkOptimizationSolution > > (
                class_name(),
                "Creates an empty CostFunctionNetworkOptimizationSolution."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < CostFunctionNetworkOptimizationSolution, CostFunctionNetworkOptimizationProblem const & > > (
                class_name(),
                "Initialization constructor: initialize the solution from the problem definition.  (The problem definition "
                "deep-cloned and stored for future reference).",
                "problem_in", "The problem definition.  Copied but otherwise unaltered by this operation."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < CostFunctionNetworkOptimizationSolution, CostFunctionNetworkOptimizationSolution const & > > (
                class_name(),
                "Copy constructor: copies an input CostFunctionNetworkOptimizationSolution.",
                "src", "The input CostFunctionNetworkOptimizationSolution to copy.  Unaltered by this operation."
            )
        );

        // Work functions:

        // Getters:

        // Setters:

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
