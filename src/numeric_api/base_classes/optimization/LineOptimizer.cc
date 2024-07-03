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

/// @file src/numeric_api/base_classes/optimization/LineOptimizer.cc
/// @brief Implementation for a pure virtual base class for LineOptimizers.
/// @details LineOptimizers solve a numerical optimization function for a real-valued
/// function of one variable.  Since line optimization is a sub-problem for many
/// other optimization problems, LineOptimizers are implemented as their own special
/// case class.  Note that this class does NOT derive from the general Optimizer class.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/LineOptimizer.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {


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
LineOptimizer::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "LineOptimizer" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
/// by derived classes.
/// @returns { "line_optimizer", "lightweight", "numeric" }
std::vector< std::string >
LineOptimizer::get_keywords() const {
	return std::vector< std::string > {
		"line_optimizer",
		"lightweight",
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
/// @returns { {"LineOptimizer"} }
std::vector< std::vector < std::string > >
LineOptimizer::get_engine_categories() const {
    return std::vector< std::vector < std::string > >{ { "LineOptimizer" } };
}

} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
