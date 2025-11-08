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

/// @file src/numeric_api/base_classes/utility/HilbertIndexedMatrix.fwd.hh
/// @brief Forward declarations for the HilbertIndexedMatrix class.
/// @details A HilbertIndexedMatrix is a 2D matrix in which values following a Hilbert curve through the
/// matrix are arrayed linearly in memory.  This is intended to minimize cache misses when looking up values
/// near to some starting point.
/// @note This class is not intrinsically threadsafe.  Calling code must implement mutex locking schemes.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_fwd_hh
#define Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace utility {

	class HilbertIndexedMatrix;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using HilbertIndexedMatrixSP = MASALA_SHARED_POINTER< HilbertIndexedMatrix >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using HilbertIndexedMatrixCSP = MASALA_SHARED_POINTER< HilbertIndexedMatrix const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using HilbertIndexedMatrixWP = MASALA_WEAK_POINTER< HilbertIndexedMatrix >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using HilbertIndexedMatrixCWP = MASALA_WEAK_POINTER< HilbertIndexedMatrix const >;

} // namespace utility
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_fwd_hh