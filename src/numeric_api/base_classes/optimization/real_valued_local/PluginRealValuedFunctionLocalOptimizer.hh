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

/// @file src/numeric_api/base_classes/optimization/real_valued_local/PluginRealValuedFunctionLocalOptimizer.hh
/// @brief Header for a pure virtual base class for PluginRealValuedFunctionLocalOptimizers.
/// @details PluginRealValuedFunctionLocalOptimizers solve a numerical loss function minimization problem using
/// gradients of the loss function with respect to free parameters.  They have no chemical knowledge.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginRealValuedFunctionLocalOptimizer_hh
#define Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginRealValuedFunctionLocalOptimizer_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/real_valued_local/PluginRealValuedFunctionLocalOptimizer.fwd.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblems_API.fwd.hh>
#include <numeric_api/auto_generated_api/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolutions_API.fwd.hh>

// Base headers:
#include <base/types.hh>

// Parent header:
#include <numeric_api/base_classes/optimization/PluginOptimizer.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace real_valued_local {

/// @brief A pure virtual base class for PluginRealValuedFunctionLocalOptimizers.
/// @details PluginRealValuedFunctionLocalOptimizers solve a numerical loss function minimization problem using
/// gradients of the loss function with respect to free parameters.  They have no chemical knowledge.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginRealValuedFunctionLocalOptimizer : public masala::numeric_api::base_classes::optimization::PluginOptimizer {

	typedef masala::numeric_api::base_classes::optimization::PluginOptimizer Parent;
	typedef masala::numeric_api::base_classes::optimization::PluginOptimizerSP ParentSP;
	typedef masala::numeric_api::base_classes::optimization::PluginOptimizerCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginRealValuedFunctionLocalOptimizer() = default;

	/// @brief Copy constructor.  Explicit due to mutex.
	PluginRealValuedFunctionLocalOptimizer( PluginRealValuedFunctionLocalOptimizer const & src);

	/// @brief Assignment operator.  Explicit due to mutex.
	PluginRealValuedFunctionLocalOptimizer & operator=( PluginRealValuedFunctionLocalOptimizer const & src );

	/// @brief Destructor.
	~PluginRealValuedFunctionLocalOptimizer() override = default;

	/// @brief Clone operation: copy this object and return a shared pointer to the
	/// copy.  Contained objects may still be shared.
	virtual
	PluginRealValuedFunctionLocalOptimizerSP
	clone() const = 0;

	/// @brief Make this object independent by calling deep_clone on all contained objects.
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all optimizers;
	/// may be overridden by derived classes.
	/// @returns { { "Optimizer", "RealValuedFunctionLocalOptimizer" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
	/// by derived classes.
	/// @returns { "optimizer", "real_valued", "local_optimizer", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Categories for engines.
    /// @details Like plugin categories, engine categories are hierarchical.  The hieraruchy
    /// is important for deciding what engines are equvalent. For instance, if I had
    /// "Solver"->"KinematicSolver"->"AnalyticKinematicSolver", I could request only the analytic
    /// kinematic solvers, all kinematic solvers, or all solvers in general.
    /// @note An engine may exist in more than one hierarchical category.  The outer vector is
    /// a list of hierarchical categories, and the inner vector is the particular hierarchical
    /// category, from most general to most specific.  Also note that this function is pure
    /// virtual, and must be defined for instantiable MasalaEngine subclasses.
	/// @returns { {"Optimizer", "RealValuedFunctionLocalOptimizer"} }
    std::vector< std::vector < std::string > >
    get_engine_categories() const override;

	/// @brief Keywords for engines.
	/// @returns { "optimizer", "real_valued", "local_optimizer", "numeric" }
	std::vector < std::string >
	get_engine_keywords() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the number of threads to request.
	/// @param setting The number of threads to request.  A value of 0 means "request all available"
	void set_threads_to_request( masala::base::Size const setting );

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief get the number of threads to request.
	/// @returns The number of threads to request.  A value of 0 means "request all available"
	masala::base::Size threads_to_request() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Run the optimizer on a set of optimization problems, and produce a set of solutions.
	/// @details Must be implemented by derived classes.  Each solutions set in the vector of solutions corresponds to
	/// the problem with the same index.
	std::vector< masala::numeric_api::auto_generated_api::optimization::OptimizationSolutions_APICSP >
	run_optimizer(
		masala::numeric_api::auto_generated_api::optimization::OptimizationProblems_API const & problems
	) const override;

	/// @brief Run the optimizer on a set of gradient-based loss function minimization problems, and produce a set of solutions.
	/// @details Must be implemented by derived classes.  Each solutions set in the vector of solutions corresponds to
	/// the problem with the same index.
	virtual
	std::vector< masala::numeric_api::auto_generated_api::optimization::real_valued_local::RealValuedFunctionLocalOptimizationSolutions_APICSP >
	run_real_valued_local_optimizer(
		masala::numeric_api::auto_generated_api::optimization::real_valued_local::RealValuedFunctionLocalOptimizationProblems_API const & problems
	) const = 0;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Access the mutex from derived classes.
	std::mutex & mutex() const;

	/// @brief Allow derived classes to access the API definition.
	/// @note Could be nullptr.  Performs no mutex locking.
	masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition();

	/// @brief Access the number of threads to request.  Assumes that the mutex has been locked.
	inline
	masala::base::Size
	protected_threads_to_request() const {
		return threads_to_request_;
	}

	/// @brief Assignment: must be implemented by derived classes, which must call the base
	/// class protected_assign().
	/// @details Performs no mutex locking.
	virtual
	void
	protected_assign(
		PluginRealValuedFunctionLocalOptimizer const & src
	);

	/// @brief Make independent: must be implemented by derived classes, which must call the base
	/// class protected_make_independent().
	/// @details Performs no mutex locking.
	virtual
	void
	protected_make_independent();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex to lock this object.
	mutable std::mutex mutex_;

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief The number of threads to request.  Defaults to 0, meaning "request all available".
	masala::base::Size threads_to_request_ = 0;

}; // class PluginRealValuedFunctionLocalOptimizer

} // namespace real_valued_local
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginRealValuedFunctionLocalOptimizer_hh