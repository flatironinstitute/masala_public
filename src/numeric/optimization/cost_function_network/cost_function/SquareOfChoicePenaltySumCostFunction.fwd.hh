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

/// @file src/numeric/optimization/cost_function_network/cost_function/SquareOfChoicePenaltySumCostFunction.fwd.hh
/// @brief Forward declarations for a class for SquareOfChoicePenaltySumCostFunctions.
/// @details SquareOfChoicePenaltySumCostFunctions define a penalty function which is based on the following:
/// - A penalty is assigned to each choice.
/// - The selected choices' penalties are summed, and a constant is added.
/// - The sum is squared, and this is returned as the penalty.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_SquareOfChoicePenaltySumCostFunction_fwd_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_SquareOfChoicePenaltySumCostFunction_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

	class SquareOfChoicePenaltySumCostFunction;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using SquareOfChoicePenaltySumCostFunctionSP = MASALA_SHARED_POINTER< SquareOfChoicePenaltySumCostFunction >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using SquareOfChoicePenaltySumCostFunctionCSP = MASALA_SHARED_POINTER< SquareOfChoicePenaltySumCostFunction const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using SquareOfChoicePenaltySumCostFunctionWP = MASALA_WEAK_POINTER< SquareOfChoicePenaltySumCostFunction >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using SquareOfChoicePenaltySumCostFunctionCWP = MASALA_WEAK_POINTER< SquareOfChoicePenaltySumCostFunction const >;

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif //Masala_src_numeric_optimization_cost_function_network_cost_function_SquareOfChoicePenaltySumCostFunction_fwd_hh