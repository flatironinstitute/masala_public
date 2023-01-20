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

/// @file src/base/managers/plugin_module/MasalaPluginModuleManager.cc
/// @brief A static singleton for managing plugin modules for Masala, such as manipulators,
/// selectors, metrics, etc.
/// @details This manages the plugin objects stored in a plugin library.  The plugin libraries
/// (dynamic-link .dll files in Windows, .so files in Linux, or .dylib files in MacOS) are in
/// turn managed by the MasalaPluginLibraryManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.hh>
#include <base/error/ErrorHandling.hh>
#include <base/utility/container/container_util.tmpl.hh>

// STL headers:
#include <string>
#include <sstream>

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

/// @brief Completely reset the manager.
/// @details Unregisters all plugins.
void
MasalaPluginModuleManager::reset() {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    plugins_by_hierarchical_category_.clear();
    plugins_by_keyword_.clear();
    all_plugin_map_.clear();
    write_to_tracer( "Reset the MasalaPluginModuleManager.  No plugins are registered." );
}

/// @brief Get the number of registered plugins.
base::Size
MasalaPluginModuleManager::total_plugins() const {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    return all_plugin_map_.size();
}

/// @brief Query whether any plugin in a vector is already known to the manager.
bool
MasalaPluginModuleManager::has_any_plugin(
    std::vector< MasalaPluginCreatorCSP > const & creators
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
    std::set< MasalaPluginCreatorCSP > const & creators
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
    MasalaPluginCreatorCSP const & creator
) const {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    return has_plugin_mutex_locked( creator );
}

/// @brief Add a vector of plugins to the list of plugins that the manager knows about.
/// @details Throws if any plugin has already been added.
void
MasalaPluginModuleManager::add_plugins(
    std::vector< MasalaPluginCreatorCSP > const & creators
) {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    for( auto const & creator : creators ) {
        add_plugin_mutex_locked( creator );
    }
}

/// @brief Add a set of plugins to the list of plugins that the manager knows about.
/// @details Throws if any plugin has already been added.
void
MasalaPluginModuleManager::add_plugins(
    std::set< MasalaPluginCreatorCSP > const & creators
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
    MasalaPluginCreatorCSP const & creator
) {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    add_plugin_mutex_locked( creator );
}

/// @brief Remove a vector of plugins from the list of plugins that the manager knows about.
/// @details Throws if the plugin is not registered
void
MasalaPluginModuleManager::remove_plugins(
    std::vector< MasalaPluginCreatorCSP > const & creators
) {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    for( auto const & creator : creators ) {
        remove_plugin_mutex_locked( creator );
    }
}

/// @brief Re,pve a set of plugins from the list of plugins that the manager knows about.
/// @details Throws if the plugin is not registered
void
MasalaPluginModuleManager::remove_plugins(
    std::set< MasalaPluginCreatorCSP > const & creators
) {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    for( auto const & creator : creators ) {
        remove_plugin_mutex_locked( creator );
    }
}
    
/// @brief Remove a plugin from the list of plugins that the manager knows about.
/// @details Throws if the plugin is not registered.  Call has_plugin()
/// first to query wiether the plugin has already been added.
void
MasalaPluginModuleManager::remove_plugin(
    MasalaPluginCreatorCSP const & creator
) {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    remove_plugin_mutex_locked( creator );
}

/// @brief Get a list of all plugins.
std::vector< std::string >
MasalaPluginModuleManager::get_all_plugin_list() const {
    std::vector< std::string > all_plugins;
    all_plugins.reserve( all_plugin_map_.size() );
    {
        std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
        for( auto const & entry : all_plugin_map_ ) {
            all_plugins.push_back( entry.first );
        }
    }
    return all_plugins;
}

/// @brief Get a list of all hierarchical categories.
std::vector< std::vector< std::string > >
MasalaPluginModuleManager::get_all_categories() const {
    std::vector< std::vector< std::string > > outvec;
    outvec.reserve( plugins_by_hierarchical_category_.size() );
    {
        std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
        for( auto const & entry : plugins_by_hierarchical_category_ ) {
            outvec.push_back( entry.first );
        }
    }
    return outvec;
}

/// @brief Get a list of all keywords.
std::vector< std::string >
MasalaPluginModuleManager::get_all_keywords() const {
    std::vector< std::string > outvec;
    outvec.reserve( plugins_by_keyword_.size() );
    {
        std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
        for( auto const & entry : plugins_by_keyword_ ) {
            outvec.push_back( entry.first );
        }
    }
    return outvec;
}

