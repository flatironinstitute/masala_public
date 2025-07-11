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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.cc
/// @brief Implementation for a class for a RealValuedFunctionLocalOptimizationProblem.
/// @details A RealValuedFunctionLocalOptimizationProblem defines a numerical minimization function to be solved by
/// gradient-based methods or other local optimization methods for an arbitrary loss function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>
#include <numeric>

// Numeric headers:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolutions.hh>

// Base headers:
#include <base/utility/execution_policy/util.hh>
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace real_valued_local {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.
RealValuedFunctionLocalOptimizationProblem::RealValuedFunctionLocalOptimizationProblem(
	RealValuedFunctionLocalOptimizationProblem const & src
) :
	masala::numeric::optimization::OptimizationProblem()
{
	std::lock( data_representation_mutex(), src.data_representation_mutex() );
	std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock );
	std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock );
	protected_assign(src);
}

// @brief Assignment operator.
RealValuedFunctionLocalOptimizationProblem &
RealValuedFunctionLocalOptimizationProblem::operator=(
	RealValuedFunctionLocalOptimizationProblem const & src
) {
	std::lock( data_representation_mutex(), src.data_representation_mutex() );
	std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock );
	std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock );
	protected_assign(src);
	return *this;
}

/// @brief Destructor.
RealValuedFunctionLocalOptimizationProblem::~RealValuedFunctionLocalOptimizationProblem() {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	if( objective_function_ != nullptr ) {
		delete objective_function_;
	}
	if( objective_function_gradient_ != nullptr ) {
		delete objective_function_gradient_;
	}
	// Base class destructor will be called automatically.
}

/// @brief Make a copy of this object, and return a shared pointer to the copy.
/// @details Does NOT copy all the internal data, but retains pointers to existing data.
masala::numeric::optimization::OptimizationProblemSP
RealValuedFunctionLocalOptimizationProblem::clone() const {
	return masala::make_shared< RealValuedFunctionLocalOptimizationProblem >( *this );
}

/// @brief Make a fully independent copy of this object.
RealValuedFunctionLocalOptimizationProblemSP
RealValuedFunctionLocalOptimizationProblem::deep_clone() const {
	RealValuedFunctionLocalOptimizationProblemSP new_problem( std::static_pointer_cast< RealValuedFunctionLocalOptimizationProblem >( clone() ) );
	new_problem->make_independent();
	return new_problem;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationProblem", "RealValuedFunctionLocalOptimizationProblem" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
RealValuedFunctionLocalOptimizationProblem::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem", "RealValuedFunctionLocalOptimizationProblem" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "local", "real_valued", "numeric" }
std::vector< std::string >
RealValuedFunctionLocalOptimizationProblem::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"local",
		"real_valued",
		"numeric"
	};
}

/// @brief Get the category for this MasalaDataRepresentation.
/// @returns { { "OptimizationProblem", "RealValuedFunctionLocalOptimizationProblem" } }.
std::vector< std::vector< std::string > >
RealValuedFunctionLocalOptimizationProblem::get_data_representation_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem", "RealValuedFunctionLocalOptimizationProblem" }
	};
}

/// @brief Get the keywords that this data representation plugin has.
/// @details Categories are hierarchical, with the hierarchy represented as a vector of
/// strings.  One data representation category can be classified into multiple categories.
/// @returns { "optimization_problem", "local", "real_valued", "numeric" }
std::vector< std::string >
RealValuedFunctionLocalOptimizationProblem::get_data_representation_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"local",
		"real_valued",
		"numeric"
	};
}

/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
/// is compatible.
/// @returns An empty list.
std::vector< std::string >
RealValuedFunctionLocalOptimizationProblem::get_compatible_masala_engines() const {
	return std::vector< std::string >{};
}

