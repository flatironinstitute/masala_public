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
#include <utility>

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

	/// @brief Accessor operator.
	T &
	operator()(
		masala::base::Size const row,
		masala::base::Size const col
	) {
		DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( row < rows_ && col < cols_, "operator()", "The matrix has " + std::to_string(rows_)
			+ " rows and " + std::to_string( cols_ ) + " columns.  Indices (" + std::to_string(row) + "," + std::to_string(col)
			+ ") are out of bounds."
		);
		return array_[ matrix_coord_to_array_coord( allocated_matrix_cols_or_rows_, row, col ) ];
	}

	/// @brief Const accessor operator.
	T const &
	operator() (
		masala::base::Size const row,
		masala::base::Size const col
	) const {
		DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( row < rows_ && col < cols_, "operator()", "The matrix has " + std::to_string(rows_)
			+ " rows and " + std::to_string( cols_ ) + " columns.  Indices (" + std::to_string(row) + "," + std::to_string(col)
			+ ") are out of bounds."
		);
		return array_[ matrix_coord_to_array_coord( allocated_matrix_cols_or_rows_, row, col ) ];
	}

	/// @brief Access the data array directly.  (Const access.)
	/// @details Only intended for testing.  Use setters, getters, and operator() for routine access.
	/// @note Could be nullptr if matrix is empty and size zero.
	inline
	T const *
	data() const {
		return array_;
	}

	/// @brief Access the data array directly.  (Non-const access.)
	/// @details Dangerous!  Only intended for testing.  Use setters, getters, and operator() for routine access.
	/// @note Could be nullptr if matrix is empty and size zero.
	inline
	T *
	data_nonconst() {
		return array_;
	}
	
	/// @brief Get the allocated array size.
	inline
	masala::base::Size
	allocated_array_size() const{
		return allocated_array_size_;
	}

	/// @brief Get the number of rows.
	inline masala::base::Size rows() const{ return rows_; }

	/// @brief Get the number of columns.
	inline masala::base::Size cols() const{ return cols_; }

	/// @brief Fill the matrix with zeroes.
	inline
	void
	setZero() {
		using masala::base::Size;

		for( Size i(0); i<allocated_array_size_; ++i ) {
			array_[i] = T(0);
		}
	}

	/// @brief Resize the matrix and preserve existing data.  Note that if the matrix shinks, some data will
	/// be lost.  If the matrix grows, the new entries will be uninitialized.
	/// @note If new_rows or new_cols is zero, the matrix size is zero and storage is deallocated.
	inline
	void
	conservativeResize(
		masala::base::Size const new_rows,
		masala::base::Size const new_cols
	) {
		using masala::base::Size;
		protected_resize_array( rows_, cols_, new_rows, new_cols );
		rows_ = new_rows;
		cols_ = new_cols;
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

		Size const old_maxdim_round( compute_power_of_two_size( oldrows, oldcols ) );

		T const * old_array = array_;
		if( rows > 0 && cols > 0 ) {
			Size const maxdim_round( compute_power_of_two_size( rows, cols ) );
			if( maxdim_round != old_maxdim_round ) {
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

					// Copy old data:
					Size const old_maxdim_sq( old_maxdim_round * old_maxdim_round );
					for( Size i(0); i<old_maxdim_sq; ++i ) {
						std::pair< Size, Size > const coord( array_coord_to_matrix_coord( old_maxdim_round, i ) );
						if( coord.first < rows && coord.second < cols ) {
							Size const new_i( matrix_coord_to_array_coord( maxdim_round, coord.first, coord.second ) );
							DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( new_i < maxdimsq, "protected_resize_array", "Destination array index out of bounds.  This is a program error.  Please consult a developer, as this ought not to happen." );
							array_[ new_i ] = old_array[i];
						}
					}
				}
			}
		} else {
			array_ = nullptr;
			allocated_array_size_ = 0;
			allocated_matrix_cols_or_rows_ = 0;
		}

		if( old_array != nullptr ) {
			delete[] old_array;
		}
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	inline
	masala::base::Size
	compute_power_of_two_size(
		masala::base::Size const nrows,
		masala::base::Size const ncols
	) const {
		using masala::base::Size;
		return static_cast< Size >(
			std::round(
				std::pow(
					2,
					std::ceil(
						std::log2(
							static_cast<double>(
								std::max( nrows, ncols )
							)
						)
					)
				)
			)
		);
	}

	/// @brief Rotate and/or flip a quadrant appropriately.  Used when coverting between the row/column index of
	/// the matrix and the linear index in the array.
	/// @details From C code taken from https://hugocisneros.com/notes/hilbert_curve_indexing/.  Credit goes to
	/// Hugo Cisneros for this.  Small modifications were made by Vikram K. Mulligan to convert to C++.
	inline
	void
	rotate_and_flip_quadrant(
		masala::base::Size const dimension,
		masala::base::Size & row,
		masala::base::Size & col,
		masala::base::Size const rx,
		masala::base::Size const ry
	) const {
		if (ry == 0) {
			if (rx == 1) {
				row = dimension-1 - row;
				col = dimension-1 - col;
			}
			// Swap x and y:
			std::swap( row, col );
		}
	}

	/// @brief Convert matrix coordinates to the linear coordinate in the array.
	/// @details From C code taken from https://hugocisneros.com/notes/hilbert_curve_indexing/.  Credit goes to
	/// Hugo Cisneros for this.  Small modifications were made by Vikram K. Mulligan to convert to C++.
	/// @param[in] dimension The dimension of the matrix.  Assumed to be an even power of 2.
	/// @param[in] row The row of the matrix.
	/// @param[in] col The column of the matrix.
	/// @return The index in the array used for data storage.
	inline
	masala::base::Size
	matrix_coord_to_array_coord(
		masala::base::Size const dimension,
		masala::base::Size row,
		masala::base::Size col
	) const {
		masala::base::Size rx, ry, lincoord(0);
		for ( masala::base::Size localdimension( dimension/2 ); localdimension >= 1; localdimension /= 2 ) {
			rx = (col & localdimension) > 0;
			ry = (row & localdimension) > 0;
			lincoord += localdimension * localdimension * ((3 * rx) ^ ry);
			rotate_and_flip_quadrant(dimension, row, col, rx, ry);
		}
		return lincoord;
	}

	/// @brief Convert the linear coordinate in the array to matrix row and column.
	/// @param dimension The dimension of the matrix.  Assumed to be an even power of 2.
	/// @param array_coord The index in the array used for data storage.
	/// @returns A pair of (row, col) indicating the coordinates in the matrix.
	inline
	std::pair< masala::base::Size, masala::base::Size >
	array_coord_to_matrix_coord(
		masala::base::Size const dimension,
		masala::base::Size const array_coord
	) const {
		masala::base::Size rx, ry, local_array_coord(array_coord);
		masala::base::Size col(0), row(0);
		for (masala::base::Size localdimension(1); localdimension<dimension; localdimension*=2) {
			rx = 1 & (local_array_coord/2);
			ry = 1 & (local_array_coord ^ rx);
			rotate_and_flip_quadrant(localdimension, row, col, rx, ry);
			col += localdimension * rx;
			row += localdimension * ry;
			local_array_coord /= 4;
		}
		return std::make_pair( row, col );
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