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

/// @file src/base/MasalaObject.fwd.hh
/// @brief Forward declarations for a base class for all Masala derived classes.  This
/// allows the possibility of having a generic MasalaObject pointer or shared pointer.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_MasalaObject_fwd_hh
#define Masala_src_base_MasalaObject_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {

	class MasalaObject;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using MasalaObjectSP = MASALA_SHARED_POINTER< MasalaObject >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using MasalaObjectCSP = MASALA_SHARED_POINTER< MasalaObject const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using MasalaObjectWP = MASALA_WEAK_POINTER< MasalaObject >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using MasalaObjectCWP = MASALA_WEAK_POINTER< MasalaObject const >;

} // namespace base
} // namespace masala

#endif //Masala_src_base_MasalaObject_fwd_hh