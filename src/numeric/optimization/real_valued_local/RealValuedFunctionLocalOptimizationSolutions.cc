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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolutions.cc
/// @brief Implementations for a container for RealValuedFunctionLocalOptimizationSolutions.
/// @details Each RealValuedFunctionLocalOptimizationSolution defines a numerical loss function
/// gradient minimization solution produced by a suitable Optimizer.  It does not contain any
/// chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolutions.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/setter_annotation/NoUISetterAnnotation.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ThreeInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <base/types.hh>
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution.hh>
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>
#include <tuple>

namespace masala {
namespace numeric {
namespace optimization {
namespace real_valued_local {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a copy of this object and return an owning pointer.
OptimizationSolutionsSP
RealValuedFunctionLocalOptimizationSolutions::clone() const {
	return masala::make_shared< RealValuedFunctionLocalOptimizationSolutions >( *this );
}

/// @brief Make a fully independent copy of this object.
RealValuedFunctionLocalOptimizationSolutionsSP
RealValuedFunctionLocalOptimizationSolutions::deep_clone() const {
    RealValuedFunctionLocalOptimizationSolutionsSP new_object( std::static_pointer_cast< RealValuedFunctionLocalOptimizationSolutions >( this->clone() ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
RealValuedFunctionLocalOptimizationSolutions::make_independent() {
    masala::numeric::optimization::OptimizationSolutions::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { { "OptimizationSolutions", "RealValuedFunctionLocalOptimizationSolutions" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
RealValuedFunctionLocalOptimizationSolutions::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationSolutions", "RealValuedFunctionLocalOptimizationSolutions" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "local", "real_valued", "optimization_solutions", "numeric" }
std::vector< std::string >
RealValuedFunctionLocalOptimizationSolutions::get_keywords() const {
	std::vector< std::string > outvec( masala::numeric::optimization::OptimizationSolutions::get_keywords() );
    outvec.push_back( "local" );
    outvec.push_back( "real_valued" );
    return outvec;
}

/// @brief Get the class name.
/// @returns "RealValuedFunctionLocalOptimizationSolutions".
std::string
RealValuedFunctionLocalOptimizationSolutions::class_name() const {
    return "RealValuedFunctionLocalOptimizationSolutions";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization::real_valued_local".
std::string
RealValuedFunctionLocalOptimizationSolutions::class_namespace() const {
    return "masala::numeric::optimization::real_valued_local";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the RealValuedFunctionLocalOptimizationSolutions class.
masala::base::api::MasalaObjectAPIDefinitionCWP
RealValuedFunctionLocalOptimizationSolutions::get_api_definition() {
    using namespace masala::base::api;
    using masala::base::Size;
    using masala::base::Real;

    std::lock_guard< std::mutex > lock( solutions_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The RealValuedFunctionLocalOptimizationSolutions class defines a container for RealValuedFunctionLocalOptimizationSolutions.  "
				"Each RealValuedFunctionLocalOptimizationSolution defines a numerical loss function "
				"gradient minimization solution produced by a suitable Optimizer.  It does not contain any "
				"chemistry-specific concepts.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < RealValuedFunctionLocalOptimizationSolutions > > (
                class_name(),
                "Creates an empty RealValuedFunctionLocalOptimizationSolutions container."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < RealValuedFunctionLocalOptimizationSolutions, RealValuedFunctionLocalOptimizationSolutions const & > > (
                class_name(),
                "Copy constructor: copies an input RealValuedFunctionLocalOptimizationSolutions container.",
                "src", "The input RealValuedFunctionLocalOptimizationSolutions container object to copy.  Unaltered by this operation."
            )
        );

        // Setters:
		{
			setter::MasalaObjectAPISetterDefinition_ZeroInputSP reset_fxn(
				masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
					"reset", "Resets the container, deleting all contained solutions.",
					false, true, std::bind( &RealValuedFunctionLocalOptimizationSolutions::reset, this )
				)
			);
			reset_fxn->add_setter_annotation( masala::make_shared< setter::setter_annotation::NoUISetterAnnotation >() );
			api_def->add_setter( reset_fxn );
		}
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationSolutionSP > >(
                "add_optimization_solution",
                "Add a cost function network optimization solution to the list of optimization solutions that this container contains.",
                "solution_in", "The cost function network optimization solution that we are adding to the container.  Throws if this is "
                "not a cost function network optimization solution.",
                false, true, std::bind( &RealValuedFunctionLocalOptimizationSolutions::add_optimization_solution, this, std::placeholders::_1 )
            )
        );
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::base::Size > >(
				"remove_optimization_solution", "Remove an optimization solution, by solution index.",
				"solution_index", "The index of the solution to remove.  Must be in range; throws otherwise.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolutions::remove_optimization_solution, this, std::placeholders::_1 )
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
RealValuedFunctionLocalOptimizationSolutions::reset() {
    masala::numeric::optimization::OptimizationSolutions::reset();
}

/// @brief Add an optimization solution to the list of optimization solutions
/// stored in this container.
/// @details Derived classes should override this to check the type of the
/// optimization solution stored.
void
RealValuedFunctionLocalOptimizationSolutions::add_optimization_solution(
    OptimizationSolutionSP solution_in
) {
    CHECK_OR_THROW_FOR_CLASS(
        std::dynamic_pointer_cast< RealValuedFunctionLocalOptimizationSolution >( solution_in ) != nullptr,
        "add_optimization_solution", "Only a RealValuedFunctionLocalOptimizationSolution can be added "
        "to a RealValuedFunctionLocalOptimizationSolutions container."
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

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala
