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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizer.hh
/// @brief Header for a pure virtual base class for PluginCostFunctionNetworkOptimizers.
/// @details PluginCostFunctionNetworkOptimizers solve a numerical cost function network optimization
/// problem.  They have no chemical knowledge.  Cost function network problems include the packing
/// or side-chain optimization problem.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizer_hh
#define Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizer_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizer.fwd.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblems_API.fwd.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions_API.fwd.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationAPI.hh>

// Parent header:
#include <numeric_api/base_classes/optimization/PluginOptimizer.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {

/// @brief A pure virtual base class for PluginCostFunctionNetworkOptimizers.
/// @details PluginCostFunctionNetworkOptimizers solve a numerical cost function network optimization
/// problem.  They have no chemical knowledge.  Cost function network problems include the packing
/// or side-chain optimization problem.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginCostFunctionNetworkOptimizer : public masala::numeric_api::base_classes::optimization::PluginOptimizer {

	typedef masala::numeric_api::base_classes::optimization::PluginOptimizer Parent;
	typedef masala::numeric_api::base_classes::optimization::PluginOptimizerSP ParentSP;
	typedef masala::numeric_api::base_classes::optimization::PluginOptimizerCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS, DESTRUCTORS, ETC.
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginCostFunctionNetworkOptimizer() = default;

	/// @brief Copy constructor.  Explicit due to mutex.
	PluginCostFunctionNetworkOptimizer( PluginCostFunctionNetworkOptimizer const & src );

	/// @brief Assignment operator.  Explicit due to mutex.
	PluginCostFunctionNetworkOptimizer &
	operator= ( PluginCostFunctionNetworkOptimizer const & src );

	/// @brief Destructor.
	~PluginCostFunctionNetworkOptimizer() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all optimizers;
	/// may be overridden by derived classes.
	/// @returns { { "Optimizer", "CostFunctionNetworkOptimizer" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
	/// by derived classes.
	/// @returns { "optimizer", "cost_function_network", "numeric" }
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
	/// @returns { {"Optimizer", "CostFunctionNetworkOptimizer"} }
    std::vector< std::vector < std::string > >
    get_engine_categories() const override;

	/// @brief Keywords for engines.
	/// @returns { "optimizer", "cost_function_network", "numeric" }
    std::vector < std::string >
    get_engine_keywords() const override;

	/// @brief Run the optimizer on a set of optimization problems, and produce a set of solutions.
	/// @details Must be implemented by derived classes.  Each solutions set in the vector of solutions corresponds to
	/// the problem with the same index.
	std::vector< masala::numeric_api::auto_generated_api::optimization::OptimizationSolutions_APICSP >
	run_optimizer(
		masala::numeric_api::auto_generated_api::optimization::OptimizationProblems_API const & problems
	) const override;

	/// @brief Run the optimizer on a set of cost function network optimization problems, and produce a set of solutions.
	/// @details Must be implemented by derived classes.  Each solutions set in the vector of solutions corresponds to
	/// the problem with the same index.
	virtual
	std::vector< masala::numeric_api::auto_generated_api::optimization::cost_function_network::CostFunctionNetworkOptimizationSolutions_APICSP >
	run_cost_function_network_optimizer(
		masala::numeric_api::auto_generated_api::optimization::cost_function_network::CostFunctionNetworkOptimizationProblems_API const & problem
	) const = 0;

	/// @brief Set a template cost function network optimization problem data representation, configured by the user but with no data entered.
	/// @details This can optionally be passed in, in which case the get_template_preferred_cfn_data_representation() function can be
	/// used to retrieve a deep clone.  This allows the solver to cache its preferred data representation with its setup.
	void
	set_template_preferred_cfn_data_representation(
		masala::base::managers::engine::MasalaDataRepresentationAPICSP const & representation_in
	);

	/// @brief Get a template cost function network optimization problem data representation, configured by the user but with no data entered.
	/// @details If set_template_preferred_cfn_data_representation() has not been called, this returns the output of protected_get_default_template_preferred_cfn_data_representation().
	/// This is nullptr by default, but can be overridden by derived classes.  Returns a deep clone of the object otherwise.
	masala::base::managers::engine::MasalaDataRepresentationAPISP
	get_template_preferred_cfn_data_representation_copy() const;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Assign src to this object.  Must be implemented by derived classes.  Performs no mutex-locking.  Derived classes should call their parent's protected_assign().
	virtual void protected_assign( PluginCostFunctionNetworkOptimizer const & src );

	/// @brief Allow derived classes to lock the mutex.
	inline std::mutex & cfn_solver_mutex() const { return cfn_solver_mutex_; }

	/// @brief Set a template cost function network optimization problem data representation, configured by the user but with no data entered.
	/// @details This can optionally be passed in, in which case the get_template_preferred_cfn_data_representation() function can be
	/// used to retrieve a deep clone.  This allows the solver to cache its preferred data representation with its setup.
	/// @note This version performs no mutex-locking, and is called by set_template_preferred_cfn_data_representation(), which does lock the mutex.
	/// This version is virtual to allow derived classes to override it, to add checks of their own.  If overridden, the override should call the
	/// base class to set the variable internally.
	virtual
	void
	protected_set_template_preferred_cfn_data_representation(
		masala::base::managers::engine::MasalaDataRepresentationAPICSP const & representation_in
	);

	/// @brief If the template preferred CFN data representation has not been set, return a default CFN data representation.
	/// @details The base class implementation returns nullptr.  Derived classes may override this to return something else.  Performs no mutex-locking.
	virtual
	masala::base::managers::engine::MasalaDataRepresentationAPISP
	protected_get_default_template_preferred_cfn_data_representation() const = 0;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A cost function network optimization problem data representation, configured by the user but with no data entered.
	/// @details This can optionally be passed in, in which case the get_template_preferred_cfn_data_representation() function can be
	/// used to retrieve a deep clone.  This allows the solver to cache its preferred data representation with its setup.
	masala::base::managers::engine::MasalaDataRepresentationAPICSP template_preferred_cfn_data_representation_;

	/// @brief A mutex for locking this object.
	mutable std::mutex cfn_solver_mutex_;

}; // class PluginCostFunctionNetworkOptimizer

} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizer_hh