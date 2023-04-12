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

/// @file src/numeric/optimization/cost_function_network/cost_function/CostFunction.fwd.hh
/// @brief Forward declarations for a non-instantiable base class for CostFunctions.
/// @details CostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_fwd_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

	class CostFunction;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using CostFunctionSP = MASALA_SHARED_POINTER< CostFunction >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using CostFunctionCSP = MASALA_SHARED_POINTER< CostFunction const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using CostFunctionWP = MASALA_WEAK_POINTER< CostFunction >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using CostFunctionCWP = MASALA_WEAK_POINTER< CostFunction const >;

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_fwd_hh