/// @brief Get the properties of this MasalaDataRepresentation.
/// @returns { "optimization_problem", "real_valued_local_optimization_problem" }.
std::vector< std::string >
RealValuedFunctionLocalOptimizationProblem::get_present_data_representation_properties() const {
	return std::vector< std::string >{ "optimization_problem", "real_valued_local_optimization_problem" };
}

/// @brief Get the name of this class.
/// @returns "RealValuedFunctionLocalOptimizationProblem".
std::string
RealValuedFunctionLocalOptimizationProblem::class_name() const {
	return "RealValuedFunctionLocalOptimizationProblem";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::real_valued_local".
std::string
RealValuedFunctionLocalOptimizationProblem::class_namespace() const {
	return "masala::numeric::optimization::real_valued_local";
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Has an objective function been provided for this problem?
bool
RealValuedFunctionLocalOptimizationProblem::has_objective_function() const {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	return objective_function_ != nullptr;
}

/// @brief Has a gradient for the objective function been provided for this problem?
bool
RealValuedFunctionLocalOptimizationProblem::has_objective_function_gradient() const {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	return objective_function_gradient_ != nullptr;
}

/// @brief Has at least one starting point been provided for this problem?
bool
RealValuedFunctionLocalOptimizationProblem::has_at_least_one_starting_point() const {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	return ( !starting_points_.empty() );
}

/// @brief Get the objective function.
/// @details Throws if objective function isn't set.
std::function< masala::base::Real( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) > const &
RealValuedFunctionLocalOptimizationProblem::objective_function() const {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "objective_function", "An objective function for this " + class_name() + "object can only be accessed after this object is finalized." );
	CHECK_OR_THROW_FOR_CLASS( objective_function_ != nullptr, "objective_function", "An objective function has not yet been set for this " + class_name() + "object!" );
	return *objective_function_;
}

/// @brief Get the objective function gradient.
/// @details Throws if objective function gradient isn't set.
std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &, Eigen::Vector< masala::base::Real, Eigen::Dynamic > & ) > const &
RealValuedFunctionLocalOptimizationProblem::objective_function_gradient() const {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "objective_function_gradient", "An objective function gradient for this " + class_name() + "object can only be accessed after this object is finalized." );
	CHECK_OR_THROW_FOR_CLASS( objective_function_gradient_ != nullptr, "objective_function_gradient", "An objective function gradient has not yet been set for this " + class_name() + "object!" );
	return *objective_function_gradient_;
}

/// @brief Access the vector of starting points.
std::vector< Eigen::Vector< masala::base::Real, Eigen::Dynamic > > const &
RealValuedFunctionLocalOptimizationProblem::starting_points() const {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "starting_points", "The starting points for this " + class_name() + "object can only be accessed after this object is finalized." );
	return starting_points_;
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the objective function.
/// @details The function object is copied.
void
RealValuedFunctionLocalOptimizationProblem::set_objective_function(
	std::function< masala::base::Real( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) > const & objective_fxn_in
) {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "set_objective_function", "Cannot set objective function after the " + class_name() + " object has been finalized." );

	if( objective_function_ != nullptr ) {
		delete objective_function_;
	}
	objective_function_ = new std::function< masala::base::Real( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) >( objective_fxn_in );
}

/// @brief Clear the objective function.
void
RealValuedFunctionLocalOptimizationProblem::clear_objective_function() {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "clear_objective_function", "Cannot unset objective function after the " + class_name() + " object has been finalized." );
	if( objective_function_ != nullptr ) {
		delete objective_function_;
	}
	objective_function_ = nullptr;
}

/// @brief Set the objective function derivative.
/// @details The derivative function object is copied.
void
RealValuedFunctionLocalOptimizationProblem::set_objective_function_gradient(
	std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &, Eigen::Vector< masala::base::Real, Eigen::Dynamic > & ) > const & objective_fxn_gradient_in
) {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "set_objective_function_gradient", "Cannot set objective function gradient after the " + class_name() + " object has been finalized." );

	if( objective_function_gradient_ != nullptr ) {
		delete objective_function_gradient_;
	}
	objective_function_gradient_ = new std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &, Eigen::Vector< masala::base::Real, Eigen::Dynamic > & ) >( objective_fxn_gradient_in );
}

