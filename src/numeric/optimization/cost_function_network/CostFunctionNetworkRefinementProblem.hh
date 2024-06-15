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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkRefinementProblem.hh
/// @brief Header for a pure virtual base class for CostFunctionNetworkRefinementProblems.
/// @details CostFunctionNetworkRefinementProblems define a numerical cost function network optimization problem to be refined
/// by a suitable refining Optimizer.  They do not contain any chemistry-specific concepts.  A cost function network problem consists
/// of N nodes with D_N candidate states per node.  A solution is a selection of one state per node.  For each candidate state,
/// there is a cost (or bonus) to selecting it, and for each pair of states, there is a possible cost (or bonus) to selecting
/// both of the pair.  Additional non-pairwise constraints can be added.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkRefinementProblem_hh
#define Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkRefinementProblem_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkRefinementProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <map>
#include <utility> //For std::pair.
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

/// @brief A pure virtual base class for CostFunctionNetworkRefinementProblems.
/// @details CostFunctionNetworkRefinementProblems define a numerical cost function network optimization problem to be refined
/// by a suitable refining Optimizer.  They do not contain any chemistry-specific concepts.  A cost function network problem consists
/// of N nodes with D_N candidate states per node.  A solution is a selection of one state per node.  For each candidate state,
/// there is a cost (or bonus) to selecting it, and for each pair of states, there is a possible cost (or bonus) to selecting
/// both of the pair.  Additional non-pairwise constraints can be added.
/// @note If no refining optimizer is available, any optimizer may run on this problem.  Candidate starting solutions will in this
/// case be ignored.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunctionNetworkRefinementProblem : public masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CostFunctionNetworkRefinementProblem() = default;

	/// @brief Copy constructor.
	CostFunctionNetworkRefinementProblem( CostFunctionNetworkRefinementProblem const & ) = default;

	// @brief Assignment operator.
	CostFunctionNetworkRefinementProblem &
	operator=( CostFunctionNetworkRefinementProblem const & ) = default;

	/// @brief Destructor.
	~CostFunctionNetworkRefinementProblem() override = default;

	/// @brief Make a fully independent copy of this object.
	CostFunctionNetworkRefinementProblemSP
	deep_clone() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "CostFunctionNetworkRefinementProblem" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "cost_function_network_refinement_problem", "numeric" }
	std::vector< std::string >
	get_keywords() const override;
	
	/// @brief Get the category for this MasalaDataRepresentation.
	/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "CostFunctionNetworkRefinementProblem" } }.
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
	/// is compatible.
	/// @returns An empty list.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the properties of this MasalaDataRepresentation.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "cost_function_network_refinement_problem" }.
	std::vector< std::string >
	get_present_data_representation_properties() const override;

	/// @brief Get the name of this class.
	/// @returns "CostFunctionNetworkRefinementProblem".
	std::string
	class_name() const override;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric::optimization::cost_function_network".
	std::string
	class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the CostFunctionNetworkRefinementProblem class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object completely.  Mutex must be locked before calling.
	void protected_reset() override;

	/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
	/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
	void protected_finalize() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief the starting solutions, for refinement.
	std::vector< std::vector< masala::base::Size > > starting_solutions_;

}; // class CostFunctionNetworkRefinementProblem

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_CostFunctionNetworkRefinementProblem_hh