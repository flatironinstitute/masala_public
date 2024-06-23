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

/// @file src/numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolutions.cc
/// @brief Implementations for a container for GradientBasedFunctionOptimizationSolutions.
/// @details Each GradientBasedFunctionOptimizationSolution defines a numerical loss function
/// gradient minimization solution produced by a suitable Optimizer.  It does not contain any
/// chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolutions.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ThreeInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <base/types.hh>
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolution.hh>
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>
#include <tuple>

namespace masala {
namespace numeric {
namespace optimization {
namespace gradient_based {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a copy of this object and return an owning pointer.
OptimizationSolutionsSP
GradientBasedFunctionOptimizationSolutions::clone() const {
	return masala::make_shared< GradientBasedFunctionOptimizationSolutions >( *this );
}

/// @brief Make a fully independent copy of this object.
GradientBasedFunctionOptimizationSolutionsSP
GradientBasedFunctionOptimizationSolutions::deep_clone() const {
    GradientBasedFunctionOptimizationSolutionsSP new_object( std::static_pointer_cast< GradientBasedFunctionOptimizationSolutions >( this->clone() ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
GradientBasedFunctionOptimizationSolutions::make_independent() {
    masala::numeric::optimization::OptimizationSolutions::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { { "OptimizationSolutions", "GradientBasedFunctionOptimizationSolutions" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
GradientBasedFunctionOptimizationSolutions::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationSolutions", "GradientBasedFunctionOptimizationSolutions" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "gradient_based_optimization_solutions", "optimization_solutions", "numeric" }
std::vector< std::string >
GradientBasedFunctionOptimizationSolutions::get_keywords() const {
	std::vector< std::string > outvec( masala::numeric::optimization::OptimizationSolutions::get_keywords() );
    outvec.push_back( "gradient_based_optimization_solutions" );
    return outvec;
}

/// @brief Get the class name.
/// @returns "GradientBasedFunctionOptimizationSolutions".
std::string
GradientBasedFunctionOptimizationSolutions::class_name() const {
    return "GradientBasedFunctionOptimizationSolutions";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization::gradient_based".
std::string
GradientBasedFunctionOptimizationSolutions::class_namespace() const {
    return "masala::numeric::optimization::gradient_based";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the GradientBasedFunctionOptimizationSolutions class.
masala::base::api::MasalaObjectAPIDefinitionCWP
GradientBasedFunctionOptimizationSolutions::get_api_definition() {
    using namespace masala::base::api;
    using masala::base::Size;
    using masala::base::Real;

    std::lock_guard< std::mutex > lock( solutions_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The GradientBasedFunctionOptimizationSolutions class defines a container for GradientBasedFunctionOptimizationSolutions.  "
				"Each GradientBasedFunctionOptimizationSolution defines a numerical loss function "
				"gradient minimization solution produced by a suitable Optimizer.  It does not contain any "
				"chemistry-specific concepts.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < GradientBasedFunctionOptimizationSolutions > > (
                class_name(),
                "Creates an empty GradientBasedFunctionOptimizationSolutions container."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < GradientBasedFunctionOptimizationSolutions, GradientBasedFunctionOptimizationSolutions const & > > (
                class_name(),
                "Copy constructor: copies an input GradientBasedFunctionOptimizationSolutions container.",
                "src", "The input GradientBasedFunctionOptimizationSolutions container object to copy.  Unaltered by this operation."
            )
        );

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Resets the container, deleting all contained solutions.",
                false, true, std::bind( &GradientBasedFunctionOptimizationSolutions::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationSolutionSP > >(
                "add_optimization_solution",
                "Add a cost function network optimization solution to the list of optimization solutions that this container contains.",
                "solution_in", "The cost function network optimization solution that we are adding to the container.  Throws if this is "
                "not a cost function network optimization solution.",
                false, true, std::bind( &GradientBasedFunctionOptimizationSolutions::add_optimization_solution, this, std::placeholders::_1 )
            )
        );
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::base::Size > >(
				"remove_optimization_solution", "Remove an optimization solution, by solution index.",
				"solution_index", "The index of the solution to remove.  Must be in range; throws otherwise.",
				false, false,
				std::bind( &GradientBasedFunctionOptimizationSolutions::remove_optimization_solution, this, std::placeholders::_1 )
			)
		);

        // Getters:

        // Work functions:

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object, clearing its solution list.
void
GradientBasedFunctionOptimizationSolutions::reset() {
    masala::numeric::optimization::OptimizationSolutions::reset();
}

/// @brief Add an optimization solution to the list of optimization solutions
/// stored in this container.
/// @details Derived classes should override this to check the type of the
/// optimization solution stored.
void
GradientBasedFunctionOptimizationSolutions::add_optimization_solution(
    OptimizationSolutionSP solution_in
) {
    CHECK_OR_THROW_FOR_CLASS(
        std::dynamic_pointer_cast< GradientBasedFunctionOptimizationSolution >( solution_in ) != nullptr,
        "add_optimization_solution", "Only a GradientBasedFunctionOptimizationSolution can be added "
        "to a GradientBasedFunctionOptimizationSolutions container."
    );
    masala::numeric::optimization::OptimizationSolutions::add_optimization_solution( solution_in );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace gradient_based
} // namespace optimization
} // namespace numeric
} // namespace masala
