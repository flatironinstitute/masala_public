/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file src/base/managers/plugin_module/MasalaPluginModuleManager.cc
/// @brief A static singleton for managing plugin modules for Masala, such as manipulators,
/// selectors, metrics, etc.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaPluginModuleManagerHandle
MasalaPluginModuleManager::get_instance() {
    static MasalaPluginModuleManager plugin_manager;
    return &plugin_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaPluginModuleManager".
std::string
MasalaPluginModuleManager::class_name() const {
    return "MasalaPluginModuleManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::plugin_module".
std::string
MasalaPluginModuleManager::class_namespace() const {
    return "masala::base::managers::plugin_module";
}

/// @brief Query whether any plugin in a vector is already known to the manager.
bool
MasalaPluginModuleManager::has_any_plugin(
    std::vector< MasalaPluginCreator const & > const & creators
) const {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    for( auto const & creator : creators ) {
        if( has_plugin_mutex_locked( creator ) ) return true;
    }
    return false;
}

/// @brief Query whether any plugin in a set is already known to the manager.
bool
MasalaPluginModuleManager::has_any_plugin(
    std::set< MasalaPluginCreator const & > const & creators
) const {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    for( auto const & creator : creators ) {
        if( has_plugin_mutex_locked( creator ) ) return true;
    }
    return false;
}

/// @brief Query whether a plugin is already known to the manager.
bool
MasalaPluginModuleManager::has_plugin(
    MasalaPluginCreator const & creator
) const {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    return has_plugin_mutex_locked( creator );
}

/// @brief Add a vector of plugins to the list of plugins that the manager knows about.
/// @details Warns about any plugin that has already been added (and does not replace),
/// but does not throw.
void
MasalaPluginModuleManager::add_plugins(
    std::vector< MasalaPluginCreator const & > const & creators
) {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    for( auto const & creator : creators ) {
        add_plugin_mutex_locked( creator );
    }
}

/// @brief Add a set of plugins to the list of plugins that the manager knows about.
/// @details Warns about any plugin that has already been added (and does not replace),
/// but does not throw.
void
MasalaPluginModuleManager::add_plugins(
    std::set< MasalaPluginCreator const & > const & creators
) {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    for( auto const & creator : creators ) {
        add_plugin_mutex_locked( creator );
    }
}
    
/// @brief Add a plugin to the list of plugins that the manager knows about.
/// @details Throws if the plugin has already been added.  Call has_plugin()
/// first to query wiether the plugin has already been added.
void
MasalaPluginModuleManager::add_plugin(
    MasalaPluginCreator const & creator
) {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    add_plugin_mutex_locked( creator );
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Check whether a plugin is already known to the list of plugins stored in
/// the manager.  Returns true if the plugin is known and false otherwise.
/// @details Assumes that the plugin_map_mutex_ has been locked!
bool
MasalaPluginModuleManager::has_plugin_mutex_locked(
    MasalaPluginCreator const & creator
) const {
    return( all_plugin_map_.find( creator.get_plugin_object_manager_key() ) != all_plugin_map_.end() );
}

/// @brief Add a plugin to the list of plugins that the manager knows about.  Assumes
/// that the plugin_map_mutex_ has already been locked!
/// @details Throws if the plugin has already been added.  Call has_plugin()
/// first to query wiether the plugin has already been added.
void
MasalaPluginModuleManager::add_plugin_mutex_locked(
    MasalaPluginCreator const & creator
) {
    CHECK_OR_THROW_FOR_CLASS(
        !has_plugin_mutex_locked(creator), "add_plugin_mutex_locked",
        "Plugin \"" + creator.get_plugin_object_name() + "\" has already been added to the plugin manager."
    );
    all_plugin_map_[creator.get_plugin_object_manager_key()] = creator;
}

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala
