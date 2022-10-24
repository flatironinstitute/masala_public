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

/// @file src/base/managers/plugin_module/MasalaPluginModuleManager.hh
/// @brief Header for a static singleton for managing plugin modules
/// for Masala, such as manipulators, selectors, metrics, etc.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_plugin_module_MasalaPluginModuleManager_hh
#define Masala_src_base_managers_plugin_module_MasalaPluginModuleManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/plugin_module/MasalaPluginModuleManager.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/api/names_from_types.tmpl.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.fwd.hh>

// STL headers:
#include <map>
#include <mutex>
#include <vector>
#include <set>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {


/// @brief A static singleton for managing output to the plugin_module (screen and/or logfile(s)).
class MasalaPluginModuleManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaPluginModuleManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaPluginModuleManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaPluginModuleManager( MasalaPluginModuleManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaPluginModuleManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaPluginModuleManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaPluginModuleManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::plugin_module".
    std::string
    class_namespace() const override;

    /// @brief Query whether any plugin in a vector is already known to the manager.
    bool
    has_any_plugin(
        std::vector< MasalaPluginCreatorCSP > const & creators
    ) const;

    /// @brief Query whether any plugin in a set is already known to the manager.
    bool
    has_any_plugin(
        std::set< MasalaPluginCreatorCSP > const & creators
    ) const;

    /// @brief Query whether a plugin is already known to the manager.
    bool
    has_plugin(
        MasalaPluginCreatorCSP const & creator
    ) const;

    /// @brief Add a vector of plugins to the list of plugins that the manager knows about.
    /// @details Throws if any plugin has already been added.
    void
    add_plugins(
        std::vector< MasalaPluginCreatorCSP > const & creators
    );

    /// @brief Add a set of plugins to the list of plugins that the manager knows about.
    /// @details Throws if any plugin has already been added.
    void
    add_plugins(
        std::set< MasalaPluginCreatorCSP > const & creators
    );
    
    /// @brief Add a plugin to the list of plugins that the manager knows about.
    /// @details Throws if the plugin has already been added.  Call has_plugin()
    /// first to query wiether the plugin has already been added.
    void
    add_plugin(
        MasalaPluginCreatorCSP const & creator
    );

    /// @brief Remove a vector of plugins from the list of plugins that the manager knows about.
    /// @details Throws if the plugin is not registered
    void
    remove_plugins(
        std::vector< MasalaPluginCreatorCSP > const & creators
    );

    /// @brief Re,pve a set of plugins from the list of plugins that the manager knows about.
    /// @details Throws if the plugin is not registered
    void
    remove_plugins(
        std::set< MasalaPluginCreatorCSP > const & creators
    );
    
    /// @brief Remove a plugin from the list of plugins that the manager knows about.
    /// @details Throws if the plugin is not registered.  Call has_plugin()
    /// first to query wiether the plugin has already been added.
    void
    remove_plugin(
        MasalaPluginCreatorCSP const & creator
    );

    // /// @brief Get a list of all plugins.
    // std::vector< std::string > get_all_plugin_list() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Check whether a plugin is already known to the list of plugins stored in
    /// the manager.  Returns true if the plugin is known and false otherwise.
    /// @details Assumes that the plugin_map_mutex_ has been locked!
    bool
    has_plugin_mutex_locked(
        MasalaPluginCreatorCSP const & creator
    ) const;

    /// @brief Add a plugin to the list of plugins that the manager knows about.  Assumes
    /// that the plugin_map_mutex_ has already been locked!
    /// @details Throws if the plugin has already been added.  Call has_plugin()
    /// first to query wiether the plugin has already been added.
    void
    add_plugin_mutex_locked(
        MasalaPluginCreatorCSP const & creator
    );

    /// @brief Remove a plugin to the list of plugins that the manager knows about.  Assumes
    /// that the plugin_map_mutex_ has already been locked!
    /// @details Throws if the plugin has already been removed.
    void
    remove_plugin_mutex_locked(
        MasalaPluginCreatorCSP const & creator
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex for the list of plugins that this object knows about.
    mutable std::mutex plugin_map_mutex_;

    /// @brief List of plugins that this object knows about.
    /// @details Plugins are stored as a map of string to creator, where the string is
    /// the concatenation of the plugin types (separated by commas) and the plugin name
    /// (preceded by a colon).  For instance, "Selector,AtomSelector:ElementAtomSelector".
    std::map< std::string, MasalaPluginCreatorCSP > all_plugin_map_;

    /// @brief Find plugins by keyword.
    /// @details Keywords can be things that are outside of the hierarchy, like "proteins"
    /// or "RNA" or "design" or "structure prediction".
    /// @note Anything added to this map should be added to the all_plugin_map_.  Anything
    /// removed from the all_plugin_map_ should be removed from this map.
    std::map< std::string, std::set< MasalaPluginCreatorCSP > > plugins_by_keyword_;

    /// @brief Find plugins by category.
    /// @details Categories are vectors of strings.  For instance:
    /// {"Selector"}
    /// {"Selector","AtomSelector"}
    /// {"Selector","AtomSelector","AnnotatedRegionSelector"}
    /// A plugin in a nested category is also put into the higher categories.
    std::map< std::vector< std::string >, std::set< MasalaPluginCreatorCSP > > plugins_by_hierarchical_category_;

};

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_plugin_module_MasalaPluginModuleManager_hh