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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.hh
/// @brief Header for a container for CostFunctionNetworkOptimizationSolutions.
/// @details CostFunctionNetworkOptimizationSolutions define a numerical optimization solution produced
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolutions_hh
#define Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolutions_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationSolutions.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.fwd.hh>
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.fwd.hh>

// STL headers:
#include <mutex>
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

/// @brief A container for CostFunctionNetworkOptimizationSolutions.
/// @details CostFunctionNetworkOptimizationSolutions define a numerical optimization solution produced
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunctionNetworkOptimizationSolutions : public masala::numeric::optimization::OptimizationSolutions {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CostFunctionNetworkOptimizationSolutions() = default;

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.  Copies the pointers to, but does not deep-clone,
	/// the optimization solutions.
	CostFunctionNetworkOptimizationSolutions( CostFunctionNetworkOptimizationSolutions const & ) = default;

	/// @brief Assignment operator.
	/// @details Copies the pointers to, but does not deep-clone,
	/// the optimization solutions.
	CostFunctionNetworkOptimizationSolutions &
	operator=(
		CostFunctionNetworkOptimizationSolutions const &
	) = default;

	/// @brief Destructor.
	~CostFunctionNetworkOptimizationSolutions() override = default;

	/// @brief Make a copy of this object and return an owning pointer.
	OptimizationSolutionsSP
	clone() const override;

	/// @brief Make a fully independent copy of this object.
	CostFunctionNetworkOptimizationSolutionsSP
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
	/// @returns { { "CostFunctionNetworkOptimizationSolutions" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "cost_function_network_optimization_solutions", "optimization_solutions", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the class name.
	/// @returns "CostFunctionNetworkOptimizationSolutions".
	std::string class_name() const override;

	/// @brief Get the class namespace.
	/// @returns "masala::numeric::optimization::cost_function_network".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the CostFunctionNetworkOptimizationSolutions class.
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
	/// @details Throws if the added solution is not a CostFunctionNetworkOptimizationSolution.
	void
	add_optimization_solution(
		OptimizationSolutionSP solution_in
	) override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the score of the nth solution.
	/// @param solution_index The index of the solution whose score we are retrieving.  This
	/// will throw if this index is not in range.
	masala::base::Real
	solution_score(
		masala::base::Size const solution_index
	) const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Does a given solution's solution vector match a solution vector to which we
	/// are comparing?
	/// @param solution_index The index of the solution.  Must be within range, or this will throw.
	/// @param comparison_solution_vector The vector of solutions to which we are comparing.  This
	/// is one choice index per variable node.  (There should not be entries for fixed nodes.)
	/// @return True if the solution vector matches, false otherwise.
	bool
	solution_matches(
		masala::base::Size const solution_index,
		std::vector< masala::base::Size > const & comparison_solution_vector
	) const;

	/// @brief Given another collection of solutions, merge-sort the solutions
	/// and keep up to the lowest-scoring N.
	/// @details The scores passed in are the solver scores.  This function will compute the
	/// data representation scores and the actual scores, and then merge-sort by actual score. 
	/// @param[in] other_solutions The other solutions, represented as a vector of
	/// tuples of (solution vector for variable positions only, solution score,
	/// solution count).  The solution score is the score returned by the solver (which
	/// may be approximate, both because the data representation may make approximations
	/// and because the solver's precision may be limited.)
	/// @param[in] max_solutions_to_store_total The maximum number of solutions that we
	/// want to be storing at the end of this operation.  The lowest-scoring solutions
	/// from the union of both sets are stored, and any solutions past the lowest N are
	/// discarded.
	/// @param[in] problem The problem for all of these solutions.
	/// @note If both sets contain the same solution, the number of times that solution
	/// was produced will be incremented in this set by the number of times it was produced
	/// in the other set.
	void
	merge_in_lowest_scoring_solutions(
		std::vector< std::tuple< std::vector< masala::base::Size >, masala::base::Real, masala::base::Size > > const & other_solutions,
		masala::base::Size const max_solutions_to_store_total,
		CostFunctionNetworkOptimizationProblemCSP problem
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////


}; // class CostFunctionNetworkOptimizationSolutions

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkOptimizationSolutions_hh