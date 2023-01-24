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
/// @brief Implementation for a pure virtual base class for OptimizationProblems.
/// @details OptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/OptimizationProblem.hh>

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
    masala::base::managers::plugin_module::MasalaPlugin(src)
    // Nothing else gets copied, by default.
{}

/// @brief Assignment operator.
OptimizationProblem &
OptimizationProblem::operator=(
    OptimizationProblem const & src
) {
    masala::base::managers::plugin_module::MasalaPlugin::operator=(src);
    //Nothing else gets assigned, by default.
    return *this;
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
/// entry in the outher vector), but must be in at least one.  The first one is used as
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

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Allow derived classes to access the mutex for this object.
/// @note The mutex is mutable, and can be locked from a const function.
std::mutex &
OptimizationProblem::problem_mutex() const {
    return problem_mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.
masala::base::api::MasalaObjectAPIDefinitionCSP &
OptimizationProblem::api_definition() {
    return api_definition_;
}

} // namespace optimization
} // namespace numeric
} // namesapce masala
