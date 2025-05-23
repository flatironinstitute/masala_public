/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/numeric_api/base_classes/optimization/real_valued_local/PluginRealValuedFunctionLocalOptimizer.cc
/// @brief Implementation for a pure virtual base class for PluginRealValuedFunctionLocalOptimizers.
/// @details PluginRealValuedFunctionLocalOptimizers solve a numerical loss function minimization problem using
/// gradients of the loss function with respect to free parameters.  They have no chemical knowledge.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/real_valued_local/PluginRealValuedFunctionLocalOptimizer.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/OptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolutions_API.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace real_valued_local {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.  Explicit due to mutex.
PluginRealValuedFunctionLocalOptimizer::PluginRealValuedFunctionLocalOptimizer(
	PluginRealValuedFunctionLocalOptimizer const & src
) :
	Parent( src )
{
	std::lock( mutex_, src.mutex_ );
	std::lock_guard< std::mutex > lockthis( mutex_, std::adopt_lock );
	std::lock_guard< std::mutex > lockthat( src.mutex_, std::adopt_lock );
	protected_assign( src );
}

/// @brief Assignment operator.  Explicit due to mutex.
PluginRealValuedFunctionLocalOptimizer &
PluginRealValuedFunctionLocalOptimizer::operator=(
	PluginRealValuedFunctionLocalOptimizer const & src
) {
	std::lock( mutex_, src.mutex_ );
	std::lock_guard< std::mutex > lockthis( mutex_, std::adopt_lock );
	std::lock_guard< std::mutex > lockthat( src.mutex_, std::adopt_lock );
	protected_assign( src );
	return *this;
}

/// @brief Make this object independent by calling deep_clone on all contained objects.
void
PluginRealValuedFunctionLocalOptimizer::make_independent() {
	std::lock_guard< std::mutex > lock( mutex_ );
	protected_make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all optimizers;
/// may be overridden by derived classes.
/// @returns { { "Optimizer", "PluginRealValuedFunctionLocalOptimizer" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
PluginRealValuedFunctionLocalOptimizer::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "Optimizer", "PluginRealValuedFunctionLocalOptimizer" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
/// by derived classes.
/// @returns { "optimizer", "real_valued", "local_optimizer", "numeric" }
std::vector< std::string >
PluginRealValuedFunctionLocalOptimizer::get_keywords() const {
	return std::vector< std::string > {
		"optimizer",
		"real_valued",
		"local_optimizer",
		"numeric"
	};
}

/// @brief Categories for engines.
/// @details Like plugin categories, engine categories are hierarchical.  The hieraruchy
/// is important for deciding what engines are equvalent. For instance, if I had
/// "Solver"->"KinematicSolver"->"AnalyticKinematicSolver", I could request only the analytic
/// kinematic solvers, all kinematic solvers, or all solvers in general.
/// @note An engine may exist in more than one hierarchical category.  The outer vector is
/// a list of hierarchical categories, and the inner vector is the particular hierarchical
/// category, from most general to most specific.  Also note that this function is pure
/// virtual, and must be defined for instantiable MasalaEngine subclasses.
/// @returns { {"Optimizer", "PluginRealValuedFunctionLocalOptimizer"} }
std::vector< std::vector < std::string > >
PluginRealValuedFunctionLocalOptimizer::get_engine_categories() const {
    return std::vector< std::vector < std::string > >{ { "Optimizer", "PluginRealValuedFunctionLocalOptimizer" } };
}

/// @brief Keywords for engines.
/// @returns { "optimizer", "real_valued", "local_optimizer", "numeric" }
std::vector < std::string >
PluginRealValuedFunctionLocalOptimizer::get_engine_keywords() const {
	return std::vector< std::string > {
		"optimizer",
		"real_valued",
		"local_optimizer",
		"numeric"
	};
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the number of threads to request.
/// @param setting The number of threads to request.  A value of 0 means "request all available"
void
PluginRealValuedFunctionLocalOptimizer::set_threads_to_request(
    masala::base::Size const setting
) {
    std::lock_guard< std::mutex > lock( mutex_ );
    threads_to_request_ = setting;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief get the number of threads to request.
/// @returns The number of threads to request.  A value of 0 means "request all available"
masala::base::Size
PluginRealValuedFunctionLocalOptimizer::threads_to_request() const {
    std::lock_guard< std::mutex > lock( mutex_ );
    return threads_to_request_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Run the optimizer on a set of optimization problems, and produce a set of solutions.
/// @details Must be implemented by derived classes.   Each solutions set in the vector of solutions corresponds to
/// the problem with the same index.
std::vector< masala::numeric_api::auto_generated_api::optimization::OptimizationSolutions_APICSP >
PluginRealValuedFunctionLocalOptimizer::run_optimizer(
    masala::numeric_api::auto_generated_api::optimization::OptimizationProblems_API const & problems
) const {
    using namespace masala::numeric_api::auto_generated_api::optimization;
    using namespace masala::numeric_api::auto_generated_api::optimization::real_valued_local;
    RealValuedFunctionLocalOptimizationProblems_API const * problems_cast( dynamic_cast< RealValuedFunctionLocalOptimizationProblems_API const * >( &problems ) );
    CHECK_OR_THROW_FOR_CLASS(
        problems_cast != nullptr,
        "run_optimizer",
        "A set of optimization problems was passed to the run_optimizer function, but it was not "
        "a set of gradient-based function optimization problems."
    );

    std::vector< RealValuedFunctionLocalOptimizationSolutions_APICSP > const outvec1( run_real_valued_local_optimizer( *problems_cast ) );

    // Conversion to base class pointers requires another step, irritatingly:
    std::vector< OptimizationSolutions_APICSP > outvec2( outvec1.size() );
    for( base::Size i(0), imax(outvec1.size()); i<imax; ++i ) {
        outvec2[i] = outvec1[i];
    }

    return outvec2;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Access the mutex from derived classes.
std::mutex &
PluginRealValuedFunctionLocalOptimizer::mutex() const {
	return mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.  Performs no mutex locking.
masala::base::api::MasalaObjectAPIDefinitionCSP &
PluginRealValuedFunctionLocalOptimizer::api_definition() {
	return api_definition_;
}

/// @brief Assignment: must be implemented by derived classes, which must call the base
/// class protected_assign().
/// @details Performs no mutex locking.
void
PluginRealValuedFunctionLocalOptimizer::protected_assign(
	PluginRealValuedFunctionLocalOptimizer const & src
) {
	threads_to_request_ = src.threads_to_request_;
    //Parent::protected_assign(src);
}


/// @brief Make independent: must be implemented by derived classes, which must call the base
/// class protected_make_independent().
/// @details Performs no mutex locking.
void
PluginRealValuedFunctionLocalOptimizer::protected_make_independent() {
	// GNDN.
}

} // namespace real_valued_local
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
