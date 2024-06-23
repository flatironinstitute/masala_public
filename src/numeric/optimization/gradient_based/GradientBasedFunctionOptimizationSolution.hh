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

/// @file src/numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolution.hh.
/// @brief Headers for a pure virtual base class for a GradientBasedFunctionOptimizationSolution.
/// @details A GradientBasedFunctionOptimizationSolution contains the solution to a particular
/// GradientBasedFunctionOptimizationProblem, after it is solved by a suitable
/// GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationSolution_hh
#define Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationSolution_hh

// Forward declarations:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolution.fwd.hh>

// Numeric headers:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationSolution.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace gradient_based {


/// @brief A pure virtual base class for a GradientBasedFunctionOptimizationSolution.
/// @details A GradientBasedFunctionOptimizationSolution contains the solution to a particular
/// GradientBasedFunctionOptimizationProblem, after it is solved by a suitable
/// GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class GradientBasedFunctionOptimizationSolution : public masala::numeric::optimization::OptimizationSolution {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	GradientBasedFunctionOptimizationSolution() = default;

	/// @brief Copy constructor.
	GradientBasedFunctionOptimizationSolution( GradientBasedFunctionOptimizationSolution const & ) = default;

	// @brief Assignment operator.
	GradientBasedFunctionOptimizationSolution &
	operator=( GradientBasedFunctionOptimizationSolution const & ) = default;

	/// @brief Destructor.
	~GradientBasedFunctionOptimizationSolution() override = default;

	/// @brief Make a copy of this object.
	masala::numeric::optimization::OptimizationSolutionSP
	clone() const override;

	/// @brief Make a fully independent copy of this object.
	GradientBasedFunctionOptimizationSolutionSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationSolution", "GradientBasedFunctionOptimizationSolution" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "optimization_solution", "gradient_based_optimization_solution", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the name of this class.
	/// @returns "GradientBasedFunctionOptimizationSolution".
	std::string
	class_name() const override;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric::optimization::gradient_based".
	std::string
	class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the GradientBasedFunctionOptimizationSolution class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

}; // class GradientBasedFunctionOptimizationSolution

} // namespace gradient_based
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationSolution_hh
