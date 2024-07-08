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

/// @file src/numeric_api/base_classes/optimization/real_valued_local/LineOptimizer.hh
/// @brief Header for a pure virtual base class for LineOptimizers.
/// @details LineOptimizers solve a numerical optimization function for a real-valued
/// function of one variable.  Since line optimization is a sub-problem for many
/// other optimization problems, LineOptimizers are implemented as their own special
/// case class.  Note that this class does NOT derive from the general Optimizer class.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_real_valued_local_LineOptimizer_hh
#define Masala_src_numeric_api_base_classes_optimization_real_valued_local_LineOptimizer_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/real_valued_local/LineOptimizer.fwd.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/OptimizationProblems_API.fwd.hh>
#include <numeric_api/auto_generated_api/optimization/OptimizationSolutions_API.fwd.hh>

// Parent header:
#include <base/managers/engine/MasalaEngine.hh>
#include <base/types.hh>
#include <functional>
#include <utility>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace real_valued_local {

/// @brief A pure virtual base class for LineOptimizers.
/// @details LineOptimizers solve a numerical optimization function for a real-valued
/// function of one variable.  Since line optimization is a sub-problem for many
/// other optimization problems, LineOptimizers are implemented as their own special
/// case class.  Note that this class does NOT derive from the general Optimizer class.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class LineOptimizer : public masala::base::managers::engine::MasalaEngine {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	LineOptimizer() = default;

	/// @brief Copy constructor.  Explicit due to mutex.
	LineOptimizer( LineOptimizer const & src );

	/// @brief Assignment operator.  Explicit due to mutex.
	LineOptimizer &
	operator=(
		LineOptimizer const & src
	);

	/// @brief Make this object independent by calling deep_clone on all contained objects.
	void
	make_independent();

	/// @brief Destructor.
	~LineOptimizer() override = default;

	/// @brief Clone operator: make a copy of this object and return a shared
	/// pointer to the copy.
	/// @details Must be implemented by derived classes.
	virtual
	LineOptimizerSP
	clone() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

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

	/// @brief Run the line optimizer on a single line optimization problem, and produce a single solution.
	/// @details Must be implemented by derived classes.  The solution is a pair of (x, f(x)) where x minimizes f.
	/// @param[in] fxn The function to minimize.
	/// @param[inout] x The value of x that (locally) minimizes f(x).  This may also be used as the starting
	/// point of the search.
	/// @param[out] fxn_at_x The value of f(x) where x (locally) minimizes f(x).
	virtual
	void
	run_line_optimizer(
		std::function< masala::base::Real( masala::base::Real ) > const & fxn,
		masala::base::Real & x,
		masala::base::Real & fxn_at_x
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

	/// @brief Assignment: must be implemented by derived classes, which must call the base
	/// class protected_assign().
	/// @details Performs no mutex locking.
	virtual
	void
	protected_assign(
		LineOptimizer const & src
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

}; // class LineOptimizer

} // namespace real_valued_local
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_real_valued_local_LineOptimizer_hh