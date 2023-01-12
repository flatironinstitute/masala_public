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

/// @file src/base/managers/plugin_module/MasalaPluginLibraryManager.hh
/// @brief Headers for a static singleton for managing plugin libaries
/// for Masala.
/// @details This manages the .dll (Windows), .so (Linux), or .dylib (MacOS)
/// dyanmic-link libraries that are loaded, which contain plugin modules.
/// The MasalaPluginModuleManager in turn manages the plugins contained by
/// these libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_plugin_module_MasalaPluginLibraryManager_hh
#define Masala_src_base_managers_plugin_module_MasalaPluginLibraryManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/plugin_module/MasalaPluginLibraryManager.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <map>
#include <mutex>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {


/// @brief A static singleton for managing plugin libaries for Masala.
/// @details This manages the .dll (Windows), .so (Linux), or .dylib (MacOS)
/// dyanmic-link libraries that are loaded, which contain plugin modules.
/// The MasalaPluginModuleManager in turn manages the plugins contained by
/// these libraries.
class MasalaPluginLibraryManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaPluginLibraryManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaPluginLibraryManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaPluginLibraryManager( MasalaPluginLibraryManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaPluginLibraryManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaPluginLibraryManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaPluginLibraryManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::plugin_module".
    std::string
    class_namespace() const override;

    /// @brief Completely reset the manager.
    /// @details Unregisters all plugin libraries.
    /// @note Calls reset() on the MasalaPluginModuleManager.
    void
    reset();

    /// @brief Get the number of registered plugin libraries.
    masala::base::Size
    total_plugin_libraries() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex for the list of plugin libraries that this object knows about.
    mutable std::mutex plugin_libraries_mutex_;

    /// @brief A map of plugin library filename to plugin library file handle.
    /// @note The dlopen() framework uses void pointers as file handles.
    std::map< std::string, void * > plugin_libraries_name_to_handle_map_;

};

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_plugin_module_MasalaPluginLibraryManager_hh