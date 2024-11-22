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
	masala::base::managers::engine::MasalaDataRepresentation()
{
	std::lock( data_representation_mutex(), src.data_representation_mutex() );
	std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock );
	std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock );
	finalized_.store(false);
	protected_assign(src);
}

/// @brief Make a copy of this object, and return a shared pointer to the copy.
/// @details Does NOT copy all the internal data, but retains pointers to existing data.
OptimizationProblemSP
OptimizationProblem::clone() const {
	return masala::make_shared< OptimizationProblem >( *this );
}

/// @brief Make a fully independent copy of this object.
OptimizationProblemSP
OptimizationProblem::deep_clone() const {
	OptimizationProblemSP new_object( clone() );
	new_object->make_independent();
	return new_object;
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

/// @brief Get the keywords that this data representation plugin has.
/// @details Categories are hierarchical, with the hierarchy represented as a vector of
/// strings.  One data representation category can be classified into multiple categories.
/// @returns { "optimization_problem", "numeric" }
std::vector< std::string >
OptimizationProblem::get_data_representation_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"numeric"
	};
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

/// @brief Finalize this problem: indicate that all problem setup is complete, and
/// carry out any precomputation necessary for efficient solution.
/// @details Derived classes should probably override this.
void
OptimizationProblem::finalize() {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	protected_finalize();
}

/// @brief Has this problem been finalized?
/// @details Locks mutex for check.
bool
OptimizationProblem::finalized() const {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	return protected_finalized();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the OptimizationProblem class.
masala::base::api::MasalaObjectAPIDefinitionCWP
OptimizationProblem::get_api_definition() {
	using namespace masala::base::api;


	std::lock_guard< std::mutex > lock( data_representation_mutex() );

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
		"This function was called on a " + class_name() + "problem definition that was already finalized!"
	);
	finalized_ = true;
}

/// @brief Inner workings of assignment operator.  Should be called with locked mutex.
/// Should be implemented by derived classes, which shoudl call base class function.
void
OptimizationProblem::protected_assign(
	Parent const & src
) {
	OptimizationProblem const * src_cast_ptr( dynamic_cast< OptimizationProblem const * >( &src ) );
	CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "protected_assign", "The " + src.class_name() + " object passed to this "
		"function was not an OptimizationProblem object."
	);
	CHECK_OR_THROW_FOR_CLASS( !finalized_, "protected_assign",
		"This function was called on a " + class_name() + " problem definition that was already finalized!"
	);
	Parent::protected_assign( src );
}

/// @brief Reset all data in this object.
/// @details Sets state to not finalized.  Mutex must be locked before calling this.
void
OptimizationProblem::protected_reset() {
	finalized_.store(false);
	//Parent::protected_reset();
}

/// @brief Make this object independent.
/// @details Assumes mutex was already locked.
/// @note Derived versions of this function should call the parent class version too.
void
OptimizationProblem::protected_make_independent() {
	api_definition_ = nullptr;
	//Parent::protected_make_independent();
}

/// @brief Is this data representation empty?
/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
/// @returns True if no data have been loaded into this data representation, false otherwise.
/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
bool
OptimizationProblem::protected_empty() const {
	return true;
}

/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
void
OptimizationProblem::protected_clear() {
	// GNDN.
}

} // namespace optimization
} // namespace numeric
} // namespace masala
