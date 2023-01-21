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

/// @file src/base/managers/database/MasalaElementDatabaseCreationKey.fwd.hh
/// @brief Forward declarations for a key class that can only be created by the
/// MasalaDatabaseManager, which ensures that only it can create sub-databases.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_database_MasalaDatabaseManagerCreationKey_fwd_hh
#define Masala_src_base_managers_database_MasalaDatabaseManagerCreationKey_fwd_hh

namespace masala {
namespace base {
namespace managers {
namespace database {

	class MasalaDatabaseManagerCreationKey;

} // namespace database
} // namespace managers
} // namespace base
} // namesapce masala

#endif //Masala_src_base_managers_database_MasalaDatabaseManagerCreationKey_fwd_hh