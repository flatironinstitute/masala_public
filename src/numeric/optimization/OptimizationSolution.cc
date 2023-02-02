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

/// @file src/numeric/optimization/OptimizationSolution.cc
/// @brief Implementation for a pure virtual base class for OptimizationSolutions.
/// @details An OptimizationSolution contains the solution to a particular OptimizationProblem,
/// after it is solved by a suitable Optimizer.  It does not contain any chemistry-specific
/// concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/OptimizationSolution.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>

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
OptimizationSolution::OptimizationSolution(
    OptimizationSolution const & src
) :
    masala::base::managers::plugin_module::MasalaPlugin(src)
{
    std::lock_guard< std::mutex > lock( src.solution_mutex_ );
    solution_score_ = src.solution_score_;
}

/// @brief Assignment operator.
OptimizationSolution &
OptimizationSolution::operator=(
    OptimizationSolution const & src
) {
    masala::base::managers::plugin_module::MasalaPlugin::operator=(src);
    std::lock( solution_mutex_, src.solution_mutex_ );
    std::lock_guard< std::mutex > lock( solution_mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lock2( src.solution_mutex_, std::adopt_lock );
    solution_score_ = src.solution_score_;
    return *this;
}

/// @brief Make a fully independent copy of this object.
OptimizationSolutionSP
OptimizationSolution::deep_clone() const {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    OptimizationSolutionSP new_object( masala::make_shared< OptimizationSolution >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
OptimizationSolution::make_independent() {
    //std::lock_guard< std::mutex > lock( solution_mutex_ );
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationSolution" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
OptimizationSolution::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationSolution" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "optimization_solution", "numeric" }
std::vector< std::string >
OptimizationSolution::get_keywords() const {
	return std::vector< std::string > {
		"optimization_solution",
		"numeric"
	};
}

/// @brief Get the class name.
/// @returns "OptimizationSolution".
std::string
OptimizationSolution::class_name() const {
    return "OptimizationSolution";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization".
std::string
OptimizationSolution::class_namespace() const {
    return "masala::numeric::optimization";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the score for this solution.
void
OptimizationSolution::set_solution_score(
    masala::base::Real const score_in
) {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    solution_score_ = score_in;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the score for this solution.
masala::base::Real
OptimizationSolution::solution_score() const {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    return solution_score_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the OptimizationSolution class.
masala::base::api::MasalaObjectAPIDefinitionCWP
OptimizationSolution::get_api_definition() {
    using namespace masala::base::api;
    using masala::base::Real;
    using masala::base::Size;

    std::lock_guard< std::mutex > lock( solution_mutex_ );

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The OptimizationSolution class stores a solution to a numerical optimization problem.  This is "
                "the solution to the problem reduced to numbers, with no chemical classes or concepts included.  "
                "Typically, one would not want to instantiate an abstract OptimizationSolution.  Instead, one would "
                "usually use a particular sub-class defining a particular type of optimization problem, "
                "such as a CostFunctionNetworkOptimizationSolution.",
                false, false
            )
        );

        // Constructors:
        ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( OptimizationSolution, api_def );

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Real > >(
                "solution_score", "Get the score associated with this solution.",
                "solution_score", "The score associated with this solution.",
                false, false,
                std::bind( &OptimizationSolution::solution_score, this )
            )
        );

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Real > >(
                "set_solution_score", "Set the score associated with this solution.",
                "score_in", "The score to set.",
                false, false,
                std::bind( &OptimizationSolution::set_solution_score, this, std::placeholders::_1 )
            ) 
        );

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
OptimizationSolution::solution_mutex() const {
    return solution_mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.
masala::base::api::MasalaObjectAPIDefinitionCSP &
OptimizationSolution::api_definition() {
    return api_definition_;
}

} // namespace optimization
} // namespace numeric
} // namesapce masala
