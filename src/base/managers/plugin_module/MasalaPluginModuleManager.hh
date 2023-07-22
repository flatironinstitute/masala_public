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

/// @file src/base/managers/plugin_module/MasalaPluginModuleManager.hh
/// @brief Header for a static singleton for managing plugin modules
/// for Masala, such as manipulators, selectors, metrics, etc.
/// @details This manages the plugin objects stored in a plugin library.  The plugin libraries
/// (dynamic-link .dll files in Windows, .so files in Linux, or .dylib files in MacOS) are in
/// turn managed by the MasalaPluginLibraryManager.
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
#include <base/managers/plugin_module/MasalaPluginAPI.fwd.hh>
#include <base/managers/plugin_module/MasalaPlugin.fwd.hh>

// STL headers:
#include <map>
#include <mutex>
#include <vector>
#include <set>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {


/// @brief A static singleton for managing plugin modules for Masala, such as manipulators,
/// selectors, metrics, etc.
/// @details This manages the plugin objects stored in a plugin library.  The plugin libraries
/// (dynamic-link .dll files in Windows, .so files in Linux, or .dylib files in MacOS) are in
/// turn managed by the MasalaPluginLibraryManager.
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

    /// @brief Completely reset the manager.
    /// @details Unregisters all plugins.
    void reset();

    /// @brief Get the number of registered plugins.
    base::Size total_plugins() const;

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
    /// @details Throws if any plugin has already been added.  If a plugin
    /// is a MasalaEngine, this also registers it with the MasalaEngineManager.
    void
    add_plugins(
        std::vector< MasalaPluginCreatorCSP > const & creators
    );

    /// @brief Add a set of plugins to the list of plugins that the manager knows about.
    /// @details Throws if any plugin has already been added.  If a plugin
    /// is a MasalaEngine, this also registers it with the MasalaEngineManager.
    void
    add_plugins(
        std::set< MasalaPluginCreatorCSP > const & creators
    );
    
    /// @brief Add a plugin to the list of plugins that the manager knows about.
    /// @details Throws if the plugin has already been added.  Call has_plugin()
    /// first to query wiether the plugin has already been added.  If the plugin
    /// is a MasalaEngine, this also registers it with the MasalaEngineManager.
    void
    add_plugin(
        MasalaPluginCreatorCSP const & creator
    );

    /// @brief Remove a vector of plugins from the list of plugins that the manager knows about.
    /// @details Throws if the plugin is not registered.  Also removes engines from the
    /// MasalaEngineManager.
    void
    remove_plugins(
        std::vector< MasalaPluginCreatorCSP > const & creators
    );

    /// @brief Re,pve a set of plugins from the list of plugins that the manager knows about.
    /// @details Throws if the plugin is not registered.  Also removes engines from the
    /// MasalaEngineManager.
    void
    remove_plugins(
        std::set< MasalaPluginCreatorCSP > const & creators
    );
    
    /// @brief Remove a plugin from the list of plugins that the manager knows about.
    /// @details Throws if the plugin is not registered.  Call has_plugin()
    /// first to query wiether the plugin has already been added.   Also removes
    /// engines from the MasalaEngineManager.
    void
    remove_plugin(
        MasalaPluginCreatorCSP const & creator
    );

    /// @brief Get a list of all plugins.
    std::vector< std::string > get_all_plugin_list() const;

    /// @brief Get a list of all hierarchical categories.
    std::vector< std::vector< std::string > > get_all_categories() const;

    /// @brief Get a list of all keywords.
    std::vector< std::string > get_all_keywords() const;

    /// @brief Get a list of plugins by keyword.
    /// @returns The name(s) of the plugin classes.  If include_namespace is
    /// true (the default), then the full namespace and name is returned.
    std::vector< std::string >
    get_list_of_plugins_by_keyword(
        std::string const & keyword,
        bool const include_namespace = true
    ) const;

    /// @brief Get a list of plugins that have multiple keywords.
    /// @details The plugins that get returned must have ALL keywords.
    /// @returns The name(s) of the plugin classes.  If include_namespace is
    /// true (the default), then the full namespace and name is returned.
    std::vector< std::string >
    get_list_of_plugins_by_keywords(
        std::vector< std::string > const & keywords,
        bool const include_namespace = true
    ) const;

    /// @brief Get a list of plugins in a given category.
    /// @param[in] category The category to search
    /// @param[in] include_subcategories If true, plugins in any subcategory are
    /// also included.  If false, only plugins in this category are included.
    /// @param[in] include_namespace If include_namespace is true (the default), then
    /// the full namespace and name is returned.
    /// @note The category is a vector of hierarchical strings.  For instance,
    /// selector->atomselector is represented as
    /// std::vector< std::string >{ "Selector", "AtomSelector"}.
    std::vector< std::string >
    get_list_of_plugins_by_category(
        std::vector< std::string > const & category,
        bool const include_subcategories,
        bool const include_namespace = true
    ) const;

    /// @brief Get a list of plugins by category.  Only names will be returned, unless
    /// there is a name conflict, in which case namespaces will be included.
    /// @param[in] category The category to search
    /// @param[in] include_subcategories If true, plugins in any subcategory are
    /// also included.  If false, only plugins in this category are included.
    std::vector< std::string >
    get_short_names_of_plugins_by_category(
        std::vector< std::string > const & category,
        bool const include_subcategories
    ) const;

    /// @brief Get a list of plugins by category as a comma-separated list.  Only names
    /// will be returned, unless there is a name conflict, in which case namespaces will
    /// be included.
    /// @param[in] category The category to search
    /// @param[in] include_subcategories If true, plugins in any subcategory are
    /// also included.  If false, only plugins in this category are included.
    /// @note Returns "(None)" if no plugins are found in the category.
    std::string
    get_short_names_of_plugins_by_category_cs_list(
        std::vector< std::string > const & category,
        bool const include_subcategories
    ) const;

    /// @brief Create a plugin object instance by category and plugin name.
    /// @details Actually creates an API container for a plugin object.  If include_subcategories
    /// is true, then we load plugins with the given name that are in any sub-category; if false, we
    /// strictly restrict our search to the given category.
    /// @note Since names must be unique, the plugin_name should include namespace.
    MasalaPluginAPISP
    create_plugin_object_instance(
        std::vector< std::string > const & category,
        std::string const & plugin_name,
        bool const include_subcategories
    ) const;

    /// @brief Create a plugin object instance by category and plugin name.  This version uses
    /// just the name of the plugin UNLESS there is a name conflict, in which case the namespace
    /// plus name is expected.
    /// @details Actually creates an API container for a plugin object.  If include_subcategories
    /// is true, then we load plugins with the given name that are in any sub-category; if false, we
    /// strictly restrict our search to the given category.
    /// @note If there is more than one plugin in a category with the same name and namespace has not
    /// been provided, this throws.
    MasalaPluginAPISP
    create_plugin_object_instance_by_short_name(
        std::vector< std::string > const & category,
        std::string const & plugin_name,
        bool const include_subcategories
    ) const;

    /// @brief Create a plugin object instance by keyword and plugin name.
    /// @details Actually creates an API container for a plugin object.
    /// @note Since names must be unique, the plugin_name should include namespace.
    MasalaPluginAPISP
    create_plugin_object_instance(
        std::string const & keyword,
        std::string const & plugin_name
    ) const;

    /// @brief Given a plugin object, encapsulate it in an API container of the corresponding type.
    /// @details Intended only to be called from auto-generated API code.
    MasalaPluginAPISP
    encapsulate_plugin_object_instance(
        MasalaPluginSP const & object
    ) const;

    /// @brief Given a plugin object, encapsulate it in an API container of the corresponding type.
    /// @details Intended only to be called from auto-generated API code.
    MasalaPluginAPICSP
    encapsulate_const_plugin_object_instance(
        MasalaPluginCSP const & object
    ) const;

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

    /// @brief Check whether a plugin with a given namespace and name is in a set.  Assumes
    /// that the plugin_map_mutex_ is already locked if the set is owned by the plugin module manager.
    bool
    plugin_name_in_set_mutex_locked(
        std::string const & plugin_namespace_and_name,
        std::set< MasalaPluginCreatorCSP > const & creator_set
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex for the list of plugins that this object knows about.
    mutable std::mutex plugin_map_mutex_;

    /// @brief List of plugins that this object knows about.
    /// @details Plugins are stored as a map of string to creator, where the string is
    /// the concatenation of the plugin types (separated by commas) and the plugin namespace and name
    /// (preceded by a colon).  For instance,
    /// "Selector,AtomSelector:standard_masala_plugins::selectors::atom_selectors::ElementAtomSelector".
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

    /// @brief Find plugins by subcategory.
    /// @details Categories are vectors of strings.  For instance:
    /// {"Selector"}
    /// {"Selector","AtomSelector"}
    /// {"Selector","AtomSelector","AnnotatedRegionSelector"}
    /// A plugin in a nested category is also NOT put into the higher categories in this list.
    std::map< std::vector< std::string >, std::set< MasalaPluginCreatorCSP > > plugins_by_hierarchical_subcategory_;

};

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_plugin_module_MasalaPluginModuleManager_hh