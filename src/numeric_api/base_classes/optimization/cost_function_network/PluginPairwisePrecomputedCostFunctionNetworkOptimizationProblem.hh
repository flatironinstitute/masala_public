/*
    Masala
    Copyright (C) 2023 Vikram K. Mulligan

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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.hh
/// @brief Headers for a base class for PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblems.
/// @details A PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem defines a special case of a numerical cost function network optimization
/// problem, defined in a plug-in library, to be solved by a suitable Optimizer.  The PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem
/// class does not contain any chemistry-specific concepts.
/// @note This class is a pure virtual base class, since get_api_definition() is not implemented.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem_hh
#define Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/cost_function_network/PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.fwd.hh>

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
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {

/// @brief A base class for PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblems.
/// @details A PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem defines a special case of a numerical cost function network optimization
/// problem, defined in a plug-in library, to be solved by a suitable Optimizer.  The PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem
/// class does not contain any chemistry-specific concepts.
/// @note This class is a pure virtual base class, since get_api_definition() is not implemented.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem : public masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem() = default;

	/// @brief Copy constructor.
	PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem( PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem const & ) = default;

	// @brief Assignment operator.
	PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem &
	operator=( PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem const & ) = default;

	/// @brief Destructor.
	~PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem() override = default;

	/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
	void make_independent();

	/// @brief Make a copy of this object, and return a shared pointer to the copy.
	/// @details Does NOT copy all the internal data, but retains pointers to existing data.
	/// @note Must be implemented by all derived classes.
	masala::numeric::optimization::OptimizationProblemSP
	clone() const override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "PairwisePrecomputedCostFunctionNetworkOptimizationProblem" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "pairwise_precomputed_cost_function_network_optimization_problem", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the category for this MasalaDataRepresentation.
	/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "PairwisePrecomputedCostFunctionNetworkOptimizationProblem" } }.
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
	/// is compatible.
	/// @returns An empty list.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the properties of this MasalaDataRepresentation.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem"}.
	std::vector< std::string >
	get_present_data_representation_properties() const override;

	/// @brief Get the properties of this MasalaDataRepresentation that might possibly be present.
	/// @details Obviously, this is a non-exhuastive list.
	/// @returns { "precomputed", "pairwise_decomposible", "partially_precomputed", "partially_pairwise_decomposible" }.
	std::vector< std::string >
	get_possibly_present_data_representation_properties() const override;

	/// @brief Get the name of this class.
	/// @returns Nothing -- must be implemented by derived classes.
	std::string
	class_name() const override = 0;

	/// @brief Get the namespace for this class.
	/// @returns Nothing -- must be implemented by derived classes.
	std::string
	class_namespace() const override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Add onebody penalty for a choice at a node.
	/// @details Must be implemented by derived classes.
	virtual
	void
	set_onebody_penalty(
		masala::base::Size const node_index,
		masala::base::Size const choice_index,
		masala::base::Real const penalty
	) = 0;

    /// @brief Set the two-node penalty for a particular pair of choice indices corresponding to a particular
    /// pair of node indices.
    /// @param[in] node_indices A pair of node indices.  The lower index should be first.  (This function should
    /// throw if it is not, since it makes the choice indices ambiguous).
    /// @param[in] choice_indices The corresponding pair of choice indices.  The first entry should be the choice
    /// index for the lower-numbered node, and the second should be the choice index for the higher-numbered node.
    /// @param[in] penalty The value of the two-node penalty (or, if negative, bonus).
	/// @details Must be implemented by derived classes.
    virtual
	void
    set_twobody_penalty(
        std::pair< masala::base::Size, masala::base::Size > const & node_indices,
        std::pair< masala::base::Size, masala::base::Size > const & choice_indices,
        masala::base::Real penalty
    ) = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem class.
	/// @details This makes this class pure virtual.  This function must be implemented in derived classes
	/// if they are to be instantiated.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override = 0;

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

}; // class PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem

} // namespace cost_function_network
} // namespace optimization
} // base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem_hh