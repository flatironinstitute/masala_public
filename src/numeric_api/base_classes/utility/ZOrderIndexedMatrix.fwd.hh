/*
    Masala
    Copyright (C) 2026 Vikram K. Mulligan

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

/// @file src/numeric_api/base_classes/utility/ZOrderIndexedMatrix.fwd.hh
/// @brief Forward declarations for the ZOrderIndexedMatrix class.
/// @details A ZOrderIndexedMatrix is a 2D matrix in which values following a fractal Z-shaped (Morton order) curve through the
/// matrix are arrayed linearly in memory.  This is intended to minimize cache misses when looking up values
/// near to some starting point, while still providing a fast way to convert between 2D matrix coordinates and 2D array coordinate.
/// @note This class is not intrinsically threadsafe.  Calling code must implement mutex locking schemes.  Also note
/// that, under the hood, storage must be allocated for a rectangular matrix where each dimension is an even power of 2, regardless
/// the actual matrix dimensions.  This means that this class is somewhat inefficient for rectangular matrices where the dimensions
/// are very different than even powers of 2.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_utility_ZOrderIndexedMatrix_fwd_hh
#define Masala_src_numeric_api_base_classes_utility_ZOrderIndexedMatrix_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace utility {

	template< typename T >
	class ZOrderIndexedMatrix;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	template< typename T >
	using ZOrderIndexedMatrixSP = MASALA_SHARED_POINTER< ZOrderIndexedMatrix<T> >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	template< typename T >
	using ZOrderIndexedMatrixCSP = MASALA_SHARED_POINTER< ZOrderIndexedMatrix<T> const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	template< typename T >
	using ZOrderIndexedMatrixWP = MASALA_WEAK_POINTER< ZOrderIndexedMatrix<T> >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	template< typename T >
	using ZOrderIndexedMatrixCWP = MASALA_WEAK_POINTER< ZOrderIndexedMatrix<T> const >;

} // namespace utility
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_utility_ZOrderIndexedMatrix_fwd_hh