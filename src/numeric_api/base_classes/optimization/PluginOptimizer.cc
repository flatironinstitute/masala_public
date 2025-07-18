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

/// @file src/numeric_api/base_classes/optimization/PluginOptimizer.cc
/// @brief Implementation for a pure virtual base class for PluginOptimizers.
/// @details PluginOptimizers solve a numerical optimization problem.  They have no
/// chemical knowledge.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/PluginOptimizer.hh>

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
/// @returns { { "Optimizer" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
PluginOptimizer::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "Optimizer" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
/// by derived classes.
/// @returns { "optimizer", "numeric" }
std::vector< std::string >
PluginOptimizer::get_keywords() const {
	return std::vector< std::string > {
		"optimizer",
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
/// @returns { {"Optimizer"} }
std::vector< std::vector < std::string > >
PluginOptimizer::get_engine_categories() const {
    return std::vector< std::vector < std::string > >{ { "Optimizer" } };
}

/// @brief Keywords for engines.
/// @returns { "optimizer", "numeric" }
std::vector < std::string >
PluginOptimizer::get_engine_keywords() const {
    return std::vector< std::string > {
		"optimizer",
		"numeric"
	};
}

} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