/// @brief Clear the objective function.
void
RealValuedFunctionLocalOptimizationProblem::clear_objective_function_gradient() {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "clear_objective_function_gradient", "Cannot unset objective function gradient after the " + class_name() + " object has been finalized." );
	if( objective_function_gradient_ != nullptr ) {
		delete objective_function_gradient_;
	}
	objective_function_gradient_ = nullptr;
}

/// @brief Add a bunch of starting points to the set of starting points for local minimum search.
void
RealValuedFunctionLocalOptimizationProblem::add_starting_points(
	std::vector< Eigen::Vector< masala::base::Real, Eigen::Dynamic > > const & starting_points_in
) {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "add_starting_points", "Starting points cannot be added after this " + class_name() + " object has been finalized." );
	starting_points_.reserve( starting_points_.size() + starting_points_in.size() );
	for( auto const & entry : starting_points_in ) {
		starting_points_.push_back( entry );
	}
}


/// @brief Add a single point to the set of starting points for local minimum search.
void
RealValuedFunctionLocalOptimizationProblem::add_starting_point(
	Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & starting_point_in
) {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "add_starting_point", "A starting point cannot be added after this " + class_name() + " object has been finalized." );
	starting_points_.push_back( starting_point_in );
}

/// @brief Clear the starting points.
void
RealValuedFunctionLocalOptimizationProblem::clear_starting_points() {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "clear_starting_points", "Starting points cannot be cleared after this " + class_name() + " object has been finalized." );
	starting_points_.clear();
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the RealValuedFunctionLocalOptimizationProblem class.
masala::base::api::MasalaObjectAPIDefinitionCWP
RealValuedFunctionLocalOptimizationProblem::get_api_definition() {
	using namespace masala::base::api;
	using namespace masala::base::api::setter;
	using namespace masala::base::api::getter;

	std::lock_guard< std::mutex > lock( data_representation_mutex() );

	if( api_definition() == nullptr ) {

		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this,
				"The RealValuedFunctionLocalOptimizationProblem class defines a numerical minimization "
				"problem for an arbitrary loss function, where the solution will be found by some sort "
				"of gradient descent algorithm or other algorithm that finds a local minimum.",
				false, false
			)
		);

		// Constructors:
		ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( RealValuedFunctionLocalOptimizationProblem, api_def );

		// Getters:
		api_def->add_getter(
			masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< bool > >(
				"has_objective_function", "Has an objective function been provided for this problem?",
				"has_objective_function", "True if an objective function has been provided, false otherwise.",
				false, false, std::bind( &RealValuedFunctionLocalOptimizationProblem::has_objective_function, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< bool > >(
				"has_objective_function_gradient", "Has an objective function gradient been provided for this problem?",
				"has_objective_function_gradient", "True if an objective function gradient has been provided, false otherwise.",
				false, false, std::bind( &RealValuedFunctionLocalOptimizationProblem::has_objective_function_gradient, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< bool > >(
				"has_at_least_one_starting_point", "Has at least one starting point been provided for the local optimum search?",
				"has_at_least_one_starting_point", "True if at least one starting point has been provided, false otherwise.",
				false, false, std::bind( &RealValuedFunctionLocalOptimizationProblem::has_at_least_one_starting_point, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< std::function< masala::base::Real( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) > const & > >(
				"objective_function", "Get the objective function.  Throws if objective function isn't set.",
				"objective_function", "The objective function for which we're trying to find a local minimum.",
				false, false, std::bind( &RealValuedFunctionLocalOptimizationProblem::objective_function, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &, Eigen::Vector< masala::base::Real, Eigen::Dynamic > & ) > const & > >(
				"objective_function_gradient", "Get the objective function gradient.  Throws if objective function gradient isn't set.",
				"objective_function_gradient", "The objective function gradient.",
				false, false, std::bind( &RealValuedFunctionLocalOptimizationProblem::objective_function_gradient, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< std::vector< Eigen::Vector< masala::base::Real, Eigen::Dynamic > > const & > >(
				"starting_points", "Access the vector of starting points.  (Could be empty.)",
				"starting_points", "The vector of starting points for the local optimum search.",
				false, false, std::bind( &RealValuedFunctionLocalOptimizationProblem::starting_points, this )
			)
		);

		// Setters:
		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_OneInput< std::function< masala::base::Real( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) > const & > >(
				"set_objective_function", "Set the objective function for which we want to find a local minimum.",
				"objective_function_in", "The objective function for which we want to find a local minimum.  This is a std::function that takes as input a vector of "
				"real numbers (a coordinate in R^N) and returns a real number.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationProblem::set_objective_function, this, std::placeholders::_1 )
			)
		);
		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_ZeroInput >(
				"clear_objective_function", "Unset the objective function.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationProblem::clear_objective_function, this )
			)
		);
		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_OneInput<std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &, Eigen::Vector< masala::base::Real, Eigen::Dynamic > & ) > const & > >(
				"set_objective_function_gradient", "Set the gradient of the objective function for which we want to find a local minimum.",
				"objective_function_gradient_in", "The gradient of the objective function for which we want to find a local minimum.  This is a std::function that takes as input a vector of "
				"real numbers (a coordinate in R^N) and a nonconst vector of real numbers; the latter is populated with the gradient with respect to the input "
				"coordinates.  The function also returns a real number for the value of the function at the coordinate.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationProblem::set_objective_function_gradient, this, std::placeholders::_1 )
			)
		);
		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_ZeroInput >(
				"clear_objective_function_gradient", "Unset the objective function gradient.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationProblem::clear_objective_function_gradient, this )
			)
		);
		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_OneInput< std::vector< Eigen::Vector< masala::base::Real, Eigen::Dynamic > > const & > >(
				"add_starting_points", "Add multiple starting points to the set of starting points for local optimum search.",
				"starting_poinst_in", "A vector of coordinates in R^N, each specifying a starting point for the local optimimum search.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationProblem::add_starting_points, this, std::placeholders::_1 )
			)
		);
		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_OneInput< Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & > >(
				"add_starting_point", "Add a single point to the set of starting points for local optimum search.",
				"starting_point_in", "A coordinate in R^N, specifying a starting point for the local optimimum search.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationProblem::add_starting_point, this, std::placeholders::_1 )
			)
		);
		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_ZeroInput >(
				"clear_starting_points", "Clear the starting points for the local optimum search.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationProblem::clear_starting_points, this )
			)
		);

		// Work functions:

		api_definition() = api_def; //Make const.
	}

	return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Is this data representation empty?
