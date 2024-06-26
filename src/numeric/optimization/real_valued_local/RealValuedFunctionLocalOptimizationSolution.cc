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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution.cc
/// @brief Implementations for a pure virtual base class for a RealValuedFunctionLocalOptimizationSolution.
/// @details A RealValuedFunctionLocalOptimizationSolution contains the solution to a particular
/// RealValuedFunctionLocalOptimizationProblem, after it is solved by a suitable
/// GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution.hh>

// Numeric headers:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.hh>

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
namespace real_valued_local {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a copy of this object.
masala::numeric::optimization::OptimizationSolutionSP
RealValuedFunctionLocalOptimizationSolution::clone() const {
    return masala::make_shared< RealValuedFunctionLocalOptimizationSolution >( *this );
}

/// @brief Make a fully independent copy of this object.
RealValuedFunctionLocalOptimizationSolutionSP
RealValuedFunctionLocalOptimizationSolution::deep_clone() const {
    RealValuedFunctionLocalOptimizationSolutionSP new_solution( std::static_pointer_cast< RealValuedFunctionLocalOptimizationSolution >( this->clone() ) );
    new_solution->make_independent();
    return new_solution;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
RealValuedFunctionLocalOptimizationSolution::make_independent() {
    masala::numeric::optimization::OptimizationSolution::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationSolution", "RealValuedFunctionLocalOptimizationSolution" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
RealValuedFunctionLocalOptimizationSolution::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationSolution", "RealValuedFunctionLocalOptimizationSolution" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "optimization_solution", "local", "real_valued", "numeric" }
std::vector< std::string >
RealValuedFunctionLocalOptimizationSolution::get_keywords() const {
	return std::vector< std::string > {
		"optimization_solution",
        "local",
		"real_valued",
		"numeric"
	};
}

/// @brief Get the name of this class.
/// @returns "RealValuedFunctionLocalOptimizationSolution".
std::string
RealValuedFunctionLocalOptimizationSolution::class_name() const {
    return "RealValuedFunctionLocalOptimizationSolution";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::real_valued_local".
std::string
RealValuedFunctionLocalOptimizationSolution::class_namespace() const {
    return "masala::numeric::optimization::real_valued_local";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the RealValuedFunctionLocalOptimizationSolution class.
masala::base::api::MasalaObjectAPIDefinitionCWP
RealValuedFunctionLocalOptimizationSolution::get_api_definition() {
    using namespace masala::base::api;
    using base::Real;
    using base::Size;

    std::lock_guard< std::mutex > lock( solution_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "A RealValuedFunctionLocalOptimizationSolution contains the solution to a particular "
				"RealValuedFunctionLocalOptimizationProblem, after it is solved by a suitable "
				"GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < RealValuedFunctionLocalOptimizationSolution > > (
                class_name(),
                "Creates an empty RealValuedFunctionLocalOptimizationSolution."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < RealValuedFunctionLocalOptimizationSolution, RealValuedFunctionLocalOptimizationSolution const & > > (
                class_name(),
                "Copy constructor: copies an input RealValuedFunctionLocalOptimizationSolution.",
                "src", "The input RealValuedFunctionLocalOptimizationSolution to copy.  Unaltered by this operation."
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

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala
