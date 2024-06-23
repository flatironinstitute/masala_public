/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolutions.hh
/// @brief Header for a container for GradientBasedFunctionOptimizationSolutions.
/// @details Each GradientBasedFunctionOptimizationSolution defines a numerical loss function
/// gradient minimization solution produced by a suitable Optimizer.  It does not contain any
/// chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationSolutions_hh
#define Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationSolutions_hh

// Forward declarations:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolutions.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationSolutions.hh>

// Numeric headers:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationSolution.fwd.hh>
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblem.fwd.hh>

// STL headers:
#include <mutex>
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {
namespace gradient_based {

/// @brief A container for GradientBasedFunctionOptimizationSolutions.
/// @details Each GradientBasedFunctionOptimizationSolution defines a numerical loss function
/// gradient minimization solution produced by a suitable Optimizer.  It does not contain any
/// chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class GradientBasedFunctionOptimizationSolutions : public masala::numeric::optimization::OptimizationSolutions {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	GradientBasedFunctionOptimizationSolutions() = default;

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.  Copies the pointers to, but does not deep-clone,
	/// the optimization solutions.
	GradientBasedFunctionOptimizationSolutions( GradientBasedFunctionOptimizationSolutions const & ) = default;

	/// @brief Assignment operator.
	/// @details Copies the pointers to, but does not deep-clone,
	/// the optimization solutions.
	GradientBasedFunctionOptimizationSolutions &
	operator=(
		GradientBasedFunctionOptimizationSolutions const &
	) = default;

	/// @brief Destructor.
	~GradientBasedFunctionOptimizationSolutions() override = default;

	/// @brief Make a copy of this object and return an owning pointer.
	OptimizationSolutionsSP
	clone() const override;

	/// @brief Make a fully independent copy of this object.
	GradientBasedFunctionOptimizationSolutionsSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared
	/// (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { { "OptimizationSolutions", "GradientBasedFunctionOptimizationSolutions" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "gradient_based_optimization_solutions", "optimization_solutions", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the class name.
	/// @returns "GradientBasedFunctionOptimizationSolutions".
	std::string class_name() const override;

	/// @brief Get the class namespace.
	/// @returns "masala::numeric::optimization::gradient_based".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the GradientBasedFunctionOptimizationSolutions class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object, clearing its solution list.
	void
	reset() override;

	/// @brief Add an optimization solution to the list of optimization solutions
	/// stored in this container.
	/// @details Throws if the added solution is not a GradientBasedFunctionOptimizationSolution.
	void
	add_optimization_solution(
		OptimizationSolutionSP solution_in
	) override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
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
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////


}; // class GradientBasedFunctionOptimizationSolutions

} // namespace gradient_based
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationSolutions_hh