/// @brief Get a list of plugins by keyword.
/// @returns The name(s) of the plugin classes.  If include_namespace is
/// true (the default), then the full namespace and name is returned.
std::vector< std::string >
MasalaPluginModuleManager::get_list_of_plugins_by_keyword(
    std::string const & keyword,
    bool const include_namespace /*= true*/
) const {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    auto const & it( plugins_by_keyword_.find( keyword ) );
    CHECK_OR_THROW_FOR_CLASS( it != plugins_by_keyword_.end(), "get_list_of_plugins_by_keyword",
        "Keyword \"" + keyword + "\" not found!"
    );
    auto const & myset( it->second );
    std::vector< std::string > outvec;
    outvec.reserve( myset.size() );
    for( auto const & entry : myset ) {
        outvec.push_back( include_namespace ? entry->get_plugin_object_namespace_and_name() : entry->get_plugin_object_name() );
    }
    return outvec;
}

/// @brief Get a list of plugins that have multiple keywords.
/// @details The plugins that get returned must have ALL keywords.
/// @returns The name(s) of the plugin classes.  If include_namespace is
/// true (the default), then the full namespace and name is returned.
std::vector< std::string >
MasalaPluginModuleManager::get_list_of_plugins_by_keywords(
    std::vector< std::string > const & keywords,
    bool const include_namespace /*= true*/
) const {
    CHECK_OR_THROW_FOR_CLASS(
        !keywords.empty(), "get_list_of_plugins_by_keywords",
        "No keywords were provided to this function!"
    );
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    auto const & it( plugins_by_keyword_.find( keywords[0] ) );
    CHECK_OR_THROW_FOR_CLASS( it != plugins_by_keyword_.end(), "get_list_of_plugins_by_keywords",
        "Keyword \"" + keywords[0] + "\" not found!"
    );
    auto const & myset( it->second );
    std::vector< std::string > outvec;
    outvec.reserve( myset.size() );
    for( auto const & entry : myset ) {
        std::vector< std::string > const curkeywords( entry->get_plugin_object_keywords() );
        bool all_found(true);
        // Check whether the rest of the keywords are here.
        for( base::Size i(1); i<keywords.size(); ++i ) {
            if( !base::utility::container::has_value(curkeywords, keywords[i]) ) {
                all_found = false;
                break;
            }
        }
        if( !all_found ) {
            continue;
        }
        outvec.push_back( include_namespace ? entry->get_plugin_object_namespace_and_name() : entry->get_plugin_object_name() );
    }
    CHECK_OR_THROW_FOR_CLASS(
        !outvec.empty(), "get_list_of_plugins_by_keywords",
        "No plugins were found containing all specified keywords."
    );
    outvec.shrink_to_fit();
    return outvec;
}

/// @brief Get a list of plugins in a given category.
/// @param[in] cateogry The category to search
/// @param[in] include_subcategories If true, plugins in any subcategory are
/// also included.  If false, only plugins in this category are included.
/// @note The category is a vector of hierarchical strings.  For instance,
/// selector->atomselector is represented as
/// std::vector< std::string >{ "Selector", "AtomSelector"}.
std::vector< std::string >
MasalaPluginModuleManager::get_list_of_plugins_by_category(
    std::vector< std::string > const & category,
    bool const include_subcategories,
    bool const include_namespace /*= true*/
) const {
    CHECK_OR_THROW_FOR_CLASS(
        !category.empty(), "get_list_of_plugins_by_category",
        "No category was provided to this function!"
    );
    std::map< std::vector< std::string >, std::set< MasalaPluginCreatorCSP > >::const_iterator it;
    std::vector< std::string > outvec;
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    if( include_subcategories ) {
        it = plugins_by_hierarchical_subcategory_.find( category );
        if( it == plugins_by_hierarchical_subcategory_.end() ) {
            return outvec;
        }
    } else {
        it = plugins_by_hierarchical_category_.find( category );
        if( it == plugins_by_hierarchical_category_.end() ) {
            return outvec;
        }
    }

    std::set< MasalaPluginCreatorCSP > const & plugins( it->second );
    outvec.reserve( plugins.size() );
    for( auto const & plugin : plugins ) {
        outvec.push_back( include_namespace ? plugin->get_plugin_object_namespace_and_name() : plugin->get_plugin_object_name() );
    }
    return outvec;
}

