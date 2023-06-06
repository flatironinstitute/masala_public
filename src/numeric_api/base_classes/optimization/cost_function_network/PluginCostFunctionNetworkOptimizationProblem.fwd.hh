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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizationProblem.fwd.hh
/// @brief Forward declarations for a base class for PluginCostFunctionNetworkOptimizationProblems.
/// @details A PluginCostFunctionNetworkOptimizationProblem defines a special case of a numerical cost function network optimization
/// problem, defined in a plug-in library, to be solved by a suitable Optimizer.  The PluginCostFunctionNetworkOptimizationProblem
/// class does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizationProblem_fwd_hh
#define Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizationProblem_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {

	class PluginCostFunctionNetworkOptimizationProblem;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using PluginCostFunctionNetworkOptimizationProblemSP = MASALA_SHARED_POINTER< PluginCostFunctionNetworkOptimizationProblem >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using PluginCostFunctionNetworkOptimizationProblemCSP = MASALA_SHARED_POINTER< PluginCostFunctionNetworkOptimizationProblem const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using PluginCostFunctionNetworkOptimizationProblemWP = MASALA_WEAK_POINTER< PluginCostFunctionNetworkOptimizationProblem >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using PluginCostFunctionNetworkOptimizationProblemCWP = MASALA_WEAK_POINTER< PluginCostFunctionNetworkOptimizationProblem const >;

} // namespace cost_function_network
} // namespace optimization
} // base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginCostFunctionNetworkOptimizationProblem_fwd_hh