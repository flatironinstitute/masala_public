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

/// @file src/numeric/optimization/OptimizationSolutions.cc
/// @brief Implementation for a base class for OptimizationSolutions continer.
/// @details The OptimizationSolutions container holds a collection of OptimizationSolution objects.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/OptimizationSolutions.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <numeric/types.hh>
#include <numeric/optimization/OptimizationSolution.hh>

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
/// @details Must be explicitly defined due to mutex.  Copies the pointers to, but does not deep-clone,
/// the optimization solutions.
OptimizationSolutions::OptimizationSolutions(
    OptimizationSolutions const & src
) :
    masala::base::managers::plugin_module::MasalaPlugin(src),
    optimization_solutions_( src.optimization_solutions_ )
{}

/// @brief Assignment operator.
/// @details Copies the pointers to, but does not deep-clone,
/// the optimization solutions.
OptimizationSolutions &
OptimizationSolutions::operator=(
    OptimizationSolutions const & src
) {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    std::lock_guard< std::mutex > lock2( src.solutions_mutex_ );
    masala::base::managers::plugin_module::MasalaPlugin::operator=(src);
    optimization_solutions_ = src.optimization_solutions_;
    return *this;
}

/// @brief Make a fully independent copy of this object.
OptimizationSolutionsSP
OptimizationSolutions::deep_clone() const {
    OptimizationSolutionsSP new_object( masala::make_shared< OptimizationSolutions >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
OptimizationSolutions::make_independent() {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    for( masala::numeric::Size i(1); i<=optimization_solutions_.size(); ++i ) {
        optimization_solutions_[i] = optimization_solutions_[i]->deep_clone();
    }
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { { "OptimizationSolutions" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
OptimizationSolutions::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationSolutions" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "optimization_solutions", "numeric" }
std::vector< std::string >
OptimizationSolutions::get_keywords() const {
	return std::vector< std::string > {
		"optimization_solutions",
		"numeric"
	};
}

/// @brief Get the class name.
/// @returns "OptimizationSolutions".
std::string
OptimizationSolutions::class_name() const {
    return "OptimizationSolutions";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization".
std::string
OptimizationSolutions::class_namespace() const {
    return "masala::numeric::optimization";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the OptimizationSolutions class.
masala::base::api::MasalaObjectAPIDefinitionCWP
OptimizationSolutions::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( solutions_mutex_ );

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The OptimizationSolutions class defines a container for many numerical optimization solutions.  These are "
                "the solutions reduced to numbers, with no chemical classes or concepts included.  Typically, "
                "one would not want to instantiate an abstract OptimizationSolutions container.  Instead, one would "
                "usually use a particular sub-class defining a container for a particular type of optimization solution, "
                "such as a CostFunctionNetworkOptimizationSolutions container.",
                false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < OptimizationSolutions > > (
                class_name(),
                "Creates an empty OptimizationSolutions container.  Cannot be used directly, but can "
                "be called from constructors of derived classes."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < OptimizationSolutions, OptimizationSolutions const & > > (
                class_name(),
                "Copy constructor: copies an input OptimizationSolutions container.",
                "src", "The input OptimizationSolutions container object to copy.  Unaltered by this operation."
            )
        );

        // Work functions:

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Resets the container, deleting all contained solutions.",
                true, false, std::bind( &OptimizationSolutions::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationSolutionSP > >(
                "add_optimization_solution",
                "Add an optimization solution to the list of optimization solutions that this container contains.",
                "solution_in", "The optimization solution that we are adding to the container.",
                true, false, std::bind( &OptimizationSolutions::add_optimization_solution, this, std::placeholders::_1 )
            )
        );

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_OneInput< OptimizationSolutionCSP, masala::numeric::Size > >(
                "solution", "Get the solution with the given index.  Throws if index is out of range.",
                "index", "The index of the solution to get.  (Note that this is zero-based.)",
                "solution", "A const shared pointer to the solution with the given index.",
                false, false,
                std::bind( &OptimizationSolutions::solution, this, std::placeholders::_1 )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::numeric::Size > >(
                "n_solutions", "Get the number of solutions stored in this object.",
                "n_solutions", "The number of solutions stored in this object, or one more than th zero-based "
                "index of the last solution.",
                false, false,
                std::bind( &OptimizationSolutions::n_solutions, this )
            )
        );

        api_definition_ = api_def; //Make const.
    }

    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object, clearing its solution list.
void
OptimizationSolutions::reset() {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    optimization_solutions_.clear();
}

/// @brief Add an optimization solution to the list of optimization solutions
/// stored in this container.
/// @details Derived classes should override this to check the type of the
/// optimization solution stored.
void
OptimizationSolutions::add_optimization_solution(
    OptimizationSolutionSP solution_in
) {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    optimization_solutions_.emplace_back( solution_in );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the ith solution in this object, where the index is zero-based.
/// @details Does bounds-checking.  Throws if out of range.  Use the
/// n_solutions() method to check number of solutions.
OptimizationSolutionCSP
OptimizationSolutions::solution(
    masala::numeric::Size const index
) const {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    CHECK_OR_THROW_FOR_CLASS(
        index < optimization_solutions_.size(),
        "solution",
        "The optimization solution index (" + std::to_string(index) + ") + is out of range.  There are only "
        + std::to_string( optimization_solutions_.size() ) + " solutions stored in this object."
    );
    return optimization_solutions_[index];
}

/// @brief Get the number of solutions stored in this object.
masala::numeric::Size
OptimizationSolutions::n_solutions() const {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    return optimization_solutions_.size();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Allow derived classes to access the mutex for this object.
/// @note The mutex is mutable, and can be locked from a const function.
std::mutex &
OptimizationSolutions::solutions_mutex() const {
    return solutions_mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.  This does NOT lock the mutex.
masala::base::api::MasalaObjectAPIDefinitionCSP &
OptimizationSolutions::api_definition() {
    return api_definition_;
}

/// @brief Allow derived classes to access the vector of optimization solutions.
/// @details This does NOT lock the solutions_mutex_ mutex.  Calling functions must
/// do this first.
std::vector< OptimizationSolutionSP > &
OptimizationSolutions::optimization_solutions() {
    return optimization_solutions_;
}

} // namespace optimization
} // namespace numeric
} // namesapce masala
