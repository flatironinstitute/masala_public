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

/// @file src/numeric_api/base_classes/optimization/Optimizer.hh
/// @brief Header for a pure virtual base class for Optimizers.
/// @details Optimizers solve a numerical optimization problem.  They have no
/// chemical knowledge.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_Optimizer_hh
#define Masala_src_numeric_api_base_classes_optimization_Optimizer_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/Optimizer.fwd.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/OptimizationProblem_API.fwd.hh>
#include <numeric/optimization/OptimizationSolution.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {

/// @brief A pure virtual base class for Optimizers.
/// @details Optimizers solve a numerical optimization problem.  They have no
/// chemical knowledge.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class Optimizer : public masala::base::managers::plugin_module::MasalaPlugin {

public:

	/// @brief Default constructor.
	Optimizer() = default;

	/// @brief Copy constructor.
	Optimizer( Optimizer const & ) = default;

	/// @brief Destructor.
	~Optimizer() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all optimizers;
	/// may be overridden by derived classes.
	/// @returns { { "Optimizer" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outher vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
	/// by derived classes.
	/// @returns { "optimizer", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Run the optimizer on an optimization problem, and produce a solution.
	/// @details Must be implemented by derived classes.
	virtual
	masala::numeric::optimization::OptimizationSolutionCSP
	run_optimizer(
		masala::numeric_api::auto_generated_api::optimization::OptimizationProblem_API const & problem
	) const = 0;

}; // class Optimizer

} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namesapce masala

#endif // Masala_src_numeric_api_base_classes_optimization_Optimizer_hh