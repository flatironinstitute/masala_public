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

/// @file src/numeric/optimization/OptimizationProblem.cc
/// @brief Implementation for a base class for OptimizationProblems.
/// @details OptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/OptimizationProblem.hh>

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
OptimizationProblem::OptimizationProblem(
    OptimizationProblem const & src
) :
    masala::base::managers::plugin_module::MasalaPlugin(src)
{
    //std::lock_guard< std::mutex > lock( problem_mutex_ );
    // Nothing else gets copied, by default.
}

/// @brief Assignment operator.
OptimizationProblem &
OptimizationProblem::operator=(
    OptimizationProblem const & src
) {
    masala::base::managers::plugin_module::MasalaPlugin::operator=(src);
    {
        //std::lock( problem_mutex_, src.problem_mutex_ );
        //std::lock_guard< std::mutex > lock( problem_mutex_, std::adopt_lock );
        //std::lock_guard< std::mutex > lock2( src.problem_mutex_, std::adopt_lock );
        //Nothing else gets assigned, by default.
    }
    return *this;
}

/// @brief Make a fully independent copy of this object.
OptimizationProblemSP
OptimizationProblem::deep_clone() const {
    OptimizationProblemSP new_object;
    {
        std::lock_guard< std::mutex > lock( problem_mutex_ );
        new_object = masala::make_shared< OptimizationProblem >( *this );
    }
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
OptimizationProblem::make_independent() {
    //std::lock_guard< std::mutex > lock( problem_mutex_ );
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationProblem" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
OptimizationProblem::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "numeric" }
std::vector< std::string >
OptimizationProblem::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"numeric"
	};
}

/// @brief Get the class name.
/// @returns "OptimizationProblem".
std::string
OptimizationProblem::class_name() const {
    return "OptimizationProblem";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization".
std::string
OptimizationProblem::class_namespace() const {
    return "masala::numeric::optimization";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the OptimizationProblem class.
masala::base::api::MasalaObjectAPIDefinitionCWP
OptimizationProblem::get_api_definition() {
    using namespace masala::base::api;


    std::lock_guard< std::mutex > lock( problem_mutex_ );

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The OptimizationProblem class defines a numerical optimization problem.  This is "
                "the problem reduced to numbers, with no chemical classes or concepts included.  Typically, "
                "one would not want to instantiate an abstract OptimizationProblem.  Instead, one would "
                "usually use a particular sub-class defining a particular type of optimization problem, "
                "such as a CostFunctionNetworkOptimizationProblem.",
                false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < OptimizationProblem > > (
                class_name(),
                "Creates an empty OptimizationProblem.  Cannot be used directly, but can "
                "be called from constructors of derived classes."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < OptimizationProblem, OptimizationProblem const & > > (
                class_name(),
                "Copy constructor: copies an input OptimizationProblem.",
                "src", "The input OptimizationProblem to copy.  Unaltered by this operation."
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
OptimizationProblem::problem_mutex() const {
    return problem_mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.
masala::base::api::MasalaObjectAPIDefinitionCSP &
OptimizationProblem::api_definition() {
    return api_definition_;
}

} // namespace optimization
} // namespace numeric
} // namesapce masala
