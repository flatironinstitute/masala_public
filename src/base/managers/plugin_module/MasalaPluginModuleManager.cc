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
    for( auto const & entry : all_plugin_map_ ) {
        all_plugins.push_back( entry.first );
    }
    return all_plugins;
}

/// @brief Get a list of all hierarchical categories.
std::vector< std::vector< std::string > >
MasalaPluginModuleManager::get_all_categories() const {
    std::vector< std::vector< std::string > > outvec;
    outvec.reserve( plugins_by_hierarchical_category_.size() );
    for( auto const & entry : plugins_by_hierarchical_category_ ) {
        outvec.push_back( entry.first );
    }
    return outvec;
}

/// @brief Get a list of all keywords.
std::vector< std::string >
MasalaPluginModuleManager::get_all_keywords() const {
    std::vector< std::string > outvec;
    outvec.reserve( plugins_by_keyword_.size() );
    for( auto const & entry : plugins_by_keyword_ ) {
        outvec.push_back( entry.first );
    }
    return outvec;
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
    std::string const plugin_object_name( creator->get_plugin_object_name() );

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
                
                std::map< std::vector< std::string >, std::set< MasalaPluginCreatorCSP > >::iterator it(
                    plugins_by_hierarchical_category_.find( ss )
                );
                if( it == plugins_by_hierarchical_category_.end() ) {
                    plugins_by_hierarchical_category_[ ss ] = std::set< MasalaPluginCreatorCSP >{ creator };
                } else {
                    it->second.insert( creator );
                }
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
    std::string const plugin_object_name( creator->get_plugin_object_name() );

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

} // MasalaPluginModuleManager::remove_plugin_mutex_locked()

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala
