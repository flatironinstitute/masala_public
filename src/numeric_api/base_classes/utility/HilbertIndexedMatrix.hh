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
/// @note This class is not intrinsically threadsafe.  Calling code must implement mutex locking schemes.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_hh
#define Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_hh

// Forward declarations:
#include <numeric_api/base_classes/utility/HilbertIndexedMatrix.fwd.hh>

// Base headers:
#include <base/MasalaNoAPIObject.hh>
#include <base/types.hh>

// Parent header:

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace utility {

/// @brief The HilbertIndexedMatrix class.
/// @details A HilbertIndexedMatrix is a 2D matrix in which values following a Hilbert curve through the
/// matrix are arrayed linearly in memory.  This is intended to minimize cache misses when looking up values
/// near to some starting point.
/// @note This class is not intrinsically threadsafe.  Calling code must implement mutex locking schemes.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T >
class HilbertIndexedMatrix : public masala::base::MasalaNoAPIObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	HilbertIndexedMatrix() = default;

	/// @brief Copy constructor.
	HilbertIndexedMatrix( HilbertIndexedMatrix const & ) = default;

	/// @brief Destructor.
	~HilbertIndexedMatrix() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Pointer to the linear array storing the values in Hilbert index order.
    /// @details Deleted on destruction.
    T * array_ = nullptr;

}; // class HilbertIndexedMatrix

template class HilbertIndexedMatrix< masala::base::Real >;
template class HilbertIndexedMatrix< masala::base::Size >;
template class HilbertIndexedMatrix< float >;
template class HilbertIndexedMatrix< signed short int >;
template class HilbertIndexedMatrix< signed int >;
template class HilbertIndexedMatrix< signed long int >;
template class HilbertIndexedMatrix< unsigned short int >;
template class HilbertIndexedMatrix< unsigned int >;
template class HilbertIndexedMatrix< bool >;
template class HilbertIndexedMatrix< char >;

} // namespace utility
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_utility_HilbertIndexedMatrix_hh