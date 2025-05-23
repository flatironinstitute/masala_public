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

/// @file src/numeric_api/base_classes/optimization/real_valued_local/PluginRealValuedFunctionLocalOptimizer.fwd.hh
/// @brief Forward declarations for a pure virtual base class for PluginRealValuedFunctionLocalOptimizers.
/// @details PluginRealValuedFunctionLocalOptimizers solve a numerical loss function minimization problem using
/// gradients of the loss function with respect to free parameters.  They have no chemical knowledge.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginRealValuedFunctionLocalOptimizer_fwd_hh
#define Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginRealValuedFunctionLocalOptimizer_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace real_valued_local {

	class PluginRealValuedFunctionLocalOptimizer;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using PluginRealValuedFunctionLocalOptimizerSP = MASALA_SHARED_POINTER< PluginRealValuedFunctionLocalOptimizer >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using PluginRealValuedFunctionLocalOptimizerCSP = MASALA_SHARED_POINTER< PluginRealValuedFunctionLocalOptimizer const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using PluginRealValuedFunctionLocalOptimizerWP = MASALA_WEAK_POINTER< PluginRealValuedFunctionLocalOptimizer >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using PluginRealValuedFunctionLocalOptimizerCWP = MASALA_WEAK_POINTER< PluginRealValuedFunctionLocalOptimizer const >;

} // namespace real_valued_local
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_optimization_real_valued_local_PluginRealValuedFunctionLocalOptimizer_fwd_hh