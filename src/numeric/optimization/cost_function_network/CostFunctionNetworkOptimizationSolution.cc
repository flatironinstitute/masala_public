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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.cc
/// @brief Implementation for a pure virtual base class for CostFunctionNetworkOptimizationSolutions.
/// @details A CostFunctionNetworkOptimizationSolution contains the solution to a particular
/// CostFunctionNetworkOptimizationProblem, after it is solved by a suitable CostFunctionNetworkOptimizer.
/// It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Constructor that initializes from the problem description.
/// @details The problem definition is stored directly, not cloned.
CostFunctionNetworkOptimizationSolution::CostFunctionNetworkOptimizationSolution(
    CostFunctionNetworkOptimizationProblemCSP const & problem_in
) :
    masala::numeric::optimization::OptimizationSolution()
{
    set_problem( problem_in );
}


/// @brief Make a fully independent copy of this object.
CostFunctionNetworkOptimizationSolutionSP
CostFunctionNetworkOptimizationSolution::deep_clone() const {
    CostFunctionNetworkOptimizationSolutionSP new_solution( masala::make_shared< CostFunctionNetworkOptimizationSolution >( *this ) );
    new_solution->make_independent();
    return new_solution;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
CostFunctionNetworkOptimizationSolution::make_independent() {
    masala::numeric::optimization::OptimizationSolution::make_independent();
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "CostFunctionNetworkOptimizationSolution" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
CostFunctionNetworkOptimizationSolution::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunctionNetworkOptimizationSolution" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "optimization_solution", "cost_function_network_optimization_solution", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizationSolution::get_keywords() const {
	return std::vector< std::string > {
		"optimization_solution",
        "cost_function_network_optimization_solution",
		"numeric"
	};
}

/// @brief Get the name of this class.
/// @returns "CostFunctionNetworkOptimizationSolution".
std::string
CostFunctionNetworkOptimizationSolution::class_name() const {
    return "CostFunctionNetworkOptimizationSolution";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkOptimizationSolution::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkOptimizationSolution class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkOptimizationSolution::get_api_definition() {
    using namespace masala::base::api;
    using base::Real;
    using base::Size;

    std::lock_guard< std::mutex > lock( solution_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The CostFunctionNetworkOptimizationSolution class stores the solution to a numerical "
                "cost function optimization problem.  This is the problem reduced to numbers, with no "
                "chemical classes or concepts included.",
                false, false
            )
        );

        // Constructors:

        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < CostFunctionNetworkOptimizationSolution > > (
                class_name(),
                "Creates an empty CostFunctionNetworkOptimizationSolution."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < CostFunctionNetworkOptimizationSolution, CostFunctionNetworkOptimizationProblem const & > > (
                class_name(),
                "Initialization constructor: initialize the solution from the problem definition.  (The problem definition "
                "deep-cloned and stored for future reference).",
                "problem_in", "The problem definition.  Copied but otherwise unaltered by this operation."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < CostFunctionNetworkOptimizationSolution, CostFunctionNetworkOptimizationSolution const & > > (
                class_name(),
                "Copy constructor: copies an input CostFunctionNetworkOptimizationSolution.",
                "src", "The input CostFunctionNetworkOptimizationSolution to copy.  Unaltered by this operation."
            )
        );

        // Work functions:
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput <void> > (
				"recompute_score", "Recompute the score for this solution.  This is useful, for instance, after "
				"an optimizer that uses approximate methods or low floating-point precision completes "
				"its work, to allow scores to be stored with full floating-point precision and accuracy.",
				false, false, false, true,
				"void", "Returns nothing", std::bind( &CostFunctionNetworkOptimizationSolution::recompute_score, this )
            )
        );

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
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationProblemCSP > >(
                "set_problem", "Set the problem that gave rise to this solution.",
                "problem_in", "Const shared pointer to the problem that gave rise to the solution.  This "
                "must be a cost function network optimizatoin problem, and this function will throw if it is "
                "not.  Used directly; not cloned.",
                false, true,
                std::bind( &CostFunctionNetworkOptimizationSolution::set_problem, this, std::placeholders::_1 )
            ) 
        );

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the problem that gave rise to this solution.
/// @details Used directly; not cloned.  This override checks that the problem
/// is a CostFunctionNetworkOptimizationProblem.
void
CostFunctionNetworkOptimizationSolution::set_problem(
    OptimizationProblemCSP const & problem
) {
    CHECK_OR_THROW_FOR_CLASS(
        std::dynamic_pointer_cast< CostFunctionNetworkOptimizationProblem const >( problem ) != nullptr,
        "set_problem", "A problem was passed to this function that was not a cost function network optimization problem."
    );
    OptimizationSolution::set_problem( problem );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Recompute the score of this solution.  This is useful, for instance, after
/// an optimizer that uses approximate methods or low floating-point precision completes
/// its work, to allow scores to be stored with full floating-point precision and accuracy.
/// @details The problem_ pointer must be set.
/// @note The base class recompute_score() function throws.  This override calls the
/// CostFunctionNetworkOptimizationProblem's calculators.
void
CostFunctionNetworkOptimizationSolution::recompute_score() {
    std::lock_guard< std::mutex > lock( solution_mutex() );
    CHECK_OR_THROW_FOR_CLASS( protected_problem() != nullptr, "recompute_score", "Cannot compute score until a "
        "problem has been associated with this solution.  Please finish configuring this problem by calling "
        "set_problem() before calling recompute_score()."
    );
#ifndef NDEBUG
    // In debug mode, use dynamic_pointer_cast with a check.
    CostFunctionNetworkOptimizationProblemCSP problem_cast( std::dynamic_pointer_cast< CostFunctionNetworkOptimizationProblem const >( protected_problem() ) );
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( problem_cast != nullptr, "recompute_score", "Somehow the problem associated with this "
        "solution was not a CostFunctionNetworkOptimizationProblem.  This should not be possible, and indicates a programming bug."
    );
#else
    // In release mode, use static_pointer_cast.  It shouldn't be possible for the pointer to be nonconst.
    CostFunctionNetworkOptimizationProblemCSP problem_cast( std::static_pointer_cast< CostFunctionNetworkOptimizationProblem const >( protected_problem() ) );
#endif

    set_solution_score( problem_cast->compute_absolute_score( solution_vector_ ) );
}

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
