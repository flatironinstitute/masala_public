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

/// @file src/numeric_api/base_classes/utility/HilbertIndexedMatrix.cc
/// @brief Implementations for the HilbertIndexedMatrix class.
/// @details A HilbertIndexedMatrix is a 2D matrix in which values following a Hilbert curve through the
/// matrix are arrayed linearly in memory.  This is intended to minimize cache misses when looking up values
/// near to some starting point.
/// @note This class is not intrinsically threadsafe.  Calling code must implement mutex locking schemes.  Also note
/// that, under the hood, storage must be allocated for a square matrix, regardless the actual matrix dimensions.  This means
/// that this class is inefficient for rectangular matrices where the dimensions are very different.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/utility/HilbertIndexedMatrix.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace utility {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Dimensions constructor.
/// @details This leaves the matrix uninitialized.
template< typename T >
HilbertIndexedMatrix<T>::HilbertIndexedMatrix(
	masala::base::Size const rows, masala::base::Size const cols
) :
	masala::base::MasalaNoAPIObject(),
	rows_( rows ),
	cols_( cols )
{
	protected_resize_array( 0, 0, rows_, cols_ );
}


/// @brief Destructor.
template< typename T >
HilbertIndexedMatrix<T>::~HilbertIndexedMatrix() {
	if( array_ != nullptr ) {
		delete[] array_;
		array_ = nullptr;
	}
}

/// @brief Get the name of this class.
/// @returns "HilbertIndexedMatrix".
template< typename T >
std::string
HilbertIndexedMatrix<T>::class_name() const {
	return "HilbertIndexedMatrix";
}

/// @brief Get the namespace of this class.
/// @returns "masala::numeric_api::base_classes::utility".
template< typename T >
std::string
HilbertIndexedMatrix<T>::class_namespace() const {
	return "masala::numeric_api::base_classes::utility";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Resize the array_ private member variable so that it matches the rows_ and columns_.
/// @details Under the hood, storage for a square matrix (with dimension equal to the larger of rows_ or columns_) is
/// always allocated.
template< typename T >
void
HilbertIndexedMatrix<T>::protected_resize_array(
	masala::base::Size const ,//oldrows,
	masala::base::Size const ,//oldcols,
	masala::base::Size const rows,
	masala::base::Size const cols
) {
	using masala::base::Size;

	T const * old_array = array_;
	if( rows > 0 && cols > 0 ) {
		Size const maxdim( std::max( rows, cols ) );
		Size const maxdimsq( maxdim*maxdim );
		array_ = new T[maxdimsq];
		if( array_ == nullptr ) {
			if( old_array != nullptr ) {
				delete[] old_array;
				MASALA_THROW( class_namespace() + "::" + class_name(), "protected_resize_array", "Unable to allocate array of size " + std::to_string( maxdimsq * sizeof(T) ) + " bytes." );
			}
		}
	} else {
		array_ = nullptr;
	}

	// TODO COPY DATA HERE.

	if( old_array != nullptr ) {
		delete[] old_array;
	}
}


} // namespace utility
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
