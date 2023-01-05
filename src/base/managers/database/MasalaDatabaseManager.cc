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

/// @file src/base/managers/database/MasalaDatabaseManager.cc
/// @brief A static singleton for managing data loaded from the Masala database.
/// @details The core Masala database stores minimal chemical information, such as
/// element properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/database/MasalaDatabaseManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/utility/string/string_manipulation.hh>
#include <base/managers/database/MasalaDatabaseManagerCreationKey.hh>

// STL headers:
#include <string>
#include <iostream>

namespace masala {
namespace base {
namespace managers {
namespace database {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaDatabaseManagerHandle
MasalaDatabaseManager::get_instance() {
    static MasalaDatabaseManager database_manager;
    return &database_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Private constructor: object can only be instantiated with getInstance().
MasalaDatabaseManager::MasalaDatabaseManager() :
    masala::base::MasalaObject()
{
    absolute_database_path_ = "../database/"; //TODO FIX THIS!
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaDatabaseManager".
std::string
MasalaDatabaseManager::class_name() const {
    return "MasalaDatabaseManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::database".
std::string
MasalaDatabaseManager::class_namespace() const {
    return "masala::base::managers::database";
}

/// @brief Access the element database.
/// @details Triggers initialization of this database (i.e. read from disk) the
/// first time this is called.  Initialization is threadsafe.
masala::base::managers::database::elements::MasalaElementDatabase const &
MasalaDatabaseManager::element_database() const {
    {
        std::lock_guard< std::mutex > lock( masala_database_manager_mutex_ );
        if( element_database_ == nullptr ) {
            element_database_ = masala::make_shared< elements::MasalaElementDatabase >(
                MasalaDatabaseManagerCreationKey(), absolute_database_path_
            );
        }
    }
    return *element_database_;
}

} // namespace database
} // namespace managers
} // namespace base
} // namespace masala
