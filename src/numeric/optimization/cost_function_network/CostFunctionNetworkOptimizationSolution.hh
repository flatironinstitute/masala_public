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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.hh
/// @brief Header for a pure virtual base class for CostFunctionNetworkOptimizationSolutions.
/// @details A CostFunctionNetworkOptimizationSolution contains the solution to a particular
/// CostFunctionNetworkOptimizationProblem, after it is solved by a suitable CostFunctionNetworkOptimizer.
/// It does not contain any chemistry-specific concepts.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolution_hh
#define Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolution_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.fwd.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationSolution.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {


/// @brief A pure virtual base class for CostFunctionNetworkOptimizationSolutions.
/// @details A CostFunctionNetworkOptimizationSolution contains the solution to a particular
/// CostFunctionNetworkOptimizationProblem, after it is solved by a suitable CostFunctionNetworkOptimizer.
/// It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunctionNetworkOptimizationSolution : public masala::numeric::optimization::OptimizationSolution {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CostFunctionNetworkOptimizationSolution() = default;

	/// @brief Constructor that initializes from the problem description.
	/// @details The problem definition is stored directly, not copied.  The solution is represented
	/// as a vector of choice indices, one per variable position (i.e. per position with more than one
	/// choice) in order of indices of variable positions.
	CostFunctionNetworkOptimizationSolution(
		CostFunctionNetworkOptimizationProblemCSP const & problem_in,
		std::vector< masala::base::Size > const & solution_vector_in,
		masala::base::Real const solution_score
	);

	/// @brief Copy constructor.
	CostFunctionNetworkOptimizationSolution( CostFunctionNetworkOptimizationSolution const & ) = default;

	// @brief Assignment operator.
	CostFunctionNetworkOptimizationSolution &
	operator=( CostFunctionNetworkOptimizationSolution const & ) = default;

	/// @brief Destructor.
	~CostFunctionNetworkOptimizationSolution() override = default;

	/// @brief Make a fully independent copy of this object.
	CostFunctionNetworkOptimizationSolutionSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "CostFunctionNetworkOptimizationSolution" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "optimization_solution", "cost_function_network_optimization_solution", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the name of this class.
	/// @returns "CostFunctionNetworkOptimizationSolution".
	std::string
	class_name() const override;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric::optimization::cost_function_network".
	std::string
	class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the CostFunctionNetworkOptimizationSolution class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the solution vector for this problem.
	/// @details This returns the solution vector as one value per
	/// variable position, in order of variable positions.  Indices
	/// in the vector do NOT necessarily correspond to node indices,
	/// since nodes with zero or one choice are omitted.
	/// @note Problem and solution vector must have been set.
	std::vector< masala::base::Size > const &
	solution_at_variable_positions() const;

	/// @brief Get the solution vector for this problem.
	/// @details This returns the solution vector as one value per
	/// position, in order of all positions.  Indices in the vector
	/// correspond to node indices.
	/// @note Problem and solution vector must have been set.
	std::vector< masala::base::Size >
	solution_at_all_positions() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the problem that gave rise to this solution.
	/// @details Stored directly (not cloned) on input.  This override checks that the problem
	/// is a CostFunctionNetworkOptimizationProblem.  If the solution vector has been
	/// set, the problem must match it.
	void set_problem( OptimizationProblemCSP const & problem ) override;

	/// @brief Set the solution vector for this problem.
	/// @details If the problem has been set, this solution vector must be of compatible size.
	void
	set_solution_vector(
		std::vector< masala::base::Size > const & solution_vector_in
	);

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Recompute the score of this solution.  This is useful, for instance, after
	/// an optimizer that uses approximate methods or low floating-point precision completes
	/// its work, to allow scores to be stored with full floating-point precision and accuracy.
	/// @details The problem_ pointer must be set.
	/// @note The base class recompute_score() function throws.  This override calls the
	/// CostFunctionNetworkOptimizationProblem's calculators.
	void recompute_score() override;

	/// @brief Determine whether this solution is the same as another.
	/// @details Compares the stored solution vector to a provided solution vector.
	bool operator==( std::vector< masala::base::Size > const & other_solution_vector ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The solution, stored as a vector of choices, one per variable position (i.e. per position with
	/// more than one choice) in order of indices of variable positions.
	std::vector< masala::base::Size > solution_vector_;

}; // class CostFunctionNetworkOptimizationSolution

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolution_hh
