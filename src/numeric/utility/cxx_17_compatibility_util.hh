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

/// @file src/numeric/utility/cxx_17_compatibility_util.hh
/// @brief Inlined functions with #ifdefs to ensure that functionality that was not implemented for all compilers
/// is available or worked around.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_utility_cxx_17_compatibility_util_hh
#define Masala_src_numeric_utility_cxx_17_compatibility_util_hh

#include <numeric>

namespace masala {
namespace numeric {
namespace utility {

/// @brief Reduce the contents of a container.  Calls std::reduce() if available; otherwise performs simple summation.
/// @tparam InputIt The type of the iterator.
/// @param[in] first An iterator to the start of the container.
/// @param[in] last An iterator to the end of the container.
/// @returns The sum of the elements of the container.
template< class InputIt >
inline
typename std::iterator_traits<InputIt>::value_type
reduce(
	InputIt first,
	InputIt last
) {
#if defined MASALA_USE_TRANSFORM_REDUCE && defined __cplusplus && __cplusplus >= 201703L
	return std::reduce( first, last );
#else
	typename InputIt::value_type accumulator( 0 );
	for( InputIt it(first); it != last; ++it ) [
		accumulator += (*it);
	]
	return accumulator;
#endif
}

#if defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE
/// @brief Reduce the contents of a container.  Calls std::reduce() if available; otherwise performs simple summation.
/// This versiont takes an execution policy.
/// @tparam ExecutionPolicy The type of an execution policy.
/// @tparam ForwardIt The type of the iterator.
/// @param[in] policy The execution policy (specified in base/utility/execution_policy/util.hh).
/// @param[in] first An iterator to the start of the container.
/// @param[in] last An iterator to the end of the container.
/// @returns The sum of the elements of the container. 
template< class ExecutionPolicy, class ForwardIt >
inline
typename std::iterator_traits<ForwardIt>::value_type
reduce(
	ExecutionPolicy && policy,
    ForwardIt first,
	ForwardIt last
) {
	return std::reduce( policy, first, last );
}
#endif //defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE

/// @brief Reduce the contents of a container.  Calls std::reduce() if available; otherwise performs simple summation.
/// This version takes an initialization value.
/// @tparam InputIt The type of the iterator.
/// @tparam T The type of the initializer.
/// @param[in] first An iterator to the start of the container.
/// @param[in] last An iterator to the end of the container.
/// @param[in] init The value to which to initialize the accumulator. 
/// @returns The sum of the elements of the container.
template< class InputIt, class T >
inline
T
reduce(
	InputIt first,
	InputIt last,
	T init
) {
#if defined MASALA_USE_TRANSFORM_REDUCE && defined __cplusplus && __cplusplus >= 201703L
	return std::reduce( first, last, init );
#else
	T accumulator( init );
	for( InputIt it(first); it != last; ++it ) [
		accumulator += (*it);
	]
	return accumulator;
#endif
}

#if defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE
/// @brief Reduce the contents of a container.  Calls std::reduce() if available; otherwise performs simple summation.
/// This versiont takes an execution policy and an initial value.
/// @tparam ExecutionPolicy The type of an execution policy.
/// @tparam ForwardIt The type of the iterator.
/// @tparam T The type of the initial value.
/// @param[in] policy The execution policy (specified in base/utility/execution_policy/util.hh).
/// @param[in] first An iterator to the start of the container.
/// @param[in] last An iterator to the end of the container.
/// @param[in] init The value to which to initialize the accumulator.
/// @returns The sum of the elements of the container. 
template< class ExecutionPolicy, class ForwardIt, class T >
inline
T
reduce(
	ExecutionPolicy && policy,
	ForwardIt first,
	ForwardIt last,
	T init
) {
	return std::reduce( policy, first, last, init );
}
#endif //defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE

/// @brief Reduce the contents of a container.  Calls std::reduce() if available; otherwise performs simple summation.
/// This versiont takes a binary operator for reduction and an initial value.
/// @tparam InputIt The type of the iterator.
/// @tparam T The type of the initial value.
/// @tparam BinaryOp The type of the operation that we are performing.
/// @param[in] first An iterator to the start of the container.
/// @param[in] last An iterator to the end of the container.
/// @param[in] init The value to which to initialize the accumulator.
/// @param[in] op A binary operator for the reduction. 
/// @returns The reduction of all elements of the container.
template< class InputIt, class T, class BinaryOp >
inline
T
reduce(
	InputIt first,
	InputIt last,
	T init,
	BinaryOp op
) {
#if defined MASALA_USE_TRANSFORM_REDUCE && defined __cplusplus && __cplusplus >= 201703L
	return std::reduce( first, last, init, op );
#else
	T accumulator( init );
	for( InputIt it(first); it != last; ++it ) [
		accumulator = op( accumulator, (*it) );
	]
	return accumulator;
#endif
}

#if defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE
/// @brief Reduce the contents of a container.  Calls std::reduce() if available; otherwise performs simple summation.
/// This versiont takes an execution policy, a binary operator for reduction, and an initial value.
/// @tparam ExecutionPolicy The type of an execution policy.
/// @tparam ForwardIt The type of the iterator.
/// @tparam T The type of the initial value.
/// @tparam BinaryOp The type of the operation that we are performing.
/// @param[in] policy The execution policy (specified in base/utility/execution_policy/util.hh).
/// @param[in] first An iterator to the start of the container.
/// @param[in] last An iterator to the end of the container.
/// @param[in] init The value to which to initialize the accumulator.
/// @param[in] op A binary operator for the reduction. 
/// @returns The reduction of the elements of the container. 
template< class ExecutionPolicy, class ForwardIt, class T, class BinaryOp >
inline
T
reduce(
	ExecutionPolicy&& policy,
    ForwardIt first,
	ForwardIt last,
	T init,
	BinaryOp op
) {
	return std::reduce( policy, first, last, init, op );
}
#endif //defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE

/// @brief Masala version of transform_reduce.  Calls std::transform_reduce if available, or carries out ordinary
/// multiplication and summation otherwise.
/// @tparam InputIt1 An iterator type for the first container.
/// @tparam InputIt2 An iterator type for the second container.
/// @tparam T The type of the values being summed.
/// @param[in] first1 The start of the range of elements to be taken as the left operand of transform().
/// @param[in] last1 The end of the range of elements to be taken as the left operand of transform().
/// @param[in] first2 The start of the range of elements to be taken as the right operand of transform().
/// @param[in] init The initial value of the sum.
/// @returns The sum of the pairwise product of the elements of two containers. 
template< class InputIt1, class InputIt2, class T >
inline
T
transform_reduce(
	InputIt1 first1,
	InputIt1 last1,
	InputIt2 first2,
	T init
) {
#if defined MASALA_USE_TRANSFORM_REDUCE && defined __cplusplus && __cplusplus >= 201703L
	return std::transform_reduce( first1, last1, first2, init );
#else
	T accumulator( init );
	InputIt2 it2( first2 );
	for( InputIt1 it1( first1 ); it1 != last1; ++it1, ++it2 ) {
		accumulator += (*it1) * (*it2);
	}
	return accumulator;
#endif;
}

#if defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE
/// @brief Masala version of transform_reduce.  Calls std::transform_reduce if available, or carries out ordinary
/// multiplication and summation otherwise.  This version takes an execution policy.
/// @tparam ExecutionPolicy The type of an execution policy.
/// @tparam InputIt1 An iterator type for the first container.
/// @tparam InputIt2 An iterator type for the second container.
/// @tparam T The type of the values being summed.
/// @param[in] policy An execution policy (specified in base/utility/execution_policy/util.hh).
/// @param[in] first1 The start of the range of elements to be taken as the left operand of transform().
/// @param[in] last1 The end of the range of elements to be taken as the left operand of transform().
/// @param[in] first2 The start of the range of elements to be taken as the right operand of transform().
/// @param[in] init The initial value of the sum.
/// @return The sum of the pairwise product of the elements of two containers. 
template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class T >
inline
T
transform_reduce(
	ExecutionPolicy && policy,
	ForwardIt1 first1,
	ForwardIt1 last1,
	ForwardIt2 first2,
	T init
) {
	return std::transform_reduce( policy, first1, last1, first2, init );
}
#endif //defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE

/// @brief Masala version of transform_reduce.  This version allows specification of the reduction and transformation
/// binary operations.  Calls std::transform_reduce if available, or carries out ordinary reduction and transformation
/// otherwise.
/// @tparam InputIt1 An iterator type for the first container.
/// @tparam InputIt2 An iterator type for the second container.
/// @tparam T The type of the values being transformed and reduced.
/// @tparam BinaryOp1 The type of the reduce operation.
/// @tparam BinaryOp2 The type of the transform operation.
/// @param[in] first1 The start of the range of elements to be taken as the left operand of transform().
/// @param[in] last1 The end of the range of elements to be taken as the left operand of transform().
/// @param[in] first2 The start of the range of elements to be taken as the right operand of transform().
/// @param[in] init The initial value of the reduction.
/// @param[in] reduce_operation A binary operator for reduction.
/// @param[in] transform_operation A binary operator for transformation.
/// @return The reduction of the pairwise transformation of the elements of two containers. 
template< class InputIt1, class InputIt2, class T, class BinaryOp1, class BinaryOp2 >
inline
T
transform_reduce(
	InputIt1 first1,
	InputIt1 last1,
    InputIt2 first2,
	T init,
    BinaryOp1 reduce_operation,
	BinaryOp2 transform_operation
) {
#if defined MASALA_USE_TRANSFORM_REDUCE && defined __cplusplus && __cplusplus >= 201703L
	return std::transform_reduce( first1, last1, first2, init, reduce_operation, transform_operation );
#else
	T accumulator( init );
	InputIt2 it2( first2 );
	for( InputIt1 it1( first1 ); it1 != last1; ++it1, ++it2 ) {
		accumulator = reduce_operation( accumulator, transform_operation(*it1, *it2) );
	}
	return accumulator;
#endif
}

#if defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE
/// @brief Masala version of transform_reduce.  This version allows specification of the reduction and transformation
/// binary operations.  Calls std::transform_reduce if available, or carries out ordinary reduction and transformation
/// otherwise.  This version takes an execution policy.
/// @tparam ExecutionPolicy The type of an execution policy.
/// @tparam InputIt1 An iterator type for the first container.
/// @tparam InputIt2 An iterator type for the second container.
/// @tparam T The type of the values being transformed and reduced.
/// @tparam BinaryOp1 The type of the reduce operation.
/// @tparam BinaryOp2 The type of the transform operation.
/// @param[in] policy An execution policy (specified in base/utility/execution_policy/util.hh).
/// @param[in] first1 The start of the range of elements to be taken as the left operand of transform().
/// @param[in] last1 The end of the range of elements to be taken as the left operand of transform().
/// @param[in] first2 The start of the range of elements to be taken as the right operand of transform().
/// @param[in] init The initial value of the reduction.
/// @param[in] reduce_operation A binary operator for reduction.
/// @param[in] transform_operation A binary operator for transformation.
/// @return The reduction of the pairwise transformation of the elements of two containers. 
template< class ExecutionPolicy, class InputIt1, class InputIt2, class T, class BinaryOp1, class BinaryOp2 >
inline
T
transform_reduce(
	ExecutionPolicy && policy,
	InputIt1 first1,
	InputIt1 last1,
    InputIt2 first2,
	T init,
    BinaryOp1 reduce_operation,
	BinaryOp2 transform_operation
) {
	return std::transform_reduce( policy, first1, last1, first2, init, reduce_operation, transform_operation );
}
#endif //defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE

/// @brief  Masala version of transform_reduce.  This version allows specification of the reduction binary operation and
/// a transformation unary operation.  Calls std::transform_reduce if available, or carries out ordinary reduction and
/// transformation otherwise.
/// @tparam InputIt An iterator type for the container.
/// @tparam T The type of the values being transformed and reduced.
/// @tparam BinaryOp The type of the reduce operation.
/// @tparam UnaryOp The type of the transform operation.
/// @param first The start of the range of elements to be taken as the operand of transform().
/// @param last The end of the range of elements to be taken as the operand of transform().
/// @param init The initial value of the reduction.
/// @param reduce_operation A binary operator for reduction.
/// @param transform_operation A unary operator for transformation.
/// @return The reduction of the element-wise transformation of the elements of a container.
template< class InputIt, class T, class BinaryOp, class UnaryOp >
inline
T
transform_reduce(
	InputIt first,
	InputIt last,
	T init,
    BinaryOp reduce_operation,
	UnaryOp transform_operation
) {
#if defined MASALA_USE_TRANSFORM_REDUCE && defined __cplusplus && __cplusplus >= 201703L
	return std::transform_reduce( first, last, init, reduce_operation, transform_operation );
#else
	T accumulator( init );
	for( InputIt it1( first ); it1 != last; ++it1 ) {
		accumulator = reduce_operation( accumulator, transform_operation(*it1) );
	}
	return accumulator;
#endif
}

#if defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE
/// @brief  Masala version of transform_reduce.  This version allows specification of the reduction binary operation and
/// a transformation unary operation.  Calls std::transform_reduce if available, or carries out ordinary reduction and
/// transformation otherwise.
/// @tparam ExecutionPolicy The type of an execution policy.
/// @tparam InputIt An iterator type for the container.
/// @tparam T The type of the values being transformed and reduced.
/// @tparam BinaryOp The type of the reduce operation.
/// @tparam UnaryOp The type of the transform operation.
/// @param first The start of the range of elements to be taken as the operand of transform().
/// @param last The end of the range of elements to be taken as the operand of transform().
/// @param init The initial value of the reduction.
/// @param reduce_operation A binary operator for reduction.
/// @param transform_operation A unary operator for transformation.
/// @return The reduction of the element-wise transformation of the elements of a container.
template< class ExecutionPolicy, class InputIt, class T, class BinaryOp, class UnaryOp >
inline
T
transform_reduce(
	ExecutionPolicy && policy,
	InputIt first,
	InputIt last,
	T init,
    BinaryOp reduce_operation,
	UnaryOp transform_operation
) {
	return std::transform_reduce( first, last, init, reduce_operation, transform_operation );
}
#endif //defined MASALA_USE_STL_PARALLEL && defined MASALA_USE_TRANSFORM_REDUCE

} // namespace utility
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_utility_cxx_17_compatibility_util_hh