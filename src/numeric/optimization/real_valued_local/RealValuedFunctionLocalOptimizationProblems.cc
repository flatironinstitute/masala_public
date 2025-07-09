/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblems.cc
/// @brief Implementations for a container for RealValuedFunctionLocalOptimizationProblems.
/// @details Each RealValuedFunctionLocalOptimizationProblem defines a numerical gradient-descent
/// minimization problem for an arbitrary loss function.  They do not contain any chemistry-specific
/// concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblems.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/setter_annotation/NoUISetterAnnotation.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <base/types.hh>
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace real_valued_local {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a fully independent copy of this object.
RealValuedFunctionLocalOptimizationProblemsSP
RealValuedFunctionLocalOptimizationProblems::deep_clone() const {
    RealValuedFunctionLocalOptimizationProblemsSP new_object( masala::make_shared< RealValuedFunctionLocalOptimizationProblems >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
RealValuedFunctionLocalOptimizationProblems::make_independent() {
    masala::numeric::optimization::OptimizationProblems::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationProblems", "RealValuedFunctionLocalOptimizationProblems" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
RealValuedFunctionLocalOptimizationProblems::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblems", "RealValuedFunctionLocalOptimizationProblems" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "local", "real_valued", "optimization_problems", "numeric" }
std::vector< std::string >
RealValuedFunctionLocalOptimizationProblems::get_keywords() const {
	std::vector< std::string > outvec( masala::numeric::optimization::OptimizationProblems::get_keywords() );
    outvec.push_back( "local" );
    outvec.push_back( "real_valued" );
    return outvec;
}

/// @brief Get the class name.
/// @returns "RealValuedFunctionLocalOptimizationProblems".
std::string
RealValuedFunctionLocalOptimizationProblems::class_name() const {
    return "RealValuedFunctionLocalOptimizationProblems";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization::real_valued_local".
std::string
RealValuedFunctionLocalOptimizationProblems::class_namespace() const {
    return "masala::numeric::optimization::real_valued_local";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the RealValuedFunctionLocalOptimizationProblems class.
masala::base::api::MasalaObjectAPIDefinitionCWP
RealValuedFunctionLocalOptimizationProblems::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( problems_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The RealValuedFunctionLocalOptimizationProblems class defines a container for "
				"RealValuedFunctionLocalOptimizationProblem instances.  Each RealValuedFunctionLocalOptimizationProblem "
				"defines a numerical gradient-descent minimization problem for an arbitrary loss function.  They "
				"do not contain any chemistry-specific concepts.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < RealValuedFunctionLocalOptimizationProblems > > (
                class_name(),
                "Creates an empty RealValuedFunctionLocalOptimizationProblems container."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < RealValuedFunctionLocalOptimizationProblems, RealValuedFunctionLocalOptimizationProblems const & > > (
                class_name(),
                "Copy constructor: copies an input RealValuedFunctionLocalOptimizationProblems container.",
                "src", "The input RealValuedFunctionLocalOptimizationProblems container object to copy.  Unaltered by this operation."
            )
        );

        // Work functions:


        // Getters:


        // Setters:
		{
			setter::MasalaObjectAPISetterDefinition_ZeroInputSP reset_fxn(
				masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
					"reset", "Resets the container, deleting all contained problems.",
					false, true, std::bind( &RealValuedFunctionLocalOptimizationProblems::reset, this )
				)
			);
			reset_fxn->add_setter_annotation( masala::make_shared< setter::setter_annotation::NoUISetterAnnotation >() );
			api_def->add_setter( reset_fxn );
		}
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationProblemSP > >(
                "add_optimization_problem",
                "Add a cost function network optimization problem to the list of optimization problems that this container contains.",
                "problem_in", "The gradient-descent loss function minimization optimization problem that we are adding to the container.  Throws if this is "
                "not a gradient descent based optimization problem.",
                false, true, std::bind( &RealValuedFunctionLocalOptimizationProblems::add_optimization_problem, this, std::placeholders::_1 )
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
RealValuedFunctionLocalOptimizationProblems::reset() {
    masala::numeric::optimization::OptimizationProblems::reset();
}

/// @brief Add an optimization problem to the list of optimization problems
/// stored in this container.
/// @details Derived classes should override this to check the type of the
/// optimization problem stored.
void
RealValuedFunctionLocalOptimizationProblems::add_optimization_problem(
    OptimizationProblemSP problem_in
) {
    CHECK_OR_THROW_FOR_CLASS(
        std::dynamic_pointer_cast< RealValuedFunctionLocalOptimizationProblem >( problem_in ) != nullptr,
        "add_optimization_problem", "Only a RealValuedFunctionLocalOptimizationProblem can be added "
        "to a RealValuedFunctionLocalOptimizationProblems container."
    );
    masala::numeric::optimization::OptimizationProblems::add_optimization_problem( problem_in );
}

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala
