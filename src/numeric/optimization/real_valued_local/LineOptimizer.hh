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

/// @file src/numeric/optimization/real_valued_local/LineOptimizer.hh
/// @brief Header for a pure virtual base class for LineOptimizers.
/// @details LineOptimizers solve a numerical optimization function for a real-valued
/// function of one variable.  Since line optimization is a sub-problem for many
/// other optimization problems, LineOptimizers are implemented as their own special
/// case class.  Note that this class does NOT derive from the general Optimizer class.
/// @note This class can be instantiated, but its API definition has protected constructors
/// effectively making it pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_real_valued_local_LineOptimizer_hh
#define Masala_src_numeric_optimization_real_valued_local_LineOptimizer_hh

// Forward declarations:
#include <numeric/optimization/real_valued_local/LineOptimizer.fwd.hh>

// Parent header:
#include <base/managers/engine/MasalaEngine.hh>

// Base headers:
#include <base/types.hh>

// External headers:
#include <external/eigen/Eigen/Core>

// STL headers:
#include <functional>
#include <utility>
#include <mutex>

namespace masala {
namespace numeric {
namespace optimization {
namespace real_valued_local {

/// @brief A pure virtual base class for LineOptimizers.
/// @details LineOptimizers solve a numerical optimization function for a real-valued
/// function of one variable.  Since line optimization is a sub-problem for many
/// other optimization problems, LineOptimizers are implemented as their own special
/// case class.  Note that this class does NOT derive from the general Optimizer class.
/// @note This class can be instantiated, but its API definition has protected constructors
/// effectively making it pure virtual.
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

	/// @brief Copy this object and all contained objects.
	LineOptimizerSP
	deep_clone() const;

	/// @brief Make this object independent by calling deep_clone on all contained objects.
	void
	make_independent();

	/// @brief Destructor.
	~LineOptimizer() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of this class ("LineOptimizer").
	std::string class_name() const override;

	/// @brief Get the namespace of this class ("masala::numeric::optimization::real_valued_local").
	std::string class_namespace() const override;

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

	/// @brief Get the keywords for this engine.
	/// @returns { "line_optimizer", "lightweight", "numeric" }
	std::vector< std::string >
	get_engine_keywords() const override;

	/// @brief Get an object describing the API for this object.
	/// @details This override makes the API class non-instantiable since it
	/// has a protected constructor.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

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
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_real_valued_local_LineOptimizer_hh