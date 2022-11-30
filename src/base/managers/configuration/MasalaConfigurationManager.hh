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

/// @file src/base/managers/configuration/MasalaConfigurationManager.hh
/// @brief A static singleton for managing global configuration for a Masala session.
/// @details The sorts of options that get set globally are defaults, which can be overridden
/// on a case-by-case basis.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_configuration_MasalaConfigurationManager_hh
#define Masala_src_base_managers_configuration_MasalaConfigurationManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/configuration/MasalaConfigurationManager.fwd.hh>

// Base headers:
#include <base/managers/configuration/ConfigurationBase.fwd.hh>
#include <base/api/names_from_types.tmpl.hh>

// STL headers:
#include <map>
#include <mutex>
#include <string>
#include <functional>

namespace masala {
namespace base {
namespace managers {
namespace configuration {


/// @brief A static singleton for managing global configuration for a Masala session.
/// @details The sorts of options that get set globally are defaults, which can be overridden
/// on a case-by-case basis.
class MasalaConfigurationManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaConfigurationManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaConfigurationManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaConfigurationManager( MasalaConfigurationManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaConfigurationManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaConfigurationManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaConfigurationManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::configuration".
    std::string
    class_namespace() const override;

    /// @brief Retrieve configuration settings for a given class.
    /// @details If the configuration settings are not already cached, we create them by calling
    /// the passed creator_function. This triggers one-time read from disk.  Threadsafe.
    /// @param[in] unique_key A unique key identifying the type of object for which we're getting
    /// the configuration.  Best practice is to use the class_name_and_namespace() function's output.
    /// @param[in] creator_function A function that takes no parameters and returns a configuration
    /// container (a derived class from ConfigurationBase).
    ConfigurationBaseCSP
    get_configuration_settings(
        std::string const & unique_key,
        std::function< ConfigurationBaseCSP ( MasalaConfigurationManagerAuthorization const & ) > const & creator_function
    );

private:

    /// @brief A mutex for the map.
    std::mutex configuration_settings_mutex_;

    /// @brief A map of all of the configuration settings, indexed by class namespace and name.
    std::map< std::string, ConfigurationBaseCSP > configuration_settings_;

};

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala {

/// @brief A macro for obtaining a configuration object for a particular class.
/// @note The class must override load_configuration().  This must be called from a member function
/// like the class constructor.
#define OBTAIN_CONFIGURATION_FROM_CONFIGURATION_MANAGER( CLASSNAME, CONFIG_CONTAINER_CLASSNAME ) \
    std::dynamic_pointer_cast< CONFIG_CONTAINER_CLASSNAME const >( \
            masala::base::managers::configuration::MasalaConfigurationManager::get_instance()->get_configuration_settings( \
                CLASSNAME::class_namespace() + "::" + CLASSNAME::class_name(), \
                std::bind( &CLASSNAME::load_configuration, this, std::placeholders::_1 ) \
            ) \
        )

#endif // Masala_src_base_managers_configuration_MasalaConfigurationManager_hh