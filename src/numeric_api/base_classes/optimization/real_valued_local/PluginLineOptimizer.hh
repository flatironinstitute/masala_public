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

/// @file src/numeric/optimization/real_valued_local/PluginLineOptimizer.hh
/// @brief Header for a pure virtual base class for PluginLineOptimizers.
/// @details PluginLineOptimizers solve a numerical optimization function for a real-valued
/// function of one variable.  Since line optimization is a sub-problem for many
/// other optimization problems, PluginLineOptimizers are implemented as their own special
/// case class.  Note that this class does NOT derive from the general Optimizer class.
/// @note This class is pure virtual since get_api_definition() is not implemented.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginLineOptimizer_hh
#define Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginLineOptimizer_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/real_valued_local/PluginLineOptimizer.fwd.hh>

// Parent header:
#include <numeric/optimization/real_valued_local/LineOptimizer.hh>

// Base headers:
#include <base/types.hh>

// External headers:
#include <external/eigen/Eigen/Core>

// STL headers:
#include <functional>
#include <utility>
#include <mutex>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace real_valued_local {

/// @brief A pure virtual base class for PluginLineOptimizers.
/// @details PluginLineOptimizers solve a numerical optimization function for a real-valued
/// function of one variable.  Since line optimization is a sub-problem for many
/// other optimization problems, PluginLineOptimizers are implemented as their own special
/// case class.  Note that this class does NOT derive from the general Optimizer class.
/// @note This class is pure virtual since get_api_definition() is not implemented.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginLineOptimizer : public masala::numeric::optimization::real_valued_local::LineOptimizer {

	typedef masala::numeric::optimization::real_valued_local::LineOptimizer LineOptimizer;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginLineOptimizer() = default;

	/// @brief Copy constructor.  Explicit due to mutex.
	PluginLineOptimizer( PluginLineOptimizer const & src ) = default;

	/// @brief Destructor.
	~PluginLineOptimizer() override = default;

	/// @brief Clone operator: make a copy of this object and return a shared
	/// pointer to the copy.
	/// @details Must be implemented by derived classes.
	virtual
	PluginLineOptimizerSP
	clone() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of this class ("PluginLineOptimizer").
	std::string class_name() const override;

	/// @brief Get the namespace of this class ("masala::numeric::optimization::real_valued_local").
	std::string class_namespace() const override;

	/// @brief Get the name of this class ("PluginLineOptimizer").  Static version.
	static std::string class_name_static();

	/// @brief Get the namespace of this class ("masala::numeric::optimization::real_valued_local").  Static version.
	static std::string class_namespace_static();

	/// @brief Get the namespace and name of this class
	/// ("masala::numeric::optimization::real_valued_local::PluginLineOptimizer").
	/// Static function.
	static std::string class_namespace_and_name_static();

	/// @brief Get the category or categories for this plugin class.  Default for all optimizers;
	/// may be overridden by derived classes.
	/// @returns { { "LineOptimizer" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
	/// by derived classes.
	/// @returns { "line_optimizer", "lightweight", "numeric" }
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
	/// @returns { {"LineOptimizer"} }
    std::vector< std::vector < std::string > >
    get_engine_categories() const override;

	/// @brief Get an object describing the API for this object.
	/// @details This override makes this class pure virtual.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override = 0;

	/// @brief Run the line optimizer on a single line optimization problem, and produce a single solution.
	/// @details Must be implemented by derived classes.  The solution is a pair of (x, f(x)) where x minimizes f.
	/// @param[in] fxn The function to minimize.
	/// @param[in] x0 The starting point for the search.
	/// @param[in] fxn_at_x0 The value of the function at the starting point for the search.
	/// @param[in] grad_of_fxn_at_x0 The gradient of the function at the starting point for the search.
	/// @param[in] search_dir The search direction, which may or may not match the negative gradient of the starting point.
	/// @param[out] x The output value of x that (locally) minimizes f(x).
	/// @param[out] fxn_at_x The output value of f(x) where x (locally) minimizes f(x).
	/// @param[inout] stepsize The size of the initial step for the search.  This is both an input (the step size that we should
	/// try initially) and an output (the step size that yielded the optimum).
	virtual
	void
	run_line_optimizer(
		std::function< masala::base::Real( Eigen::VectorXd const & ) > const & fxn,
		Eigen::VectorXd const & x0,
		masala::base::Real const fxn_at_x0,
		Eigen::VectorXd const & grad_of_fxn_at_x0,
		Eigen::VectorXd const & search_dir,
		Eigen::VectorXd & x,
		masala::base::Real & fxn_at_x,
		masala::base::Real & stepsize
	) const = 0;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Assignment: must be implemented by derived classes, which must call the base
	/// class protected_assign().
	/// @details Performs no mutex locking.
	void
	protected_assign(
		LineOptimizer const & src
	) override;

	/// @brief Make independent: must be implemented by derived classes, which must call the base
	/// class protected_make_independent().
	/// @details Performs no mutex locking.
	void
	protected_make_independent() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

}; // class PluginLineOptimizer

} // namespace real_valued_local
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginLineOptimizer_hh