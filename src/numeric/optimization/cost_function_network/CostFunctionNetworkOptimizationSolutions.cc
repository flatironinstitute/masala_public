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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.cc
/// @brief Implementation for CostFunctionNetworkOptimizationSolutions container class.
/// @details CostFunctionNetworkOptimizationSolutionss define a numerical optimization solution produced
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <numeric/types.hh>
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a fully independent copy of this object.
CostFunctionNetworkOptimizationSolutionsSP
CostFunctionNetworkOptimizationSolutions::deep_clone() const {
    CostFunctionNetworkOptimizationSolutionsSP new_object( masala::make_shared< CostFunctionNetworkOptimizationSolutions >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
CostFunctionNetworkOptimizationSolutions::make_independent() {
    masala::numeric::optimization::OptimizationSolutions::make_independent();
}

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
CostFunctionNetworkOptimizationSolutions::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunctionNetworkOptimizationSolutions" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "cost_function_network_optimization_solutions", "optimization_solutions", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizationSolutions::get_keywords() const {
	std::vector< std::string > outvec( masala::numeric::optimization::OptimizationSolutions::get_keywords() );
    outvec.push_back( "cost_function_network_optimization_solutions" );
    return outvec;
}

/// @brief Get the class name.
/// @returns "CostFunctionNetworkOptimizationSolutions".
std::string
CostFunctionNetworkOptimizationSolutions::class_name() const {
    return "CostFunctionNetworkOptimizationSolutions";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkOptimizationSolutions::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkOptimizationSolutions class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkOptimizationSolutions::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( solutions_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The CostFunctionNetworkOptimizationSolutions class defines a container for cost function network "
                "numerical optimization solutions.  These are the solutions reduced to numbers, with no chemical "
                "classes or concepts included.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < CostFunctionNetworkOptimizationSolutions > > (
                class_name(),
                "Creates an empty CostFunctionNetworkOptimizationSolutions container."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < CostFunctionNetworkOptimizationSolutions, CostFunctionNetworkOptimizationSolutions const & > > (
                class_name(),
                "Copy constructor: copies an input CostFunctionNetworkOptimizationSolutions container.",
                "src", "The input CostFunctionNetworkOptimizationSolutions container object to copy.  Unaltered by this operation."
            )
        );

        // Work functions:


        // Getters:


        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Resets the container, deleting all contained solutions.",
                false, true, std::bind( &CostFunctionNetworkOptimizationSolutions::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationSolutionSP > >(
                "add_optimization_solution",
                "Add a cost function network optimization solution to the list of optimization solutions that this container contains.",
                "solution_in", "The cost function network optimization solution that we are adding to the container.  Throws if this is "
                "not a cost function network optimization solution.",
                false, true, std::bind( &CostFunctionNetworkOptimizationSolutions::add_optimization_solution, this, std::placeholders::_1 )
            )
        );

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object, clearing its solution list.
void
CostFunctionNetworkOptimizationSolutions::reset() {
    masala::numeric::optimization::OptimizationSolutions::reset();
}

/// @brief Add an optimization solution to the list of optimization solutions
/// stored in this container.
/// @details Derived classes should override this to check the type of the
/// optimization solution stored.
void
CostFunctionNetworkOptimizationSolutions::add_optimization_solution(
    OptimizationSolutionSP solution_in
) {
    CHECK_OR_THROW_FOR_CLASS(
        std::dynamic_pointer_cast< CostFunctionNetworkOptimizationSolution >( solution_in ) != nullptr,
        "add_optimization_solution", "Only a CostFunctionNetworkOptimizationSolution can be added "
        "to a CostFunctionNetworkOptimizationSolutions container."
    );
    masala::numeric::optimization::OptimizationSolutions::add_optimization_solution( solution_in );
}

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
