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

namespace base {
namespace managers {
namespace configuration {


/// @brief A static singleton for managing global configuration for a Masala session.
/// @details The sorts of options that get set globally are defaults, which can be overridden
/// on a case-by-case basis.
class MasalaConfigurationManager : public base::MasalaObject {

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
    /// @details Returns "base::managers::configuration".
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

#endif // Masala_src_base_managers_configuration_MasalaConfigurationManager_hh