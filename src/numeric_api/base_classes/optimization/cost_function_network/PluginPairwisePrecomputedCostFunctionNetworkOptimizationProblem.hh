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
#include <numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem.hh>

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
class PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem : public masala::numeric::optimization::cost_function_network::PairwisePrecomputedCostFunctionNetworkOptimizationProblem {

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

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationProblem", "PairwisePrecomputedCostFunctionNetworkOptimizationProblem" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the name of this class.
	/// @returns "PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem".
	std::string
	class_name() const override = 0;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric_api::base_classes::optimization::cost_function_network".
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

	/// @brief Reset all data in this object.
	void
	reset() override;

	/// @brief Finalize problem setup: indicate that all problem setup is complete, and that
	/// the object should now be locked for read only.
	void
	finalize() override;

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