/// @brief Create a plugin object instance by category and plugin name.
/// @details Actually creates an API container for a plugin object.
/// @note Since names must be unique, the plugin_name should include namespace.
MasalaPluginAPISP
MasalaPluginModuleManager::create_plugin_object_instance(
    std::vector< std::string > const & category,
    std::string const & plugin_name
) const {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    std::map< std::vector< std::string >, std::set< MasalaPluginCreatorCSP > >::const_iterator it(
        plugins_by_hierarchical_category_.find( category )
    );
    CHECK_OR_THROW_FOR_CLASS( it != plugins_by_hierarchical_category_.end(), "create_plugin_object_instance",
        "Could not find plugin category [ " + base::utility::container::container_to_string( category, ", " ) +
        " ] when attempting to create a plugin instance of type \"" + plugin_name + "\"."
    );
    std::set< MasalaPluginCreatorCSP > const & myset( it->second );
    for( auto const & entry : myset ) {
        if( entry->get_plugin_object_namespace_and_name() == plugin_name ) {
            write_to_tracer( "Creating an instance of \"" + entry->get_plugin_object_namespace_and_name() + "\"." );
            return entry->create_plugin_object();
        }
    }
    MASALA_THROW( class_namespace_and_name(), "create_plugin_object_instance", "Could not find a plugin "
        "with name \"" + plugin_name + "\" in category [ " + base::utility::container::container_to_string( category, ", " )
        + " ]."
    );
    return nullptr;
}

