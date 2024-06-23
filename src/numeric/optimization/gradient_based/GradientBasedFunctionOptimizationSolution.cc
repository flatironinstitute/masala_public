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

/// @file src/numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolution.cc
/// @brief Implementations for a pure virtual base class for a GradientBasedFunctionOptimizationSolution.
/// @details A GradientBasedFunctionOptimizationSolution contains the solution to a particular
/// GradientBasedFunctionOptimizationProblem, after it is solved by a suitable
/// GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolution.hh>

// Numeric headers:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblem.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_FiveInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace gradient_based {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a copy of this object.
masala::numeric::optimization::OptimizationSolutionSP
GradientBasedFunctionOptimizationSolution::clone() const {
    return masala::make_shared< GradientBasedFunctionOptimizationSolution >( *this );
}

/// @brief Make a fully independent copy of this object.
GradientBasedFunctionOptimizationSolutionSP
GradientBasedFunctionOptimizationSolution::deep_clone() const {
    GradientBasedFunctionOptimizationSolutionSP new_solution( std::static_pointer_cast< GradientBasedFunctionOptimizationSolution >( this->clone() ) );
    new_solution->make_independent();
    return new_solution;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
GradientBasedFunctionOptimizationSolution::make_independent() {
    masala::numeric::optimization::OptimizationSolution::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationSolution", "GradientBasedFunctionOptimizationSolution" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
GradientBasedFunctionOptimizationSolution::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationSolution", "GradientBasedFunctionOptimizationSolution" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "optimization_solution", "gradient_based_optimization_solution", "numeric" }
std::vector< std::string >
GradientBasedFunctionOptimizationSolution::get_keywords() const {
	return std::vector< std::string > {
		"optimization_solution",
        "gradient_based_optimization_solution",
		"numeric"
	};
}

/// @brief Get the name of this class.
/// @returns "GradientBasedFunctionOptimizationSolution".
std::string
GradientBasedFunctionOptimizationSolution::class_name() const {
    return "GradientBasedFunctionOptimizationSolution";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::gradient_based".
std::string
GradientBasedFunctionOptimizationSolution::class_namespace() const {
    return "masala::numeric::optimization::gradient_based";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the GradientBasedFunctionOptimizationSolution class.
masala::base::api::MasalaObjectAPIDefinitionCWP
GradientBasedFunctionOptimizationSolution::get_api_definition() {
    using namespace masala::base::api;
    using base::Real;
    using base::Size;

    std::lock_guard< std::mutex > lock( solution_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "A GradientBasedFunctionOptimizationSolution contains the solution to a particular "
				"GradientBasedFunctionOptimizationProblem, after it is solved by a suitable "
				"GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < GradientBasedFunctionOptimizationSolution > > (
                class_name(),
                "Creates an empty GradientBasedFunctionOptimizationSolution."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < GradientBasedFunctionOptimizationSolution, GradientBasedFunctionOptimizationSolution const & > > (
                class_name(),
                "Copy constructor: copies an input GradientBasedFunctionOptimizationSolution.",
                "src", "The input GradientBasedFunctionOptimizationSolution to copy.  Unaltered by this operation."
            )
        );

        // Work functions:

        // Getters:

        // Setters:

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
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
