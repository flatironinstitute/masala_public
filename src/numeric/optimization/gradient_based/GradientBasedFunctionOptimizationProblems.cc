/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblems.cc
/// @brief Implementations for a container for GradientBasedFunctionOptimizationProblems.
/// @details Each GradientBasedFunctionOptimizationProblem defines a numerical gradient-descent
/// minimization problem for an arbitrary loss function.  They do not contain any chemistry-specific
/// concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblems.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <base/types.hh>
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace gradient_based {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a fully independent copy of this object.
GradientBasedFunctionOptimizationProblemsSP
GradientBasedFunctionOptimizationProblems::deep_clone() const {
    GradientBasedFunctionOptimizationProblemsSP new_object( masala::make_shared< GradientBasedFunctionOptimizationProblems >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
GradientBasedFunctionOptimizationProblems::make_independent() {
    masala::numeric::optimization::OptimizationProblems::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationProblems", "GradientBasedFunctionOptimizationProblems" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
GradientBasedFunctionOptimizationProblems::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblems", "GradientBasedFunctionOptimizationProblems" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "gradient_based_optimization_problems", "optimization_problems", "numeric" }
std::vector< std::string >
GradientBasedFunctionOptimizationProblems::get_keywords() const {
	std::vector< std::string > outvec( masala::numeric::optimization::OptimizationProblems::get_keywords() );
    outvec.push_back( "gradient_based_optimization_problems" );
    return outvec;
}

/// @brief Get the class name.
/// @returns "GradientBasedFunctionOptimizationProblems".
std::string
GradientBasedFunctionOptimizationProblems::class_name() const {
    return "GradientBasedFunctionOptimizationProblems";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization::gradient_based".
std::string
GradientBasedFunctionOptimizationProblems::class_namespace() const {
    return "masala::numeric::optimization::gradient_based";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the GradientBasedFunctionOptimizationProblems class.
masala::base::api::MasalaObjectAPIDefinitionCWP
GradientBasedFunctionOptimizationProblems::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( problems_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The GradientBasedFunctionOptimizationProblems class defines a container for "
				"GradientBasedFunctionOptimizationProblem instances.  Each GradientBasedFunctionOptimizationProblem "
				"defines a numerical gradient-descent minimization problem for an arbitrary loss function.  They "
				"do not contain any chemistry-specific concepts.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < GradientBasedFunctionOptimizationProblems > > (
                class_name(),
                "Creates an empty GradientBasedFunctionOptimizationProblems container."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < GradientBasedFunctionOptimizationProblems, GradientBasedFunctionOptimizationProblems const & > > (
                class_name(),
                "Copy constructor: copies an input GradientBasedFunctionOptimizationProblems container.",
                "src", "The input GradientBasedFunctionOptimizationProblems container object to copy.  Unaltered by this operation."
            )
        );

        // Work functions:


        // Getters:


        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Resets the container, deleting all contained problems.",
                false, true, std::bind( &GradientBasedFunctionOptimizationProblems::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationProblemSP > >(
                "add_optimization_problem",
                "Add a cost function network optimization problem to the list of optimization problems that this container contains.",
                "problem_in", "The gradient-descent loss function minimization optimization problem that we are adding to the container.  Throws if this is "
                "not a gradient descent based optimization problem.",
                false, true, std::bind( &GradientBasedFunctionOptimizationProblems::add_optimization_problem, this, std::placeholders::_1 )
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
GradientBasedFunctionOptimizationProblems::reset() {
    masala::numeric::optimization::OptimizationProblems::reset();
}

/// @brief Add an optimization problem to the list of optimization problems
/// stored in this container.
/// @details Derived classes should override this to check the type of the
/// optimization problem stored.
void
GradientBasedFunctionOptimizationProblems::add_optimization_problem(
    OptimizationProblemSP problem_in
) {
    CHECK_OR_THROW_FOR_CLASS(
        std::dynamic_pointer_cast< GradientBasedFunctionOptimizationProblem >( problem_in ) != nullptr,
        "add_optimization_problem", "Only a GradientBasedFunctionOptimizationProblem can be added "
        "to a GradientBasedFunctionOptimizationProblems container."
    );
    masala::numeric::optimization::OptimizationProblems::add_optimization_problem( problem_in );
}

} // namespace gradient_based
} // namespace optimization
} // namespace numeric
} // namespace masala