/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
/// @returns True if no data have been loaded into this data representation, false otherwise.
/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
bool
RealValuedFunctionLocalOptimizationProblem::protected_empty() const {
	return (
		( objective_function_ == nullptr ) &&
		( objective_function_gradient_ == nullptr ) &&
		( starting_points_.empty() ) &&
		masala::numeric::optimization::OptimizationProblem::protected_empty()
	);
}

/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
void
RealValuedFunctionLocalOptimizationProblem::protected_clear() {
	if( objective_function_ != nullptr ) {
		delete objective_function_;
	}
	objective_function_ = nullptr;

	if( objective_function_gradient_ != nullptr ) {
		delete objective_function_gradient_;
	}
	objective_function_gradient_ = nullptr;

	starting_points_.clear();
	masala::numeric::optimization::OptimizationProblem::protected_clear();
}

/// @brief Reset this object completely.  Mutex must be locked before calling.
void 
RealValuedFunctionLocalOptimizationProblem::protected_reset() {
	protected_clear();
	masala::numeric::optimization::OptimizationProblem::protected_reset();
}

/// @brief Make this object independent.
/// @details Assumes mutex was already locked.
/// @note Derived versions of this function should call the parent class version too.
void
RealValuedFunctionLocalOptimizationProblem::protected_make_independent() {
	using masala::base::Real;
	if( objective_function_ != nullptr ) {
		std::function<Real (Eigen::Vector< Real, Eigen::Dynamic > const &)> const * oldfunc( objective_function_ );
		objective_function_ = new std::function<Real (Eigen::Vector< Real, Eigen::Dynamic > const &)>( *oldfunc );
		delete oldfunc;
	}
	if( objective_function_gradient_ != nullptr ) {
		std::function<Real (Eigen::Vector< Real, Eigen::Dynamic > const &, Eigen::Vector< Real, Eigen::Dynamic > &)> const * oldfunc( objective_function_gradient_ );
		objective_function_gradient_ = new std::function<Real (Eigen::Vector< Real, Eigen::Dynamic > const &, Eigen::Vector< Real, Eigen::Dynamic > &) >( *oldfunc );
		delete oldfunc;
	}
	masala::numeric::optimization::OptimizationProblem::protected_make_independent();
}

