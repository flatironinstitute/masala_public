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

// Numeric headers:
#include <numeric/optimization/OptimizationProblem.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>

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
    problem_ = src.problem_;
    n_times_solution_was_produced_ = src.n_times_solution_was_produced_;
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
    problem_ = src.problem_;
    n_times_solution_was_produced_ = src.n_times_solution_was_produced_;
    return *this;
}

/// @brief Make a copy of this object.
/// @details Must be implemented for derived classes.
OptimizationSolutionSP
OptimizationSolution::clone() const {
	return masala::make_shared< OptimizationSolution >( *this );
}

/// @brief Make a fully independent copy of this object.
OptimizationSolutionSP
OptimizationSolution::deep_clone() const {
    OptimizationSolutionSP new_object( this->clone() );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
OptimizationSolution::make_independent() {
    //std::lock_guard< std::mutex > lock( solution_mutex_ );
    if( problem_ != nullptr ) {
        problem_ = problem_->deep_clone();
    }
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


/// @brief Set the problem that gave rise to this solution.
/// @details Cloned on input.
void
OptimizationSolution::set_problem(
    OptimizationProblemCSP const & problem
) {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    problem_ = ( problem == nullptr ? nullptr : problem->deep_clone() );
}

/// @brief Increment the number of times that the solution was produced by 1.
///	@details An optimizer might produce the same solution many times.  This is
/// the count of the number of times this solution was produced during optimization.
void
OptimizationSolution::increment_n_times_solution_was_produced() {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    ++n_times_solution_was_produced_;
}

/// @brief Increment the number of times that the solution was produced by additional_times_produced.
///	@details An optimizer might produce the same solution many times.  This is
/// the count of the number of times this solution was produced during optimization.
void
OptimizationSolution::increment_n_times_solution_was_produced(
    masala::base::Size const additional_times_produced
) {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    n_times_solution_was_produced_ += additional_times_produced;
}

/// @brief Set the number of times that the solution was produced.
///	@details An optimizer might produce the same solution many times.  This is
/// the count of the number of times this solution was produced during optimization.
void
OptimizationSolution::set_n_times_solution_was_produced(
    masala::base::Size const n_times_produced
) {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    n_times_solution_was_produced_ = n_times_produced;
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

/// @brief Access the problem.
OptimizationProblemCSP
OptimizationSolution::problem() const {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    return problem_;
}

/// @brief Get the number of times that the solution was produced.
///	@details An optimizer might produce the same solution many times.  This is
/// the count of the number of times this solution was produced during optimization.
masala::base::Size
OptimizationSolution::n_times_solution_was_produced() const {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    return n_times_solution_was_produced_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Recompute the score of this solution.
/// @details The problem_ pointer must be set.
/// @note The base class recompute_score() function throws.  Derived classes
/// must override this and provide their own implementations.
void
OptimizationSolution::recompute_score() {
    std::lock_guard< std::mutex > lock( solution_mutex_ );
    CHECK_OR_THROW_FOR_CLASS( problem_ != nullptr, "recompute_score", "Cannot compute score until a "
        "problem has been associated with this solution.  Please finish configuring this problem by calling "
        "set_problem() before calling recompute_score()."
    );
    MASALA_THROW( class_namespace_and_name(), "recompute_score", "The recompute_score() function has not been "
        "implemented for the abstract OptimizationSolution base class.  It must be implemented for derived classes."
    );
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
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< OptimizationProblemCSP > >(
                "problem", "Get the problem associated with this solution.",
                "problem", "The problem associated with this solution.",
                false, false,
                std::bind( &OptimizationSolution::problem, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Size > >(
                "n_times_solution_was_produced", "An optimizer may produce the same solution many times.  This "
                "retrieves the number of times this solution was produced by the optimizer.",
                "n_times_solution_was_produced", "The number of times this solution was produced by the optimizer.",
                false, false,
                std::bind( &OptimizationSolution::n_times_solution_was_produced, this )
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
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationProblemCSP > >(
                "set_problem", "Set the problem that gave rise to this solution.",
                "problem_in", "Const shared pointer to the problem that gave rise to the solution.  Deep-cloned on input.",
                true, false,
                std::bind( &OptimizationSolution::set_problem, this, std::placeholders::_1 )
            ) 
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "increment_n_times_solution_was_produced", "An optimizer may produce the same solution many times.  This "
                "increments the number of times this solution was produced by the optimizer by 1.",
                false, false,
                std::bind( static_cast< void( OptimizationSolution::* )() >( &OptimizationSolution::increment_n_times_solution_was_produced ), this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Size > >(
                "increment_n_times_solution_was_produced", "An optimizer may produce the same solution many times.  This "
                "increments the number of times this solution was produced by the optimizer by additional_times_produced.",
                "additional_times_produced", "The number of additional times that this solution was seen.  (The number by "
                "which to increment the counter.)",
                false, false,
                std::bind( static_cast< void( OptimizationSolution::* )( Size ) >( &OptimizationSolution::increment_n_times_solution_was_produced ), this, std::placeholders::_1 )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Size > >(
                "set_n_times_solution_was_produced", "An optimizer may produce the same solution many times.  This "
                "sets the number of times this solution was produced.",
                "n_times_produced", "The number of times that this solution was seen.",
                false, false,
                std::bind( &OptimizationSolution::set_n_times_solution_was_produced, this, std::placeholders::_1 )
            )
        );

        // Work functions:
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput <void> > (
				"recompute_score", "Recompute the score for this solution.  This is useful, for instance, after "
				"an optimizer that uses approximate methods or low floating-point precision completes "
				"its work, to allow scores to be stored with full floating-point precision and accuracy.",
				false, false, true, false,
				"void", "Returns nothing", std::bind( &OptimizationSolution::recompute_score, this )
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

/// @brief Access the solution score from derived classes.
/// @details Performs no mutex locking.  Should be called from a mutex-locked
/// context only.
masala::base::Real &
OptimizationSolution::protected_solution_score() {
	return solution_score_;
}

/// @brief Const access to the solution score from derived classes.
/// @details Performs no mutex locking.  Should be called from a mutex-locked
/// context only.
masala::base::Real const &
OptimizationSolution::protected_solution_score() const {
	return solution_score_;
}

/// @brief Access the problem.
/// @details Performs no mutex locking.  Should be called from a mutex-locked
/// context only.  May return nullptr.
OptimizationProblemCSP &
OptimizationSolution::protected_problem() {
	return problem_;
}

/// @brief Access the problem.  Const version.
/// @details Performs no mutex locking.  Should be called from a mutex-locked
/// context only.  May return nullptr.
OptimizationProblemCSP const &
OptimizationSolution::protected_problem() const {
	return problem_;
}

} // namespace optimization
} // namespace numeric
} // namespace masala
