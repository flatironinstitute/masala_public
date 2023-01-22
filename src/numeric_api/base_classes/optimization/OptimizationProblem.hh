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

/// @file src/numeric_api/base_classes/optimization/OptimizationProblem.hh
/// @brief Header for a pure virtual base class for OptimizationProblems.
/// @details OptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_OptimizationProblem_hh
#define Masala_src_numeric_api_base_classes_optimization_OptimizationProblem_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/OptimizationProblem.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {

/// @brief A pure virtual base class for OptimizationProblems.
/// @details OptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class OptimizationProblem : public masala::base::managers::plugin_module::MasalaPlugin {

public:

	/// @brief Default constructor.
	OptimizationProblem() = default;

	/// @brief Copy constructor.
	OptimizationProblem( OptimizationProblem const & ) = default;

	/// @brief Destructor.
	~OptimizationProblem() override = default;

public:

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
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

}; // class OptimizationProblem

} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namesapce masala

#endif // Masala_src_numeric_api_base_classes_optimization_OptimizationProblem_hh