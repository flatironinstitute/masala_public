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

/// @file src/base/managers/configuration/MasalaConfigurationManagerAuthorization.hh
/// @brief A "key" class with a private constructor, which can only be instantiated by
/// the MasalaConfigurationManager, used to ensure that only the configuration manager
/// can instantiate configuration objects.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_configuration_MasalaConfigurationManagerAuthorization_hh
#define Masala_src_base_managers_configuration_MasalaConfigurationManagerAuthorization_hh

// Parent header
#include <base/MasalaObject.hh>

// Base headers
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.fwd.hh>
#include <base/managers/configuration/MasalaConfigurationManager.fwd.hh>

namespace masala {
namespace base{
namespace managers{
namespace configuration{

/// @brief A "key" class with a private constructor, which can only be instantiated by
/// the MasalaConfigurationManager, used to ensure that only the configuration manager
/// can instantiate configuration objects.
class MasalaConfigurationManagerAuthorization : public masala::base::MasalaObject {

    friend class MasalaConfigurationManager;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR -- ONLY ACCESSIBLE TO MasalaConfigurationManager
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaConfigurationManagerAuthorization() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Copy constructor.
    MasalaConfigurationManagerAuthorization( MasalaConfigurationManagerAuthorization const & src ) = delete;

    /// @brief Default destructor.
    ~MasalaConfigurationManagerAuthorization() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the class name ("MasalaConfigurationManagerAuthorization").
    std::string class_name() const override;

    /// @brief Get the class namespace ("masala::base::managers::configuration").
    std::string class_namespace() const override;

};

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_configuration_MasalaConfigurationManagerAuthorization_hh
