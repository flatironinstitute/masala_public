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

/// @file src/numeric_api/base_classes/optimization/LineOptimizer.fwd.hh
/// @brief Forward declarations for a pure virtual base class for LineOptimizers.
/// @details LineOptimizers solve a numerical optimization function for a real-valued
/// function of one variable.  Since line optimization is a sub-problem for many
/// other optimization problems, LineOptimizers are implemented as their own special
/// case class.  Note that this class does NOT derive from the general Optimizer class.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_LineOptimizer_fwd_hh
#define Masala_src_numeric_api_base_classes_optimization_LineOptimizer_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {

	class LineOptimizer;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using LineOptimizerSP = MASALA_SHARED_POINTER< LineOptimizer >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using LineOptimizerCSP = MASALA_SHARED_POINTER< LineOptimizer const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using LineOptimizerWP = MASALA_WEAK_POINTER< LineOptimizer >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using LineOptimizerCWP = MASALA_WEAK_POINTER< LineOptimizer const >;

} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_optimization_LineOptimizer_fwd_hh