/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
void
RealValuedFunctionLocalOptimizationProblem::protected_finalize() {
	using masala::base::Size;
	// Do a series of checks:
	if( starting_points_.size() > 1 ) {
		CHECK_OR_THROW_FOR_CLASS( starting_points_[0].size() > 0, "protected_finalize",
			"A zero-size starting point vector was encountered for starting point 1."
		);
		Size const nentries( static_cast< Size >( starting_points_[0].size() ) );
		for( Size i(1); i<starting_points_.size(); ++i ) {
			CHECK_OR_THROW_FOR_CLASS( starting_points_[i].size() > 0, "protected_finalize",
				"A zero-size starting point vector was encountered for starting point "
				+ std::to_string(i+1) + "."
			);
			CHECK_OR_THROW_FOR_CLASS( static_cast< Size >( starting_points_[i].size() ) == nentries, "protected_finalize",
				"The number of entries in starting point vector " + std::to_string(i) + " is " +
				std::to_string( starting_points_[i].size() ) + ", but entry 0 had " +
				std::to_string(nentries) + " entries."
			);
		}
	}
	masala::numeric::optimization::OptimizationProblem::protected_finalize();
}

/// @brief Inner workings of assignment operator.  Should be called with locked mutex.
/// Should be implemented by derived classes, which shoudl call base class function.
void
RealValuedFunctionLocalOptimizationProblem::protected_assign(
	masala::base::managers::engine::MasalaDataRepresentation const & src
) {
	RealValuedFunctionLocalOptimizationProblem const * src_ptr_cast(
		dynamic_cast< RealValuedFunctionLocalOptimizationProblem const * >( &src )
	);
	CHECK_OR_THROW_FOR_CLASS( src_ptr_cast != nullptr, "protected_assign", "Could not assign an "
		"object of type " + src.class_name() + " to an object of type " + class_name() + "."
	);

	if( objective_function_ != nullptr ) { delete objective_function_; }
	if( objective_function_gradient_ != nullptr ) { delete objective_function_gradient_; }
	if( src_ptr_cast->objective_function_ != nullptr ) {
		objective_function_ = new std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) >( *src_ptr_cast->objective_function_ );
	} else {
		objective_function_ = nullptr;
	}
	if( src_ptr_cast->objective_function_gradient_ != nullptr ) {
		objective_function_gradient_ = new std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &, Eigen::Vector< masala::base::Real, Eigen::Dynamic > & ) >( *src_ptr_cast->objective_function_gradient_ );
	} else {
		objective_function_gradient_ = nullptr;
	}

	starting_points_ = src_ptr_cast->starting_points_;
	masala::numeric::optimization::OptimizationProblem::protected_assign(src);
}


} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala
