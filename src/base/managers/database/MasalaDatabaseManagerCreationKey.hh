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

/// @file src/base/managers/database/MasalaElementDatabaseCreationKey.hh
/// @brief Headers for a key class that can only be created by the MasalaDatabaseManager,
/// which ensures that only it can create sub-databases.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_database_MasalaDatabaseManagerCreationKey_hh
#define Masala_src_base_managers_database_MasalaDatabaseManagerCreationKey_hh

// Friend header:
#include <base/managers/database/MasalaDatabaseManager.hh>

namespace masala {
namespace base {
namespace managers {
namespace database {

/// @brief A key class that can only be created by the MasalaDatabaseManager,
/// which ensures that only it can create sub-databases.
class MasalaDatabaseManagerCreationKey {

    // Friendship to ensure that only the MasalaDatabaseManager can create this
    // key class, which has a private constructor:
    friend class MasalaDatabaseManager;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated by the
    /// MasalaDatabaseManager, its friend.
    MasalaDatabaseManagerCreationKey() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaDatabaseManagerCreationKey( MasalaDatabaseManagerCreationKey const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaDatabaseManagerCreationKey const & ) = delete;

    /// @brief Default destructor.
    ~MasalaDatabaseManagerCreationKey() = default;

};

} // namespace database
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_database_MasalaDatabaseManagerCreationKey_hh