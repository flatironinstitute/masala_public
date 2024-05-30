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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.fwd.hh
/// @brief Implementations for a base class for PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblems.
/// @details A PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem defines a special case of a numerical cost function network optimization
/// problem, defined in a plug-in library, to be solved by a suitable Optimizer.  The PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem
/// class does not contain any chemistry-specific concepts.
/// @note This class is a pure virtual base class, since get_api_definition() is not implemented.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/cost_function_network/PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ThreeInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
void
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::make_independent() {
    masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem::make_independent();
    //GNDN
}

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
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "PairwisePrecomputedCostFunctionNetworkOptimizationProblem" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "pairwise_precomputed_cost_function_network_optimization_problem", "numeric" }
std::vector< std::string >
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function_network_optimization_problem",
        "pairwise_precomputed_cost_function_network_optimization_problem",
		"numeric"
	};
}

/// @brief Get the category for this MasalaDataRepresentation.
/// @returns { { "OptimizationProblem", "CostFunctionNetworkOptimizationProblem", "PairwisePrecomputedCostFunctionNetworkOptimizationProblem" } }.
std::vector< std::vector< std::string > >
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_data_representation_categories() const {
    return std::vector< std::vector< std::string > >{
        {
            "OptimizationProblem",
            "CostFunctionNetworkOptimizationProblem",
            "PairwisePrecomputedCostFunctionNetworkOptimizationProblem"
        }
    };
}

/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
/// is compatible.
/// @returns An empty list.
std::vector< std::string >
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_compatible_masala_engines() const {
    return std::vector< std::string >{};
}

/// @brief Get the properties of this MasalaDataRepresentation.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem" }.
std::vector< std::string >
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_present_data_representation_properties() const {
    return std::vector< std::string >{
        "optimization_problem",
        "cost_function_network_optimization_problem"
    };
}

/// @brief Get the properties of this MasalaDataRepresentation that might possibly be present.
/// @details Obviously, this is a non-exhuastive list.
/// @returns { "precomputed", "pairwise_decomposible", "partially_precomputed", "partially_pairwise_decomposible" }.
std::vector< std::string >
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_possibly_present_data_representation_properties() const {
    return std::vector< std::string >{
        "precomputed",
        "pairwise_decomposible",
        "partially_precomputed",
        "partially_pairwise_decomposible"
    };
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset all data in this object.
void
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::reset() {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::protected_reset();
}

/// @brief Finalize problem setup: indicate that all problem setup is complete, and that
/// the object should now be locked for read only.
void
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::finalize() {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::protected_finalize();
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object completely.  Mutex must be locked before calling.
void 
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::protected_reset() {
    masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem::protected_reset();
}

/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
void
PluginPairwisePrecomputedCostFunctionNetworkOptimizationProblem::protected_finalize() {
    masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem::protected_finalize();
}

} // namespace cost_function_network
} // namespace optimization
} // base_classes
} // namespace numeric_api
} // namespace masala
