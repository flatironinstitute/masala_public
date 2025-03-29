/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginPairwisePrecomputedCFNProblemScratchSpace.fwd.hh
/// @brief Forward declarations for a non-instantiable base class for PluginPairwisePrecomputedCFNProblemScratchSpaces.
/// @details PluginPairwisePrecomputedCFNProblemScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunctionNetworkOptimizationProblem to another.  They store the scratch spaces for the individual cost functions.  These
/// are subclassed in other Masala libraries.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCFNProblemScratchSpace_fwd_hh
#define Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCFNProblemScratchSpace_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {

	class PluginPairwisePrecomputedCFNProblemScratchSpace;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using PluginPairwisePrecomputedCFNProblemScratchSpaceSP = MASALA_SHARED_POINTER< PluginPairwisePrecomputedCFNProblemScratchSpace >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using PluginPairwisePrecomputedCFNProblemScratchSpaceCSP = MASALA_SHARED_POINTER< PluginPairwisePrecomputedCFNProblemScratchSpace const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using PluginPairwisePrecomputedCFNProblemScratchSpaceWP = MASALA_WEAK_POINTER< PluginPairwisePrecomputedCFNProblemScratchSpace >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using PluginPairwisePrecomputedCFNProblemScratchSpaceCWP = MASALA_WEAK_POINTER< PluginPairwisePrecomputedCFNProblemScratchSpace const >;

} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCFNProblemScratchSpace_fwd_hh