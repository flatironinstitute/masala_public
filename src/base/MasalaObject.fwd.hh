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

/// @file src/base/MasalaObject.fwd.hh
/// @brief Forward declarations for a base class for all Masala derived classes.  This
/// allows the possibility of having a generic MasalaObject pointer or shared pointer.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_MasalaObject_fwd_hh
#define Masala_src_base_MasalaObject_fwd_hh

#include <memory> // For std::shared_ptr

namespace masala {
namespace base {

	class MasalaObject;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	using MasalaObjectSP = std::shared_ptr< MasalaObject >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	using MasalaObjectCSP = std::shared_ptr< MasalaObject const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	using MasalaObjectWP = std::weak_ptr< MasalaObject >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	using MasalaObjectCWP = std::weak_ptr< MasalaObject const >;

} // namespace base
} // namesapce masala

#endif //Masala_src_base_MasalaObject_fwd_hh