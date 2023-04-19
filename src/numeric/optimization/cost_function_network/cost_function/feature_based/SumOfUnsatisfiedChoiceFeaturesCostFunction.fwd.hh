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

/// @file src/numeric/optimization/cost_function_network/cost_function/feature_based/SumOfUnsatisfiedChoiceFeaturesCostFunction.fwd.hh
/// @brief Forward declarations for a pure virtual base class for SumOfUnsatisfiedChoiceFeaturesCostFunctions.
/// @details SumOfUnsatisfiedChoiceFeaturesCostFunctions define a penalty function which is based on the following:
/// - One or more features are defined for each choice at each node.  (A feature could be a hydrogen bond
/// donor or acceptor, for instance, in a packing problem)
/// - Each feature has an expected minimum and maximum number of connections that can be set.
/// - For each pair of choices, the features that are connected can be set.
/// - At calculation time, the number of unsatisfied features (total features minus features
/// satisfied by connections) is returned.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_SumOfUnsatisfiedChoiceFeaturesCostFunction_fwd_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_SumOfUnsatisfiedChoiceFeaturesCostFunction_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {
namespace feature_based {

	template< typename T >
	class SumOfUnsatisfiedChoiceFeaturesCostFunction;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	template< typename T >
	using SumOfUnsatisfiedChoiceFeaturesCostFunctionSP = MASALA_SHARED_POINTER< SumOfUnsatisfiedChoiceFeaturesCostFunction<T> >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	template< typename T >
	using SumOfUnsatisfiedChoiceFeaturesCostFunctionCSP = MASALA_SHARED_POINTER< SumOfUnsatisfiedChoiceFeaturesCostFunction<T> const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	template< typename T >
	using SumOfUnsatisfiedChoiceFeaturesCostFunctionWP = MASALA_WEAK_POINTER< SumOfUnsatisfiedChoiceFeaturesCostFunction<T> >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	template< typename T >
	using SumOfUnsatisfiedChoiceFeaturesCostFunctionCWP = MASALA_WEAK_POINTER< SumOfUnsatisfiedChoiceFeaturesCostFunction<T> const >;

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_SumOfUnsatisfiedChoiceFeaturesCostFunction_fwd_hh