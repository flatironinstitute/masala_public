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

/// @file src/base/managers/version/MasalaVersionManager.cc
/// @brief A static singleton for managing the version of Masala's core library and
/// of plugin libraries, along with any inter-library version dependencies.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/version/MasalaVersionManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/version/masala_version.hh>
#include <base/managers/version/MasalaModuleVersionInfo.hh>

// STL headers:

namespace masala {
namespace base {
namespace managers {
namespace version {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaVersionManagerHandle
MasalaVersionManager::get_instance() {
    static MasalaVersionManager version_manager;
    return &version_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Private constructor: object can only be instantiated with getInstance().
MasalaVersionManager::MasalaVersionManager() :
    masala::base::MasalaObject()
{
    std::lock_guard< std::mutex > lock( masala_version_manager_mutex_ );
    module_version_infos_[ "Masala" ] = masala::make_shared< MasalaModuleVersionInfo >( "Masala", masala_version() );
}


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaVersionManager".
std::string
MasalaVersionManager::class_name() const {
    return "MasalaVersionManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::version".
std::string
MasalaVersionManager::class_namespace() const {
    return "masala::base::managers::version";
}


} // namespace version
} // namespace managers
} // namespace base
} // namespace masala