/// @brief Create a plugin object instance by keyword and plugin name.
/// @details Actually creates an API container for a plugin object.
/// @note Since names must be unique, the plugin_name should include namespace.
MasalaPluginAPISP
MasalaPluginModuleManager::create_plugin_object_instance(
    std::string const & keyword,
    std::string const & plugin_name
) const {
    std::lock_guard< std::mutex > lock( plugin_map_mutex_ );
    std::map< std::string, std::set< MasalaPluginCreatorCSP > >::const_iterator it(
        plugins_by_keyword_.find( keyword )
    );
    CHECK_OR_THROW_FOR_CLASS( it != plugins_by_keyword_.end(), "create_plugin_object_instance",
        "Could not find plugin keyword \"" + keyword +
        "\" when attempting to create a plugin instance of type \"" + plugin_name + "\"."
    );
    std::set< MasalaPluginCreatorCSP > const & myset( it->second );
    for( auto const & entry : myset ) {
        if( entry->get_plugin_object_namespace_and_name() == plugin_name ) {
            write_to_tracer( "Creating an instance of \"" + entry->get_plugin_object_namespace_and_name() + "\"." );
            return entry->create_plugin_object();
        }
    }
    MASALA_THROW( class_namespace_and_name(), "create_plugin_object_instance", "Could not find a plugin "
        "with name \"" + plugin_name + "\" and keyword \"" + keyword + "\"."
    );
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Check whether a plugin is already known to the list of plugins stored in
/// the manager.  Returns true if the plugin is known and false otherwise.
/// @details Assumes that the plugin_map_mutex_ has been locked!
bool
MasalaPluginModuleManager::has_plugin_mutex_locked(
    MasalaPluginCreatorCSP const & creator
) const {
    return( all_plugin_map_.find( creator->get_plugin_object_manager_key() ) != all_plugin_map_.end() );
}

/// @brief Add a plugin to the list of plugins that the manager knows about.  Assumes
/// that the plugin_map_mutex_ has already been locked!
/// @details Throws if the plugin has already been added.  Call has_plugin()
/// first to query wiether the plugin has already been added.
void
MasalaPluginModuleManager::add_plugin_mutex_locked(
    MasalaPluginCreatorCSP const & creator
) {
    std::string const plugin_object_name( creator->get_plugin_object_namespace_and_name() );

    CHECK_OR_THROW_FOR_CLASS(
        !has_plugin_mutex_locked(creator), "add_plugin_mutex_locked",
        "Plugin \"" + plugin_object_name + "\" has already been added to the plugin manager."
    );
    all_plugin_map_[creator->get_plugin_object_manager_key()] = creator;

    // Add keywords:
    std::vector< std::string > keywords( creator->get_plugin_object_keywords() );
    if( !keywords.empty() ) {
        for( std::string const & keyword : keywords ) {
            std::map< std::string, std::set< MasalaPluginCreatorCSP > >::iterator it( plugins_by_keyword_.find(keyword) );
            if( it == plugins_by_keyword_.end() ) {
                plugins_by_keyword_[keyword] = std::set< MasalaPluginCreatorCSP >{ creator };
            } else {
                it->second.insert( creator );
            }
        }
    }

    // Add categories:
    std::vector< std::vector< std::string > > set_of_categories( creator->get_plugin_object_categories() );
    if( !set_of_categories.empty() ) {
        for( auto const & categories : set_of_categories ) {
            CHECK_OR_THROW_FOR_CLASS( !categories.empty(), "add_plugin_mutex_locked",
                "The hierarchy wasn't defined for one of the categories for a plugin!"
            );
            
            std::vector< std::string > ss;
            
            for( std::string const & category : categories ) {
                ss.push_back( category );
                
                // Update the map that DOES put plugins in parent categories.
                std::map< std::vector< std::string >, std::set< MasalaPluginCreatorCSP > >::iterator it(
                    plugins_by_hierarchical_category_.find( ss )
                );
                if( it == plugins_by_hierarchical_category_.end() ) {
                    plugins_by_hierarchical_category_[ ss ] = std::set< MasalaPluginCreatorCSP >{ creator };
                } else {
                    it->second.insert( creator );
                }
            }

            // Update the map that does NOT put plugins in parent categories.
            std::map< std::vector< std::string >, std::set< MasalaPluginCreatorCSP > >::iterator it2(
                plugins_by_hierarchical_subcategory_.find( ss )
            );
            if( it2 == plugins_by_hierarchical_subcategory_.end() ) {
                plugins_by_hierarchical_subcategory_[ ss ] = std::set< MasalaPluginCreatorCSP >{ creator };
            } else {
                it2->second.insert( creator );
            }
        }
    }

    write_to_tracer( "Added plugin \"" + plugin_object_name + "\"." );
} // MasalaPluginModuleManager::add_plugin_mutex_locked()

/// @brief Remove a plugin to the list of plugins that the manager knows about.  Assumes
/// that the plugin_map_mutex_ has already been locked!
/// @details Throws if the plugin has already been removed.
void
MasalaPluginModuleManager::remove_plugin_mutex_locked(
    MasalaPluginCreatorCSP const & creator
) {
    std::string const plugin_object_name( creator->get_plugin_object_namespace_and_name() );

    CHECK_OR_THROW_FOR_CLASS(
        has_plugin_mutex_locked(creator), "remove_plugin_mutex_locked",
        "Plugin \"" + plugin_object_name + "\" is not present in the plugin manager."
    );

    std::map< std::string, MasalaPluginCreatorCSP >::iterator it(
        all_plugin_map_.find( creator->get_plugin_object_manager_key() )
    );
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( it != all_plugin_map_.end(), "remove_plugin_mutex_locked",
        "Program error!  Unable to find plugin to remove."
    );
    all_plugin_map_.erase(it);

    // Remove from keywords:
    std::vector< std::string > const keywords( creator->get_plugin_object_keywords() );
    if( !keywords.empty() ) {
        for( std::string const & keyword : keywords ) {
            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( plugins_by_keyword_.count(keyword) > 0, "remove_plugin_mutex_locked",
                "Program error!  Unable to find keyword \"" + keyword + "\"!"
            );
            std::set< MasalaPluginCreatorCSP > & myset( plugins_by_keyword_[keyword] );
            bool found(false);
            for( std::set< MasalaPluginCreatorCSP >::iterator it( myset.begin() ); it != myset.end(); ++it ) {
                if( (**it) == (*creator) ) {
                    found = true;
                    myset.erase( it );
                    break;
                }
            }
            CHECK_OR_THROW_FOR_CLASS( found, "remove_plugin_mutex_locked",
                "Program error!  Could not find plugin \"" + plugin_object_name + "\" in keyword "
                "category \"" + keyword + "\"."
            );
            if( myset.empty() ) {
                plugins_by_keyword_.erase( keyword );
            }
        }
    }

    // Remove from hierarchical categories:
    std::vector< std::vector< std::string > > const set_of_categories( creator->get_plugin_object_categories() );
    for( auto const & categories : set_of_categories ) {
        std::vector< std::string > ss;
        for( std::string const & category : categories ) {
            ss.push_back( category );

            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( plugins_by_hierarchical_category_.count( ss ) > 0,
                "remove_plugin_mutex_locked", "Program error! Could not find category [ " +
                base::utility::container::container_to_string( ss, ", " ) + " ] in hierarchical "
                "category map."
            );
            std::set< MasalaPluginCreatorCSP > & myset( plugins_by_hierarchical_category_[ ss ] );
            bool found( false );
            for( std::set< MasalaPluginCreatorCSP >::iterator it( myset.begin() ); it != myset.end(); ++it ) {
                if( (**it) == (*creator) ) {
                    found = true;
                    myset.erase( it );
                    break;
                }
            }
            CHECK_OR_THROW_FOR_CLASS( found, "remove_plugin_mutex_locked",
                "Program error!  Could not find plugin \"" + plugin_object_name + "\" in hierarchical "
                "category [ " + base::utility::container::container_to_string( ss, ", " ) + " ]."
            );
            if( myset.empty() ) {
                plugins_by_hierarchical_category_.erase( ss );
            }
        }
    }
    write_to_tracer( "Removed plugin \"" + plugin_object_name + "\"." );
} // MasalaPluginModuleManager::remove_plugin_mutex_locked()

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala
