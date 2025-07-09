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

/// @file src/base/managers/configuration/MasalaConfigurationManager.cc
/// @brief A static singleton for managing global configuration for a Masala session.
/// @details The sorts of options that get set globally are defaults, which can be overridden
/// on a case-by-case basis.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/configuration/MasalaConfigurationManager.hh>

// Base headers:
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace configuration {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaConfigurationManagerHandle
MasalaConfigurationManager::get_instance() {
    static MasalaConfigurationManager config_manager;
    return &config_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaConfigurationManager".
std::string
MasalaConfigurationManager::class_name() const {
    return "MasalaConfigurationManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::configuration".
std::string
MasalaConfigurationManager::class_namespace() const {
    return "masala::base::managers::configuration";
}

/// @brief Retrieve configuration settings for a given class.
/// @details If the configuration settings are not already cached, we create them by calling
/// the passed creator_function. This triggers one-time read from disk.  Threadsafe.
/// @param[in] unique_key A unique key identifying the type of object for which we're getting
/// the configuration.  Best practice is to use the class_name_and_namespace() function's output.
/// @param[in] creator_function A function that takes an authorization key and returns a configuration
/// container (a derived class from ConfigurationBase).  This should be the load_configuration() function
/// for the class for which we're getting configuration.
ConfigurationBaseCSP
MasalaConfigurationManager::get_configuration_settings(
    std::string const & unique_key,
    std::function< ConfigurationBaseCSP ( MasalaConfigurationManagerAuthorization const & ) > const & creator_function
) {
    std::lock_guard< std::mutex > lock( configuration_settings_mutex_ );
    std::map< std::string, ConfigurationBaseCSP >::const_iterator it( configuration_settings_.find( unique_key ) );
    if( it != configuration_settings_.end() ) {
        return it->second;
    }
    // If we reach here, we have to create the object.
    MasalaConfigurationManagerAuthorization authorization_key;
    ConfigurationBaseCSP config( creator_function( authorization_key ) );
    configuration_settings_[unique_key] = config;
    return config;
}

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala
