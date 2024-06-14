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

// Numeric headers:
#include <numeric/optimization/OptimizationSolutions.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
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
OptimizationProblem::OptimizationProblem(
    OptimizationProblem const & src
) :
    masala::base::managers::engine::MasalaDataRepresentation(src)
{
    std::lock_guard< std::mutex > lock( src.problem_mutex_ );
    finalized_ = src.finalized_.load();
}

/// @brief Assignment operator.
OptimizationProblem &
OptimizationProblem::operator=(
    OptimizationProblem const & src
) {
    masala::base::managers::engine::MasalaDataRepresentation::operator=(src);
    {
        std::lock( problem_mutex_, src.problem_mutex_ );
        std::lock_guard< std::mutex > lock( problem_mutex_, std::adopt_lock );
        std::lock_guard< std::mutex > lock2( src.problem_mutex_, std::adopt_lock );
        finalized_ = src.finalized_.load();
    }
    return *this;
}

/// @brief Make a fully independent copy of this object.
OptimizationProblemSP
OptimizationProblem::deep_clone() const {
    OptimizationProblemSP new_object( masala::make_shared< OptimizationProblem >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
OptimizationProblem::make_independent() {
    std::lock_guard< std::mutex > lock( problem_mutex_ );
    protected_make_independent();
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

/// @brief Get the categories that this data representation plugin falls into.
/// @details Categories are hierarchical, with the hierarchy represented as a vector of
/// strings.  One data representation category can be classified into multiple categories.
/// @returns {{ "OptimizationProblem" }}
std::vector< std::vector< std::string > >
OptimizationProblem::get_data_representation_categories() const {
    return std::vector< std::vector< std::string > >{{"OptimizationProblem"}};
}

/// @brief Get the MasalaEngines that with which this data representation plugin
/// is DEFINITELY compatible.  (There may be other engines with which it is also
/// compatible, so this is not necessarily an exhaustive list.)
/// @note Must be implemented by derived classes.  The list is by full name (i.e.
/// namespace + name), so for instance
/// "specialized_masala_plugins::optimizers::SpecializedChargeOptimizer".
/// @returns An empty list.
std::vector< std::string >
OptimizationProblem::get_compatible_masala_engines() const {
    return std::vector< std::string >{};
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

/// @brief Reset all data in this object.
void
OptimizationProblem::reset() {
    std::lock_guard< std::mutex > lock( problem_mutex_ );
    OptimizationProblem::protected_reset();
}

/// @brief Finalize this problem: indicate that all problem setup is complete, and
/// carry out any precomputation necessary for efficient solution.
/// @details Derived classes should probably override this.
void
OptimizationProblem::finalize() {
    std::lock_guard< std::mutex > lock( problem_mutex_ );
    OptimizationProblem::protected_finalize();
}

/// @brief Has this problem been finalized?
/// @details Locks mutex for check.
bool
OptimizationProblem::finalized() const {
    std::lock_guard< std::mutex > lock( problem_mutex_ );
    return OptimizationProblem::protected_finalized();
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
                false, false
            )
        );

        // Constructors:
        ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( OptimizationProblem, api_def );

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< bool > >(
                "finalized", "Has this problem description been finalized?  That is, is the problem setup "
                "complete and the object locked to now be read-only?",
                "finalized", "True if the object has been finalized, false otherwise.",
                false, false,
                std::bind( &OptimizationProblem::finalized, this )
            )
        );

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "finalize", "Finalize this object completely -- i.e. indicate that all problem setup is complete, and "
                "the object should now be read-only.  May be overridden by derived classes.",
                true, false, std::bind( &OptimizationProblem::finalize, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Reset this object completely.  (Resets finalization state.)",
                true, false, std::bind( &OptimizationProblem::reset, this )
            )
        );

        // Work functions:
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput< OptimizationSolutionsSP > >(
                "create_solutions_container", "Create a solutions container for this type of optimization problem.  "
				"Base class implementation creates a generic OptimizationSolutions container.  Derived classes may "
				"override this to create specialized solutions containers.",
				true, false, true, false,
				"solutions_container", "An OptimizationSolutions object (or instance of a derived class thereof) for holding "
				"solutions to this optimization problem.",
				std::bind( &OptimizationProblem::create_solutions_container, this )
            )
        );

        api_definition_ = api_def; //Make const.
    }

    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Create a solutions container for this type of optimization problem.
/// @details Base class implementation creates a generic OptimizationSolutions container.  Derived
/// classes may override this to create specialized solutions containers.
OptimizationSolutionsSP
OptimizationProblem::create_solutions_container() const {
    return masala::make_shared< OptimizationSolutions >();
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

/// @brief Inner workings of finalize function.  Should be called with locked mutex.
/// Base class protected_finalize() sets finalized_ to true.
void
OptimizationProblem::protected_finalize() {
    CHECK_OR_THROW_FOR_CLASS( !finalized_, "protected_finalize",
        "This function was called on a problem definition that was already finalized!"
    );
    finalized_ = true;
}

/// @brief Reset all data in this object.
/// @details Sets state to not finalized.  Mutex must be locked before calling this.
void
OptimizationProblem::protected_reset() {
    finalized_ = false;
}

/// @brief Make this object independent.
/// @details Assumes mutex was already locked.
/// @note Derived versions of this function should call the parent class version too.
void
OptimizationProblem::protected_make_independent() {
	api_definition_ = nullptr;
}

} // namespace optimization
} // namespace numeric
} // namespace masala
