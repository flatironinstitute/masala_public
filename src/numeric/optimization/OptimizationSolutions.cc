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
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <base/types.hh>
#include <numeric/optimization/OptimizationSolution.hh>

// STL headers:
#include <vector>
#include <string>
#include <algorithm>

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
    masala::base::managers::plugin_module::MasalaPlugin(src)
{
    std::lock_guard< std::mutex > lock( src.solutions_mutex_ );
    optimization_solutions_ = src.optimization_solutions_;
}

/// @brief Assignment operator.
/// @details Copies the pointers to, but does not deep-clone,
/// the optimization solutions.
OptimizationSolutions &
OptimizationSolutions::operator=(
    OptimizationSolutions const & src
) {
    std::lock( solutions_mutex_, src.solutions_mutex_ );
    std::lock_guard< std::mutex > lock( solutions_mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lock2( src.solutions_mutex_, std::adopt_lock );
    masala::base::managers::plugin_module::MasalaPlugin::operator=(src);
    optimization_solutions_ = src.optimization_solutions_;
    return *this;
}

/// @brief Make a fully independent copy of this object.
OptimizationSolutionsSP
OptimizationSolutions::deep_clone() const {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    OptimizationSolutionsSP new_object( masala::make_shared< OptimizationSolutions >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
OptimizationSolutions::make_independent() {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    for( masala::base::Size i(1); i<=optimization_solutions_.size(); ++i ) {
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
                false, true
            )
        );

        // Constructors:
        ADD_PROTECTED_CONSTRUCTOR_DEFINITIONS( OptimizationSolutions, api_def );

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
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::base::Size > >(
                "increment_n_times_solution_was_produced", "An optimizer may produce the same solution many times.  This "
                "increments the number of times a solution was produced by the optimizer by 1.",
                "solution_index", "The index of the solution to increment.  Must be in range; throws otherwise.",
                false, false,
                std::bind( static_cast< void( OptimizationSolutions::* )( base::Size ) >( &OptimizationSolutions::increment_n_times_solution_was_produced ), this, std::placeholders::_1 )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< masala::base::Size, masala::base::Size > >(
                "increment_n_times_solution_was_produced", "An optimizer may produce the same solution many times.  This "
                "increments the number of times a solution was produced by the optimizer by additional_times_produced.",
                "solution_index", "The index of the solution to increment.  Must be in range; throws otherwise.",
                "additional_times_produced", "The number of additional times that this solution was seen.  (The number by "
                "which to increment the counter.)",
                false, false,
                std::bind( static_cast< void( OptimizationSolutions::* )( base::Size, base::Size ) >( &OptimizationSolutions::increment_n_times_solution_was_produced ), this, std::placeholders::_1, std::placeholders::_2 )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< masala::base::Size, masala::base::Size > >(
                "set_n_times_solution_was_produced", "An optimizer may produce the same solution many times.  This "
                "sets the number of times a solution was produced.",
                "solution_index", "The index of the solution to increment.  Must be in range; throws otherwise.",
                "n_times_produced", "The number of times that this solution was seen.",
                false, false,
                std::bind( &OptimizationSolutions::set_n_times_solution_was_produced, this, std::placeholders::_1, std::placeholders::_2 )
            )
        );
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::base::Size > >(
				"remove_optimization_solution", "Remove an optimization solution, by solution index.",
				"solution_index", "The index of the solution to remove.  Must be in range; throws otherwise.",
				false, false,
				std::bind( &OptimizationSolutions::remove_optimization_solution, this, std::placeholders::_1 )
			)
		);

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_OneInput< OptimizationSolutionCSP, masala::base::Size > >(
                "solution", "Get the solution with the given index.  Throws if index is out of range.",
                "index", "The index of the solution to get.  (Note that this is zero-based.)",
                "solution", "A const shared pointer to the solution with the given index.",
                false, false,
                std::bind( &OptimizationSolutions::solution, this, std::placeholders::_1 )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::base::Size > >(
                "n_solutions", "Get the number of solutions stored in this object.",
                "n_solutions", "The number of solutions stored in this object, or one more than th zero-based "
                "index of the last solution.",
                false, false,
                std::bind( &OptimizationSolutions::n_solutions, this )
            )
        );
        
        // Work functions:
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput< void > >(
                "sort_by_score", "Sorts solutions from lowest to highest by the score stored in the solution.",
                false, false, false, false,
                "void", "Returns nothing.",
                std::bind( &OptimizationSolutions::sort_by_score, this )
            )
        );
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput< void > >(
                "recompute_all_scores", "Recalculate the scores of all solutions stored in this object.  "
                "This can be useful when, for instance, problems are solved with inexact "
	            "optimizers that use reduced numerical precision, or which accumulate numerical "
	            "error through long Monte Carlo trajectories.",
                false, false, false, false,
                "void", "Returns nothing.",
                std::bind( static_cast<void(OptimizationSolutions::*)()>( &OptimizationSolutions::recompute_all_scores ), this )
            )
        );
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< void, masala::base::Real > >(
                "recompute_all_scores", "Recalculate the scores of all solutions stored in this object.  "
                "This can be useful when, for instance, problems are solved with inexact "
	            "optimizers that use reduced numerical precision, or which accumulate numerical "
	            "error through long Monte Carlo trajectories.  This version throws if any score's "
                "value changes by more than the old value multiplied by max_fractional_error.",
                false, false, false, false,
                "max_fractional_error", "The maximum fractional amount by which each solution's score is "
                "allowed to change.  Outside this range, the function throws.",
                "void", "Returns nothing.",
                std::bind( static_cast<void(OptimizationSolutions::*)( masala::base::Real )>( &OptimizationSolutions::recompute_all_scores ), this, std::placeholders::_1 )
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

/// @brief Increment the number of times the Nth solution was produced, by 1.
/// @param solution_index The index of the solution to increment.  Must be in range (throws otherwise).
void
OptimizationSolutions::increment_n_times_solution_was_produced(
    masala::base::Size const solution_index
) {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    CHECK_OR_THROW_FOR_CLASS( solution_index < optimization_solutions_.size(), "increment_n_times_solution_was_produced",
        "The solution index " + std::to_string( solution_index ) + " was out of range.  This object stores "
        + std::to_string( optimization_solutions_.size() ) + "solutions."
    );
    optimization_solutions_[solution_index]->increment_n_times_solution_was_produced();
}

/// @brief Increment the number of times the Nth solution was produced, by additional_times_produced.
/// @param solution_index The index of the solution to increment.  Must be in range (throws otherwise).
/// @param additional_times_produced The number by which to increment this.
void
OptimizationSolutions::increment_n_times_solution_was_produced(
    masala::base::Size const solution_index,
    masala::base::Size const additional_times_produced
) {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    CHECK_OR_THROW_FOR_CLASS( solution_index < optimization_solutions_.size(), "increment_n_times_solution_was_produced",
        "The solution index " + std::to_string( solution_index ) + " was out of range.  This object stores "
        + std::to_string( optimization_solutions_.size() ) + "solutions."
    );
    optimization_solutions_[solution_index]->increment_n_times_solution_was_produced( additional_times_produced );
}

/// @brief Set the number of times the Nth solution was produced.
/// @param solution_index The index of the solution to increment.  Must be in range (throws otherwise).
/// @param n_times_produced The number of times that this solutinos was produced.
void
OptimizationSolutions::set_n_times_solution_was_produced(
    masala::base::Size const solution_index,
    masala::base::Size const n_times_produced
) {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    CHECK_OR_THROW_FOR_CLASS( solution_index < optimization_solutions_.size(), "set_n_times_solution_was_produced",
        "The solution index " + std::to_string( solution_index ) + " was out of range.  This object stores "
        + std::to_string( optimization_solutions_.size() ) + "solutions."
    );
    optimization_solutions_[solution_index]->set_n_times_solution_was_produced( n_times_produced );
}


/// @brief Remove an optimization solution from the list of optimization solutions
/// stored in this container.
/// @details Throws if the solution index is out of range.
void
OptimizationSolutions::remove_optimization_solution(
    masala::base::Size const solution_index
) {
	std::lock_guard< std::mutex > lock( solutions_mutex_ );
	CHECK_OR_THROW_FOR_CLASS( solution_index < optimization_solutions_.size(),
		"remove_optimization_solution", "The solution index " + std::to_string( solution_index ) +
		" is out of range.  This object currently stores only " + std::to_string( optimization_solutions_.size() ) +
		" solutions."
	);
	std::vector< OptimizationSolutionSP >::iterator it( optimization_solutions_.begin() + solution_index );
	optimization_solutions_.erase( it );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the ith solution in this object, where the index is zero-based.
/// @details Does bounds-checking.  Throws if out of range.  Use the
/// n_solutions() method to check number of solutions.
OptimizationSolutionCSP
OptimizationSolutions::solution(
    masala::base::Size const index
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
masala::base::Size
OptimizationSolutions::n_solutions() const {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    return optimization_solutions_.size();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Sort all of the solutions stored in this object by score.
void
OptimizationSolutions::sort_by_score() {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    std::sort(
        optimization_solutions_.begin(),
        optimization_solutions_.end(),
        []( OptimizationSolutionSP const & a, OptimizationSolutionSP const & b ) { return a->solution_score() < b->solution_score(); }
    );
}

/// @brief Recompute all of the scores for all of the stored solutions.
/// @details This can be useful when, for instance, problems are solved with inexact
/// optimizers that use reduced numerical precision, or which accumulate numerical
/// error through long Monte Carlo trajectories.
void
OptimizationSolutions::recompute_all_scores() {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    for( OptimizationSolutionSP const & solution : optimization_solutions_ ) {
        solution->recompute_score();
    }
}
	
/// @brief Recompute all of the scores for all of the stored solutions.
/// @details This can be useful when, for instance, problems are solved with inexact
/// optimizers that use reduced numerical precision, or which accumulate numerical
/// error through long Monte Carlo trajectories.
/// @note This version throws if any score's value changes by more than the old value
/// multiplied by max_fractional_error.
void
OptimizationSolutions::recompute_all_scores(
    masala::base::Real const max_fractional_error
) {
    std::lock_guard< std::mutex > lock( solutions_mutex_ );
    masala::base::Size failed_count(0);
    for( OptimizationSolutionSP const & solution : optimization_solutions_ ) {
        masala::base::Real const old_score( solution->solution_score() );
        solution->recompute_score();
        masala::base::Real const delta( std::abs( old_score - solution->solution_score() ) );
        if( delta > max_fractional_error * old_score ) {
            ++failed_count;
        }
    }
    CHECK_OR_THROW_FOR_CLASS(
        failed_count == 0,
        "recompute_all_scores",
        "A total of " + std::to_string( failed_count ) + " out of " +
        std::to_string( optimization_solutions_.size() ) + " optimization "
        "solutions showed solution value changes larger than " +
        std::to_string(max_fractional_error) + " times the original score."
    );
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
