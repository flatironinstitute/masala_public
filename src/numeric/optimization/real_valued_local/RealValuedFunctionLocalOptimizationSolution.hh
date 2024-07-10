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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution.hh.
/// @brief Headers for a pure virtual base class for a RealValuedFunctionLocalOptimizationSolution.
/// @details A RealValuedFunctionLocalOptimizationSolution contains the solution to a particular
/// RealValuedFunctionLocalOptimizationProblem, after it is solved by a suitable
/// GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationSolution_hh
#define Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationSolution_hh

// Forward declarations:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution.fwd.hh>

// Numeric headers:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationSolution.hh>

// External headers:
#include <external/eigen/Eigen/Core>

namespace masala {
namespace numeric {
namespace optimization {
namespace real_valued_local {


/// @brief A pure virtual base class for a RealValuedFunctionLocalOptimizationSolution.
/// @details A RealValuedFunctionLocalOptimizationSolution contains the solution to a particular
/// RealValuedFunctionLocalOptimizationProblem, after it is solved by a suitable
/// GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class RealValuedFunctionLocalOptimizationSolution : public masala::numeric::optimization::OptimizationSolution {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	RealValuedFunctionLocalOptimizationSolution() = default;

	/// @brief Copy constructor.
	RealValuedFunctionLocalOptimizationSolution( RealValuedFunctionLocalOptimizationSolution const & ) = default;

	// @brief Assignment operator.
	RealValuedFunctionLocalOptimizationSolution &
	operator=( RealValuedFunctionLocalOptimizationSolution const & ) = default;

	/// @brief Destructor.
	~RealValuedFunctionLocalOptimizationSolution() override = default;

	/// @brief Make a copy of this object.
	masala::numeric::optimization::OptimizationSolutionSP
	clone() const override;

	/// @brief Make a fully independent copy of this object.
	RealValuedFunctionLocalOptimizationSolutionSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationSolution", "RealValuedFunctionLocalOptimizationSolution" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "optimization_solution", "local", "real_valued", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the name of this class.
	/// @returns "RealValuedFunctionLocalOptimizationSolution".
	std::string
	class_name() const override;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric::optimization::real_valued_local".
	std::string
	class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the RealValuedFunctionLocalOptimizationSolution class.
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

	/// @brief Set the problem that gave rise to this solution.
	/// @details Stored directly (not cloned) on input.  This override checks that the problem
	/// is a RealValuedFunctionLocalOptimizationProblem.  If the solution vector has been
	/// set, the problem must match it.  If a starting point has already been set, the problem
	/// must correspond.
	void set_problem( OptimizationProblemCSP const & problem ) override;

	/// @brief Set the starting point that gave rise to this local minimum, and the corresponding
	/// starting point index in the problem.
	/// @details If the problem has already been set, this must match it.  If a solution vector has
	/// been set, the starting point's length must match it.
	void
	set_starting_point_and_index(
		Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & starting_point_in,
		masala::base::Size const starting_point_index
	);

	/// @brief Set the point found that is a local minimum.
	/// @details If the problem has already been set, this must match it.  If a starting point has
	/// been set, the solution vector's length must match it.
	void set_solution_point(  Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & solution_point_in );

	/// @brief Set whether the optimizer reported convergence.
	void set_converged( bool const converged_in );

	/// @brief Set the number of iterations that the optimizer reported taking.
	/// @details Some optimizers may use non-iterative approaches, in which case this value will be zero.
	void set_iterations( masala::base::Size const iterations_in );

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

	/// @brief The starting point that gave rise to this local minimum.
	Eigen::Vector< masala::base::Real, Eigen::Dynamic > starting_point_;

	/// @brief The starting point index in the problem.
	masala::base::Size starting_point_index_ = 0;

	/// @brief The point found that is a local minimum.
	Eigen::Vector< masala::base::Real, Eigen::Dynamic > solution_point_;

	/// @brief Did the optimizer report convergence?
	bool is_converged_ = false;

	/// @brief How many iterations did the optimizer report taking?
	/// @details Some optimizers may use non-iterative approaches, in which case this value will be zero.
	masala::base::Size iterations_ = 0;

}; // class RealValuedFunctionLocalOptimizationSolution

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationSolution_hh
