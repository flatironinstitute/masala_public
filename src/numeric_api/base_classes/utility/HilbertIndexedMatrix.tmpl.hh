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

/// @file src/numeric_api/base_classes/utility/HilbertIndexedMatrix.hh
/// @brief Headers for the HilbertIndexedMatrix class.
/// @details A HilbertIndexedMatrix is a 2D matrix in which values following a Hilbert curve through the
/// matrix are arrayed linearly in memory.  This is intended to minimize cache misses when looking up values
/// near to some starting point.
/// @note This class is not intrinsically threadsafe.  Calling code must implement mutex locking schemes.  Also note
/// that, under the hood, storage must be allocated for a square matrix, regardless the actual matrix dimensions.  This means
/// that this class is inefficient for rectangular matrices where the dimensions are very different.  Moreover, the actual
/// size (number of rows or columns) of the allocated matrix must be an even power of 2, so there's a rounding-up.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_hh
#define Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_hh

// Forward declarations:
#include <numeric_api/base_classes/utility/HilbertIndexedMatrix.fwd.hh>

// Base headers:
#include <base/MasalaNoAPIObject.hh>
#include <base/types.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace utility {

/// @brief The HilbertIndexedMatrix class.
/// @details A HilbertIndexedMatrix is a 2D matrix in which values following a Hilbert curve through the
/// matrix are arrayed linearly in memory.  This is intended to minimize cache misses when looking up values
/// near to some starting point.
/// @note This class is not intrinsically threadsafe.  Calling code must implement mutex locking schemes.  Also note
/// that, under the hood, storage must be allocated for a square matrix, regardless the actual matrix dimensions.  This means
/// that this class is inefficient for rectangular matrices where the dimensions are very different.  Moreover, the actual
/// size (number of rows or columns) of the allocated matrix must be an even power of 2, so there's a rounding-up.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T >
class HilbertIndexedMatrix : public masala::base::MasalaNoAPIObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	HilbertIndexedMatrix() = default;

	/// @brief Dimensions constructor.
	/// @details This leaves the matrix uninitialized.
	HilbertIndexedMatrix(
		masala::base::Size const rows,
		masala::base::Size const cols
	) :
		masala::base::MasalaNoAPIObject(),
		rows_( rows ),
		cols_( cols )
	{
		protected_resize_array( 0, 0, rows_, cols_ );
	}

	/// @brief Copy constructor.
	HilbertIndexedMatrix( HilbertIndexedMatrix const & ) = default;

	/// @brief Destructor.
	~HilbertIndexedMatrix() override {
		if( array_ != nullptr ) {
			delete[] array_;
			array_ = nullptr;
		}
	}

	/// @brief Get the name of this class.
	/// @returns "HilbertIndexedMatrix".
	std::string
	class_name() const override {
		return "HilbertIndexedMatrix";
	}

	/// @brief Get the namespace of this class.
	/// @returns "masala::numeric_api::base_classes::utility".
	std::string
	class_namespace() const override {
		return "masala::numeric_api::base_classes::utility";
	}

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Access the data array directly.  (Const access.)
	/// @details Only intended for testing.  Use setters, getters, and operator() for routine access.
	/// @note Could be nullptr if matrix is empty and size zero.
	inline T const *
	data() const {
		return array_;
	}

	/// @brief Access the data array directly.  (Non-const access.)
	/// @details Dangerous!  Only intended for testing.  Use setters, getters, and operator() for routine access.
	/// @note Could be nullptr if matrix is empty and size zero.
	inline T *
	data_nonconst() {
		return array_;
	}

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Resize the array_ private member variable so that it matches the rows_ and columns_.
	/// @details Under the hood, storage for a square matrix (with dimension equal to the larger of rows_ or columns_) is
	/// always allocated.
	inline
	void
	protected_resize_array(
		masala::base::Size const oldrows,
		masala::base::Size const oldcols,
		masala::base::Size const rows,
		masala::base::Size const cols
	) {
		using masala::base::Size;

		T const * old_array = array_;
		if( rows > 0 && cols > 0 ) {
			Size const maxdim( std::max( rows, cols ) );
			Size const maxdim_round( static_cast< Size >( std::round( std::pow( 2, std::ceil( std::log2( static_cast<double>(maxdim) ) ) ) ) ) );
			Size const maxdimsq( maxdim_round*maxdim_round );
			array_ = new T[maxdimsq];
			if( array_ == nullptr ) {
				allocated_array_size_ = 0;
				allocated_matrix_cols_or_rows_ = 0;
				if( old_array != nullptr ) {
					delete[] old_array;
					MASALA_THROW( class_namespace() + "::" + class_name(), "protected_resize_array", "Unable to allocate array of size " + std::to_string( maxdimsq * sizeof(T) ) + " bytes." );
				}
			} else {
				allocated_array_size_ = maxdimsq;
				allocated_matrix_cols_or_rows_ = maxdim_round;
			}
		} else {
			array_ = nullptr;
			allocated_array_size_ = 0;
			allocated_matrix_cols_or_rows_ = 0;
		}

		// TODO COPY DATA HERE.

		if( old_array != nullptr ) {
			delete[] old_array;
		}
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Rotate and/or flip a quadrant appropriately.  Used when coverting between the row/column index of
	/// the matrix and the linear index in the array.
	/// @details From C code taken from https://hugocisneros.com/notes/hilbert_curve_indexing/.  Credit goes to
	/// Hugo Cisneros for this.  Small modifications were made by Vikram K. Mulligan to convert to C++.
	inline
	void
	rotate_and_flip_quadrant(
		masala::base::Size const dimension,
		masala::base::Size & x,
		masala::base::Size & y,
		masala::base::Size const rx,
		masala::base::Size const ry
	) const {
		if (ry == 0) {
			if (rx == 1) {
				x = dimension-1 - x;
				y = dimension-1 - y;
			}
			// Swap x and y:
			std::swap( x, y );
		}
	}

	/// @brief Convert matrix coordinates to the linear coordinate in the array.
	/// @details From C code taken from https://hugocisneros.com/notes/hilbert_curve_indexing/.  Credit goes to
	/// Hugo Cisneros for this.  Small modifications were made by Vikram K. Mulligan to convert to C++.
	/// @tparam T The type contained in this matrix.
	/// @param dimension The dimension of the matrix.  Assumed to be an even power of 2.
	/// @param x The column of the matrix.
	/// @param y The row of the matrix.
	/// @return The index in the array used for data storage.
	inline
	masala::base::Size
	matrix_coord_to_array_coord(
		masala::base::Size const dimension,
		masala::base::Size x,
		masala::base::Size y
	) const {
		masala::base::Size rx, ry, lincoord(0);
		for ( masala::base::Size localdimension( dimension/2 ); localdimension >= 1; localdimension /= 2 ) {
			rx = (x & localdimension) > 0;
			ry = (y & localdimension) > 0;
			lincoord += localdimension * localdimension * ((3 * rx) ^ ry);
			rotate_and_flip_quadrant(dimension, x, y, rx, ry);
		}
		return lincoord;
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The number of rows in this object.
	masala::base::Size rows_ = 0;

	/// @brief The number of columns in this object.
	masala::base::Size cols_ = 0;

	/// @brief Pointer to the linear array storing the values in Hilbert index order.
	/// @details Deleted on destruction.
	T * array_ = nullptr;

	/// @brief The size of the allocated array.
	masala::base::Size allocated_array_size_ = 0;

	/// @brief The dimension of the square matrix actually allocated.
	/// @details This is the largest of rows_ or columns_, rounded up to be a power of 2.
	masala::base::Size allocated_matrix_cols_or_rows_ = 0;

}; // class HilbertIndexedMatrix

} // namespace utility
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_hh