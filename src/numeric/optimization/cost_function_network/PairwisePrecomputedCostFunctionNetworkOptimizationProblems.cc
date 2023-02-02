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

/// @file src/numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblems.cc
/// @brief Implementation for PairwisePrecomputedCostFunctionNetworkOptimizationProblems container class.
/// @details PairwisePrecomputedCostFunctionNetworkOptimizationProblemss define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblems.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <base/types.hh>
#include <numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem.hh>

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
PairwisePrecomputedCostFunctionNetworkOptimizationProblemsSP
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::deep_clone() const {
    PairwisePrecomputedCostFunctionNetworkOptimizationProblemsSP new_object( masala::make_shared< PairwisePrecomputedCostFunctionNetworkOptimizationProblems >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::make_independent() {
    CostFunctionNetworkOptimizationProblems::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "PairwisePrecomputedCostFunctionNetworkOptimizationProblems" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "PairwisePrecomputedCostFunctionNetworkOptimizationProblems" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "pairwise_precomputed_cost_function_network_optimization_problems",
///     "cost_function_network_optimization_problems",
///     "optimization_problems"
///     "numeric"
/// }
std::vector< std::string >
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::get_keywords() const {
	std::vector< std::string > outvec( CostFunctionNetworkOptimizationProblems::get_keywords() );
    outvec.push_back( "pairwise_precomputed_cost_function_network_optimization_problems" );
    return outvec;
}

/// @brief Get the class name.
/// @returns "PairwisePrecomputedCostFunctionNetworkOptimizationProblems".
std::string
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::class_name() const {
    return "PairwisePrecomputedCostFunctionNetworkOptimizationProblems";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the PairwisePrecomputedCostFunctionNetworkOptimizationProblems class.
masala::base::api::MasalaObjectAPIDefinitionCWP
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( problems_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The PairwisePrecomputedCostFunctionNetworkOptimizationProblems class defines a container for cost function network "
                "numerical optimization problems that have one- and two-node terms precomputed.  These are the problems reduced to "
                "numbers, with no chemical classes or concepts included.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < PairwisePrecomputedCostFunctionNetworkOptimizationProblems > > (
                class_name(),
                "Creates an empty PairwisePrecomputedCostFunctionNetworkOptimizationProblems container."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < PairwisePrecomputedCostFunctionNetworkOptimizationProblems, PairwisePrecomputedCostFunctionNetworkOptimizationProblems const & > > (
                class_name(),
                "Copy constructor: copies an input PairwisePrecomputedCostFunctionNetworkOptimizationProblems container.",
                "src", "The input PairwisePrecomputedCostFunctionNetworkOptimizationProblems container object to copy.  Unaltered by this operation."
            )
        );

        // Work functions:


        // Getters:


        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Resets the container, deleting all contained problems.",
                false, true, std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblems::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationProblemSP > >(
                "add_optimization_problem",
                "Add a cost function network optimization problem to the list of optimization problems that this container contains.",
                "problem_in", "The cost function network optimization problem that we are adding to the container.  Throws if this is "
                "not a cost function network optimization problem.",
                false, true, std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblems::add_optimization_problem, this, std::placeholders::_1 )
            )
        );

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object, clearing its problem list.
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::reset() {
    masala::numeric::optimization::OptimizationProblems::reset();
}

/// @brief Add an optimization problem to the list of optimization problems
/// stored in this container.
/// @details Derived classes should override this to check the type of the
/// optimization problem stored.
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblems::add_optimization_problem(
    OptimizationProblemSP problem_in
) {
    CHECK_OR_THROW_FOR_CLASS(
        std::dynamic_pointer_cast< PairwisePrecomputedCostFunctionNetworkOptimizationProblem >( problem_in ) != nullptr,
        "add_optimization_problem", "Only a PairwisePrecomputedCostFunctionNetworkOptimizationProblem can be added "
        "to a PairwisePrecomputedCostFunctionNetworkOptimizationProblems container."
    );
    masala::numeric::optimization::OptimizationProblems::add_optimization_problem( problem_in );
}

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
