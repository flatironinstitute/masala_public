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

/// @file src/base/managers/database/elements/MasalaElementDatabase.fwd.hh
/// @brief Forward declarations for a class stored within the MasalaDatabaseManager, which
/// manages element data.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_database_elements_MasalaElementDatabase_fwd_hh
#define Masala_src_base_managers_database_elements_MasalaElementDatabase_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace managers {
namespace database {
namespace elements {

	class MasalaElementDatabase;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using MasalaElementDatabaseSP = MASALA_SHARED_POINTER< MasalaElementDatabase >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using MasalaElementDatabaseCSP = MASALA_SHARED_POINTER< MasalaElementDatabase const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using MasalaElementDatabaseWP = MASALA_WEAK_POINTER< MasalaElementDatabase >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using MasalaElementDatabaseCWP = MASALA_WEAK_POINTER< MasalaElementDatabase const >;

} // namespace elements
} // namespace database
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_database_elements_MasalaElementDatabase_fwd_hh