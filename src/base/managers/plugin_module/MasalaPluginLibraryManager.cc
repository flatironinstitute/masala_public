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

/// @file src/base/managers/plugin_module/MasalaPluginLibraryManager.cc
/// @brief A static singleton for managing plugin libaries for Masala.
/// @details This manages the .dll (Windows), .so (Linux), or .dylib (MacOS)
/// dyanmic-link libraries that are loaded, which contain plugin modules.
/// The MasalaPluginModuleManager in turn manages the plugins contained by
/// these libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/plugin_module/MasalaPluginLibraryManager.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>

// STL headers:
#include <string>
#include <dlfcn.h>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaPluginLibraryManagerHandle
MasalaPluginLibraryManager::get_instance() {
    static MasalaPluginLibraryManager plugin_manager;
    return &plugin_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaPluginLibraryManager".
std::string
MasalaPluginLibraryManager::class_name() const {
    return "MasalaPluginLibraryManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::plugin_module".
std::string
MasalaPluginLibraryManager::class_namespace() const {
    return "masala::base::managers::plugin_module";
}

/// @brief Completely reset the manager.
/// @details Unregisters all plugin libraries.
/// @note Calls reset() on the MasalaPluginModuleManager.
void
MasalaPluginLibraryManager::reset() {
    std::lock_guard< std::mutex > lock( plugin_libraries_mutex_ );
    MasalaPluginModuleManager::get_instance()->reset();
    for(
        std::map< std::string, void * >::iterator it( plugin_libraries_name_to_handle_map_.begin() );
        it != plugin_libraries_name_to_handle_map_.end();
        ++it
    ) {
        dlclose( it->second );
    }
    plugin_libraries_name_to_handle_map_.clear();
}

/// @brief Get the number of registered plugin libraries.
masala::base::Size
MasalaPluginLibraryManager::total_plugin_libraries() const {
    std::lock_guard< std::mutex > lock( plugin_libraries_mutex_ );
    return plugin_libraries_name_to_handle_map_.size();
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala
