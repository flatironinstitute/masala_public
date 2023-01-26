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

/// @file src/numeric/optimization/OptimizationProblems.cc
/// @brief Implementation for a base class for OptimizationProblemss.
/// @details OptimizationProblemss define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/OptimizationProblems.hh>

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

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.
/// @details Must be explicitly defined due to mutex.
OptimizationProblems::OptimizationProblems(
    OptimizationProblems const & src
) :
    masala::base::managers::plugin_module::MasalaPlugin(src)
    // Nothing else gets copied, by default.
{}

/// @brief Assignment operator.
OptimizationProblems &
OptimizationProblems::operator=(
    OptimizationProblems const & src
) {
    masala::base::managers::plugin_module::MasalaPlugin::operator=(src);
    //Nothing else gets assigned, by default.
    return *this;
}

/// @brief Make a fully independent copy of this object.
OptimizationProblemsSP
OptimizationProblems::deep_clone() const {
    OptimizationProblemsSP new_object( masala::make_shared< OptimizationProblems >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
OptimizationProblems::make_independent() {
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationProblems" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
OptimizationProblems::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblems" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problems", "numeric" }
std::vector< std::string >
OptimizationProblems::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problems",
		"numeric"
	};
}

/// @brief Get the class name.
/// @returns "OptimizationProblems".
std::string
OptimizationProblems::class_name() const {
    return "OptimizationProblems";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization".
std::string
OptimizationProblems::class_namespace() const {
    return "masala::numeric::optimization";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the OptimizationProblems class.
masala::base::api::MasalaObjectAPIDefinitionCWP
OptimizationProblems::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( problems_mutex_ );

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The OptimizationProblems class defines a container for many numerical optimization problems.  These are "
                "the problems reduced to numbers, with no chemical classes or concepts included.  Typically, "
                "one would not want to instantiate an abstract OptimizationProblems container.  Instead, one would "
                "usually use a particular sub-class defining a container for a particular type of optimization problem, "
                "such as a CostFunctionNetworkOptimizationProblems container.",
                false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < OptimizationProblems > > (
                class_name(),
                "Creates an empty OptimizationProblems container.  Cannot be used directly, but can "
                "be called from constructors of derived classes."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < OptimizationProblems, OptimizationProblems const & > > (
                class_name(),
                "Copy constructor: copies an input OptimizationProblems container.",
                "src", "The input OptimizationProblems container object to copy.  Unaltered by this operation."
            )
        );

        // Work functions:


        // Getters:


        // Setters:

        api_definition_ = api_def; //Make const.
    }

    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Allow derived classes to access the mutex for this object.
/// @note The mutex is mutable, and can be locked from a const function.
std::mutex &
OptimizationProblems::problems_mutex() const {
    return problems_mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.
masala::base::api::MasalaObjectAPIDefinitionCSP &
OptimizationProblems::api_definition() {
    return api_definition_;
}

} // namespace optimization
} // namespace numeric
} // namesapce masala
